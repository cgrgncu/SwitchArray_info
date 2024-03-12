
#include "pin.h"
int bcount = 0;  //DD
unsigned long connect_last_time;
//=====================================================================================================================================

void setup() {
  pinMode(OFF_PSU, OUTPUT);
  digitalWrite(OFF_PSU, 0);
  pinMode(REF_EXTERNAL, OUTPUT);
  digitalWrite(REF_EXTERNAL, 0);
  pinMode(REF_PSU_NEG, OUTPUT);
  digitalWrite(REF_PSU_NEG, 0);
  pinMode(REF_PSU_POS, OUTPUT);
  digitalWrite(REF_PSU_POS, 0);
  pinMode(RESET, OUTPUT);
  digitalWrite(RESET, 1);
  pinMode(PUSH_PIN, OUTPUT);
  digitalWrite(PUSH_PIN, 0);
  pinMode(READY_VOLTAGE, OUTPUT);
  digitalWrite(READY_VOLTAGE, 0);
  pinMode(READY_PSU, OUTPUT);
  digitalWrite(READY_PSU, 0);
  pinMode(OFF_VOLTAGE, OUTPUT);
  digitalWrite(OFF_VOLTAGE, 1);
  pinMode(DATA, OUTPUT);
  digitalWrite(DATA, 0);
  pinMode(READY_PIN_CURRENT_POS, OUTPUT);
  digitalWrite(READY_PIN_CURRENT_POS, 0);
  pinMode(READY_PIN_CURRENT_NEG, OUTPUT);
  digitalWrite(READY_PIN_CURRENT_NEG, 0);
  clearEveryOutput();
  pinMode(READY_VOLTAGE, INPUT);
  Serial.begin(115200);  
  connect_last_time=millis();
}


void loop() {

  while (Serial.available() > 0) {

    readCommand(Serial.read());
    connect_last_time=millis();
  }

  if(millis()-connect_last_time>300000)
  {
    if(millis()-connect_last_time<330000)
    {
      pinMode(READY_VOLTAGE, INPUT);
    }
    delay(1000);
  }

}
//===================================================================================================================================
