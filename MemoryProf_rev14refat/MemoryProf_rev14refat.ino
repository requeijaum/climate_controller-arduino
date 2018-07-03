#include <MemoryFree.h>
#define JSONOBJECT_JSON_SIZE      (JSON_OBJECT_SIZE(13)) 
#define JSON_OUT_SIZE             128                      //numero de chars do JSON
#define DELAY_MS                  500     //mudei - era 250

#include <ArduinoJson.h>
StaticJsonBuffer<128> jsonBuffer;

  unsigned char json[] = 
    "{\"m\": ,\"p\": ,\"pd1\": ,\"pd2\": ,\"pl1\": ,\"pl2\": ,\"t1\": ,\"t2\": ,\"t3\": ,\"tt\": }";

  JsonObject& root = jsonBuffer.parseObject(json);
  void lerSerial(String texto, char* teste){
    //lê "String texto" vindo da "Serial" e copia para "char texto[JSON_OUT_SIZE]"
    //--> falta implementar anti-DDoS pela porta serial
    if(Serial.available() > 0) {
      //Serial.println(Serial.available());
      texto = Serial.readString();
      //texto = "aa";
      Serial.setTimeout(1000);  //in milliseconds - devo definir isso? evita um tipo de DDoS pela porta serial.
      //Serial.println(texto);
    }  
    texto.getBytes(teste, JSON_OUT_SIZE); 
    //Serial.print("testeleitura = ");
    //Serial.println(teste);    //não precisa imprimir o que recebeu - sem loopback/echo
}

void deserialize(char* jsonstr)
{   
   // if(root.success()) {
   //   Serial.println("sucesso");
   // }
    //else {
    //  Serial.println("SEM SUCESSO");
    //} {"m": 127 ,"p": 1 ,"pd1": "1700" ,"pd2": "1200" ,"pl1": "9999" ,"pl2": "9999" ,"t1": 23 ,"t3": 25 ,"tt": 5 }
    String teste = String(jsonstr);
    //Serial.print("testeconversao = ");
    Serial.println(teste);
    signed int index = -1,indexf = -1,indexl = -1;
    String temp = "";
    if( (index = teste.indexOf("\"m\":")) != -1 ) {
      //Serial.println(index);
      indexf = teste.indexOf(':',index);
      //Serial.println(indexf);
      if( (indexl = teste.indexOf(' ',indexf+2)) != -1) {
        //Serial.println(indexl);
        //Serial.println(teste.substring(indexf+3,indexl));
        if( !root.set("m",teste.substring(indexf+2,indexl).toInt()) ) {
          Serial.println("DEU MERDA A PARADA");
        }
      }
    }
    if( (index = teste.indexOf("\"pd1\":")) != -1 ) {
      //Serial.println(index);
      indexf = teste.indexOf(':',index);
      //Serial.println(indexf);
      if( (indexl = teste.indexOf('"',indexf+3)) != -1) {
        //Serial.println(indexl);
        //Serial.println(teste.substring(indexf+3,indexl));
        if ( !root.set("pd1",teste.substring(indexf+3,indexl)) ) {
          Serial.println("DEU MERDA A PARADA");
        }
      }
    }
    if( (index = teste.indexOf("\"pd2\":")) != -1 ) {
      //Serial.println(index);
      indexf = teste.indexOf(':',index);
      //Serial.println(indexf);
      if( (indexl = teste.indexOf('"',indexf+3)) != -1) {
        //Serial.println(indexl);
        //Serial.println(teste.substring(indexf+3,indexl));
        if ( !root.set("pd2",teste.substring(indexf+3,indexl)) ) {
          Serial.println("DEU MERDA A PARADA");
        }
      }
    }
    if( (index = teste.indexOf("\"pl1\":")) != -1 ) {
      //Serial.println(index);
      indexf = teste.indexOf(':',index);
      //Serial.println(indexf);
      if( (indexl = teste.indexOf('"',indexf+3)) != -1) {
        //Serial.println(indexl);
        //Serial.println(teste.substring(indexf+3,indexl));
        if( !root.set("pl1",teste.substring(indexf+3,indexl)) ) {
          Serial.println("DEU MERDA A PARADA"); 
        }
      }
    }
    if( (index = teste.indexOf("\"pl2\":")) != -1 ) {
      //Serial.println(index);
      indexf = teste.indexOf(':',index);
      //Serial.println(indexf);
      if( (indexl = teste.indexOf('"',indexf+3)) != -1) {
        //Serial.println(indexl);
        //Serial.println(teste.substring(indexf+3,indexl));
        if( !root.set("pl2",teste.substring(indexf+3,indexl)) ) {
          Serial.println("DEU MERDA A PARADA");
        }
      }
    }
    if( (index = teste.indexOf("\"t1\":")) != -1 ) {
      //Serial.println(index);
      indexf = teste.indexOf(':',index);
      //Serial.println(indexf);
      if( (indexl = teste.indexOf(' ',indexf+2)) != -1) {
        //Serial.println(indexl);
        //Serial.println(teste.substring(indexf+3,indexl));
        if ( !root.set("t1",teste.substring(indexf+2,indexl).toInt()) ) {
          Serial.println("DEU MERDA A PARADA");
        }
      }
    }
    if( (index = teste.indexOf("\"t3\":")) != -1 ) {
      //Serial.println(index);
      indexf = teste.indexOf(':',index);
      //Serial.println(indexf);
      if( (indexl = teste.indexOf(' ',indexf+2)) != -1) {
        //Serial.println(indexl);
        //Serial.println(teste.substring(indexf+3,indexl));
        if( !root.set("t3",teste.substring(indexf+2,indexl).toInt()) ){
          Serial.println("DEU MERDA A PARADA");
        }
      }
    }
    if( (index = teste.indexOf("\"tt\":")) != -1 ) {
      //Serial.println(index);
      indexf = teste.indexOf(':',index);
      //Serial.println(indexf);
      if( (indexl = teste.indexOf(' ',indexf+2)) != -1) {
        //Serial.println(indexl);
        //Serial.println(teste.substring(indexf+3,indexl));
        if ( !root.set("tt",teste.substring(indexf+2,indexl).toInt()) ) {
          Serial.println("DEU MERDA A PARADA");
        }
      }
    }
   delay(DELAY_MS);  
   return;
     
}


void serialize()
{
    //root.printTo(json,  maxSize);
    //memcpy(copy , json, maxSize);
    root.printTo(Serial);
    Serial.println();
    delay(DELAY_MS);
    return;
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
   root["pl1"] = "1000";
  root["pd1"] = "1200";
  root["pl2"] = "1630";
  root["pd2"] = "1740";
  root["t3"] = 26;
  root["t1"] = 20;
  root["tt"] = 5;
  root["m"] = 127;
  root["p"] = 1;
}

void loop() {
  // put your main code here, to run repeatedly:
  String    texto;
  char      teste[JSON_OUT_SIZE];
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
