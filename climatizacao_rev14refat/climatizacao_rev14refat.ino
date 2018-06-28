//#include <Flash.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h> // import the serial library
#include <String.h>

#define JSONOBJECT_JSON_SIZE      (JSON_OBJECT_SIZE(13)) 
#define JSON_OUT_SIZE             128                      //numero de chars do JSON

#define pinPres                   12      //igual a pirPin

#define DELAY_MS                  100     //mudei - era 250
#define DELAY_LED                 250     //mudei - era 300
#define DELAY_IR                  250     //mudei - era 500

uint8_t   i;

//--------------------------------------------------------------------------------------
//estruturas de dados para as variáveis a serem (de)codificadas no objeto JSON

//parece que boolean é uma má ideia e não economiza memória direito
//usar char ou uint8_t


//Vamos tentar começar... Refatoração do código.
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
    //Serial.println(teste);
    signed int index,indexf,indexl;
    String temp;
    if( (index = teste.indexOf("\"m\":")) != -1 ) {
      //Serial.println(index);
      indexf = teste.indexOf(':',index);
      //Serial.println(indexf);
      if( (indexl = teste.indexOf(' ',indexf+2)) != -1) {
        //Serial.println(indexl);
        //Serial.println(teste.substring(indexf+3,indexl));
        root.set("m",teste.substring(indexf+2,indexl).toInt());
      }
    }
    if( (index = teste.indexOf("\"p\":")) != -1 ) {
      //Serial.println(index);
      indexf = teste.indexOf(':',index);
      //Serial.println(indexf);
      if( (indexl = teste.indexOf(' ',indexf+2)) != -1) {
        //Serial.println(indexl);
        //Serial.println(teste.substring(indexf+3,indexl));
        root.set("p",teste.substring(indexf+2,indexl).toInt());
      }
    }
    if( (index = teste.indexOf("\"pd1\":")) != -1 ) {
      //Serial.println(index);
      indexf = teste.indexOf(':',index);
      //Serial.println(indexf);
      if( (indexl = teste.indexOf('"',indexf+3)) != -1) {
        //Serial.println(indexl);
        //Serial.println(teste.substring(indexf+3,indexl));
        root.set("pd1",teste.substring(indexf+3,indexl));
      }
    }
    if( (index = teste.indexOf("\"pd2\":")) != -1 ) {
      //Serial.println(index);
      indexf = teste.indexOf(':',index);
      //Serial.println(indexf);
      if( (indexl = teste.indexOf('"',indexf+3)) != -1) {
        //Serial.println(indexl);
        //Serial.println(teste.substring(indexf+3,indexl));
        root.set("pd2",teste.substring(indexf+3,indexl));
      }
    }
    if( (index = teste.indexOf("\"pl1\":")) != -1 ) {
      //Serial.println(index);
      indexf = teste.indexOf(':',index);
      //Serial.println(indexf);
      if( (indexl = teste.indexOf('"',indexf+3)) != -1) {
        //Serial.println(indexl);
        //Serial.println(teste.substring(indexf+3,indexl));
        root.set("pl1",teste.substring(indexf+3,indexl));
      }
    }
    if( (index = teste.indexOf("\"pl2\":")) != -1 ) {
      //Serial.println(index);
      indexf = teste.indexOf(':',index);
      //Serial.println(indexf);
      if( (indexl = teste.indexOf('"',indexf+3)) != -1) {
        //Serial.println(indexl);
        //Serial.println(teste.substring(indexf+3,indexl));
        root.set("pl2",teste.substring(indexf+3,indexl));
      }
    }
    if( (index = teste.indexOf("\"t1\":")) != -1 ) {
      //Serial.println(index);
      indexf = teste.indexOf(':',index);
      //Serial.println(indexf);
      if( (indexl = teste.indexOf(' ',indexf+2)) != -1) {
        //Serial.println(indexl);
        //Serial.println(teste.substring(indexf+3,indexl));
        root.set("t1",teste.substring(indexf+2,indexl).toInt());
      }
    }
    if( (index = teste.indexOf("\"t3\":")) != -1 ) {
      //Serial.println(index);
      indexf = teste.indexOf(':',index);
      //Serial.println(indexf);
      if( (indexl = teste.indexOf(' ',indexf+2)) != -1) {
        //Serial.println(indexl);
        //Serial.println(teste.substring(indexf+3,indexl));
        root.set("t3",teste.substring(indexf+2,indexl).toInt());
      }
    }
    if( (index = teste.indexOf("\"tt\":")) != -1 ) {
      //Serial.println(index);
      indexf = teste.indexOf(':',index);
      //Serial.println(indexf);
      if( (indexl = teste.indexOf(' ',indexf+2)) != -1) {
        //Serial.println(indexl);
        //Serial.println(teste.substring(indexf+3,indexl));
        root.set("tt",teste.substring(indexf+2,indexl).toInt());
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



//--------------------------------------------------------------------------------------------------------------


#include <OneWire.h>
#include <DallasTemperature.h>

#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;

// FSM states
#define STATE_OFF  0
#define STATE_ON   1

// Timer settings
#define START_TIME  root.get<int>("pl1")//700//prog.pl1
#define END_TIME    root.get<int>("pd1")//1800//prog.pd1

//int
char    fsm_state;

//char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// LED INFRAVERMELHO USAR O PINO 3 (TIMER 2) DO ARDUINO
#define IR_USE_TIMER2
// Data wire is plugged into port 2 on the Arduino

#define pirPin        12
#define ledRed        5
#define ledBlue       10
#define ledGreen      6
#define IR_LED        3
#define IR_Remote     2
#define rele          9
#define pinTemp       4

#define TEMPERATURA_IDEAL   root.get<int>("t3")//23.0//data.tMax    //era 23.0
#define TEMP_MIN            root.get<int>("t1")//22.5//data.tMin    //era 22.5  //só posso usar int no json

//#define TEMPO_TRIGGER 5400000  // 60*60*15
//#define TEMPO_TRIGGER   300000  // 5 minutos //enviar pro JSON  
#define TEMPO_TRIGGER root.get<int>("tt")//data.tTrigger

#define deltaTEMP  1.5


// Temperatura

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(pinTemp);
#define TEMPERATURE_PRECISION 12

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
DeviceAddress tempDeviceAddress; // We'll use this variable to store a found device address

// Controle remoto
#include <IRremote.h>

IRsend irsend;

//int 
char khz = 38; // 38kHz carrier frequency for the NEC protocol
//----------------------------------

/*
 * SUBSTITUIR OS ARRAYS DE LIGAR_AR e DESLIGAR_AR usando a biblioteca flash
 */


static const unsigned int irSignal_Ligar_Ar[] PROGMEM = {
  4500, 4250, 600, 1550, 650, 450, 600, 1550, 650, 1500, 
  650, 450, 650, 450, 600, 1550, 650, 450, 600, 500, 600, 
  1550, 650, 450, 600, 450, 650, 1550, 600, 1550, 650, 
  450, 600, 1550, 650, 1500, 650, 450, 650, 1500, 650, 
  1550, 600, 1550, 650, 1500, 650, 1550, 600, 1550, 600, 
  500, 600, 1550, 650, 450, 600, 450, 650, 450, 650, 450, 
  600, 450, 650, 450, 650, 1550, 600, 1550, 650, 450, 600, 
  450, 650, 450, 650, 450, 600, 450, 650, 450, 650, 450, 
  650, 450, 600, 1550, 650, 1500, 650, 1550, 600, 1550, 
  650, 1500, 650, 1550, 600, 5100, 4500, 4250, 600, 1550, 
  650, 450, 600, 1550, 650, 1500, 650, 450, 650, 450, 600, 
  1550, 650, 450, 600, 500, 600, 1550, 650, 450, 600, 450, 
  650, 1550, 600, 1550, 650, 450, 600, 1550, 650, 1500, 650, 
  450, 650, 1500, 650, 1550, 600, 1550, 650, 1500, 650, 1500, 
  650, 1550, 600, 500, 600, 1550, 600, 450, 650, 450, 650, 450, 
  650, 450, 600, 450, 650, 450, 650, 1500, 650, 1550, 600, 
  450, 650, 450, 650, 450, 650, 450, 600, 450, 650, 450, 650, 
  450, 600, 450, 650, 1550, 600, 1550, 650, 1500, 650, 1550, 
  600, 1550, 650, 1500, 600}; // SAMSUNG B24DBF40


/*
FLASH_ARRAY(unsigned int, irSignal_Ligar_Ar, 4500, 4250, 600, 1550, 650, 
  450, 600, 1550, 650, 1500, 650, 450, 650, 450, 600, 1550, 650, 450, 600, 
  500, 600, 1550, 650, 450, 600, 450, 650, 1550, 600, 1550, 650, 450, 600, 
  1550, 650, 1500, 650, 450, 650, 1500, 650, 1550, 600, 1550, 650, 1500, 
  650, 1550, 600, 1550, 600, 500, 600, 1550, 650, 450, 600, 450, 650, 450, 
  650, 450,  600, 450, 650, 450, 650, 1550, 600, 1550, 650, 450, 600, 
  450, 650, 450, 650, 450, 600, 450, 650, 450, 650, 450, 
  650, 450, 600, 1550, 650, 1500, 650, 1550, 600, 1550, 
  650, 1500, 650, 1550, 600, 5100, 4500, 4250, 600, 1550, 
  650, 450, 600, 1550, 650, 1500, 650, 450, 650, 450, 600, 
  1550, 650, 450, 600, 500, 600, 1550, 650, 450, 600, 450, 
  650, 1550, 600, 1550, 650, 450, 600, 1550, 650, 1500, 650, 
  450, 650, 1500, 650, 1550, 600, 1550, 650, 1500, 650, 1500, 
  650, 1550, 600, 500, 600, 1550, 600, 450, 650, 450, 650, 450, 
  650, 450, 600, 450, 650, 450, 650, 1500, 650, 1550, 600, 
  450, 650, 450, 650, 450, 650, 450, 600, 450, 650, 450, 650, 
  450, 600, 450, 650, 1550, 600, 1550, 650, 1500, 650, 1550, 
  600, 1550, 650, 1500, 600 );
*/


static const unsigned int irSignal_Desligar_Ar[] PROGMEM = {
  4450, 4300, 600, 1550, 650, 450, 600, 1550, 650, 1500, 
  650, 450, 650, 450, 600, 1550, 650, 450, 600, 500, 600, 
  1550, 650, 450, 600, 450, 650, 1550, 600, 1550, 650, 
  450, 600, 1550, 650, 450, 600, 1550, 650, 1500, 650, 
  1550, 600, 1550, 650, 450, 600, 1550, 650, 1500, 650, 
  1550, 600, 450, 650, 450, 650, 450, 600, 500, 600, 1550, 
  600, 500, 600, 450, 650, 1550, 600, 1550, 650, 1500, 650, 
  450, 650, 450, 600, 450, 650, 450, 650, 450, 600, 500, 
  600, 450, 650, 450, 650, 1500, 650, 1550, 600, 1550, 650, 
  1500, 650, 1500, 600, 5150, 4500, 4250, 600, 1550, 650, 
  450, 600, 1550, 650, 1500, 650, 450, 650, 450, 600, 1550, 
  650, 450, 600, 450, 650, 1550, 600, 500, 600, 450, 650, 1550, 
  600, 1550, 600, 500, 600, 1550, 650, 450, 600, 1550, 650, 
  1500, 650, 1500, 650, 1550, 600, 450, 650, 1550, 650, 1500, 
  650, 1550, 600, 450, 650, 450, 650, 450, 600, 450, 650, 1550, 
  600, 450, 650, 450, 650, 1550, 600, 1550, 600, 1550, 650, 450, 
  600, 500, 600, 450, 650, 450, 650, 450, 600, 450, 650, 450, 
  650, 450, 650, 1500, 650, 1500, 650, 1550, 600, 1550, 
  650, 1500, 600}; // SAMSUNG B24D7B84

/*
FLASH_ARRAY(unsigned int, irSignal_Desligar_Ar, 4450, 4300, 600, 1550, 650, 
  450, 600, 1550, 650, 1500, 
  650, 450, 650, 450, 600, 1550, 650, 450, 600, 500, 600, 
  1550, 650, 450, 600, 450, 650, 1550, 600, 1550, 650, 
  450, 600, 1550, 650, 450, 600, 1550, 650, 1500, 650, 
  1550, 600, 1550, 650, 450, 600, 1550, 650, 1500, 650, 
  1550, 600, 450, 650, 450, 650, 450, 600, 500, 600, 1550, 
  600, 500, 600, 450, 650, 1550, 600, 1550, 650, 1500, 650, 
  450, 650, 450, 600, 450, 650, 450, 650, 450, 600, 500, 
  600, 450, 650, 450, 650, 1500, 650, 1550, 600, 1550, 650, 
  1500, 650, 1500, 600, 5150, 4500, 4250, 600, 1550, 650, 
  450, 600, 1550, 650, 1500, 650, 450, 650, 450, 600, 1550, 
  650, 450, 600, 450, 650, 1550, 600, 500, 600, 450, 650, 1550, 
  600, 1550, 600, 500, 600, 1550, 650, 450, 600, 1550, 650, 
  1500, 650, 1500, 650, 1550, 600, 450, 650, 1550, 650, 1500, 
  650, 1550, 600, 450, 650, 450, 650, 450, 600, 450, 650, 1550, 
  600, 450, 650, 450, 650, 1550, 600, 1550, 600, 1550, 650, 450, 
  600, 500, 600, 450, 650, 450, 650, 450, 600, 450, 650, 450, 
  650, 450, 650, 1500, 650, 1500, 650, 1550, 600, 1550, 
  650, 1500, 600);
*/

/*
  unsigned int irSignal_Descer_Temp[] = { // 21 graus
  4450, 4250, 650, 1500, 650, 450, 650, 1500, 650, 1550, 600, 450, 650, 450, 650, 1500, 650, 450, 650, 450, 600, 1550, 650, 450, 650, 450, 600, 1550, 650, 1500, 650, 450, 650, 1500, 650, 1550, 600, 450, 650, 1550, 600, 1550, 650, 1500, 650, 1500, 650, 1550, 600, 1550, 600, 500, 600, 1550, 650, 450, 600, 450, 650, 450, 650, 450, 650, 450, 600, 450, 650, 450, 650, 1500, 650, 1550, 600, 450, 650, 450, 650, 450, 600, 450, 650, 450, 650, 1500, 650, 450, 650, 450, 650, 1500, 650, 1500, 650, 1550, 600, 1550, 650, 1500, 600, 5150, 4450, 4250, 650, 1500, 650, 450, 650, 1500, 650, 1500, 650, 450, 650, 450, 650, 1500, 650, 450, 650, 450, 600, 1550, 650, 450, 600, 450, 650, 1550, 600, 1550, 650, 450, 600, 1550, 650, 1500, 650, 450, 650, 1500, 650, 1550, 600, 1550, 650, 1500, 650, 1550, 600, 1550, 650, 450, 600, 1550, 650, 450, 600, 450, 650, 450, 650, 450, 600, 450, 650, 450, 650, 450, 650, 1500, 650, 1500, 650, 450, 650, 450, 650, 450, 600, 450, 650, 450, 650, 1500, 650, 450, 650, 450, 600, 1550, 650, 1500, 650, 1500, 650, 1550, 600, 1550, 600
  };  // SAMSUNG B24DBF40
*/

/*
  unsigned int irSignal_Descer_Temp[] = { // 18 graus
  4400, 4350, 550, 1600, 550, 550, 550, 1600, 600, 1550, 600, 500, 550, 550, 550, 1600, 600, 500, 550, 550, 550, 1600, 550, 550, 550, 500, 550, 1650, 550, 1600, 550, 550, 550, 1600, 550, 1600, 550, 550, 550, 1600, 600, 1600, 550, 1600, 550, 1600, 550, 1600, 600, 1600, 550, 550, 550, 1600, 550, 500, 600, 500, 550, 550, 550, 550, 550, 500, 550, 550, 550, 550, 550, 550, 550, 500, 550, 1650, 550, 500, 550, 550, 550, 550, 550, 500, 550, 1650, 550, 1600, 550, 1600, 550, 550, 550, 1600, 550, 1650, 550, 1600, 550, 1600, 650, 5100, 4400, 4300, 550, 1650, 550, 500, 550, 1650, 550, 1600, 550, 550, 550, 500, 550, 1650, 550, 500, 550, 550, 550, 1650, 550, 500, 550, 550, 550, 1600, 550, 1600, 600, 500, 550, 1650, 550, 1600, 550, 550, 550, 1600, 550, 1600, 550, 1650, 550, 1600, 550, 1600, 550, 1600, 550, 550, 550, 1600, 550, 550, 550, 550, 550, 550, 550, 500, 550, 550, 550, 550, 550, 500, 600, 500, 550, 550, 550, 1600, 550, 550, 550, 550, 550, 500, 550, 550, 550, 1600, 600, 1600, 550, 1600, 550, 550, 550, 1600, 550, 1600, 550, 1650, 550, 1600, 650
  };
*/



/*
  unsigned int irSignal_Aumentar_Temp[] = { // 26 graus
  4450, 4300, 600, 1550, 600, 500, 600, 1550, 600, 1550, 600, 500, 600, 500, 600, 1550, 600, 500, 600, 450, 650, 1550, 600, 450, 650, 450, 650, 1500, 650, 1550, 600, 450, 650, 1550, 600, 1550, 600, 500, 650, 1500, 600, 1550, 650, 1550, 600, 1550, 600, 1550, 650, 1550, 600, 450, 600, 1600, 600, 450, 600, 500, 600, 500, 600, 450, 650, 450, 600, 500, 600, 1550, 600, 1600, 600, 450, 650, 1550, 600, 450, 650, 450, 650, 450, 600, 500, 600, 450, 650, 450, 600, 1550, 650, 450, 600, 1550, 650, 1550, 600, 1550, 600, 1550, 600, 5150, 4450, 4250, 600, 1550, 650, 450, 600, 1600, 600, 1550, 600, 450, 650, 450, 600, 1550, 650, 450, 650, 450, 650, 1500, 600, 500, 600, 500, 600, 1550, 650, 1500, 600, 500, 600, 1550, 650, 1550, 600, 450, 650, 1550, 600, 1550, 650, 1500, 650, 1550, 600, 1550, 600, 1550, 600, 500, 600, 1550, 600, 500, 650, 450, 600, 450, 600, 500, 600, 500, 600, 450, 650, 1550, 600, 1550, 600, 500, 600, 1550, 600, 500, 650, 450, 600, 450, 600, 500, 600, 500, 600, 450, 650, 1550, 600, 500, 600, 1550, 650, 1500, 600, 1550, 650, 1550, 600
  }; // SAMSUNG B24DBF40

*/

/*unsigned int irSignal_Aumentar_Temp[] = { // 24 graus
  4400, 4350, 550, 1600, 550, 550, 550, 1600, 600, 1550, 600, 500, 550, 550, 550, 1600, 550, 550, 550, 500, 600, 1600, 550, 500, 600, 500, 600, 1550, 600, 1600, 550, 500, 600, 1600, 550, 1600, 600, 500, 550, 1600, 600, 1600, 550, 1600, 550, 1600, 600, 1550, 600, 1600, 550, 500, 600, 1600, 550, 500, 600, 500, 600, 500, 550, 550, 550, 500, 600, 500, 600, 500, 550, 1600, 600, 500, 550, 500, 600, 500, 600, 500, 550, 550, 550, 500, 600, 1600, 550, 500, 600, 1600, 550, 1600, 600, 1550, 600, 1600, 550, 1600, 550, 1600, 650, 5100, 4400, 4300, 600, 1600, 550, 500, 600, 1600, 550, 1600, 550, 550, 550, 500, 600, 1600, 550, 500, 600, 500, 600, 1550, 600, 500, 600, 500, 550, 1600, 600, 1550, 600, 500, 600, 1600, 550, 1600, 550, 550, 550, 1600, 600, 1550, 600, 1600, 550, 1600, 550, 1600, 550, 1600, 600, 500, 600, 1550, 600, 500, 600, 500, 550, 550, 550, 500, 550, 550, 550, 550, 550, 500, 600, 1600, 550, 500, 600, 500, 550, 550, 550, 550, 550, 500, 600, 500, 600, 1550, 600, 500, 550, 1650, 550, 1600, 550, 1600, 550, 1600, 550, 1650, 550, 1600, 650
  };  // SAMSUNG B24DBF40
*/
// Codigo abaixo p/ 27 graus
//unsigned int irSignal_Aumentar_Temp[] = {
//  4450, 4250, 650, 1500, 650, 450, 650, 1500, 650, 1500, 650, 450, 650, 450, 650, 1500, 650, 450, 650, 450, 600, 1550, 650, 450, 600, 450, 650, 1550, 600, 1550, 650, 450, 600, 1550, 650, 1500, 650, 450, 650, 1550, 600, 1550, 600, 1550, 650, 1500, 650, 1550, 600, 1550, 650, 450, 600, 1550, 650, 450, 600, 450, 650, 450, 650, 450, 600, 450, 650, 450, 650, 1550, 600, 450, 650, 450, 650, 1500, 650, 450, 650, 450, 600, 450, 650, 450, 650, 450, 650, 1500, 650, 1500, 650, 450, 650, 1550, 600, 1550, 600, 1550, 650, 1500, 600, 5150, 4450, 4250, 650, 1550, 600, 450, 650, 1550, 650, 1500, 650, 450, 600, 500, 600, 1550, 600, 500, 600, 450, 650, 1550, 600, 450, 650, 450, 650, 1500, 650, 1550, 600, 450, 650, 1550, 600, 1550, 650, 450, 600, 1550, 650, 1500, 650, 1550, 600, 1550, 650, 1500, 650, 1500, 650, 450, 650, 1500, 650, 450, 650, 450, 650, 450, 600, 450, 650, 450, 650, 450, 600, 1550, 650, 450, 650, 450, 600, 1550, 600, 450, 650, 450, 650, 450, 650, 450, 600, 450, 650, 1550, 600, 1550, 650, 450, 600, 1550, 650, 1500, 650, 1550, 600, 1550, 550
//};  // SAMSUNG B24DBF40

//unsigned int abaixarTemp[] = {
//  4450,4300, 600,1550, 650,450, 600,1550, 650,1500, 650,450, 650,450, 600,1550, 650,450, 600,450, 650,1550, 650,450, 600,450, 650,1550, 600,1550, 650,450, 600,1550, 650,1500, 650,450, 650,1500, 650,1550, 600,1550, 650,1500, 650,1550, 600,1550, 650,450, 600,1550, 650,450, 600,450, 650,450, 650,450, 600,450, 650,450, 650,450, 650,1500, 650,1500, 650,1550, 600,450, 650,450, 650,450, 650,450, 600,1550, 650,450, 600,500, 600,450, 650,1550, 600,1550, 650,1500, 650,1500, 600,5150, 4500,4250, 600,1550, 650,450, 600,1550, 650,1500, 650,450, 650,450, 600,1550, 650,450, 600,500, 600,1550, 650,450, 600,450, 650,1550, 600,1550, 650,450, 600,1550, 650,1500, 650,450, 650,1500, 650,1550, 600,1550, 650,1500, 650,1550, 600,1550, 650,450, 600,1550, 650,450, 600,450, 650,450, 650,450, 600,450, 650,450, 650,450, 650,1500, 650,1500, 650,1550, 600,450, 650,450, 650,450, 650,450, 600,1550, 650,450, 600,450, 650,450, 650,1550, 600,1550, 650,1500, 650,1500, 600}; // 0xB24D7B84;

//unsigned int desligarAr[] = {
//4450,4300, 600,1550, 650,450, 600,1550, 650,1500, 650,450, 650,450, 600,1550, 650,450, 600,450, 650,1550, 650,450, 600,450, 650,1550, 600,1550, 650,450, 600,1550, 650,1500, 650,450, 650,1500, 650,1550, 600,1550, 650,1500, 650,1550, 600,1550, 650,450, 600,1550, 650,450, 600,450, 650,450, 650,450, 600,450, 650,450, 650,450, 650,1500, 650,1500, 650,1550, 600,450, 650,450, 650,450, 650,450, 600,1550, 650,450, 600,500, 600,450, 650,1550, 600,1550, 650,1500, 650,1500, 600,5150, 4500,4250, 600,1550, 650,450, 600,1550, 650,1500, 650,450, 650,450, 600,1550, 650,450, 600,500, 600,1550, 650,450, 600,450, 650,1550, 600,1550, 650,450, 600,1550, 650,1500, 650,450, 650,1500, 650,1550, 600,1550, 650,1500, 650,1550, 600,1550, 650,450, 600,1550, 650,450, 600,450, 650,450, 650,450, 600,450, 650,450, 650,450, 650,1500, 650,1500, 650,1550, 600,450, 650,450, 650,450, 650,450, 600,1550, 650,450, 600,450, 650,450, 650,1550, 600,1550, 650,1500, 650,1500, 600};
//unsigned int ligarAr[] = {
//  4400,4300, 600,1550, 600,500, 600,1550, 600,1550, 650,450, 600,500, 600,1550, 600,500, 600,500, 600,1550, 600,500, 600,450, 650,1550, 600,1550, 650,450, 600,1550, 600,1550, 650,450, 650,1500, 650,1550, 600,1550, 600,1550, 600,1600, 600,1550, 600,500, 600,1550, 650,450, 600,450, 600,500, 600,500, 600,450, 650,450, 600,500, 650,450, 600,450, 650,1550, 600,450, 650,450, 600,500, 600,500, 600,1550, 650,1500, 600,1550, 650,450, 600,1600, 600,1550, 600,1550, 600,1550, 600,5150, 4450,4300, 600,1550, 600,500, 600,1550, 600,1550, 600,500, 600,500, 600,1550, 600,500, 600,450, 650,1550, 600,450, 650,450, 600,1550, 650,1550, 600,450, 650,1550, 600,1550, 600,500, 600,1550, 600,1550, 650,1550, 600,1550, 600,1550, 600,1600, 600,450, 650,1550, 600,450, 650,450, 600,500, 600,450, 650,450, 600,500, 600,500, 600,450, 650,450, 600,1550, 650,450, 600,500, 600,450, 650,450, 600,1600, 600,1550, 600,1550, 600,500, 600,1550, 600,1550, 650,1550, 600,1550, 600};  // SAMSUNG B24DBF40 unsigned int  data = 0xB24DBF40;

float   temperatura = 0;

boolean flagAcionar = false;
boolean temGente    = false;
boolean tempAlta    = false;

#define hora_liga        7
#define hora_desliga     15

boolean ar_desligado = false;

long previousMillis = 0;        // will store last time LED was updated

void setup(void)
{

  Serial.begin(57600);
  
  //seed para randomizar tAtual
  randomSeed(analogRead(0));

//  prog.pl1      = 1000;
  //prog.pd1      = 1200;
  //prog.pl2      = 1630;
  //prog.pd2      = 1740;
  root.set("pl1", "1000");
  root.set("pd1", "1200");
  root.set("pl2", "1630");
  root.set("pd2", "1740");

  //data.tMax     = 26;
  //data.tMin     = 20;  
  //data.tTrigger = 15; // tempo em minutos para indicar ausencia de pessoas
  root.set("t3", 26);
  root.set("t1", 20);
  root.set("tt", 15);
  root.set("m", "127");
  
  fsm_state = STATE_OFF;
  if (! rtc.begin()) {
    /*Serial.println("Couldn't find RTC");*/
    while (1);
  }


  if (rtc.lostPower()) {
    //  Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  // start serial port
  Serial.begin(57600);  //mudei pra funcionar com o bluetooth

  pinMode(pirPin, INPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(rele, OUTPUT);
  // Start up the library
  sensors.begin();
  //  sensors.getAddress(tempDeviceAddress, 0);
  // set the resolution to TEMPERATURE_PRECISION bit (Each Dallas/Maxim device is capable of several different resolutions)
  //  sensors.setResolution(tempDeviceAddress, TEMPERATURE_PRECISION);
  // printAddress(tempDeviceAddress);

  sensors.requestTemperatures(); // Send the command to get temperatures
  temperatura = sensors.getTempCByIndex(0);
  root.set("t2", temperatura);

  // Atualizar o estado inicial das variaveis
  if (temperatura <= TEMPERATURA_IDEAL ) {
    digitalWrite(ledBlue, HIGH);
    digitalWrite(ledRed, LOW);
    tempAlta = true;

  }
  else {
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledBlue, LOW);
    tempAlta = false;
  }
}


void loop(void)
{

  //variáveis de armazenamento de JSON - mudei pra local: economizou mais de 100 bytes de SRAM
  String    texto;
  char      teste[JSON_OUT_SIZE];


  lerSerial(texto, teste);
  //troca_status();

  //envia valor de pinPres (D7) --> variável "Pres"
  //data.Pres        = digitalRead(pinPres); 
    root.set("t2", digitalRead(pinPres));
    /*
    if (temGente == 1){
      data.Pres = 1;      
    }

    if (temGente == 0){
      data.Pres = 0;      
    }*/
        
        
  //Serial.println(" --> deserialize(data, teste);");
  deserialize(teste);


  
  DateTime now = rtc.now();

  unsigned long currentMillis = millis();
  //  Serial.println(currentMillis);

  //int
  char pirVal = digitalRead(pirPin);

  if (pirVal == HIGH) { //was motion detected
    digitalWrite(ledGreen, HIGH);
    /*Serial.print("\t     MOVIMENTO ");*/
    /* Apareceu um t aqui */
    temGente = true;
    previousMillis = currentMillis;
  }
  else {
    digitalWrite(ledGreen, LOW);
    /*Serial.print(F("\t SEM MOVIMENTO "));*/
  }

  sensors.requestTemperatures(); // Send the command to get temperatures
  temperatura = sensors.getTempCByIndex(0);
  root.set("t2", temperatura);

  // Se o tempo de trigger passar, ativar.
  if (currentMillis - previousMillis >= (TEMPO_TRIGGER*60*1000) ) {
    // save the last time you blinked the LED
    // Aumenta a temperatura pois nao possui ninguem no setor

    Desligar_FANCOIL();
    /*
    Serial.println(F("Enviado o sinal Subir Temp1"));
    Serial.println(F("NINGUEM NA SALA"));
    */
    digitalWrite(ledBlue, HIGH);
    digitalWrite(ledRed, HIGH);

    delay(DELAY_LED);
    digitalWrite(ledBlue, LOW);
    digitalWrite(ledRed, LOW);
    delay(DELAY_LED);
    digitalWrite(ledBlue, HIGH);
    digitalWrite(ledRed, HIGH);

    delay(DELAY_LED);
    digitalWrite(ledBlue, LOW);
    digitalWrite(ledRed, LOW);

    // Atualizar o estado inicial das variaveis
    if (temperatura <= TEMPERATURA_IDEAL ) {
      digitalWrite(ledBlue, HIGH);
      digitalWrite(ledRed, LOW);
      tempAlta = false;
/*
      Serial.println("T");
*/
    }
    else {
      digitalWrite(ledRed, HIGH);
      digitalWrite(ledBlue, LOW);
      tempAlta = true;
   /*   Serial.println("F"); */
    }

    flagAcionar = true;

    temGente = false;
    tempAlta = false;

    previousMillis = currentMillis;

  }

  if (temperatura <= TEMPERATURA_IDEAL ) {  // Caso a temperatura esteja ABAIXO da IDEAL
    digitalWrite(ledBlue, HIGH);
    digitalWrite(ledRed, LOW);
    if (temGente == true) {       // Se tiver gente na sala
      if (tempAlta == true) {     // E a temperatura estava Alta antes
        Desligar_FANCOIL();
      /*
        Serial.println(F("DESLIGAR AR"));
        Serial.println(F("Enviado o sinal Subir Temp2"));      
      */

        temGente = false;         // Altera o status da variavel
        flagAcionar = false;
        tempAlta = false;
      }
    }
   /* Serial.println("A"); */
  }
  else if ((temperatura > ( TEMPERATURA_IDEAL + deltaTEMP) )) { // Ter o debounce da temperatura
    // Caso a temperatura esteja acima da ideal MAIS um DELTA
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledBlue, LOW);
   /* Serial.println("B"); */
    // Se a temperatura estiver alta e tiver gente na sala
    if (temGente == true) {
      if (tempAlta == false) { // Verificado se a flag da temp estava BAIXA
     /*   Serial.println("C"); */
        Ligar_FANCOIL();
       /* Serial.println("Enviado o sinal Descer Temp3"); */

        flagAcionar = false;
        temGente = false;
        tempAlta = true;      // Confirma que a temperatura esta alta
      }
    }

   } else if ( temperatura <= TEMP_MIN) {
  /*  Serial.println("D"); */
    if (temGente == true) {

      digitalWrite(ledRed, HIGH);
      digitalWrite(ledBlue, LOW);
      Desligar_FANCOIL();
   /*   Serial.println(F("DESLIGAR AR")); */
    /*  Serial.println(F("Enviado o sinal Subir Temp4")); */

      temGente = false;
      flagAcionar = false;
      tempAlta = false;

    }

  }

  /*
  Serial.print(F("Temperatura: "));
  Serial.print(temperatura);

  Serial.print("\t G - ");
  Serial.print(temGente);

  Serial.print("\t Ta - ");
  Serial.print(tempAlta);
  Serial.print("\t");
  Serial.print("\n");

  */

  int nowHourMinute = now.hour() * 100 + now.minute();
  
  // Serial.println(nowHourMinute);
  // FSM states
  switch (fsm_state) {

    case STATE_OFF:
      if (nowHourMinute > START_TIME && nowHourMinute < END_TIME) {
        /*     Serial.print(now.hour(), DEC);
             Serial.print(':');
             Serial.print(now.minute(), DEC);
             Serial.println(", it's time to wake up!");
        */
        Ligar_FANCOIL();
        fsm_state = STATE_ON;
      }
      break;

    case STATE_ON:
      if (nowHourMinute > END_TIME) {
        /*     Serial.print(now.hour(), DEC);
            Serial.print(':');
            Serial.print(now.minute(), DEC);
            Serial.println(", it's time to go to sleep!");
        */
        Desligar_FANCOIL();
        fsm_state = STATE_OFF;
      }
      break;
  }


//------------------------

    

    
    //preparar variáveis aqui

    
    //data.tAtual      = random(10, 30);
    //data.tAtual = (unsigned int)temperatura;
    
    //jogar temGente para  data.Pres
    //if (temGente == true)  data.Pres = 1;
    //if (temGente == false) data.Pres = 0;
    

   
    //Serial.println(" --> serialize(data, JSON, JSON_OUT_SIZE);");
    serialize();
    //busy();  //obrigatório depois de enviar JSON
    //Serial.print("copia = ");
    //Serial.println(copia);
}
/*
  // function to print a device address
  void printAddress(DeviceAddress deviceAddress)
  {
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
  }



*/

void printData() {
  DateTime now = rtc.now();
  // Send Day-of-Week  Serial.print(now.year(), DEC);
  /*  Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
  */
}

/*
//_FLASH_ARRAY <unsigned int> sinal

int enviaIR( _FLASH_ARRAY <unsigned int> sinal , unsigned int c, char* freq) {
        
       irsend.sendRaw( sinal.access() , c , freq);
       return 0;  
  }

void Desligar_FANCOIL() {

  unsigned int  a = irSignal_Desligar_Ar.count();
  unsigned int  b = irSignal_Desligar_Ar[0];
  unsigned int  c = (a/b) ;
  
  digitalWrite( rele, LOW);
  enviaIR(irSignal_Desligar_Ar, c , khz); //Note the approach used to automatically calculate the size of the array.
  delay(500);
  enviaIR(irSignal_Desligar_Ar, c , khz); //Note the approach used to automatically calculate the size of the array.

}

void Ligar_FANCOIL() {

  unsigned int  a = irSignal_Ligar_Ar.count();
  unsigned int  b = irSignal_Ligar_Ar[0];
  unsigned int  c = (a/b) ;
  
  digitalWrite( rele, HIGH);
  enviaIR(irSignal_Ligar_Ar, c , khz); //Note the approach used to automatically calculate the size of the array.
  delay(500);
  enviaIR(irSignal_Ligar_Ar, c , khz); //Note the approach used to automatically calculate the size of the array.

}
*/

/*
 * nenhuma variável no json monitora o estado do relé... implemento?
 */


void Desligar_FANCOIL(){

  unsigned int c = sizeof(irSignal_Desligar_Ar) / sizeof(irSignal_Desligar_Ar[0]) ;
  
  digitalWrite( rele, LOW);
  irsend.sendRaw_P(irSignal_Desligar_Ar , c , khz);
  delay(DELAY_IR);
  irsend.sendRaw_P(irSignal_Desligar_Ar , c , khz);  
  }

void Ligar_FANCOIL(){

  unsigned int c = sizeof(irSignal_Ligar_Ar) / sizeof(irSignal_Ligar_Ar[0]) ;
  
  digitalWrite( rele, HIGH);
  irsend.sendRaw_P(irSignal_Ligar_Ar , c , khz);
  delay(DELAY_IR);
  irsend.sendRaw_P(irSignal_Ligar_Ar , c , khz);
}









