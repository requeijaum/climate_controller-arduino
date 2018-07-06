#include <IRremote.h>
IRrecv irrecv(2); // Receive on pin 11
decode_results results;

void setup()
{
  Serial.begin(57600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value);
    irrecv.resume(); // Continue receiving
  }
}
