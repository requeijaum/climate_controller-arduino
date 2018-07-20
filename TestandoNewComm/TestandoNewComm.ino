#include <ArduinoJson.h>
#include <SoftwareSerial.h> // import the serial library
#include <String.h>
#include <ArduinoIonicComm.h>
#include <ArduinoIRComm.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include "RTClib.h"
// Controle remoto
#include <IRremote.h>


#define pinPres                   12      //igual a pirPin
#define DELAY_LED                 250     //mudei - era 300
#define DELAY_IR                  250     //mudei - era 500
#define pirPin        12
#define ledRed        5
#define ledBlue       10
#define ledGreen      6
#define IR_LED        3
#define IR_Remote     2
#define rele          9
#define pinTemp       4
#define TEMPERATURE_PRECISION 12
// FSM states
#define STATE_OFF  0
#define STATE_ON   1
// LED INFRAVERMELHO USAR O PINO 3 (TIMER 2) DO ARDUINO
#define IR_USE_TIMER2
// Data wire is plugged into port 2 on the Arduino

OneWire oneWire(pinTemp);
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
DeviceAddress tempDeviceAddress; // We'll use this variable to store a found device address
RTC_DS3231 rtc;
IRrecv irrecv(IR_Remote);

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)



//int 
char khz = 38; // 38kHz carrier frequency for the NEC protocol

unsigned long previousMillisPres = 0;        // will store last time LED was updated
unsigned long previousMillisTemp = 0;
unsigned long currentMillis; 
boolean firstActionFlag;

int deltaTemp;

//int
char    fsm_state;

float temperatura;

//char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};







/////////////////////////////////////////////////////////////////////////////////////////////////////////////// COPIEI TUDO DO CÓDIGO ANTERIOR POR QUE PODE SER UTIL  ^^^^^^^^^^^^^^^^^^^^^^



SensorData data;
ProgramaHorario prog;
Solicitacoes slcts;

IRSignals irsignals;
arStatus arstatus;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  prog.pl1      = "1000";
  prog.pd1      = "1200";
  prog.pl2      = "1630";
  prog.pd2      = "1740";

  data.tAtual   = 25;
  data.tMax     = 26;
  data.tMin     = 20;  
  data.tTrigger = 15;
  data.s = 0;
  slcts.dado = "0";
  firstActionFlag = false;
}

void loop() {
  // put your main code here, to run repeatedly:
  String    texto;
  char      teste[JSON_OUT_SIZE];
  
  // MUDO CURRENTMILLIS POR APENAS MILLIS() ???????? POSSO FAZER ISSO????? SE SIM, DARIA MAIS PRECISAO
  lerSerial(texto, teste);
  deserialize(&data,&prog,&slcts,teste);
  if( slcts.solicitouGravacao == 1 || slcts.solicitouTeste == 1 ) {            // Se solicitou gravação ou teste 
      if(slcts.solicitouGravacao) {                                           // Se solicitou gravacao
        if(slcts.dado != "0") {                                               // Se pegou o dado a ser gravado
        //  Serial.println("Pegou dado.");
         // Serial.println("Solicitou gravacao, gravacao feita");
         gravarIR(slcts.dado,&irsignals, irrecv);
          slcts.solicitouGravacao = 0;
          slcts.gravacaoRealizada = 1;
          slcts.dado = "0";
        }
        else {                                                               // Se nao pegou o dado
       //   Serial.println("Erro!, nao pegou dado!");
          slcts.solicitouGravacao = 0;
        }
      }
      else {                                                                // Se solicitou teste
        if(slcts.dado != "0") {                                             // Se pegou dado a ser testado
       //   Serial.println("Pegou dado.");
       //   Serial.println("Solicitou teste, teste feito");
          mandarSinalIR(slcts.dado, irsignals, &arstatus);
          slcts.solicitouTeste = 0;
          slcts.testeRealizado = 1;
          slcts.dado = "0";
        }
        else {                                                          // Se nao pego o dado
       //   Serial.println("Erro!, nao pegou dado!");
          slcts.solicitouTeste = 0;
        }
      }
  }
  else if(slcts.configCompleta){                                       // Se a configuração está completa rode o código;
    //Serial.println("Codigo rodando.");
    // TODO: Biblioteca para controle do IR, Biblioteca para o controle do Ar condicionado
    
    if(1) { // Esta condicional deve ser feita após configurar o RTC, deve ter: Se o horário atual está dentro do horário de funcionamento
      currentMillis = millis();
      if(1) { // Se detectou movimento
        //meche no LED
        previousMillisPres = currentMillis;
        data.Pres = 1;
        if(1){ // Se o ar condicionado não estiver ligado ligue-o agora.
          //mandarSinalIR("l", irsignals, &arstatus);
        //  Serial.println("Se ar-condicionado não estava ligado, ligou agora");
        }
      }
      else { // Nao identificou movimento
        // Meche no led
        data.Pres = 0;
      }
      if(currentMillis - previousMillisPres >= (data.tTrigger*60*1000)) {  // Se movimento nao foi identificado há algum tempo.
        // Desliga a.r.
        // meche em led's
       // Serial.println("Desligou a.r.");
       // mandarSinalIR("d", irsignals, &arstatus);
        previousMillisPres = currentMillis;
      }
      else { // Caso contrário rode o algoritmo
        if( ((data.tAtual <  data.tMin || data.tAtual > data.tMax)) && ((currentMillis - previousMillisTemp >= ((unsigned long) 1 * (unsigned long) 60 * (unsigned long) 1000)) || firstActionFlag == false ) ) { // Se a temperatura atual estiver fora do intervalo e qualquer ação tenha sido tomada há 10 minutos ( tempo suficiente para qualquer ambiente resfriar ou aquecer ) entre OU que nenhuma ação tenha sido tomada ainda.
          firstActionFlag = true;
         // Serial.println("Tomando ação para regular temp");
          if(data.tAtual < data.tMin) { // Se estiver abaixo do desejado
            //meche nos leds para mostrar que a temperatura esta abaixo do intervalo
            deltaTemp = data.tMin - data.tAtual;
            // mandarSinalIR(deltaTemp, irsignals, &arstatus);
            //Serial.println("Aumentou temp");
          }
          else { // Se estiver acima do desejado
            deltaTemp = data.tAtual - data.tMax;
            // mandarSinalIR(deltaTemp, irsignals, &arstatus);
           // Serial.println("Diminuiu temp");
          }
          previousMillisTemp = currentMillis;
        }
        else {
          //meche nos leds pra mostrar que a temperatura esta no intervalo
          // quem sabe regula para que a temperatura fique na media do intervalo, ou variando dentro do intervalo
        }
      }
    }
  }
  serialize(&data,&prog,&slcts);
  delay(1500);

  
}
