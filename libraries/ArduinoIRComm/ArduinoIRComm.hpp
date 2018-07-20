// ArduinoIRComm - Lucas Borges

#include <Arduino.h>
#include <String.h>
#include "../IRremote/IRremote.h"
#include <stdlib.h>
#define FREQUENCY 38

struct sinais {

   unsigned int *   l = NULL;
   unsigned int *   d = NULL;
   unsigned int * t15 = NULL;
   unsigned int * t16 = NULL;
   unsigned int * t17 = NULL;
   unsigned int * t18 = NULL;
   unsigned int * t19 = NULL;
   unsigned int * t20 = NULL;
   unsigned int * t21 = NULL;
   unsigned int * t22 = NULL;
   unsigned int * t23 = NULL;
   unsigned int * t24 = NULL;
   unsigned int * t25 = NULL;
   unsigned int * t26 = NULL;
   unsigned int * t27 = NULL;
   unsigned int * t28 = NULL;
   unsigned int * t29 = NULL;
   unsigned int * t30 = NULL;

   int irSignalsLength;
};

struct status {

    unsigned short int tAtual;
    bool ligado;

};

typedef struct sinais IRSignals;
typedef struct status arStatus;

void gravarIR(String dado, IRSignals* x, IRrecv irrecv);

void mandarSinalIR(String dado, IRSignals x , arStatus* y);


