#include <IRremote.h>
IRrecv irrecv(2); // Receive on pin 11
decode_results results;

void setup()
{
  Serial.begin(57600);
  irrecv.enableIRIn(); // Start the receiver
}

/*
 typedef
 enum {
    UNKNOWN      = -1,
    UNUSED       =  0,
    RC5,//1
    RC6,//2
    NEC,//3
    SONY,//4
    PANASONIC,//5
    JVC,//6
    SAMSUNG,//7
    WHYNTER,//8
    AIWA_RC_T501,//9
    LG,//10
    SANYO,//11
    MITSUBISHI,//12
    DISH,//13
    SHARP,//14
    DENON,//15
    PRONTO,//16
  }
decode_type_t;
 */
void loop() {
  if (irrecv.decode(&results)) {
     Serial.println("Results:");
  Serial.println("------------------");  
  Serial.print("Received: ");
  Serial.println(results.value);
  Serial.print("Received (HEX):");
  Serial.println(results.value, HEX);
  Serial.print("Decode type:");
  Serial.println(results.decode_type);   
  Serial.print("Number of items:");
  Serial.println(results.rawlen); 
  Serial.println(""); 
  irrecv.resume(); 
  }
}
