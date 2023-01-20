#include "PalolaLedRGB.h"

PalolaLedRGB::PalolaLedRGB(int pin1, int pin2, int pin3) {
    _pin1 = pin1;
    _pin2 = pin2;
    _pin3 = pin3;
    _lastBlinkTime = 0;
    _lastState = 0;
}

PalolaLedRGB::PalolaLedRGB() {
    _pin1 = 0;
    _pin2 = 0;
    _pin3 = 0;
    _lastBlinkTime = 0;
    _lastState = 0;
}

void PalolaLedRGB::setArduinoPinsOutput() {
    pinMode(_pin1, OUTPUT);
    pinMode(_pin2, OUTPUT);
    pinMode(_pin3, OUTPUT);
}

void PalolaLedRGB::setMode(LED_MODE mode) {
    switch (mode) {
        case LED_BUSY:
            // ORANGE
            setColor(255, 140, 0);
            break;
        case LED_READY:
            // GREEN
            setColor(0, 255, 0);
            break;
        case LED_FEEDING:
            // BLUE
            setColor(0, 0, 255);
            break;
        case LED_ERROR:
            // RED
            setColor(255, 0, 0);
            break;
        case LED_INICIALIZING:
            // YELLOW
            setColor(255, 255, 0);
            break;
        case LED_SEARCHING:
            // PURPLE
            setColor(255, 0, 255);
            break;
        default:
            setColor(0, 0, 0);
            break;
    }
}

// async blinking of the led with a delay
void PalolaLedRGB::blink(LED_MODE mode, int delayTime) {
    unsigned long currentMillis = millis();
    if (currentMillis - _lastBlinkTime > delayTime) {
        _lastBlinkTime = currentMillis;
        if (_lastState == 0) {
            _lastState = 1;
            setMode(mode);
        } else {
            _lastState = 0;
            turnOff();
        }
    }
}


void PalolaLedRGB::turnOff() {
    setColor(0, 0, 0);
}

void PalolaLedRGB::setColor(int red, int green, int blue) {
    analogWrite(_pin1, red);
    analogWrite(_pin2, green);
    analogWrite(_pin3, blue);
}