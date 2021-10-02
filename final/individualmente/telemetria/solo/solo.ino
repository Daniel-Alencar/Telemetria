#include <SPI.h>
#include <RF24.h>
#include "nRF24L01.h"

// Instância de radio definindo pinos CE (porta D7) e CSN (porta D8)
RF24 radio(9, 10);
// Definindo variável que vai definir a ação a ser executada
char releaseParachute = '0';

// Contador usado para a definição do dado a ser enviado
// Se count == 0, então, radio envia '0'
// Se count == 1, então, radio envia '1'
uint8_t count = 0;

// Definição de endereços para cada dispositivo (foguete e solo)
const byte endereco[][6] = {"1node", "2node"};

void setup() {
  Serial.begin(9600);

  // Inicializa a comunicação com o modulo de rádio
  radio.begin();
  // Desativar pacotes de reconhecimento automático
  radio.setAutoAck(false);

  // Define o endereço deste dispositivo
  radio.openWritingPipe(endereco[1]);
  // Define o endereço de onde será "escutado" os dados
  radio.openReadingPipe(1, endereco[0]);
  // Prepara este dispositivo para enviar informações
  radio.stopListening();
}

void loop() {
  // Definimos diferentes valores a serem enviados de acordo com o valor de 'count'
  switch(count){
    case 0:
      releaseParachute = '0';
      break;
    case 1:
      releaseParachute = '1';
      break;
  }
  // Atualizamos o valor de 'count' para a próxima interação
  count = (count+1) % 2;
  
  // Tentamos enviar os dados
  int transmitidoERecebido = radio.write(&releaseParachute, sizeof(releaseParachute));
  // Verificamos se obtemos sucesso no envio
  Serial.println(transmitidoERecebido);
  
  // Definimos um tempo de delay para a próxima interação
  delay(2000);
}

