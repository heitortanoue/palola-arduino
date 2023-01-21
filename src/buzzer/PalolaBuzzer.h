#ifndef __PALOLA_BUZZER_H__
#define __PALOLA_BUZZER_H__

#include <Arduino.h>
#include "../../Pins.h"

#define NOTE_D5 587
#define NOTE_G5 784
#define NOTE_B5 988
#define BUZZER_DURATION 1000

class PalolaBuzzer {
    public:
        PalolaBuzzer();
        PalolaBuzzer(int pin);
        void setArduinoPinsOutput();
        
        void playWhenMealIsFinished();
        void playWhenReady();
    private:
        int _pin;
};

#endif
