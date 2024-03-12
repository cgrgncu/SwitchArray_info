#define switchTurnOffTime 200 

void resetSerial() {
  digitalWrite(RESET, 0);
  delayMicroseconds(pushPeriod);
  digitalWrite(RESET, 1);
}

void clearEveryOutput() {
  resetSerial();
  digitalWrite(READY_PIN_CURRENT_POS, 1);
  delayMicroseconds(pushPeriod);
  digitalWrite(READY_PIN_CURRENT_POS, 0);
  delayMicroseconds(pushPeriod);
  digitalWrite(READY_PIN_CURRENT_NEG, 1);
  delayMicroseconds(pushPeriod);
  digitalWrite(READY_PIN_CURRENT_NEG, 0);
  delayMicroseconds(pushPeriod);
  digitalWrite(READY_VOLTAGE, 1);
  delayMicroseconds(pushPeriod);
  digitalWrite(READY_VOLTAGE, 0);
  delayMicroseconds(pushPeriod);
  digitalWrite(READY_PSU, 1);
  delayMicroseconds(pushPeriod);
  digitalWrite(READY_PSU, 0);
  delayMicroseconds(switchTurnOffTime);
}