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
#include <SoftwareSerial.h>
SoftwareSerial monitorSerial(5, 6);

#define timeOut 10

// Configurações da flag Paraquedas e do NRF24L01
char parachute = '0';
int nrf = 1;

void setup()
{
    monitorSerial.begin(9600);
    Serial.begin(9600);
    // int i = 0;

    // Configurações da telemetria e do cartão SD.
    // while (!settingsSD())
    // {
    //     if (i >= timeOut)
    //     {
    //         break;
    //     }
    //     i++;
    // }

    i = 0;
    while (!longRangeSettings())
    {
        if (i >= timeOut)
        {
            nrf = 0;
            break;
        }
        i++;
    }

    if (nrf)
    {
        setAddress(ADDRESS_0, ADDRESS_1);
    }
}

void loop()
{
    // Tempo(ms),Altitude(m),AltitudeFK,VelocidadeFK,Paraquedas
    // 000000,000.00,000.00,000.00,0
    
    if (monitorSerial.available() > 0)
    {
        String message = monitorSerial.readStringUntil('\n');
        Serial.println(message);

        // Atualização das flags
        parachute = message[28];

        // Verificação do cartão SD
        // writeOnSD(message);

        // Verificação do NRF24L01
        if (nrf)
        {
            // char str[32];
            // message.toCharArray(str, 32);
            sendMessage();
        }
    }

    // if(available()) {
    //     readMessage();
    //     if(message == "Ativa!") {
    //         monitorSerial.println(message);
    //     }
    // }
}
