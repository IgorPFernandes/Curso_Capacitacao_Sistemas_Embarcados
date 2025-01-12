#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "ws2812.pio.h"  // Certifique-se de ter o PIO compilado para WS2812

#define NUM_LEDS 25
#define DATA_PIN 7
#define COLOR_RED 0x140000  // Vermelho: 20, 0, 0 no formato RGB compacto
#define COLOR_OFF 0x000000  // Desligado

// Define o padrao para formar o coracao
const int coracao[5][5] = {
    {0, 0, 1, 0, 0},
    {0, 1, 1, 1, 0},
    {1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1},
    {0, 1, 0, 1, 0}
};

uint32_t pixels[NUM_LEDS];  // Buffer para os LEDs

void acender_coracao() {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            int index = i * 5 + j;
            if (coracao[i][j] == 1) {
                pixels[index] = COLOR_RED;  // Define a cor vermelha para LEDs ligados
            } else {
                pixels[index] = COLOR_OFF;  // Define como desligado
            }
        }
    }
    ws2812_send_pixels(pixels, NUM_LEDS);  // Envia os dados para os LEDs
}

int main() {
    stdio_init_all();

    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);
    ws2812_program_init(pio, sm, offset, DATA_PIN, 800000, false);

    acender_coracao();
    sleep_ms(5000);  // Mantém o coração por 5 segundos

    for (int i = 0; i < NUM_LEDS; i++) {
        pixels[i] = COLOR_OFF;  // Desliga todos os LEDs
    }
    ws2812_send_pixels(pixels, NUM_LEDS);

    return 0;
}