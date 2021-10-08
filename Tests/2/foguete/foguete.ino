#include <SPI.h>
#include <RF24.h>
#include "nRF24L01.h"

// LEDs para teste
#define ON_BUTTON 4
#define OFF_BUTTON 5

// Pinos CE e CSN
RF24 radio(9, 10);

bool buttons[2];
bool buttons[0] = false;
bool buttons[1] = false;

bool receivedMessage = false;

const byte endereco[][6] = {"1node", "2node"};

void setup() {
  Serial.begin(9600);

  pinMode(ON_BUTTON, INPUT);
  pinMode(OFF_BUTTON, INPUT);

  // Inicializa a comunicação com o modulo de rádio
  radio.begin();
  radio.setAutoAck(false);

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

  Serial.println("ANTES DO IF--------------------------");
  if(radio.available()) {

    radio.read(&receivedMessage, sizeof(receivedMessage));
    Serial.println(receivedMessage);

    if(receivedMessage){
      Serial.println("The message was received!");
      delay(2000);

    } else {

      Serial.println("The message was not received!");
      delay(2000);
    }

  }
  radio.stopListening();
}
