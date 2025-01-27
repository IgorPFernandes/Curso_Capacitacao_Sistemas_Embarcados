#include <Servo.h>  // Inclui a biblioteca Servo

// Criação dos objetos Servo
Servo servo1;  // Servo da garra
Servo servo2;  // Servo esquerdo
Servo servo3;  // Servo direito
Servo servo4;  // Servo da base

// Pinos de conexão dos servos
int pinServo1 = 9;   // Pino para o servo da garra
int pinServo2 = 10;  // Pino para o servo esquerdo
int pinServo3 = 11;  // Pino para o servo direito
int pinServo4 = 6;   // Pino para o servo da base (alterado para 6)

// Pinos dos potenciômetros
int potPin1 = A0;  // Pino para o potenciômetro do servo da garra
int potPin2 = A1;  // Pino para o potenciômetro do servo esquerdo
int potPin3 = A2;  // Pino para o potenciômetro do servo direito
int potPin4 = A3;  // Pino para o potenciômetro do servo da base

int potValue1, potValue2, potValue3, potValue4;  // Valores lidos dos potenciômetros
int angulo1, angulo2, angulo3, angulo4;  // Ângulos mapeados para os servos

void setup() {
  // Conectar os servos aos pinos
  servo1.attach(pinServo1);
  servo2.attach(pinServo2);
  servo3.attach(pinServo3);
  servo4.attach(pinServo4);
  
  Serial.begin(9600);  // Inicia a comunicação serial
}

void loop() {
  // Lê os valores dos potenciômetros
  potValue1 = analogRead(potPin1);  // Lê o potenciômetro do servo da garra
  potValue2 = analogRead(potPin2);  // Lê o potenciômetro do servo esquerdo
  potValue3 = analogRead(potPin3);  // Lê o potenciômetro do servo direito
  potValue4 = analogRead(potPin4);  // Lê o potenciômetro do servo da base
  
  // Mapeando os valores dos potenciômetros para os ângulos dos servos
  angulo1 = map(potValue1, 0, 1023, 0, 105);     // Servo 1 (Garra): 0° a 105°
  angulo2 = map(potValue2, 0, 1023, 30, 170);   // Servo 2 (Esquerdo): 30° a 170°
  angulo3 = map(potValue3, 0, 1023, 80, 170);   // Servo 3 (Direito): 80° a 170°
  angulo4 = map(potValue4, 0, 1023, 0, 180);    // Servo 4 (Base): 0° a 180°

  // Suavizando a movimentação dos servos simultaneamente
  suavizarMovimentoSimultaneo(servo1, angulo1);
  suavizarMovimentoSimultaneo(servo2, angulo2);
  suavizarMovimentoSimultaneo(servo3, angulo3);
  suavizarMovimentoSimultaneo(servo4, angulo4);

  delay(10);  // Aguarda os servos se moverem para a nova posição
}

// Função para suavizar o movimento dos servos simultaneamente
void suavizarMovimentoSimultaneo(Servo& servo, int anguloDesejado) {
  int anguloAtual = servo.read();  // Obtém o ângulo atual do servo
  
  // Se o ângulo atual não for igual ao desejado, mova o servo
  if (anguloAtual != anguloDesejado) {
    // Define o intervalo de movimento
    int passos = (anguloAtual < anguloDesejado) ? 1 : -1;

    // Faz a movimentação gradual
    for (int i = anguloAtual; i != anguloDesejado; i += passos) {
      servo.write(i);  // Atualiza a posição do servo
      delay(5);  // Aguarda para criar a suavização no movimento
    }
  }
}
