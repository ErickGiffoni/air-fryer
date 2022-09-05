#ifndef GPIO_H
#define GPIO_H

#define FAN_PIN   18
#define FAN_GPIO  24
#define FAN_WiPi  5

#define RESISTOR_PIN    16
#define RESISTOR_GPIO   23
#define RESISTOR_WiPi   4

// FUNCTIONS

void initWiringPi();
void coolOvenDown(int control_signal);
void heatOvenUp(int control_signal);

#endif