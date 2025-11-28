#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>
#include "MotorController.h"
#include "DistanceSensor.h"
#include "LineSensor.h"

// ESTADOS DO ROBÔ
enum Estado {
  INICIO,
  BUSCA,
  ATAQUE,
  FUGA_FRENTE,
  FUGA_TRAS
};

// DEFINIÇÃO DE PINOS
// Ultrassom
#define US_ESQ_TRIG 4
#define US_ESQ_ECHO 5
#define US_DIR_TRIG 13
#define US_DIR_ECHO 34

// Linha (Digital)
#define LINHA_FRONTAL_PIN 36
#define LINHA_TRASEIRA_PIN 39

// VARIÁVEIS COMPARTILHADAS
extern volatile Estado estadoAtual;
extern volatile float distEsq;
extern volatile float distDir;
extern volatile bool bordaFrente;
extern volatile bool bordaTras;

// OBJETOS GLOBAIS (Hardware)
extern MotorController robo;
extern DistanceSensor usEsq;
extern DistanceSensor usDir;
extern LineSensor linhaFrontal;
extern LineSensor linhaTraseira;

#endif