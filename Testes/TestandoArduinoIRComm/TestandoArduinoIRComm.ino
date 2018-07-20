
#include <IRremote.h>

int RECV_PIN = 2;

IRrecv irrecv(RECV_PIN);

long a;
#include <String.h>
#include <ArduinoIRComm.h>
IRSignals irsignals;
arStatus arstatus;

void setup() {
  Serial.begin(57600);
}

//int khz = 38; // 38kHz carrier frequency for the NEC protocol
 // unsigned int irSignal[] =  { // 24 graus
 // 4400, 4350, 550, 1600, 550, 550, 550, 1600, 600, 1550, 600, 500, 550, 550, 550, 1600, 550, 550, 550, 500, 600, 1600, 550, 500, 600, 500, 600, 1550, 600, 1600, 550, 500, 600, 1600, 550, 1600, 600, 500, 550, 1600, 600, 1600, 550, 1600, 550, 1600, 600, 1550, 600, 1600, 550, 500, 600, 1600, 550, 500, 600, 500, 600, 500, 550, 550, 550, 500, 600, 500, 600, 500, 550, 1600, 600, 500, 550, 500, 600, 500, 600, 500, 550, 550, 550, 500, 600, 1600, 550, 500, 600, 1600, 550, 1600, 600, 1550, 600, 1600, 550, 1600, 550, 1600, 650, 5100, 4400, 4300, 600, 1600, 550, 500, 600, 1600, 550, 1600, 550, 550, 550, 500, 600, 1600, 550, 500, 600, 500, 600, 1550, 600, 500, 600, 500, 550, 1600, 600, 1550, 600, 500, 600, 1600, 550, 1600, 550, 550, 550, 1600, 600, 1550, 600, 1600, 550, 1600, 550, 1600, 550, 1600, 600, 500, 600, 1550, 600, 500, 600, 500, 550, 550, 550, 500, 550, 550, 550, 550, 550, 500, 600, 1600, 550, 500, 600, 500, 550, 550, 550, 550, 550, 500, 600, 500, 600, 1550, 600, 500, 550, 1650, 550, 1600, 550, 1600, 550, 1600, 550, 1650, 550, 1600, 650
//  };
  
void loop() {
  String texto;
  //irsend.sendRaw(irSignal, sizeof(irSignal) / sizeof(irSignal[0]), khz); //Note the approach used to automatically calculate the size of the array.
  if(Serial.available() > 0) {
    texto = Serial.readString();
      Serial.setTimeout(1000);
        if(texto[0] == 'g') {
          Serial.println("Gravando...");
          gravarIR("23",&irsignals,irrecv);
          Serial.println("gravado...");
        }
        else {
          Serial.println("Testando...");
          mandarSinalIR("23", irsignals , &arstatus);
          Serial.println("testado...");
        }
        
    }
   // delay ( 3000 );
}
