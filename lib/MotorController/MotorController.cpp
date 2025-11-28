#include "MotorController.h"

// DEFINIÇÃO DE PINOS
// Motor LF (Esquerdo Frontal)
MotorConfig mLF = {32, 15, 18, 0}; 
// Motor RF (Direito Frontal)
MotorConfig mRF = {12, 14, 19, 1};
// Motor LR (Esquerdo Traseiro)
MotorConfig mLR = {16, 17, 21, 2};
// Motor RR (Direito Traseiro)
MotorConfig mRR = {26, 25, 22, 3};

// Configurações PWM
const int FREQ = 5000;
const int RES = 8;
const int PWM_MAX = 250; // Limite de segurança 6V

MotorController::MotorController() {}

void MotorController::init() {
    // Configura Motor LF
    pinMode(mLF.pinIN1, OUTPUT); 
    pinMode(mLF.pinIN2, OUTPUT);
    ledcSetup(mLF.canalPWM, FREQ, RES); 
    ledcAttachPin(mLF.pinPWM, mLF.canalPWM);

    // Configura Motor RF
    pinMode(mRF.pinIN1, OUTPUT); 
    pinMode(mRF.pinIN2, OUTPUT);
    ledcSetup(mRF.canalPWM, FREQ, RES); 
    ledcAttachPin(mRF.pinPWM, mRF.canalPWM);

    // Configura Motor LR
    pinMode(mLR.pinIN1, OUTPUT); 
    pinMode(mLR.pinIN2, OUTPUT);
    ledcSetup(mLR.canalPWM, FREQ, RES); 
    ledcAttachPin(mLR.pinPWM, mLR.canalPWM);

    // Configura Motor RR
    pinMode(mRR.pinIN1, OUTPUT); 
    pinMode(mRR.pinIN2, OUTPUT);
    ledcSetup(mRR.canalPWM, FREQ, RES); 
    ledcAttachPin(mRR.pinPWM, mRR.canalPWM);

    parar();
}

void MotorController::setMotor(MotorConfig &m, int velocidade) {
    // Limita PWM
    if (velocidade > PWM_MAX) velocidade = PWM_MAX;
    if (velocidade < -PWM_MAX) velocidade = -PWM_MAX;

    int pwmVal = abs(velocidade);
    
    ledcWrite(m.canalPWM, pwmVal);

    if (velocidade > 0) {       // FRENTE
        digitalWrite(m.pinIN1, HIGH);
        digitalWrite(m.pinIN2, LOW);
    } else if (velocidade < 0) { // TRÁS
        digitalWrite(m.pinIN1, LOW);
        digitalWrite(m.pinIN2, HIGH);
    } else {                     // FREIO
        digitalWrite(m.pinIN1, HIGH);
        digitalWrite(m.pinIN2, HIGH);
    }
}

void MotorController::moverDiferencial(int velEsq, int velDir) {
    setMotor(mLF, velEsq);
    setMotor(mLR, velEsq);
    setMotor(mRF, velDir);
    setMotor(mRR, velDir);
}

void MotorController::parar() { moverDiferencial(0, 0); }
void MotorController::frente(int vel) { moverDiferencial(vel, vel); }
void MotorController::tras(int vel) { moverDiferencial(-vel, -vel); }
void MotorController::girarEsquerda(int vel) { moverDiferencial(-vel, vel); }
void MotorController::girarDireita(int vel) { moverDiferencial(vel, -vel); }