//ArduinoIonicComm - Rafael Requião e Lucas Borges

#ifndef ARDUINOIONICCOMM_HPP
#define ARDUINOIONICCOMM_HPP

#include <Arduino.h>
#include <String.h>
#include "../ArduinoJson/ArduinoJson.h"

#define JSONOBJECT_JSON_SIZE 128
#define JSON_OUT_SIZE        128
#define DELAY_MS             100

struct SensorData {
   uint8_t    Pres;
   uint8_t    s;
   uint8_t    tTrigger;
   uint8_t    tMin;
   uint8_t    tAtual;
   uint8_t    tMax;
   
};

struct ProgramaHorario { 

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

struct Solicitacoes {
  uint8_t solicitouGravacao;
  uint8_t gravacaoRealizada;
  uint8_t solicitouTeste;
  uint8_t testeRealizado;

  String dado;
};

typedef struct SensorData SensorData;
typedef struct ProgramaHorario ProgramaHorario;
typedef struct Solicitacoes Solicitacoes;

void serialize(SensorData* data, ProgramaHorario* prog, Solicitacoes* sclts); 

void deserialize(SensorData* data, ProgramaHorario* prog, Solicitacoes* slcts,unsigned char* json);

void lerSerial(String texto,unsigned char* teste);

void checkbitmask(ProgramaHorario* prog);

void checkslctsbitmask(SensorData* data,Solicitacoes* slcts);

void atualizaStatus(SensorData* data,Solicitacoes* slcts);

#endif