// ArduinoIRComm - Lucas Borges

#include "ArduinoIRComm.h"

void gravarIR(String dado, IRSignals* x, IRrecv irrecv) {
    decode_results results;
    irrecv.enableIRIn();
    unsigned int* dadoAtual;
    /*if( dado == "l" ) {
        dadoAtual = x->l;
    }
    if( dado == "d" ) {
        dadoAtual = x->d;
    }
    if( dado == "15" ) {
        dadoAtual = x->t15;
    }
    if( dado == "16" ) {
        dadoAtual = x->t16;
    }
    if( dado == "17" ) {
        dadoAtual = x->t17;
    }
    if( dado == "18" ) {
        dadoAtual = x->t18;
    }
    if( dado == "19" ) {
        dadoAtual = x->t19;
    }
    if( dado == "20" ) {
        dadoAtual = x->t20;
    }
    if( dado == "21" ) {
        dadoAtual = x->t21;
    }
    if( dado == "22" ) {
        dadoAtual = x->t22;
    }*/
    if( dado.equals("23") ) {
        dadoAtual = x->t23;
    }/*
    if( dado == "24" ) {
        dadoAtual = x->t24;
    }
    if( dado == "25" ) {
        dadoAtual = x->t25;
    }
    if( dado == "26" ) {
        dadoAtual = x->t26;
    }
    if( dado == "27" ) {
        dadoAtual = x->t27;
    }
    if( dado == "28" ) {
        dadoAtual = x->t28;
    }
    if( dado == "29" ) {
        dadoAtual = x->t29;
    }
    if( dado == "30" ) {
        dadoAtual = x->t30;
    }*/
    bool flag = false;
    while(!flag) {
        if(irrecv.decode(&results)) {
            record(&results, dadoAtual);
            irrecv.resume(); // Receive the next value
            flag = true;
        }
    }
}

void record(decode_results *results, unsigned int* comando) {
  int count = results->rawlen-1;
  //comando = malloc (count * sizeof(unsigned long));
  for (int i = 0; i < count; i++) {
    comando[i] = (unsigned long) results->rawbuf[i+1] * USECPERTICK;
  }
  // cinza à direita. (DO LADO DO RECEPTOR);
  // VERDE DIREITA TB
}

void testarIR(String dado,/* unsigned int *  dadoAtual*/ IRSignals x /*, IRsend irsend, arStatus* y*/) {
    IRsend irsend;
    /*if( dado == "l" ) {
        irsend.sendRaw(x.l, sizeof(x.l) / sizeof(x.l[0]), FREQUENCY);
        y.ligado = true;
    }
    if( dado == "d" ) {
        irsend.sendRaw(x.d, sizeof(x.t23) / sizeof(x.d[0]), FREQUENCY);
        y.ligado = false;
    }
    if( dado == "15" ) {
        irsend.sendRaw(x.t15, sizeof(x.t15) / sizeof(x.t15[0]), FREQUENCY);
        y.tAtual = 15;
    }
    if( dado == "16" ) {
        irsend.sendRaw(x.t23, sizeof(x.t23) / sizeof(x.t23[0]), FREQUENCY);
        y.tAtual = 16;
    }
    if( dado == "17" ) {
        irsend.sendRaw(x.t19, sizeof(x.t19) / sizeof(x.t19[0]), FREQUENCY);
        y.tAtual = 17;
    }
    if( dado == "18" ) {
        irsend.sendRaw(x.t18, sizeof(x.t18) / sizeof(x.t18[0]), FREQUENCY);
        y.tAtual = 18;
    }
    if( dado == "19" ) {
        irsend.sendRaw(x.t19, sizeof(x.t19) / sizeof(x.t19[0]), FREQUENCY);
        y.tAtual = 19;
    }
    if( dado == "20" ) {
        irsend.sendRaw(x.t20, sizeof(x.t20) / sizeof(x.t20[0]), FREQUENCY);
        y.tAtual = 20;
    }
    if( dado == "21" ) {
        irsend.sendRaw(x.t21, sizeof(x.t21) / sizeof(x.t21[0]), FREQUENCY);
        y.tAtual = 21;
    }
    if( dado == "22" ) {
        irsend.sendRaw(x.t22, sizeof(x.t22) / sizeof(x.t22[0]), FREQUENCY);
        y.tAtual = 22;
    }*/
    if( dado == "23" ) {
        irsend.sendRaw(x.t23, sizeof(x.t23) / sizeof(x.t23[0]), FREQUENCY);
        //y.tAtual = 23;
    }/*
    if( dado == "24" ) {
        irsend.sendRaw(x.t24, sizeof(x.t24) / sizeof(x.t24[0]), FREQUENCY);
        y.tAtual = 24;
    }
    if( dado == "25" ) {
        irsend.sendRaw(x.t25, sizeof(x.t25) / sizeof(x.t25[0]), FREQUENCY);
        y.tAtual = 25;
    }
    if( dado == "26" ) {
        irsend.sendRaw(x.t26, sizeof(x.t26) / sizeof(x.t26[0]), FREQUENCY);
        y.tAtual = 26;
    }
    if( dado == "27" ) {
        irsend.sendRaw(x.t27, sizeof(x.t27) / sizeof(x.t27[0]), FREQUENCY);
        y.tAtual = 27;
    }
    if( dado == "28" ) {
        irsend.sendRaw(x.t28, sizeof(x.t28) / sizeof(x.t28[0]), FREQUENCY);
        y.tAtual = 28;
    }
    if( dado == "29" ) {
        irsend.sendRaw(x.t29, sizeof(x.t29) / sizeof(x.t29[0]), FREQUENCY);
        y.tAtual = 29;
    }
    if( dado == "30" ) {
        irsend.sendRaw(x.t30, sizeof(x.t30) / sizeof(x.t30[0]), FREQUENCY);
        y.tAtual = 30;
    }*/
}

void mandarSinalIR(int deltaTemp, IRSignals x, arStatus* y) {
   /* int proxTemp = (int) y.tAtual + deltaTemp;
    bool flag = true;
    while(!proxTemp enquanto esta temperatura nao estiver registrada  ) {
        if(proxTemp == 15) { // Se estiver na ultima temperatura e ela nao estiver registrada break;
            flag = false;
            break;
        }
        if(deltaTemp > 0) {
            proxTemp++;
        }
        else {
            proxTemp--;
        }
    }
    if(flag) {
        testarIR(String(proxTemp), x, y);
    }
*/
}
void mandarSinalIR(String comando, IRSignals x, arStatus* y) { // acho que esta função não será necessária....
    Serial.println("por enquanto nada...");
}