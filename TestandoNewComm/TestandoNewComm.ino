#include <ArduinoJson.h>
#include <SoftwareSerial.h> // import the serial library
#include <String.h>
#include <ArduinoIonicComm.h>

SensorData data;
ProgramaHorario prog;
Solicitacoes slcts;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  prog.pl1      = "1000";
  prog.pd1      = "1200";
  prog.pl2      = "1630";
  prog.pd2      = "1740";

  data.tMax     = 26;
  data.tMin     = 20;  
  data.tTrigger = 15;
  data.s = 0;
  slcts.dado = "0";
}

void loop() {
  // put your main code here, to run repeatedly:
  String    texto;
  char      teste[JSON_OUT_SIZE];
  

  lerSerial(texto, teste);
  deserialize(&data,&prog,&slcts,teste);
  if( slcts.solicitouGravacao == 1 || slcts.solicitouTeste == 1 ) {
      if(slcts.solicitouGravacao) {
        if(slcts.dado != "0") {
          Serial.println("Pegou dado.");
          slcts.dado = "0";
        }
        Serial.println("Solicitou gravacao, gravacao feita");
        slcts.solicitouGravacao = 0;
        slcts.gravacaoRealizada = 1;
      }
      else {
        if(slcts.dado != "0") {
          Serial.println("Pegou dado.");
          slcts.dado = "0";
        }
        Serial.println("Solicitou teste, teste feito");
        slcts.solicitouTeste = 0;
        slcts.testeRealizado = 1;
      }
  }
  else { // DEFINIR TERMINO DE CONFIGURACAO COM S
    Serial.println("Codigo rodando.");
    delay(3000);
  }
  serialize(&data,&prog,&slcts);

  
}
