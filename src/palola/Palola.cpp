#include "Palola.h"

Palola::Palola() {
    stepper = PalolaStepper(PIN_STEPPER_1, PIN_STEPPER_2, PIN_STEPPER_3, PIN_STEPPER_4);
    //loadSensor = PalolaLoadSensor(PIN_LOAD_SENSOR_DT, PIN_LOAD_SENSOR_SCK);
    led = PalolaLedRGB(PIN_LED_RGB_R, PIN_LED_RGB_G, PIN_LED_RGB_B);
    wifi = PalolaWifi();
    buzzer = PalolaBuzzer(PIN_BUZZER);
}

// Blink the LED to indicate that the system is initializing until all the sensors are ready
void Palola::getReady() {
    Serial.println("Initializing system");
    stepper.setArduinoPinsOutput();
    loadSensor.setArduinoPinsOutput();
    led.setArduinoPinsOutput();
    wifi.connectToWifi();
    buzzer.setArduinoPinsOutput();

    while (
        !loadSensor.isReady() ||
        !wifi.isConnected()
    ) {
        wifi.connectToWifi();
        loadSensor.turnOn();

        led.setMode(LED_INICIALIZING);
        delay(500);
        led.turnOff();
        delay(500);
    } 

    led.setMode(LED_READY);
    buzzer.playWhenReady();
    Serial.println("All systems ready");
}

// Check if it's time to feed the pet
void Palola::checkMeals() {
    if (!wifi.isConnected()) {
        Serial.println("Not connected to WiFi");
        led.setMode(LED_ERROR);
        this->getReady();
        return;
    }

    led.blink(LED_SEARCHING, 500);
    const Meal meal = wifi.getPendingMeal();

    // Check if there are meals pending
    if (meal.id != 0) {
        Serial.println("Found meal of id " + String(meal.id));
        this->feed(meal);
    } else {
        Serial.println("No meals pending");
        led.blink(LED_READY, 500);
    }
}

// Feed the pet
void Palola::feed(Meal meal) {
    Serial.println("Feeding pet");
    led.setMode(LED_SEARCHING);

    // Check if the bowl is full
    // if (!loadSensor.isBowlEmpty()) {
    //     Serial.println("Bowl is full");
    //     led.setMode(LED_ERROR);

    //     meal.status = MEAL_STATUS_FULL;
    //     wifi.finishMeal(meal, this->loadSensor.getWeight());

    //     led.turnOff();
    //     return;
    // }

    led.setMode(LED_FEEDING);

    stepper.dispenseMeal();

    meal.status = MEAL_STATUS_ACCEPTED;
    wifi.finishMeal(meal, 0.623);

    led.setMode(LED_READY);
    buzzer.playWhenMealIsFinished();
    delay(5000);
    led.turnOff();
}