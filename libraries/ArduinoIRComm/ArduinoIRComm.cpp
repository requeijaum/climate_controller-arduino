// ArduinoIRComm - Lucas Borges

#include "ArduinoIRComm.h"

void gravarIR(String dado, IRSignals* x, IRrecv irrecv) {
    Serial.println("Gravando sinal...");
    decode_results results;
    irrecv.enableIRIn();
    bool flag = false;
    while(!flag) {
        if(irrecv.decode(&results)) {
            irrecv.resume();
            flag = true;
        }
    }
    int count = results.rawlen-1;
    x->irSignalsLength = count;
    if( dado == "l" ) {
        x->l = new unsigned int[count];
        for (int i = 0; i < count; i++) {
            x->l[i] = (unsigned long) results.rawbuf[i+1] * USECPERTICK;
        }
    }
    if( dado == "d" ) {
        x->d = new unsigned int[count];
        for (int i = 0; i < count; i++) {
            x->d[i] = (unsigned long) results.rawbuf[i+1] * USECPERTICK;
        }
    }
    if( dado == "15" ) {
        x->t15 = new unsigned int[count];
        for (int i = 0; i < count; i++) {
            x->t15[i] = (unsigned long) results.rawbuf[i+1] * USECPERTICK;
        }
    }
    if( dado == "16" ) {
        x->t16 = new unsigned int[count];
        for (int i = 0; i < count; i++) {
            x->t16[i] = (unsigned long) results.rawbuf[i+1] * USECPERTICK;
        }
    }
    if( dado == "17" ) {
        x->t17 = new unsigned int[count];
        for (int i = 0; i < count; i++) {
            x->t17[i] = (unsigned long) results.rawbuf[i+1] * USECPERTICK;
        }
    }
    if( dado == "18" ) {
        x->t18 = new unsigned int[count];
        for (int i = 0; i < count; i++) {
            x->t18[i] = (unsigned long) results.rawbuf[i+1] * USECPERTICK;
        }
    }
    if( dado == "19" ) {
        x->t19 = new unsigned int[count];
        for (int i = 0; i < count; i++) {
            x->t19[i] = (unsigned long) results.rawbuf[i+1] * USECPERTICK;
        }
    }
    if( dado == "20" ) {
        x->t20 = new unsigned int[count];
        for (int i = 0; i < count; i++) {
            x->t20[i] = (unsigned long) results.rawbuf[i+1] * USECPERTICK;
        }
    }
    if( dado == "21" ) {
        x->t21 = new unsigned int[count];
        for (int i = 0; i < count; i++) {
            x->t21[i] = (unsigned long) results.rawbuf[i+1] * USECPERTICK;
        }
    }
    if( dado == "22" ) {
        x->t22 = new unsigned int[count];
        for (int i = 0; i < count; i++) {
            x->t22[i] = (unsigned long) results.rawbuf[i+1] * USECPERTICK;
        }
    }
    if( dado.equals("23") ) {
        Serial.println("entrou 23");
        x->t23 = new unsigned int[count];
        for (int i = 0; i < count; i++) {
            x->t23[i] = (unsigned long) results.rawbuf[i+1] * USECPERTICK;
            Serial.println(x->t23[i]);
        }
    }
    if( dado == "24" ) {
        x->t24 = new unsigned int[count];
        for (int i = 0; i < count; i++) {
            x->t24[i] = (unsigned long) results.rawbuf[i+1] * USECPERTICK;
        }
    }
    if( dado == "25" ) {
        x->t25 = new unsigned int[count];
        for (int i = 0; i < count; i++) {
            x->t25[i] = (unsigned long) results.rawbuf[i+1] * USECPERTICK;
        }
    }
    if( dado == "26" ) {
        x->t26 = new unsigned int[count];
        for (int i = 0; i < count; i++) {
            x->t26[i] = (unsigned long) results.rawbuf[i+1] * USECPERTICK;
        }
    }
    if( dado == "27" ) {
        x->t27 = new unsigned int[count];
        for (int i = 0; i < count; i++) {
            x->t27[i] = (unsigned long) results.rawbuf[i+1] * USECPERTICK;
        }
    }
    if( dado == "28" ) {
        x->t28 = new unsigned int[count];
        for (int i = 0; i < count; i++) {
            x->t28[i] = (unsigned long) results.rawbuf[i+1] * USECPERTICK;
        }
    }
    if( dado == "29" ) {
        x->t29 = new unsigned int[count];
        for (int i = 0; i < count; i++) {
            x->t29[i] = (unsigned long) results.rawbuf[i+1] * USECPERTICK;
        }
    }
    if( dado == "30" ) {
        x->t30 = new unsigned int[count];
        for (int i = 0; i < count; i++) {
            x->t30[i] = (unsigned long) results.rawbuf[i+1] * USECPERTICK;
        }
    }
    Serial.println("Sinal gravado.");
}

