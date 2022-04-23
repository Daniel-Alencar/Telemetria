/*
  O NRF24L01 trabalha com um tamanho máximo de 32 bytes para cada pacote enviado/recebido
  Sendo assim, optamos por enviar:
  Altitude(m),AltitudeFK,Velocidade(m/s),VelocidadeFK,Paraquedas
  000.00,000.00,000.00,000.00,0
  Com um total de:
  6+1+6+1+6+1+6+1+1 = 29 Bytes
*/

#include <SPI.h>
#include <RF24.h>
#include <string.h>
#include <nRF24L01.h>

#define ADDRESS_0 0
#define ADDRESS_1 1
#define ADDRESS_2 2

#define CE 7
#define CSN 8

RF24 radio(CE, CSN);
const byte endereco[][6] = {"1node", "2node", "3node"};

bool longRangeSettings()
{
  radio.begin();
  radio.setPALevel(RF24_PA_HIGH);
  return true;
}

bool lowRangeSettings()
{
  radio.begin();
  radio.setPALevel(RF24_PA_MIN);
  return true;
}

void setAddress(int thisDevice, int anotherDevice)
{
  radio.openWritingPipe(endereco[thisDevice]);
  radio.openReadingPipe(1, endereco[anotherDevice]);
}

bool available()
{
  return radio.available();
}

bool isPlusVariant()
{
  return radio.isPVariant();
}

void readMessage()
{
  radio.startListening();

  if(available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));

    Serial.println(">>");
    Serial.println(text);
    Serial.println(">>");
  }
}

bool sendMessage()
{
  radio.stopListening();

  const char otherMessage[] = "000000,000.00,000.00,000.00,0";
  return radio.write(&otherMessage, sizeof(otherMessage));
}