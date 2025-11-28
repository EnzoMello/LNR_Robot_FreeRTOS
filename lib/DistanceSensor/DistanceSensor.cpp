#include "DistanceSensor.h"

DistanceSensor::DistanceSensor(int trigPin, int echoPin) : _trig(trigPin), _echo(echoPin) {}

void DistanceSensor::init() {
    pinMode(_trig, OUTPUT);
    pinMode(_echo, INPUT);
}

float DistanceSensor::read() {
    digitalWrite(_trig, LOW); delayMicroseconds(2);
    digitalWrite(_trig, HIGH); delayMicroseconds(10);
    digitalWrite(_trig, LOW);

    long duration = pulseIn(_echo, HIGH, 25000); // Timeout 25ms
    if (duration == 0) return 999.0; // Infinito/Sem detecção

    return duration * 0.01715; // cm
}