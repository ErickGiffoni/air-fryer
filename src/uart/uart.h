/**
 * @file uart.h
 
 * @author Erick Giffoni (github.com/ErickGiffoni)
 * @brief C module for communication in a Raspberry 4 using UART
 * @version 0.2
 * @date 2022-09-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef  UART_H
#define  UART_H

#define DEVICE_ADDRESS     0x01  // ESP32

#define CODE_23            0x23  // requesting data
#define CODE_16            0x16  // sending    data

#define RES_PKG_LEN        255   // length of response
#define INT_PKG_LEN        9     // 3+4+2
#define FLOAT_PKG_LEN      9

#define SEND_STRING_CODE   0xB3
#define SEND_INT_CODE      0xB1
#define SEND_FLOAT_CODE    0xB2

// SYSTEM COMMANDS

#define REQ_INTERNAL_TEMP_CODE   0xC1  // request internal temperature
#define REQ_REFERENCE_TEMP_CODE  0xC2  // request reference temperature
#define REQ_USER_INPUT_CODE      0xC3  // read user input

#define SEND_CONTROL_SIGNAL      0xD1  // send control signal (4 bytes)
#define SEND_REFERENCE_SIGNAL    0xD2  // send reference signal (4 bytes)
#define SEND_SYSTEM_STATE        0xD3  // send system state: 0->off; 1->on
#define SET_CONTROL_MODE         0xD4  // set control mode: 0->dashboard; 1->terminal (1 byte)
#define SEND_FUNCTIONING_STATE   0xD5  // send functioning state: 0->stoped; 1->working
#define SEND_TIMER_VALUE         0xD6  // send timer value (int)

// USER COMMANDS

#define OVEN_ON         0x01
#define OVEN_OFF        0x02
#define START_HEATING   0x03
#define CANCEL_PROCCESS 0x04
#define TIMER_PLUS_1    0x05
#define TIMER_LESS_1    0x06
#define MENU            0x07

// FUNCTIONS

void openUart(char *path);
void closeUart();
void setCommunicationOptions();
void writeToUart(char *package, int pkgLength);

void setCrc(char *package, int pkgLength);
char verifyCrc(char *package, int pkgLength);

void getResponse();

void sendString(char *message, int msgLength);
void getStringResponse();

void sendInt(int number);
void getIntResponse();

void sendFloat(float number);
void getFloatResponse();

// 2022-09-03

void setStudentId(char *package);
float readInternalTemperature();
float readReferenceTemperature();
void sendControlSignal(int control_signal);
void sendSystemStateSignal(int system_state);
void sendFunctioningStateSignal(int functioning_state);

#endif