#include "PalolaStepper.h"

PalolaStepper stepper(8, 9, 10, 11);

void setup () {
    Serial.begin(9600);
    Serial.println("Hello World");
    stepper.setArduinoPinsOutput();
}

void loop () {
    Serial.println("loop started...");
    stepper.rotateHOR();
}