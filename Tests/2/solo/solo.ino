#include <SPI.h>
#include <RF24.h>
#include "nRF24L01.h"

// LEDs para teste
#define ON_BUTTON 4
#define OFF_BUTTON 5

// Pinos CE e CSN
RF24 radio(9, 10);

bool buttons[] = {false, false};
bool receivedMessage = false;

const byte endereco[][6] = {"1node", "2node"};

void setup() {
  Serial.begin(9600);

  pinMode(ON_BUTTON, INPUT);
  pinMode(OFF_BUTTON, INPUT);

  // Inicializa a comunicação com o modulo de rádio
  radio.begin();
  radio.setAutoAck(false);
  radio.setPALevel(RF24_PA_HIGH);
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(0);

  // Define o endereço do transmissor
  radio.openWritingPipe(endereco[0]);
  radio.openReadingPipe(1, endereco[1]);

  // Prepara para o modo de envio
  radio.stopListening();
}

void loop() {
  buttons[0] = digitalRead(ON_BUTTON);
  buttons[1] = digitalRead(OFF_BUTTON);
  
  radio.write(&buttons, sizeof(buttons));
  radio.startListening();

  Serial.println("ANTES DO IF");
  if(radio.available()) {

    radio.read(&receivedMessage, sizeof(receivedMessage));

    if(receivedMessage){
      Serial.println("The message was received!");
    } else {
      Serial.println("The message was not received!");
    }
  }
  radio.stopListening();
}
