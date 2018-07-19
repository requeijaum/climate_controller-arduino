
#include <IRremote.h>

int RECV_PIN = 2;

IRrecv irrecv(RECV_PIN);

long a;
#include <String.h>
#include <ArduinoIRComm.h>
IRSignals irsignals;

void setup() {
  Serial.begin(57600);
}

  
void loop() {
  String texto;
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
          testarIR("23", irsignals );
          Serial.println("testado...");
        }
        
    }
}
