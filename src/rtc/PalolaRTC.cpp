#include "PalolaRTC.h"

PalolaRTC::PalolaRTC(int pin1, int pin2) {
    _pin1 = pin1;
    _pin2 = pin2;
}

PalolaRTC::PalolaRTC() {
    _pin1 = 0;
    _pin2 = 0;
}

void PalolaRTC::setArduinoPinsOutput() {
    Wire.begin(_pin1, _pin2);
}

boolean PalolaRTC::isReady() {
    return _rtc.begin() && _rtc.isrunning();
}

RTC_DS1307 PalolaRTC::getRTC() {
    return _rtc;
}