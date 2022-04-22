/* ================================================================================== */
/* ===== PROGRAMA PRINCIPAL : ATMEGA328P + TELEMETRIA + CARTÃO SD + EXPERIMENTO ===== */
/* ================================================================================== */

/*
    Pinagem:
    - Pino no arduino (Pino no ATMEGA328)
    
    - 11 (17): MOSI (NRF)
    - 12 (18): MISO (NRF)
    - 13 (19): SCK (NRF)
    - 08 (14): CSN (NRF)
    - 07 (13): CE (NRF)
    
    - 04 (06): ON_BUTTON (Botão de ativação do paraquedas)
*/

// Declaração de bibliotecas
#include "libs/NRF24L01_BIBLIOTECA.h"

void setup() {
  Serial.begin(9600);

  longRangeSettings();
  setAddress(ADDRESS_1, ADDRESS_0);
}

void loop() {
  readMessage();
}
