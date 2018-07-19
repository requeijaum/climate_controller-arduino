// ArduinoIRComm - Lucas Borges

#include <Arduino.h>
#include <String.h>
#include "../IRremote/IRremote.h"

#define FREQUENCY 38

struct sinais {

   //unsigned int l [200];
   //unsigned int d [200];
  // unsigned int t15[200];
   //unsigned int t16[200];
   //unsigned int t17[200];
   //unsigned int t18[200];
   //unsigned int t19[200];
   //unsigned int t20[200];
   //unsigned int t21[200];
   //unsigned int t22[200];
   unsigned int t23[199];
   //unsigned int t24[200];
   //unsigned int t25[200];
   //unsigned int t26[200];
   //unsigned int t27[200];
   //unsigned int t28[200];
   //unsigned int t29[200];
   //unsigned int t30[200];

};

struct status {

    unsigned short int tAtual;
    bool ligado;

};

typedef struct sinais IRSignals;
typedef struct status arStatus;

void gravarIR(String dado, IRSignals* x, IRrecv irrecv);
void record(decode_results *results, unsigned int* comando);

void testarIR(String dado, IRSignals x/*, arStatus* y*/);

void mandarSinalIR(int deltaTemp, IRSignals x, arStatus* y);
void mandarSinalIR(String comando, IRSignals x, arStatus* y);

