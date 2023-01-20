#include "src/palola/Palola.h"

Palola palola = Palola();

void setup () {
    Serial.begin(115200);
    palola.getReady();
    palola.checkMeals();
}

unsigned long lastTimeCheck = 0;
unsigned long lastTimeCounter = 0;

bool isSinceLastTime(unsigned int sec, unsigned long lastTime) {
    if(millis() - lastTime > sec * 1000) {
        return true;
    }
    return false;
}

void loop () {
    if (isSinceLastTime(MINUTES_BETWEEN_CHECKS * 60, lastTimeCheck)) {
        lastTimeCheck = millis();
        palola.checkMeals();
    }

    palola.led.blink(LED_INICIALIZING, 500);

    if (isSinceLastTime(1, lastTimeCounter)) {
        lastTimeCounter = millis();
        unsigned long lastTimeCheckSec = (MINUTES_BETWEEN_CHECKS * 60) - ((millis() - lastTimeCheck) / 1000);
        Serial.println((String) "Time until next check: " + (String) (lastTimeCheckSec/60) + (String) ":" + (String) (lastTimeCheckSec%60));
    }
}