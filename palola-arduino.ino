#include "src/stepper/PalolaStepper.h"
#include "src/loadsensor/PalolaLoadSensor.h"
#include "Pins.h"

PalolaStepper stepper(STEPPER_PIN1, STEPPER_PIN2, STEPPER_PIN3, STEPPER_PIN4);

void setup () {
    Serial.begin(9600);
    Serial.println("Hello World");
    stepper.setArduinoPinsOutput();
}

void loop () {
    Serial.println("loop started...");
    stepper.rotateHOR();
}