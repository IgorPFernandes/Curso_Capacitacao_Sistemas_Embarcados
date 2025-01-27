#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/i2c.h"
#include "inc/ssd1306.h"
#include "Servo/Servo.h"

#define JOYSTICK_PIN_X 26
#define JOYSTICK_PIN_Y 27
#define BUTTON_PIN 6 // Pino do Botão B
#define BUTTON_A_PIN 5 // Pino do Botão A (para controle do Servo 4)

#define SERVO_PIN_1 9  // Garra
#define SERVO_PIN_2 8  // Esquerdo
#define SERVO_PIN_3 3  // Base
#define SERVO_PIN_4 4  // Direito

#define I2C_PORT i2c1
const uint I2C_SDA = 14;
const uint I2C_SCL = 15;

#define DEADZONE_MIN 1980
#define DEADZONE_MAX 2116

ssd1306_t oled_display;
int buttonState = 0;
bool controlFirstPair = true;

Servo* servo1;
Servo* servo2;
Servo* servo3;
Servo* servo4;

// Armazena os ângulos atuais dos servos
float currentAngle1 = 0;
float currentAngle2 = 30;
float currentAngle3 = 0; // Inicializa o ângulo da base em 0
float currentAngle4 = 80;
bool increasingAngle4 = true; // Indica a direção do movimento do Servo 4

// Armazena a posição inicial do joystick
uint16_t initialJoystickX = 2048;
uint16_t initialJoystickY = 2048;

// Armazena as últimas posições do joystick
uint16_t lastJoystickX = 2048; // Posição neutra do ADC (no meio)
uint16_t lastJoystickY = 2048; // Posição neutra do ADC (no meio)

// Armazena o estado do botão A
int buttonAState = 0;
int lastButtonAState = 0;

void updateDisplay() {
    char mensagem[64];
    if (controlFirstPair) {
        snprintf(mensagem, sizeof(mensagem), "Joystick\ncontrolando:\nMotor 1\ne Motor 2");
    } else {
        snprintf(mensagem, sizeof(mensagem), "Joystick\ncontrolando:\nMotor 3\ne Motor 4");
    }

    struct render_area frame_area = {
        .start_column = 0,
        .end_column = ssd1306_width - 1,
        .start_page = 0,
        .end_page = ssd1306_n_pages - 1
    };

    uint8_t ssd[ssd1306_buffer_length];
    memset(ssd, 0, ssd1306_buffer_length);
    calculate_render_area_buffer_length(&frame_area);
    render_on_display(ssd, &frame_area);

    int y = 0;
    const int line_height = 8;
    char *line = strtok(mensagem, "\n");
    while (line != NULL) {
        ssd1306_draw_string(ssd, 5, y, line);
        y += line_height;
        line = strtok(NULL, "\n");
    }

    render_on_display(ssd, &frame_area);
    printf("Display updated with message: %s\n", mensagem);
}

void setup() {
    stdio_init_all();
    printf("Starting setup...\n");
    adc_init();
    adc_gpio_init(JOYSTICK_PIN_X);
    adc_gpio_init(JOYSTICK_PIN_Y);

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    gpio_init(BUTTON_A_PIN);
    gpio_set_dir(BUTTON_A_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_A_PIN);

    // Inicialização do i2c
    i2c_init(I2C_PORT, 100 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    // Inicializa o display OLED
    ssd1306_init(&oled_display);
    updateDisplay();

    // Inicializa os servos
    servo1 = servo_create(SERVO_PIN_1);
    servo2 = servo_create(SERVO_PIN_2);
    servo3 = servo_create(SERVO_PIN_3);
    servo4 = servo_create(SERVO_PIN_4);

    printf("Setup completo\n");
}

void loop() {
    adc_select_input(0);
    uint16_t joystickY = adc_read();
    adc_select_input(1);
    uint16_t joystickX = adc_read();

    buttonState = !gpio_get(BUTTON_PIN);
    buttonAState = !gpio_get(BUTTON_A_PIN);

    if (buttonState == 1) {
        controlFirstPair = !controlFirstPair;
        updateDisplay();
        sleep_ms(500); // Debounce do botão
        printf("Button pressed, controlFirstPair toggled to %d\n", controlFirstPair);
    }

    // Verifica se o joystick está na zona morta
    bool inDeadZoneX = (joystickX >= DEADZONE_MIN && joystickX <= DEADZONE_MAX);
    bool inDeadZoneY = (joystickY >= DEADZONE_MIN && joystickY <= DEADZONE_MAX);

    // Mapeia os valores do joystick para os intervalos específicos de cada motor
    float angleX1 = 0 + ((float)joystickX / 4095) * 105; // Garra: 0° a 105°
    float angleY1 = 30 + ((float)joystickY / 4095) * 140;  // Esquerdo: 30° a 170°
    float angleX2 = 80 + ((float)joystickX / 4095) * 90;  // Direito: 80° a 170°
    float angleY2 = 0 + ((float)joystickY / 4095) * 180;  // Base: 0° a 180°

    // Só atualiza o ângulo dos servos se o joystick se mover ativamente (para frente ou para trás)
    if (controlFirstPair) {
        if (!inDeadZoneX && ((joystickX > initialJoystickX && angleX1 > currentAngle1) || (joystickX < initialJoystickX && angleX1 < currentAngle1))) {
            servo_go_degree(servo1, angleX1);
            currentAngle1 = angleX1;
        }
        if (!inDeadZoneY && ((joystickY > initialJoystickY && angleY1 > currentAngle2) || (joystickY < initialJoystickY && angleY1 < currentAngle2))) {
            servo_go_degree(servo2, angleY1);
            currentAngle2 = angleY1;
        }
    } else {
        if (!inDeadZoneX && ((joystickX > initialJoystickX && angleX2 > currentAngle3) || (joystickX < initialJoystickX && angleX2 < currentAngle3))) {
            servo_go_degree(servo4, angleX2);
            currentAngle4 = angleX2;
        }
        if (!inDeadZoneY && ((joystickY > initialJoystickY && angleY2 > currentAngle3) || (joystickY < initialJoystickY && angleY2 < currentAngle3))) {
            servo_go_degree(servo3, angleY2);
            currentAngle3 = angleY2;
        }
    }

    lastButtonAState = buttonAState;

    // Atualiza as últimas posições do joystick
    lastJoystickX = joystickX;
    lastJoystickY = joystickY;

    printf("Joystick X: %d, Y: %d\n", joystickX, joystickY);
    printf("Servo1 Angle: %.2f, Servo2 Angle: %.2f\n", currentAngle1, currentAngle2);
    printf("Servo3 Angle: %.2f, Servo4 Angle: %.2f\n", currentAngle3, currentAngle4);

    sleep_ms(50); // Pequeno atraso para estabilizar as leituras
}

int main() {
    setup();
    while (true) {
        loop();
    }

    // Destrói os servos (não será alcançado, mas bom para ilustrar a limpeza de memória)
    servo_destroy(servo1);
    servo_destroy(servo2);
    servo_destroy(servo3);
    servo_destroy(servo4);
}