void mandarSinalIR(String dado, IRSignals x , arStatus* y) {
    IRsend irsend;
    Serial.println("Enviando sinal...");
    if( dado == "l" ) {
        unsigned int a[x.irSignalsLength];
        for(int i=0;i<x.irSignalsLength; i++) {
            a[i] = x.t23[i];

        }
        irsend.sendRaw( a, sizeof(a) / sizeof(a[0]) , FREQUENCY);
        y->ligado = true;
    }
    if( dado == "d" ) {
        unsigned int a[x.irSignalsLength];
        for(int i=0;i<x.irSignalsLength; i++) {
            a[i] = x.t23[i];

        }
        irsend.sendRaw( a, sizeof(a) / sizeof(a[0]) , FREQUENCY);
        y->ligado = false;
    }
    if( dado == "15" ) {
        unsigned int a[x.irSignalsLength];
        for(int i=0;i<x.irSignalsLength; i++) {
            a[i] = x.t23[i];

        }
        irsend.sendRaw( a, sizeof(a) / sizeof(a[0]) , FREQUENCY);
        y->tAtual = 15;
    }
    if( dado == "16" ) {
        unsigned int a[x.irSignalsLength];
        for(int i=0;i<x.irSignalsLength; i++) {
            a[i] = x.t23[i];

        }
        irsend.sendRaw( a, sizeof(a) / sizeof(a[0]) , FREQUENCY);
        y->tAtual = 16;
    }
    if( dado == "17" ) {
        unsigned int a[x.irSignalsLength];
        for(int i=0;i<x.irSignalsLength; i++) {
            a[i] = x.t23[i];

        }
        irsend.sendRaw( a, sizeof(a) / sizeof(a[0]) , FREQUENCY);
        y->tAtual = 17;
    }
    if( dado == "18" ) {
        unsigned int a[x.irSignalsLength];
        for(int i=0;i<x.irSignalsLength; i++) {
            a[i] = x.t23[i];

        }
        irsend.sendRaw( a, sizeof(a) / sizeof(a[0]) , FREQUENCY);
        y->tAtual = 18;
    }
    if( dado == "19" ) {
        unsigned int a[x.irSignalsLength];
        for(int i=0;i<x.irSignalsLength; i++) {
            a[i] = x.t23[i];

        }
        irsend.sendRaw( a, sizeof(a) / sizeof(a[0]) , FREQUENCY);
        y->tAtual = 19;
    }
    if( dado == "20" ) {
        unsigned int a[x.irSignalsLength];
        for(int i=0;i<x.irSignalsLength; i++) {
            a[i] = x.t23[i];

        }
        irsend.sendRaw( a, sizeof(a) / sizeof(a[0]) , FREQUENCY);
        y->tAtual = 20;
    }
    if( dado == "21" ) {
        unsigned int a[x.irSignalsLength];
        for(int i=0;i<x.irSignalsLength; i++) {
            a[i] = x.t23[i];

        }
        irsend.sendRaw( a, sizeof(a) / sizeof(a[0]) , FREQUENCY);
        y->tAtual = 21;
    }
    if( dado == "22" ) {
        unsigned int a[x.irSignalsLength];
        for(int i=0;i<x.irSignalsLength; i++) {
            a[i] = x.t23[i];

        }
        irsend.sendRaw( a, sizeof(a) / sizeof(a[0]) , FREQUENCY);
        y->tAtual = 22;
    }
    if( dado == "23" ) {
        unsigned int a[x.irSignalsLength];
        for(int i=0;i<x.irSignalsLength; i++) {
            a[i] = x.t23[i];

        }
        irsend.sendRaw( a, sizeof(a) / sizeof(a[0]) , FREQUENCY);
        y->tAtual = 23;
    }
    if( dado == "24" ) {
        unsigned int a[x.irSignalsLength];
        for(int i=0;i<x.irSignalsLength; i++) {
            a[i] = x.t23[i];

        }
        irsend.sendRaw( a, sizeof(a) / sizeof(a[0]) , FREQUENCY);
        y->tAtual = 24;
    }
    if( dado == "25" ) {
        unsigned int a[x.irSignalsLength];
        for(int i=0;i<x.irSignalsLength; i++) {
            a[i] = x.t23[i];

        }
        irsend.sendRaw( a, sizeof(a) / sizeof(a[0]) , FREQUENCY);
        y->tAtual = 25;
    }
    if( dado == "26" ) {
        unsigned int a[x.irSignalsLength];
        for(int i=0;i<x.irSignalsLength; i++) {
            a[i] = x.t23[i];

        }
        irsend.sendRaw( a, sizeof(a) / sizeof(a[0]) , FREQUENCY);
        y->tAtual = 26;
    }
    if( dado == "27" ) {
        unsigned int a[x.irSignalsLength];
        for(int i=0;i<x.irSignalsLength; i++) {
            a[i] = x.t23[i];

        }
        irsend.sendRaw( a, sizeof(a) / sizeof(a[0]) , FREQUENCY);
        y->tAtual = 27;
    }
    if( dado == "28" ) {
        unsigned int a[x.irSignalsLength];
        for(int i=0;i<x.irSignalsLength; i++) {
            a[i] = x.t23[i];

        }
        irsend.sendRaw( a, sizeof(a) / sizeof(a[0]) , FREQUENCY);
        y->tAtual = 28;
    }
    if( dado == "29" ) {
        unsigned int a[x.irSignalsLength];
        for(int i=0;i<x.irSignalsLength; i++) {
            a[i] = x.t23[i];

        }
        irsend.sendRaw( a, sizeof(a) / sizeof(a[0]) , FREQUENCY);
        y->tAtual = 29;
    }
    if( dado == "30" ) {
        unsigned int a[x.irSignalsLength];
        for(int i=0;i<x.irSignalsLength; i++) {
            a[i] = x.t23[i];

        }
        irsend.sendRaw( a, sizeof(a) / sizeof(a[0]) , FREQUENCY);
        y->tAtual = 30;
    }
    Serial.println("Sinal enviado.");
}

