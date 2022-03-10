// Declaração de bibliotecas
#include "libs/NRF24L01_BIBLIOTECA.h"

void setup() {
  Serial.begin(9600);

  // Inicializa a comunicação com o modulo de rádio
  longRangeSettings();
  // Define o endereço do transmissor
  setAddress(ADDRESS_1, ADDRESS_0);
}

void loop() {
  readMessage();
  Serial.println(message);
}
