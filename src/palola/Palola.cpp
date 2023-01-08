#include "Palola.h"

Palola::Palola() {
    stepper = PalolaStepper(PIN_STEPPER_1, PIN_STEPPER_2, PIN_STEPPER_3, PIN_STEPPER_4);
    loadSensor = PalolaLoadSensor(PIN_LOAD_SENSOR_DT, PIN_LOAD_SENSOR_SCK);
    // rtc = PalolaRTC(PIN_RTC_SCL, PIN_RTC_SDA);
    led = PalolaLedRGB(PIN_LED_RGB_R, PIN_LED_RGB_G, PIN_LED_RGB_B);
    wifi = PalolaWifi();
}

// Blink the LED to indicate that the system is initializing until all the sensors are ready
void Palola::getReady() {
    stepper.setArduinoPinsOutput();
    loadSensor.setArduinoPinsOutput();
    led.setArduinoPinsOutput();
    // rtc.setArduinoPinsOutput();
    wifi.connectToWifi();

    while (
        // !rtc.isReady() ||
        !loadSensor.isReady() ||
        !wifi.isConnected()
    ) {
        led.setMode(LED_INICIALIZING);
        delay(500);
        led.turnOff();
        delay(500);
    } 
}

// Check if it's time to feed the pet
void Palola::checkMeals() {
    led.blink(LED_SEARCHING, 500);
    const Meal meal = wifi.getPendingMeal();

    // Check if there are meals pending
    if (meal.id != 0) {
        this->feed();
    } else {
        led.blink(LED_ERROR, 500);
    }
}

// Feed the pet
void Palola::feed() {
    led.setMode(LED_SEARCHING);

    // Check if the bowl is full
    if (!loadSensor.isBowlEmpty()) {
        led.setMode(LED_ERROR);
        wifi.finishMeal(MEAL_STATUS_FULL);
        led.turnOff();
        return;
    }

    wifi.startMeal();
    led.setMode(LED_FEEDING);

    stepper.dispenseMeal();

    wifi.finishMeal(MEAL_STATUS_ACCEPTED);

    led.setMode(LED_READY);
    delay(5000);
    led.turnOff();
}