//ArduinoIonicComm - Rafael Requião e Lucas Borges

#include "ArduinoIonicComm.h"

void serialize(SensorData* data, ProgramaHorario* prog, Solicitacoes* sclts)
{
    StaticJsonBuffer<128> jsonBuffer;      //preciso mudar o tamanho a depender do JSON
    JsonObject& root = jsonBuffer.createObject();           //ou a depender de "int data.Status"
    atualizaStatus(data,sclts);

        root["m"]   = prog->mask;
        root["p"]   = data->Pres;
        root["s"]   = data->s;
        root["pd1"] = prog->pd1;
        root["pd2"] = prog->pd2;
        root["pl1"] = prog->pl1;
        root["pl2"] = prog->pl2;
        root["t1"]  = data->tMin;
        root["t2"]  = data->tAtual;
        root["t3"]  = data->tMax;
        root["tt"]  = data->tTrigger;

    root.printTo(Serial);
    Serial.println("");
    delay(DELAY_MS);
    return;
}



void deserialize(SensorData* data, ProgramaHorario* prog, Solicitacoes* slcts,unsigned char* json)
{
    StaticJsonBuffer<JSONOBJECT_JSON_SIZE> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(json);
   

    if (!root.success()) {
     // Serial.println("parseObject() failed");
      return;
    }
    
    if (root.success()) {
      //Serial.println("parseObject() successful");

     //previne sobrescrever valores na estrutura "nulos ou zeros", 
     //caso não tenha recebido um JSON válido

         if (root.containsKey("m")){
          prog->mask      = root["m"];
         }

         if(root.containsKey("s")){
          data->s     = root["s"];
         }
         if(root.containsKey("d")) {
          slcts->dado = root.get<String>("d");
         }
         if (root.containsKey("p")) {
          data->Pres      = root["p"];
         }
         if (root.containsKey("pd1")) {
          prog->pd1       = root.get<String>("pd1");
          //bfr = root["pd1"];
          //bfr.toCharArray(bfr,4);
         }

         if (root.containsKey("pd2")){
          prog->pd2       = root.get<String>("pd2");
          //bfr = root["pd2"];
          //bfr.toCharArray(bfr,4);
         }

         if (root.containsKey("pl1")) {
          prog->pl1       = root.get<String>("pl1");
          //bfr = root["pl1"];
          //bfr.toCharArray(bfr,4);
         }

         if (root.containsKey("pl2")) {
          prog->pl2       = root.get<String>("pl2");
          //bfr = root["pl2"];
          //bfr.toCharArray(bfr,4); 
         }

         if (root.containsKey("t1")){
          data->tMin      = root["t1"]; 
         }

         if (root.containsKey("t2")){
          data->tAtual    = root["t2"]; 
         }

         if (root.containsKey("t3")){
          data->tMax      = root["t3"]; 
         }

         if (root.containsKey("tt")){
          data->tTrigger  = root["tt"]; 
         }
         checkbitmask(prog);
         checkslctsbitmask(data,slcts);
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

/*      BITWISE AND

        0101 (decimal 5)
    AND 0011 (decimal 3)
      = 0001 (decimal 1)
*/
void checkbitmask(ProgramaHorario* prog) {

  if ( (prog->mask & 1) ==   1 ) prog->segunda = 1;
  else prog->segunda = 0;

  if ( (prog->mask & 2) ==   2 ) prog->terca = 1;
  else prog->terca = 0;

  if ( (prog->mask & 4) ==   4 ) prog->quarta = 1;
  else prog->quarta = 0;

  if ( (prog->mask & 8) ==   8 ) prog->quinta = 1;
  else prog->quinta = 0;

  if ( (prog->mask & 16) == 16 ) prog->sexta = 1;
  else prog->sexta = 0;

  if ( (prog->mask & 32) == 32 ) prog->sabado = 1;
  else prog->sabado = 0;

  if ( (prog->mask & 64) == 64 ) prog->domingo = 1;
  else prog->domingo = 0;


}

void checkslctsbitmask(SensorData* data,Solicitacoes* slcts) {
    if( (data->s & 1) == 1 ) slcts->solicitouGravacao = 1;
    else slcts->solicitouGravacao = 0;

    if( (data->s & 4) == 4) slcts->solicitouTeste = 1;
    else slcts->solicitouTeste = 0;
}

void atualizaStatus(SensorData* data,Solicitacoes* slcts) {
    data->s = 0;
    if(slcts->solicitouGravacao == 1) {
        data->s += 1;
    }
    if(slcts->gravacaoRealizada == 1) {
        data->s += 2;
    }
    if(slcts->solicitouTeste == 1) {
        data->s += 4;
    }
    if(slcts->testeRealizado == 1) {
        data->s += 8;
    }
}