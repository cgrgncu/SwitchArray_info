int USBread() {
  int temp = -1;
   while (temp == -1) {
    while (Serial.available() == 0) {
    }
    delayMicroseconds(100);
    temp = Serial.read();
  }
  return temp;
}