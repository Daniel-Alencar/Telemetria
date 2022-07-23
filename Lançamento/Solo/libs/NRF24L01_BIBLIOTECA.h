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

#define PIPE_1 1
#define PIPE_2 2
#define PIPE_3 3
#define PIPE_4 4
#define PIPE_5 5
#define PIPE_0 0

#define CE 7
#define CSN 8

RF24 radio(CE, CSN);
const byte endereco[][6] = {"00001", "00002"};

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

void setAddress(int pipeAddressIndex, int pipe)
{
  radio.openWritingPipe(endereco[pipeAddressIndex]);
  radio.openReadingPipe(pipe, endereco[pipeAddressIndex]);
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
    
    Serial.println(text);
  } else {
    serial.println("0,0,0,0,0");
  }
}

bool sendMessage(char *message)
{
  radio.stopListening();
  return radio.write(message, sizeof(*message) * strlen(message));
}
