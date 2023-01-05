#include "src/palola/Palola.h"

Palola palola = Palola();

void setup () {
    Serial.begin(115200);
    palola.getReady();

}

void loop () {
    palola.checkMeals();
    delay(MINUTES_BETWEEN_CHECKS * 60 * 1000);
}