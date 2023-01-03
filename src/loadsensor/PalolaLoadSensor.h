#ifndef __PALOLA_LOAD_SENSOR_H__
#define __PALOLA_LOAD_SENSOR_H__

#include <Arduino.h>
#include "HX711.h"

#define CALIBRATION_FACTOR -459.542

class PalolaLoadSensor {
    public:
        PalolaLoadSensor(int pinDOUT, int pinPD_SCK);
        void setArduinoPinsOutput();
        void setTare(float newTare);
        float getWeight();
    private:
        int _pinDOUT;
        int _pinPD_SCK;
        float _tare;
        float _currentWeight;
        float _maxWeight;
        HX711 _loadSensor;
};

#endif