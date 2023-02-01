#ifndef __PALOLA_H__
#define __PALOLA_H__

#include <Arduino.h>
#include "../stepper/PalolaStepper.h"
#include "../loadsensor/PalolaLoadSensor.h"
#include "../../Pins.h"
#include "../ledrgb/PalolaLedRGB.h"
#include "../wifi/PalolaWifi.h"
#include "../buzzer/PalolaBuzzer.h"

#define MINUTES_BETWEEN_CHECKS 1 

class Palola {
    public:
        Palola();
        void getReady();
        void checkMeals();
        void feed(Meal meal);

        PalolaStepper stepper;
        PalolaLoadSensor loadSensor;
        PalolaLedRGB led;
        PalolaWifi wifi;
        PalolaBuzzer buzzer;
    private:
        String _lastMealId;
};

#endif