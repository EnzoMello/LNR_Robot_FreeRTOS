#include <Arduino.h>
#include "Tasks.h"
#include "./Globals/Globals.h" // Acesso aos sensores e motores

// Configurações de Estratégia
#define DIST_ATAQUE_MAX 50
#define DIST_ATAQUE_MIN 5
#define VEL_ATAQUE_MIN 140
#define VEL_ATAQUE_MAX 250

//TASK 1: LEITURA DE SENSORES 
void taskSensores(void *pvParam) {
  while (true) {
    bordaFrente = linhaFrontal.check(); 
    bordaTras = linhaTraseira.check();

    //Leitura Ultrassom
    float dE = usEsq.read();
    vTaskDelay(pdMS_TO_TICKS(5)); 
    float dD = usDir.read();
    
    // Filtro de erro
    if (dE < 0) dE = 999;
    if (dD < 0) dD = 999;

    distEsq = dE;
    distDir = dD;

    vTaskDelay(pdMS_TO_TICKS(20));
  }
}

// MÁQUINA DE ESTADOS
void taskControle(void *pvParam) {
  while (true) {
    
    // DECISÃO
    if (bordaFrente) {
      estadoAtual = FUGA_FRENTE;
    } 
    else if (bordaTras) {
      estadoAtual = FUGA_TRAS;
    }
    else if (estadoAtual != INICIO && (distEsq < DIST_ATAQUE_MAX || distDir < DIST_ATAQUE_MAX)) {
      estadoAtual = ATAQUE;
    }
    else if (estadoAtual != INICIO && estadoAtual != FUGA_FRENTE && estadoAtual != FUGA_TRAS) {
      estadoAtual = BUSCA;
    }

    // AÇÃO
    switch (estadoAtual) {
      case INICIO:
        robo.parar();
        break;

      case FUGA_FRENTE:
        robo.tras(250);
        vTaskDelay(pdMS_TO_TICKS(300));
        estadoAtual = BUSCA;
        break;

      case FUGA_TRAS:
        robo.frente(250);
        vTaskDelay(pdMS_TO_TICKS(300));
        estadoAtual = BUSCA;
        break;

      case BUSCA:
        robo.moverDiferencial(-150, 150); // Giro moderado
        break;

      case ATAQUE:
        bool viuEsq = (distEsq < DIST_ATAQUE_MAX);
        bool viuDir = (distDir < DIST_ATAQUE_MAX);

        if (viuEsq && viuDir) {
          // Ataque Centralizado (Proporcional)
          float menorDist = min(distEsq, distDir);
          int vel = map((long)menorDist, DIST_ATAQUE_MAX, DIST_ATAQUE_MIN, VEL_ATAQUE_MIN, VEL_ATAQUE_MAX);
          vel = constrain(vel, VEL_ATAQUE_MIN, VEL_ATAQUE_MAX);

          float erro = distDir - distEsq;
          int ajuste = erro * 4; 

          // robo.moverDiferencial(vel - ajuste, vel + ajuste);
          robo.moverDiferencial(-250, -250);
        }
        else if (viuEsq) {
          robo.moverDiferencial(100, -250); // Curva Esq
        }
        else if (viuDir) {
          robo.moverDiferencial(-250, 100); // Curva Dir
        }
        break;
    }

    vTaskDelay(pdMS_TO_TICKS(10));
  }
}