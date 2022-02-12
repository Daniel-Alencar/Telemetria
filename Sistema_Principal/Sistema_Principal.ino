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

    Pinagem opcional?
    - GND (08): GND do outro ATMEGA

    Dúvidas:
    - GND do NRF e SD vão para onde (GND do ATMEGA ou outro GND)?
    - MOSI, MISO e SCK irão ser compartilhados entre o NRF e o SD, né?
*/

// Declaração de bibliotecas
#include "NRF24L01_BIBLIOTECA.h"
#include "ARMAZENAMENTO_BIBLIOTECA.h"

// Declarar frequência do atmega como 16 MHz e do Time Out
#define timeOut 10

// Configurações da flag Paraquedas e do NRF24L01
char parachute = '0';
int nrf = 1;

void setup()
{
    Serial.begin(9600);
    int i = 0;

    // Configurações da telemetria e do cartão SD.
    while (!settingsSD())
    {
        if (i >= timeOut)
        {
            break;
        }
        i++;
    }

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
    if (Serial.available() > 0)
    {
        String message = Serial.readString();

        // Atualização das flags
        parachute = message[28];

        // Verificação do cartão SD
        writeOnSD(message);

        // Verificação do NRF24L01
        if (nrf)
        {
            char str[32];
            message.toCharArray(str, 32);
            sendMessage(str);
        }
    }
}
