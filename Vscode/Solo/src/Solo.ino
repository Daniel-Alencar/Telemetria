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

const byte address[6] = "00002";
 bool notSent = false;

void setup() {
  Serial.begin(9600);

  radio.begin();
  radio.openReadingPipe(0, address); 
  radio.setPALevel(RF24_PA_HIGH);
}

void loop() {
   if(!notSent){
     Serial.println("\nINICIADO!");
     notSent = true;
   }
  readMessage();
}
