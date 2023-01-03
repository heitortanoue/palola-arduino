#ifndef __PALOLA_STEPPER_H__
#define __PALOLA_STEPPER_H__

#include <Arduino.h>
#define ATRASO_FASE 2         // Intervalo de tempo entre as fases em milisegundos

class PalolaStepper {
    public:
        PalolaStepper(int pin1, int pin2, int pin3, int pin4);
        void rotateHOR();
        void rotateAHO();
        void setArduinoPinsOutput();
    private:
        int _pin1;
        int _pin2;
        int _pin3;
        int _pin4;

        void loadMatrixIntoArduino(byte matrix[4]);
};

#endif