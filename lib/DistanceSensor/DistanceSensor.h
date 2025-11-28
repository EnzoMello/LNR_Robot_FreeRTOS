#ifndef DISTANCE_SENSOR_H
#define DISTANCE_SENSOR_H
#include <Arduino.h>

class DistanceSensor {
    
public:
    DistanceSensor(int trigPin, int echoPin);
    void init();
    float read(); // Retorna cm (ou -1 se erro)

private:
    int _trig, _echo;
};
#endif