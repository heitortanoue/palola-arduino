#ifndef __PALOLA_STEPPER_H__
#define __PALOLA_STEPPER_H__

#include <Arduino.h>
#define STEPPER_DELAY_PHASE 2         // Intervalo de tempo entre as fases em milisegundos
#define STEPPER_TURNS_FOR_MEAL 2      // Quantidade de voltas do motor para dispensar uma xícara de ração

class PalolaStepper {
    public:
        PalolaStepper();
        PalolaStepper(int pin1, int pin2, int pin3, int pin4);
        void setArduinoPinsOutput();
        void dispenseMeal( float foodQuantity ); 

    private:
        int _pin1;
        int _pin2;
        int _pin3;
        int _pin4;

        void loadMatrixIntoArduino(byte matrix[4]);
        void rotateHOR();
        void rotateAHO();
        void turnOff();
};

#endif