/* ================================================================================== */
/* ===== PROGRAMA PRINCIPAL : ATMEGA328P + TELEMETRIA + CARTÃO SD + EXPERIMENTO ===== */
/* ================================================================================== */

/*
    Pinagem:
    - Pino no arduino (Pino no ATMEGA328)
    
    - 11 (17): MOSI (NRF + SD)
    - 12 (18): MISO (NRF + SD)
    - 13 (19): SCK (NRF + SD)
    - 08 (14): CSN (NRF)
    - 07 (13): CE (NRF)
    - 10 (16): CS_PIN (SD)
    - 00 (02): RX (Comunicação serial)
    - 01 (03): TX (Comunicação serial)
*/

// Declaração de bibliotecas
#include "libs/NRF24L01_BIBLIOTECA.h"
#include "libs/ARMAZENAMENTO_BIBLIOTECA.h"

#define timeOut 10

float time1;  
float time2;

void setup()
{
    Serial.begin(9600);

    radio.begin();
    radio.setPALevel(RF24_PA_HIGH);
    radio.openWritingPipe(endereco[ADDRESS_0]);
}

void loop() {
    String message = "000000,000.00,000.00,000.00,0";   
    Serial.println(message);
    
    char str[32];
    message.toCharArray(str, 32);
    Serial.println(str);

    time1 = millis();
    bool teste = sendMessage(str);
    time2 = millis();

    Serial.print("RF: ");
    Serial.println(time2 - time1);

    Serial.println(teste);

}
