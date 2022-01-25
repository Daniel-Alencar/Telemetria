/* ================================================================================== */
/* ===== PROGRAMA PRINCIPAL : ATMEGA328P + TELEMETRIA + CARTÃO SD + EXPERIMENTO ===== */
/* ================================================================================== */

// Declaração de bibliotecas
#include "NRF24L01_BIBLIOTECA"
#include "ARMAZENAMENTO_BIBLIOTECA"

// Declarar frequência do atmega como 16 MHz e do Time Out
#define F_CPU 16000000UL
#define timeOut 10

// Configurações da flag
byte flags = 11111111; // Paraquedas, BMP, MPU, NRF24L01, SD

#define set_bit(flag, bit) (flag & (1 << bit))
#define reset_bit(flag, bit) (flag | !(1 << bit))
#define updateFlag(value, bit) (value ? set_bit(flags, bit) : reset_bit(flags, bit))
#define verifyFlag(flag, bit) ((flag & (1 << bit)) ? true : false)

void setup()
{
    Serial.begin(9600);
    int i = 0;

    // Configurações da telemetria e do cartão SD.
    while (!settingsSD())
    {
        if (i >= timeOut)
        {
            updateFlag(false, 0);
            break;
        }
        i++;
    }

    i = 0;
    while (!longRangeSettings())
    {
        if (i >= timeOut)
        {
            updateFlag(false, 1);
            break;
        }
        i++;
    }

    if (verifyFlag(flags, 1))
    {
        setAddress(ADDRESS_0, ADDRESS_1);
    }
}

void loop()
{
    // Recebendo as informações da Serial: Tempo, Altitude, AltitudeFk, AY, Temperatura, PBM (Paraquedas, BMP, MPU)
    if (Serial.available() > 0)
    {
        String message = Serial.readString();

        // Concatenação das flags
        String flagsString = String(flags);
        String messageWithFlags = String(message) + flagsString[6] + flagsString[7];

        // Atualização das flags
        for (int i = 27; i < 31; i++)
        {
            if (messageWithFlags[i] == '1')
            {
                set_bit(flags, 31 - i);
            }
            else
            {
                reset_bit(flags, 31 - i);
            }
        }

        // Verificação do cartão SD
        if (verifyFlag(flags, 0))
        {
            writeOnSD(message);
        }

        // Verificação do NRF24L01
        if (verifyFlag(flags, 1))
        {
            sendMessage(message);
        }
    }

    // Talvez implementar
    /*
    else {
        if (verifyFlag(flags, 0)) {
            writeOnSD("Serial isn't responding!");
        }

        if (verifyFlag(flags, 1)) {
            sendMessage("Serial isn't responding!");
        }
    }
    */
}