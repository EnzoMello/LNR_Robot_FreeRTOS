#include "Globals.h"

// Inicialização das variáveis
volatile Estado estadoAtual = INICIO;
volatile float distEsq = 999;
volatile float distDir = 999;
volatile bool bordaFrente = false;
volatile bool bordaTras = false;

// Instanciação dos objetos de Hardware
MotorController robo;
DistanceSensor usEsq(US_ESQ_TRIG, US_ESQ_ECHO);
DistanceSensor usDir(US_DIR_TRIG, US_DIR_ECHO);
LineSensor linhaFrontal(LINHA_FRONTAL_PIN);
LineSensor linhaTraseira(LINHA_TRASEIRA_PIN);