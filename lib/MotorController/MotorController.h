#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

#include <Arduino.h>

// Estrutura de configuração de cada motor
struct MotorConfig {
    uint8_t pinIN1;
    uint8_t pinIN2;
    uint8_t pinPWM;
    uint8_t canalPWM;
};

class MotorController {
public:
    MotorController();
    
    // Configura os pinos e o PWM
    void init();

    // Comandos de Alto Nível
    void parar();
    void frente(int velocidade);
    void tras(int velocidade);
    void girarEsquerda(int velocidade);
    void girarDireita(int velocidade);

    // Controle Diferencial (para curvas de ataque)
    // velEsq e velDir aceitam valores negativos para ré
    void moverDiferencial(int velEsq, int velDir);

private:
    // Helper para controlar um motor específico
    void setMotor(MotorConfig &motor, int velocidade); // velocidade: -255 a 255
};

#endif