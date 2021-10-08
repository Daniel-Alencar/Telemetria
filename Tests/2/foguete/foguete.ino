#include <SPI.h>
#include <RF24.h>
#include "nRF24L01.h"

#define LED 4

// Pinos CE e CSN
RF24 radio(9, 10);

bool buttons[2];
bool buttons[0] = false;
bool buttons[1] = false;

bool receivedMessage = true;

const byte endereco[][6] = {"1node", "2node"};

void setup() {
  // Inicia a comunicação serial
  Serial.begin(9600);

  digitalWrite(LED, LOW);

  // Inicia a comunicação com o modulo
  radio.begin();
  radio.setAutoAck(false);

  // Define o endereço do receptor (data pipe 0)
  // Define o endereço do transmissor
  radio.openWritingPipe(endereco[1]);
  radio.openReadingPipe(1, endereco[0]);

  // Entra no modo de recebimento
  radio.startListening();
}

void loop() {
  if(radio.available()) {

    // Se recebeu algum pacote, lê o conteudo na variável
    radio.read(&buttons, sizeof(buttons));
    // Imprime o que foi recebido
    Serial.println("buttons[0] == " + buttons[0] + " | buttons[1] == " + buttons[1]);

    radio.stopListening();
    radio.write(&receivedMessage, sizeof(bool));
    radio.startListening();

    if(buttons[0] && !buttons[1]) {
      digitalWrite(LED, HIGH);
    } else if(!buttons[0] && buttons[1]) {
      digitalWrite(LED, LOW);
    }
  }
}