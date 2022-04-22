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
#include "nRF24L01.h"

#define ADDRESS_0 0
#define ADDRESS_1 1
#define ADDRESS_2 2

#define CE 8
#define CSN 7

RF24 radio(CE, CSN);
bool receivedMessage = false;
char message[50];
const byte endereco[][6] = {"1node", "2node", "3node"};

bool longRangeSettings()
{
  radio.begin();
  radio.setAutoAck(false);
  radio.setPALevel(RF24_PA_HIGH);
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(0);
  return true;
}

bool lowRangeSettings()
{
  radio.begin();
  radio.setAutoAck(false);
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_1MBPS);
  radio.setChannel(0);
  return true;
}

void setAddress(int thisDevice, int anotherDevice)
{
  radio.openWritingPipe(endereco[thisDevice]);
  radio.openReadingPipe(0, endereco[anotherDevice]);
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
    int length = 0;
    length = radio.getDynamicPayloadSize();
    Serial.println(length);

    char str[30] = "";

    radio.read(&str, 30);

    Serial.println(str); 
    Serial.println(">> readMessage");
  }
}

bool sendMessage()
{
  radio.stopListening();

  //char otherMessage[32] = "000000,000.00,000.00,000.00,0";
  //return radio.write(otherMessage, strlen(otherMessage));

  char otherMessage[32] = "000000,000.00,000.00,000.00,0";
  return radio.write(&otherMessage, strlen(otherMessage));

  // String str = "000000,000.00,000.00,000.00,0";
  // return radio.write(&str, str.length() * sizeof(str));
}
