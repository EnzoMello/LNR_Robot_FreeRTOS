#ifndef LINE_SENSOR_H
#define LINE_SENSOR_H
#include <Arduino.h>

class LineSensor {
    
public:
    LineSensor(int pin);
    
    // Inicializa o pino
    void init();
    
    // Retorna true se viu a linha
    bool check(); 

private:
    int _pin;
};
#endif