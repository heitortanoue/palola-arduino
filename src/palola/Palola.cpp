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

    led.setMode(LED_SEARCHING);
    const Meal meal = wifi.getPendingMeal();

    // if (meal.status == MEAL_STATUS_REJECTED) {
    //     Serial.println("Error getting pending meal");
    //     led.setMode(LED_ERROR);
    //     delay(5000);
    //     return;
    // }

    // Check if there are meals pending
    if (meal.id != 0) {
        Serial.println("Found meal of id " + String(meal.id));
        // Serial.println((String) "Last meal id: " + (String) _lastMealId);
        // if (meal.id == _lastMealId) {
        //     Serial.println("Meal already accepted before");
        //     led.setMode(LED_ERROR);
        //     wifi.finishMeal(meal, 0.623);
        //     return;
        // }
        this->feed(meal);
        // _lastMealId = meal.id;
    } else {
        Serial.println("No meals pending");
        led.setMode(LED_READY);
        delay(5000);
    }
}

// Feed the pet
void Palola::feed(Meal meal) {
    Serial.println("Feeding pet");

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

    stepper.dispenseMeal(meal.foodQuantity);

    meal.status = MEAL_STATUS_ACCEPTED;
    wifi.finishMeal(meal, 0.623);

    led.setMode(LED_READY);
    buzzer.playWhenMealIsFinished();
    delay(5000);
    led.turnOff();
}