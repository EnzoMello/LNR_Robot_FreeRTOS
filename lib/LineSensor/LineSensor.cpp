#include "LineSensor.h"

LineSensor::LineSensor(int pin) : _pin(pin) {}

void LineSensor::init() {
    pinMode(_pin, INPUT); 
}

bool LineSensor::check() {
    bool estado = digitalRead(_pin);

    return (estado == HIGH); 
    
}