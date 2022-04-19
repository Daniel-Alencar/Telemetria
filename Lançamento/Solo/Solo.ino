// Declaração de bibliotecas
#include "libs/NRF24L01_BIBLIOTECA.h"

// #define ON_BUTTON 4
// bool button = false;
bool notSent = false;

void setup() {
  Serial.begin(9600);

  // pinMode(ON_BUTTON, INPUT);

  // Inicializa a comunicação com o modulo de rádio
  longRangeSettings();
  // Define o endereço do transmissor
  setAddress(ADDRESS_1, ADDRESS_0);
}

void loop() {
  if(!notSent){
    Serial.println("INICIADO!");
    notSent = true;
  }

  // button = digitalRead(ON_BUTTON);
  // if(button) {
  //   sendMessage("Ativa!");
  // }

  readMessage();
  Serial.println(message);
}
