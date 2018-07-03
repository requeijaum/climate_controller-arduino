#include <MemoryFree.h>
#include <SoftwareSerial.h> // import the serial library
#include <ArduinoJson.h>

#define JSONOBJECT_JSON_SIZE      (JSON_OBJECT_SIZE(11)) 
#define JSON_OUT_SIZE             128                      //numero de chars do JSON
#define DELAY_MS                  500     //mudei - era 250

uint8_t   i;

//--------------------------------------------------------------------------------------
//estruturas de dados para as variáveis a serem (de)codificadas no objeto JSON

//parece que boolean é uma má ideia e não economiza memória direito
//usar char ou uint8_t
//} {"m": 127 ,"pd1": "1700" ,"pd2": "1200" ,"pl1": "9999" ,"pl2": "9999" ,"t1": 23 ,"t3": 25 ,"tt": 5 }
struct SensorData {
   uint8_t    Pres;
   uint8_t    tTrigger;
   uint8_t    tMin;
   uint8_t    tAtual;
   uint8_t    tMax;
   
};

struct ProgramaHorario { //Auto, Busy, e Status... você acessa "struct SensorData"... 
                         //precisamos economizar memória
  String    pd1;
  String    pd2;
  String    pl1;
  String    pl2; 
  
  uint8_t             mask;
  uint8_t             domingo;
  uint8_t             segunda;
  uint8_t             terca;
  uint8_t             quarta;
  uint8_t             quinta;
  uint8_t             sexta;
  uint8_t             sabado;        
  
};

struct SensorData                  data;   //no rev4_2 era "msg"
struct ProgramaHorario             prog;



//--------------------------------------------------------------------------------------------------------------


void serialize()
{
    StaticJsonBuffer<JSONOBJECT_JSON_SIZE> jsonBuffer;      //preciso mudar o tamanho a depender do JSON
    JsonObject& root = jsonBuffer.createObject();           //ou a depender de "int data.Status"
        root["m"]   = prog.mask;
        root["p"]   = data.Pres;
        root["pd1"] = prog.pd1;
        root["pd2"] = prog.pd2;
        root["pl1"] = prog.pl1;
        root["pl2"] = prog.pl2;
        root["t1"]  = data.tMin;
        root["t2"]  = data.tAtual;
        root["t3"]  = data.tMax;
        root["tt"]  = data.tTrigger;

    root.printTo(Serial);
    Serial.println("");
    delay(DELAY_MS);
    return;
}



void deserialize(unsigned char* json)
{
    StaticJsonBuffer<256> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(json);
   

    if (!root.success()) {
      //Serial.println("parseObject() failed");
      return;
    }
    
    if (root.success()) {
      //Serial.println("parseObject() successful");

     //previne sobrescrever valores na estrutura "nulos ou zeros", 
     //caso não tenha recebido um JSON válido


         if (root.containsKey("m")){
          prog.mask      = root["m"]; 
         }

         if (root.containsKey("p")) {
          data.Pres      = root["p"];
         }

         if (root.containsKey("pd1")) {
          prog.pd1       = root.get<String>("pd1");
          //bfr = root["pd1"];
          //bfr.toCharArray(bfr,4);
         }

         if (root.containsKey("pd2")){
          prog.pd2       = root.get<String>("pd2");
          //bfr = root["pd2"];
          //bfr.toCharArray(bfr,4);
         }

         if (root.containsKey("pl1")) {
          prog.pl1       = root.get<String>("pl1");
          //bfr = root["pl1"];
          //bfr.toCharArray(bfr,4);
         }

         if (root.containsKey("pl2")) {
          prog.pl2       = root.get<String>("pl2");
          //bfr = root["pl2"];
          //bfr.toCharArray(bfr,4); 
         }


         if (root.containsKey("t1")){
          data.tMin      = root["t1"]; 
         }

         if (root.containsKey("t2")){
          data.tAtual    = root["t2"]; 
         }

         if (root.containsKey("t3")){
          data.tMax      = root["t3"]; 
         }

         if (root.containsKey("tt")){
          data.tTrigger  = root["tt"]; 
         }
         
     }
     
   delay(DELAY_MS);  
   return;
     
    }
    void lerSerial(String texto,unsigned char* teste){
    //lê "String texto" vindo da "Serial" e copia para "char texto[JSON_OUT_SIZE]"
    //--> falta implementar anti-DDoS pela porta serial
    if(Serial.available() > 0) {
      //Serial.println(Serial.available());
      texto = Serial.readString();
      //texto = "aa";
      Serial.setTimeout(1000);  //in milliseconds - devo definir isso? evita um tipo de DDoS pela porta serial.
      Serial.println(texto);
    }  
    texto.getBytes(teste, JSON_OUT_SIZE); 
    //Serial.print("testeleitura = ");
    //Serial.println(teste);    //não precisa imprimir o que recebeu - sem loopback/echo
}

void checkbitmask(void) {

  //aí... agora vai?

  if ( (prog.mask & 1) ==   1 ) prog.segunda = 1;
  else prog.segunda = 0;

  if ( (prog.mask & 2) ==   2 ) prog.terca = 1;
  else prog.terca = 0;

  if ( (prog.mask & 4) ==   4 ) prog.quarta = 1;
  else prog.quarta = 0;

  if ( (prog.mask & 8) ==   8 ) prog.quinta = 1;
  else prog.quinta = 0;

  if ( (prog.mask & 16) == 16 ) prog.sexta = 1;
  else prog.sexta = 0;

  if ( (prog.mask & 32) == 32 ) prog.sabado = 1;
  else prog.sabado = 0;

  if ( (prog.mask & 64) == 64 ) prog.domingo = 1;
  else prog.domingo = 0;


}
    
void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);

  prog.pl1      = "1000";
  prog.pd1      = "1200";
  prog.pl2      = "1630";
  prog.pd2      = "1740";
  

  data.tMax     = 26;
  data.tMin     = 20;  
  data.tTrigger = 15; // tempo em minutos para indicar ausencia de pessoas
}

void loop() {
  // put your main code here, to run repeatedly:
  String    texto;
  unsigned char      teste[JSON_OUT_SIZE];

  Serial.println("--start");
  Serial.print("freeMemory()=");
  Serial.println(freeMemory());
  lerSerial(texto, teste);
  Serial.print("freeMemory()=");
  Serial.println(freeMemory());
  deserialize(teste);
  Serial.print("freeMemory()=");
  Serial.println(freeMemory());
  serialize();
  Serial.println("--end");
}