unsigned int * getPointerSinal (String dado, IRSignals x) {
    if( dado == "l" ) {
        return x.l;
    }
    if( dado == "d" ) {
        return x.d;
    }
    if( dado == "15" ) {
        return x.t15;
    }
    if( dado == "16" ) {
        return x.t16;
    }
    if( dado == "17" ) {
        return x.t17;
    }
    if( dado == "18" ) {
        return x.t18;
    }
    if( dado == "19" ) {
        return x.t19;
    }
    if( dado == "20" ) {
        return x.t20;
    }
    if( dado == "21" ) {
        return x.t21;
    }
    if( dado == "22" ) {
        return x.t22;
    }
    if( dado == "23" ) {
        return x.t23;
    }
    if( dado == "24" ) {
        return x.t24;
    }
    if( dado == "25" ) {
        return x.t25;
    }
    if( dado == "26" ) {
        return x.t26;
    }
    if( dado == "27" ) {
        return x.t27;    
    }
    if( dado == "28" ) {
        return x.t28;
    }
    if( dado == "29" ) {
        return x.t29;
    }
    if( dado == "30" ) {
        return x.t30;
    }
}

void mandarSinalIR(int deltaTemp, IRSignals x, arStatus* y) {
    int proxTemp = (int) y->tAtual + deltaTemp;
    bool flag = true;
    unsigned int * signal = getPointerSinal(String(proxTemp),x);
    while( signal == NULL  ) {
        if(proxTemp == 15 || proxTemp == 30) { // Se estiver na ultima temperatura e ela nao estiver registrada break;
            flag = false;
            break;
        }
        if(deltaTemp > 0) {
            proxTemp++;
        }
        else {
            proxTemp--;
        }
        signal = getPointerSinal(String(proxTemp),x);
    }
    if(flag) {
        mandarSinalIR(String(proxTemp), x, y);
    }
}