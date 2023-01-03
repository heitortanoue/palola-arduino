#include "PalolaLoadSensor.h"

PalolaLoadSensor::PalolaLoadSensor(int dout, int pd_sck) {
    _pinDOUT = dout;
    _pinPD_SCK = pd_sck;
    _tare = 0;
    _currentWeight = 0;
    _maxWeight = 0;
    _loadSensor = HX711();

    _loadSensor.set_scale(CALIBRATION_FACTOR);
    _loadSensor.tare();
}

void PalolaLoadSensor::setArduinoPinsOutput() {
    _loadSensor.begin(_pinDOUT, _pinPD_SCK);
}

void PalolaLoadSensor::setTare(float newTare) {
    _tare = newTare;
}

float PalolaLoadSensor::getWeight() {
    if (_loadSensor.is_ready() == false) {
        Serial.println("HX711 not found.");
        return -1;
    }

    _currentWeight = _loadSensor.get_units(5);
    _currentWeight -= _tare;

    if (_currentWeight < 0) {
        _currentWeight = 0;
    }
}

