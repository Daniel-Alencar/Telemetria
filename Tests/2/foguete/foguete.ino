#include <SPI.h>
#include <RF24.h>
#include "nRF24L01.h"

#define LED 4

// Pinos CE e CSN
RF24 radio(9, 10);

bool buttons[] = {false, false};
bool receivedMessage = true;

const byte endereco[][6] = {"1node", "2node"};

void setup() {
  // Inicia a comunicação serial
  Serial.begin(9600);

  digitalWrite(LED, LOW);

  // Inicia a comunicação com o modulo
  radio.begin();
  radio.setAutoAck(false);
  radio.setPALevel(RF24_PA_HIGH);
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(0);

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
    Serial.print("buttons[0] == ");
    Serial.print(buttons[0]);
    Serial.print(" | buttons[1] == ");
    Serial.println(buttons[1]);

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
