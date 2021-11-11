/*
    Time, Altitude , FKAltitude,     TIME=              ALTITUDE= 4+1+2            
    AcelerometerX, AcelerometerY,    FKAltitude= 4+1+2   Ax= 5                 Ay= 5               
    AcelerometerZ , Temperature \n   Az= 5               TEMP=   5              \n=1   \0 = 1     

    900.00,1000.00,1000.00,54.05,54.05,54.05,23.01

    TIME OUT= TOU
*/

    //TEMPO, ALTITUDE,AltitudeFk, AY, Temperatura
    //6+1+5+1+5+1+3+1+3+1 = 27 BYTES
    

 
#include <SPI.h>
#include <RF24.h>
#include "nRF24L01.h"

RF24 radio(9, 10);
bool receivedMessage = false;
char message[50];
const byte endereco[][6] = {"1node", "2node"};

void longRangeSettings() {
  radio.begin();
  radio.setAutoAck(false);
  radio.setPALevel(RF24_PA_HIGH);
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(0);
}

void lowRangeSettings() {
  radio.begin();
  radio.setAutoAck(false);
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_2MBPS);
  radio.setChannel(0);
}

void setAddress() {
  radio.openWritingPipe(endereco[1]);
  radio.openReadingPipe(1, endereco[0]);
}

void readMessage() {
  radio.startListening();
  radio.read(&message, sizeof(message));
}

void sendMessage(char *message) {
  radio.stopListening();
  radio.write(message, sizeof(*message));
}

bool avaiable() {
  return radio.available();
}