#include "./PalolaBuzzer.h"

PalolaBuzzer::PalolaBuzzer() {
    _pin = D2;
}

PalolaBuzzer::PalolaBuzzer(int pin) {
    _pin = pin;
}

void PalolaBuzzer::setArduinoPinsOutput() {
    pinMode(_pin, OUTPUT);
}

void PalolaBuzzer::playWhenMealIsFinished() {
    unsigned long noteDuration = BUZZER_DURATION / 6;
    for (int i = 0; i < 3; i++) {
        digitalWrite(_pin, HIGH);
        delay(noteDuration);
        digitalWrite(_pin, LOW);
        delay(noteDuration);
    }
}

void PalolaBuzzer::playWhenReady() {
    digitalWrite(_pin, HIGH);
    delay(BUZZER_DURATION);
    digitalWrite(_pin, LOW);
}