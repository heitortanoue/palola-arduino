#ifndef __PALOLA_H__
#define __PALOLA_H__

#include <Arduino.h>
#include "../stepper/PalolaStepper.h"
#include "../loadsensor/PalolaLoadSensor.h"
// #include "../rtc/PalolaRTC.h"
#include "../../Pins.h"
#include "../ledrgb/PalolaLedRGB.h"
#include "../wifi/PalolaWifi.h"

#define MINUTES_BETWEEN_CHECKS 1 

class Palola {
    public:
        Palola();
        void getReady();
        void checkMeals();
        void feed(Meal meal);

        PalolaStepper stepper;
        PalolaLoadSensor loadSensor;
        // PalolaRTC rtc;
        PalolaLedRGB led;
        PalolaWifi wifi;
};

#endif