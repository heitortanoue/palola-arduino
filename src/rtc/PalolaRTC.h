#ifndef __PALOLA_RTC_H__
#define __PALOLA_RTC_H__

#include <Arduino.h>
#include <RTClib.h>
#include <Wire.h>

class PalolaRTC {
    public:
        PalolaRTC();
        PalolaRTC(int pin1, int pin2);
        void setArduinoPinsOutput();
        boolean isReady();
        RTC_DS1307 getRTC();
    private:
        int _pin1;
        int _pin2;
        RTC_DS1307 _rtc;
};

#endif