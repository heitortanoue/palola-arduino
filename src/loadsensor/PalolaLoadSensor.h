#ifndef __PALOLA_LOAD_SENSOR_H__
#define __PALOLA_LOAD_SENSOR_H__

#include <Arduino.h>
#include "HX711.h"

#define CALIBRATION_FACTOR -459.542
#define MIN_EMPTY_PERCENTAGE 0.2

class PalolaLoadSensor {
    public:
        PalolaLoadSensor();
        PalolaLoadSensor(int pinDOUT, int pinPD_SCK);

        void setArduinoPinsOutput();
        boolean isReady();
        
        void setTare(float newTare);
        float getWeight();

        boolean isBowlEmpty();
    private:
        int _pinDOUT;
        int _pinPD_SCK;
        float _tare;
        float _currentWeight;
        float _maxWeight;
        HX711 _loadSensor;
};

#endif