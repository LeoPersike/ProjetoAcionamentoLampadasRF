/* Projeto: Acionador de lâmpadas via RF
 * Autor: Leonardo Persike Martins (PK)
 * Contato: Leonardo.Persike.Martins@gmail.com
 * Data: 21.08.2022 
*/

/* Bibliotecas */
#include "RCSwitch.h"

/* Criando o controle */
RCSwitch mySwitch = RCSwitch();

/* Definicoes */
#define ESQ 0
#define DIR 1

/* Codificacao do controle */
#define BOTAO_1 "100101001110111110100001"
#define BOTAO_2 "100101001110111110100010"
#define PULSE_LENGTH 374
#define PROTOCOL 1

/* Pinos */
int sensorBarreira = 2;  // Pino onde o relé do sensor de barreira irá ser conectado

/* Setup */
void setup() 
{
  /* Serial para debug */
  Serial.begin(9600);

  /* Coloca interrupcao em Pull-Up*/ 
  pinMode(sensorBarreira, INPUT_PULLUP);

  /* Configura transmissor */
  mySwitch.enableTransmit(10);
  mySwitch.setPulseLength(PULSE_LENGTH);
  mySwitch.setProtocol(PROTOCOL); 
}

/* Loop principal */
void loop() 
{
  while(1)
  {
    if(digitalRead(sensorBarreira) == LOW) /* Detecta a passagem do veiculo: nível baixo no relé */
    {
      Serial.println("Passagem pela barreira.");
      acionaLuz();
    }
  }
}

/* Funcão para acionar a luz esquerda ou direita aleatóriamente */
void acionaLuz()
{
  int aleatorio = random(2);
  
  if(aleatorio == ESQ)
  {
    Serial.println("Apertando botão 1!");
    /* Envia código binário do botão A 2 vezes (liga e desliga) */
    mySwitch.send(BOTAO_1);
    delay(3000);  
    mySwitch.send(BOTAO_1);
    delay(1000);
  }
  else
  {
    Serial.println("Apertando botão 2!");
    /* Envia código binário do botão B 2 vezes (liga e desliga) */
    mySwitch.send(BOTAO_2);
    delay(3000);  
    mySwitch.send(BOTAO_2);
    delay(1000);
  }
}
