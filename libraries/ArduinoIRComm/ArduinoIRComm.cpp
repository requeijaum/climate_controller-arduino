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
  // Dumps out the decode_results structure.
  // Call this after IRrecv::decode()
  int count = results->rawlen;
  /*if (results->decode_type == UNKNOWN) {
    Serial.print("Unknown encoding: ");
  }
  else if (results->decode_type == NEC) {
    Serial.print("Decoded NEC: ");

  }
  else if (results->decode_type == SONY) {
    Serial.print("Decoded SONY: ");
  }
  else if (results->decode_type == RC5) {
    Serial.print("Decoded RC5: ");
  }
  else if (results->decode_type == RC6) {
    Serial.print("Decoded RC6: ");
  }
  else if (results->decode_type == PANASONIC) {
    Serial.print("Decoded PANASONIC - Address: ");
    Serial.print(results->address, HEX);
    Serial.print(" Value: ");
  }
  else if (results->decode_type == LG) {
    Serial.print("Decoded LG: ");
  }
  else if (results->decode_type == JVC) {
    Serial.print("Decoded JVC: ");
  }
  else if (results->decode_type == AIWA_RC_T501) {
    Serial.print("Decoded AIWA RC T501: ");
  }
  else if (results->decode_type == WHYNTER) {
    Serial.print("Decoded Whynter: ");
  }
  Serial.print(results->value, HEX);
  Serial.print(" (");
  Serial.print(results->bits, DEC);
  Serial.println(" bits)");
  Serial.print("Raw (");
  Serial.print(count, DEC);
  Serial.print("): ");*/
    Serial.println(count);
  for (int i = 1; i < count; i++) {
    /*if (i & 1) {
      Serial.print(results->rawbuf[i]*USECPERTICK, DEC);
    }
    else {
      Serial.write('-');
      Serial.print((unsigned long) results->rawbuf[i]*USECPERTICK, DEC);
    }
    Serial.print(" ");*/

    comando[i] = (unsigned long) results->rawbuf[i] * USECPERTICK;
  }
  //Serial.println();
}

void testarIR(String dado, IRSignals x, IRsend irsend/*, arStatus* y*/) {
    //IRsend irsend;
    unsigned int* dadoAtual;
    /*if( dado == "l" ) {
        dadoAtual = x.l;
    }
    if( dado == "d" ) {
        dadoAtual = x.d;
    }
    if( dado == "15" ) {
        dadoAtual = x.t15;
    }
    if( dado == "16" ) {
        dadoAtual = x.t16;
    }
    if( dado == "17" ) {
        dadoAtual = x.t17;
    }
    if( dado == "18" ) {
        dadoAtual = x.t18;
    }
    if( dado == "19" ) {
        dadoAtual = x.t19;
    }
    if( dado == "20" ) {
        dadoAtual = x.t20;
    }
    if( dado == "21" ) {
        dadoAtual = x.t21;
    }
    if( dado == "22" ) {
        dadoAtual = x.t22;
    }*/
    if( dado == "23" ) {
        Serial.println("entrou no 23");
        dadoAtual = x.t23;
    }/*
    if( dado == "24" ) {
        dadoAtual = x.t24;
    }
    if( dado == "25" ) {
        dadoAtual = x.t25;
    }
    if( dado == "26" ) {
        dadoAtual = x.t26;
    }
    if( dado == "27" ) {
        dadoAtual = x.t27;
    }
    if( dado == "28" ) {
        dadoAtual = x.t28;
    }
    if( dado == "29" ) {
        dadoAtual = x.t29;
    }
    if( dado == "30" ) {
        dadoAtual = x.t30;
    }*/
    irsend.sendRaw_P(dadoAtual, sizeof(dadoAtual) / sizeof(dadoAtual[0]), FREQUENCY);
}

void mandarSinalIR(int deltaTemp, IRSignals x, arStatus* y) {
    Serial.println("por enquanto nada...");
}
void mandarSinalIR(String comando, IRSignals x, arStatus* y) {
    Serial.println("por enquanto nada...");
}