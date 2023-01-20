#ifndef __PALOLA_LED_RGB_H__
#define __PALOLA_LED_RGB_H__

#include <Arduino.h>

enum LED_MODE {
    LED_BUSY,
    LED_READY,
    LED_FEEDING,
    LED_ERROR,
    LED_INICIALIZING,
    LED_SEARCHING
};

// LED common cathode
class PalolaLedRGB {
    public:
        PalolaLedRGB();
        PalolaLedRGB(int pin1, int pin2, int pin3);
        void setArduinoPinsOutput();
        void setMode(LED_MODE mode);
        void blink(LED_MODE mode, int delayTime);
        void turnOff();
    private:
        void setColor(int red, int green, int blue);
        int _pin1;
        int _pin2;
        int _pin3;

        byte _lastState;
        long _lastBlinkTime;
};

#endif