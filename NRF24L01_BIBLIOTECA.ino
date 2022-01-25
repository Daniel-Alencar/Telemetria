/*
  O NRF24L01 trabalha com um tamanho máximo de 32 bytes para cada pacote enviado/recebido
  Sendo assim, optamos por enviar:
  Tempo, Altitude, AltitudeFk, AY, Temperatura
  000010,00001,00001,010,000.

  Com um total de:
  6+1+5+1+5+1+3+1+3+1 = 27 Bytes
*/

#include <SPI.h>
#include <RF24.h>
#include "nRF24L01.h"

#define ADDRESS_0 0
#define ADDRESS_1 1
#define ADDRESS_2 2

RF24 radio(9, 10);
bool receivedMessage = false;
char message[50];
const byte endereco[][6] = {"1node", "2node", "3node"};

void longRangeSettings()
{
  if (radio.begin())
  {
    radio.setAutoAck(false);
    radio.setPALevel(RF24_PA_HIGH);
    radio.setDataRate(RF24_250KBPS);
    radio.setChannel(0);
    return true
  }
  return false;
}

void lowRangeSettings()
{
  if (radio.begin())
  {
    radio.setAutoAck(false);
    radio.setPALevel(RF24_PA_MIN);
    radio.setDataRate(RF24_1MBPS);
    radio.setChannel(0);
    return true
  }
  return false;
}

void setAddress(int thisDevice, int anotherDevice)
{
  radio.openWritingPipe(endereco[thisDevice]);
  radio.openReadingPipe(1, endereco[anotherDevice]);
}

void readMessage()
{
  radio.startListening();
  radio.read(&message, sizeof(message));
}

void sendMessage(char *message)
{
  radio.stopListening();
  radio.write(message, sizeof(*message));
}

bool available()
{
  return radio.available();
}

bool isPlusVariant()
{
  return radio.isPVariant();
}
