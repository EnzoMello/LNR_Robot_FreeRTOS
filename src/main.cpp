#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "./Globals/Globals.h"
#include "./Tasks/Tasks.h"

void setup() {
  Serial.begin(115200);
  
  // Inicializa Hardware (Objetos globais definidos em Globals.cpp)
  robo.init();
  usEsq.init();
  usDir.init();
  linhaFrontal.init();
  linhaTraseira.init();
  

  Serial.println("Robo Sumo PRONTO.");
  Serial.println("Aguardando 5 segundos...");
  
  // Delay de segurança obrigatório
  delay(5000); 
  
  Serial.println("INICIANDO COMBATE!");
  estadoAtual = BUSCA; 

  // Cria as Tasks
  xTaskCreate(taskSensores, "Sensores", 2048, NULL, 2, NULL); // Prioridade Alta
  xTaskCreate(taskControle, "Controle", 4096, NULL, 1, NULL); // Prioridade Média
}

void loop() {
  // Loop vazio - FreeRTOS gerencia as tasks
  vTaskDelete(NULL);
}