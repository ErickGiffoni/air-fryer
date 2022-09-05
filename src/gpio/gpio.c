#include "gpio.h"

#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>

// FUNCTIONS

void initWiringPi(){
   wiringPiSetup();
   pinMode(FAN_WiPi, OUTPUT);
   pinMode(RESISTOR_WiPi, OUTPUT);

   softPwmCreate(FAN_WiPi,1,100);
   softPwmCreate(RESISTOR_WiPi,1,100);

   return;
}

/**
 * Controle da ventoinha
 */
void coolOvenDown(int control_signal){
   softPwmWrite (FAN_WiPi, control_signal);
   // heatOvenUp(0);
   return;
}

/**
 * Controle do resistor
 */
void heatOvenUp(int control_signal){
   softPwmWrite (RESISTOR_WiPi, control_signal);
   // coolOvenDown(0);
   return;
}