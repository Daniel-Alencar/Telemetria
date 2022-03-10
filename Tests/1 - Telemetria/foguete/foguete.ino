#include <SPI.h>
#include <RF24.h>
#include "nRF24L01.h"

// Pinagem de LEDs para teste
#define LED0 4
#define LED1 2

// Instância de radio definindo pinos CE (porta D7) e CSN (porta D8)
RF24 radio(9, 10);
// Definindo variavel que vai definir a ação a ser executada
char releaseParachute = '0';

// Definição de endereços para cada dispositivo (foguete e solo)
const byte endereco[][6] = {"1node", "2node"};

void setup() {
  Serial.begin(9600);

  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  digitalWrite(LED0, LOW);
  digitalWrite(LED1, LOW);

  // Inicializa a comunicação com o modulo de rádio
  radio.begin();
  // Desativar pacotes de reconhecimento automático
  radio.setAutoAck(false);

  // Define o endereço deste dispositivo
  radio.openWritingPipe(endereco[0]);
  // Define o endereço de onde será "escutado" os dados
  radio.openReadingPipe(1, endereco[1]);
  // Prepara este dispositivo para receber informações
  radio.startListening();
}

void loop() {
  // Se "escutou" alguma coisa
  if(radio.available()) {

    // Coloca a informação recebida na variável releaseParachute
    radio.read(&releaseParachute, sizeof(releaseParachute));
    // Faremos diferentes ações de acordo com o valor de releaseParachute
    switch(releaseParachute) {
      case '0':
        Serial.println("Ligando Led 0!");
        digitalWrite(LED0, HIGH);
        digitalWrite(LED1, LOW);
        break;
      case '1':
        Serial.println("Ligando Led 1!");
        digitalWrite(LED1, HIGH);
        digitalWrite(LED0, LOW);
        break;
    }
  }
}
