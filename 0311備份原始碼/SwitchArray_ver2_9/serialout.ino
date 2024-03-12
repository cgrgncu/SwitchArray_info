
void serialOut(int data_pin, int push_pin, int ready_pin, int delay_micro_second, int* switch_array, int length) {
  //Serial.println("**");
  resetSerial();
  for (int i = 0; i < length; i++) {
    digitalWrite(data_pin, switch_array[length - 1 - i]);
    delayMicroseconds(delay_micro_second);
    digitalWrite(push_pin, 1);
    delayMicroseconds(delay_micro_second);
    digitalWrite(push_pin, 0);

    //Serial.print(switch_array[length-1-i]);
  }
  digitalWrite(ready_pin, 1);
  delayMicroseconds(delay_micro_second);
  digitalWrite(ready_pin, 0);
  digitalWrite(data_pin, 0);
}

void serialOut_withTime(int data_pin, int push_pin, int ready_pin, int delay_micro_second, int* switch_array, int length, unsigned long initial_time, unsigned long wait_period) {
  //Serial.println("**");
  resetSerial();
  for (int i = 0; i < length; i++) {
    digitalWrite(data_pin, switch_array[length - 1 - i]);
    delayMicroseconds(delay_micro_second);
    digitalWrite(push_pin, 1);
    delayMicroseconds(delay_micro_second);
    digitalWrite(push_pin, 0);

    //Serial.print(switch_array[length-1-i]);
  }
  while ((micros() - initial_time) < wait_period) {
  }
  digitalWrite(ready_pin, 1);
  delayMicroseconds(delay_micro_second);
  digitalWrite(ready_pin, 0);
  digitalWrite(data_pin, 0);
}
