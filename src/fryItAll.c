#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>

#include "uart/uart.h"
#include "gpio/gpio.h"
#include "pid/pid.h"

FILE *logFile;
time_t time_;

void interuption(int signal);

int main(){

   signal(SIGINT, interuption);

   openUart("/dev/serial0");
   setCommunicationOptions();

   initWiringPi();

   logFile = fopen("../logs/log.csv", "a+");
   time_ = time(NULL);
   struct tm tmTime;

   // LOOP DE CONTROLE DE TEMP.
   while(1){

      // ler temp. interna
      float internal_temperature = readInternalTemperature();
      // ler temp. ref.
      float reference_temperature = readReferenceTemperature();

      // pid
      pid_atualiza_referencia(reference_temperature);

      // pid: get pid -> sinal de controle
      int control_signal = (int) pid_controle(internal_temperature);

      // write logs
      if(logFile!=NULL){
         time_ = time(NULL);
         tmTime = *localtime(&time_);
         fprintf(logFile, "%d-%02d-%02d %02d:%02d:%02d,%.2f,%.2f,%d%%\n", tmTime.tm_mday, tmTime.tm_mon + 1,tmTime.tm_year + 1900, tmTime.tm_hour, tmTime.tm_min, tmTime.tm_sec, internal_temperature, reference_temperature, control_signal);
      }

      // pid: enviar sinal de controle
      sendControlSignal(control_signal);

      // pid: se negativo -> ventoinha
      if(control_signal < 0.0){
         printf("AirFryer: iniciando acionamento de ventoinha");
         control_signal = control_signal > -40 ? 40 : control_signal*(-1);
         coolOvenDown(control_signal);
         heatOvenUp(0);
      }

      // pid: se positivo -> resistencia
      else if(control_signal > 0.0){
         printf("AirFryer: iniciando acionamento da resistencia");
         heatOvenUp(control_signal);
         coolOvenDown(0);
      }

      sendSystemStateSignal(1);
      sendFunctioningStateSignal(1);
   }

   // closeUart();

   return 0;
}

void interuption(int signal){
   printf("Signal %d recebido\nEncerrando..........");

   heatOvenUp(0);
   coolOvenDown(0);
   sendSystemStateSignal(0);
   sendFunctioningStateSignal(0);

   if(logFile!=NULL)
      fclose(logFile);
   else{
      printf("Log file error: %s\n", strerror(errno));
   }

   closeUart();

   printf("\n----- THANK YOU FOR USING THIS AMAZING AIR FRYER -----\n");
   exit(1);
}