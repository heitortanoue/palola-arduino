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

void PalolaBuzzer::playNote(unsigned int note, unsigned long noteDuration) {
    tone(_pin, note);
    delay(noteDuration);
    noTone(_pin);
}

void PalolaBuzzer::playWhenMealIsFinished() {
    unsigned long noteDuration = BUZZER_DURATION / 6;
    for (int i = 0; i < 3; i++) {
        playNote(NOTE_D5, noteDuration);
        delay(noteDuration);
        playNote(NOTE_G5, noteDuration);
    }
}

void PalolaBuzzer::playWhenReady() {
    unsigned long noteDuration = BUZZER_DURATION / 6;
    for (int i = 0; i < 3; i++) {
        playNote(NOTE_B5, noteDuration);
        delay(noteDuration);
    }
}