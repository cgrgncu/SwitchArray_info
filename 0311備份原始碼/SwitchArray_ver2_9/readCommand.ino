#include "pin.h"
#define pushPeriod 2            
#define measureTurnOnTime 16760
#define measureTurnOffTime 200
#define MAX_channel_count 255
#define SCAN_BUFFER 0  
void readCommand(char commandRead) {
  static int error_count = 0;
  static int receive_current_state = 0;
  static char *current_mode;
  static int channel_count = 0;
  static int current_state = 0;
  static int scan_interval = 300;
  static int accurate_measure_channel = 0;
  static int P_channel_count = 0;
  static int N_channel_count = 0;
  static int V_count = 0;
  static int N_count = 0;
  static int P_count = 0;
  static char receive_state = 0; 
  static bool measurement_toggle = 0;
  static bool accurate_I_only = 0;
  static bool enable_accurate = 0;
  static int scan_turn_on_time = 200;  
  static unsigned long scan_last_time = 0;
  static int switchTurnOnTime = 50;   
  static int switchTurnOffTime = 200;  
  static int sample_number = 1;
  static int scan_mode = 0;
  if (receive_state == 0) {

    switch (commandRead) {
      case 'a':  
        {
          if (enable_accurate) {
            if (P_count != P_channel_count) { 
              error_count++;
              Serial.println("!!!!!!!!!!!!!!!!!!");
              Serial.print("error count= ");
              Serial.println(error_count);
              Serial.print("error type: command'");
              Serial.print(commandRead);
              Serial.print("' didn't get correct \nnumber of data in\nprevious 'P' command ,\n P_count=");
              Serial.println(P_count);
              Serial.print("which should be ");
              Serial.println(P_channel_count);
              Serial.print("when current state is ");
              Serial.println(current_state);
            }
          }
          V_count = 0;
          P_count = 0;
          N_count = 0;
          measurement_toggle = 0;
          accurate_measure_channel = 0;
          while (Serial.available() == 0) {
          }                               
          channel_count = Serial.read(); 
          while (Serial.available() == 0) {
          }                                        
          int current_state_temp = Serial.read();  
          while (Serial.available() == 0) {
          }                                                          
          current_state = Serial.read() + 256 * current_state_temp; 
          delete[] current_mode;
          current_mode = new char[channel_count];
          receive_state = 'a';
          receive_current_state = 0;
          P_channel_count = 0;
          N_channel_count = 0;
          if (current_state > 0) {
            /*
            Serial.print("bcount= ");  //DD
            Serial.println(bcount);    //DD
            */
          }
          bcount = 0;  //DD
          break;
        }
      case 'b':  
        {
          bcount++;  //DD
          resetREF();

          resetSerial(); 
          digitalWrite(READY_PSU, 1);
          delayMicroseconds(pushPeriod);
          digitalWrite(READY_PSU, 0);
          delayMicroseconds(switchTurnOffTime);


          for (int sample_i = 0; sample_i < sample_number; sample_i++) {
            digitalWrite(REF_EXTERNAL, 1);
            delayMicroseconds(switchTurnOnTime);

            resetSerial();  
            digitalWrite(DATA, 1);
            delayMicroseconds(pushPeriod);
            digitalWrite(PUSH_PIN, 1);
            delayMicroseconds(pushPeriod);
            digitalWrite(PUSH_PIN, 0);
            digitalWrite(DATA, 0);
            for (int ii = 0; ii < channel_count; ii++) {  
              if (current_mode[ii] == 0) {
                digitalWrite(READY_VOLTAGE, 1);
                delayMicroseconds(pushPeriod);
                digitalWrite(READY_VOLTAGE, 0);

                digitalWrite(OFF_VOLTAGE, 0);
                delayMicroseconds(scan_turn_on_time);
                digitalWrite(OFF_VOLTAGE, 1);
                delayMicroseconds(switchTurnOffTime);
              } else {
                delayMicroseconds(pushPeriod);
              }
              digitalWrite(PUSH_PIN, 1);
              delayMicroseconds(pushPeriod);
              digitalWrite(PUSH_PIN, 0);
            }

            resetREF();
            delayMicroseconds(switchTurnOffTime);

            for (int ii = 0; ii < channel_count; ii++) {  
              if (current_mode[ii] != 0) {
                resetSerial();
                digitalWrite(DATA, 1);
                delayMicroseconds(pushPeriod);
                digitalWrite(PUSH_PIN, 1);
                delayMicroseconds(pushPeriod);
                digitalWrite(PUSH_PIN, 0);
                digitalWrite(DATA, 0);
                for (int i = 0; i < ii; i++) {
                  digitalWrite(PUSH_PIN, 1);
                  delayMicroseconds(pushPeriod);
                  digitalWrite(PUSH_PIN, 0);
                  delayMicroseconds(pushPeriod);
                }

                digitalWrite(READY_PSU, 1);
                delayMicroseconds(pushPeriod);
                digitalWrite(READY_PSU, 0);
                delayMicroseconds(switchTurnOnTime);  

                digitalWrite(READY_VOLTAGE, 1);
                delayMicroseconds(pushPeriod);
                digitalWrite(READY_VOLTAGE, 0);
                digitalWrite(OFF_VOLTAGE, 0);
                delayMicroseconds(scan_turn_on_time);
                digitalWrite(OFF_VOLTAGE, 1);
                resetSerial();               
                digitalWrite(READY_PSU, 1);  
                delayMicroseconds(pushPeriod);
                digitalWrite(READY_PSU, 0);
                delayMicroseconds(switchTurnOffTime);
              }
            }
          }


          /*
        Serial.println("====================");
        Serial.print("time= ");    //DD
        Serial.println(millis());  //DD
        */
          break;
        }
      case 'B': 
        for (int ii = 0; ii < channel_count * sample_number; ii++) {
          digitalWrite(READY_VOLTAGE, 1);
          delayMicroseconds(pushPeriod);
          digitalWrite(READY_VOLTAGE, 0);
          delayMicroseconds(scan_turn_on_time);
        }
        break;



      case 'V': 
        {
          int measure_temp[channel_count];
          for (int ii = 0; ii < channel_count; ii++) {
            measure_temp[ii] = 0;
          }
          if (V_count == 0) {
            resetREF();
            delayMicroseconds(switchTurnOffTime);
            digitalWrite(REF_EXTERNAL, 1);
            delayMicroseconds(switchTurnOnTime);

            P_count = 0;
            accurate_measure_channel = 0;
          }
          for (int ii = accurate_measure_channel; ii < channel_count; ii++) {
            if (current_mode[ii] == 0) {
              V_count++;
              accurate_measure_channel = ii + 1;
              measure_temp[ii] = 1;
              break;
            }
          }
          serialOut(DATA, PUSH_PIN, READY_VOLTAGE, pushPeriod, measure_temp, channel_count);
          digitalWrite(OFF_VOLTAGE, 0);
          delayMicroseconds(measureTurnOnTime);
          digitalWrite(OFF_VOLTAGE, 1);
          delayMicroseconds(measureTurnOffTime);
          break;
        }

      case 'N':  
        {
          int measure_temp[channel_count];
          for (int ii = 0; ii < channel_count; ii++) {
            measure_temp[ii] = 0;
          }
          if (N_count == 0) {
            if (!accurate_I_only) {
              if (V_count != channel_count - P_channel_count - N_channel_count) {
                error_count++;
                Serial.println("!!!!!!!!!!!!!!!!!!");
                Serial.print("error count= ");
                Serial.println(error_count);
                Serial.print("error type: command'");
                Serial.print(commandRead);
                Serial.print("' didn't get correct \nnumber of data in\nprevious 'V' command ,\n V_count=");
                Serial.println(V_count);
                Serial.print("which should be ");
                Serial.println(channel_count - P_channel_count - N_channel_count);
                Serial.print("when current state is ");
                Serial.println(current_state);
              }
            }
            resetREF();
            V_count = 0;
            accurate_measure_channel = 0;
          }

          for (int ii = accurate_measure_channel; ii < channel_count; ii++) {
            if (current_mode[ii] == 2) {
              measure_temp[ii] = 1;
              serialOut(DATA, PUSH_PIN, READY_PSU, pushPeriod, measure_temp, channel_count);
              delayMicroseconds(switchTurnOnTime);
              serialOut(DATA, PUSH_PIN, READY_VOLTAGE, pushPeriod, measure_temp, channel_count);
              digitalWrite(OFF_VOLTAGE, 0);
              delayMicroseconds(measureTurnOnTime);
              digitalWrite(OFF_VOLTAGE, 1);
              delayMicroseconds(measureTurnOffTime);
              resetSerial();               
              digitalWrite(READY_PSU, 1);  
              delayMicroseconds(pushPeriod);
              digitalWrite(READY_PSU, 0);
              delayMicroseconds(switchTurnOffTime);
              N_count++;
              accurate_measure_channel = ii++;
              break;
            }
          }

          break;
        }

      case 'P':  
        {
          int measure_temp[channel_count];
          for (int ii = 0; ii < channel_count; ii++) {
            measure_temp[ii] = 0;
          }
          if (P_count == 0) {
            if (N_count != N_channel_count) {
              error_count++;
              Serial.println("!!!!!!!!!!!!!!!!!!");
              Serial.print("error count= ");
              Serial.println(error_count);
              Serial.print("error type: command'");
              Serial.print(commandRead);
              Serial.print("' didn't get correct \nnumber of data in\nprevious 'N' command ,\n N_count=");
              Serial.println(N_count);
              Serial.print("which should be ");
              Serial.println(N_channel_count);
              Serial.print("when current state is ");
              Serial.println(current_state);
            }
            resetREF();
            N_count = 0;
            accurate_measure_channel = 0;
          }

          for (int ii = accurate_measure_channel; ii < channel_count; ii++) {
            if (current_mode[ii] == 1) {
              measure_temp[ii] = 1;
              serialOut(DATA, PUSH_PIN, READY_PSU, pushPeriod, measure_temp, channel_count);
              delayMicroseconds(switchTurnOnTime);
              serialOut(DATA, PUSH_PIN, READY_VOLTAGE, pushPeriod, measure_temp, channel_count);
              digitalWrite(OFF_VOLTAGE, 0);
              delayMicroseconds(measureTurnOnTime);
              digitalWrite(OFF_VOLTAGE, 1);
              delayMicroseconds(measureTurnOffTime);
              resetSerial();              
              digitalWrite(READY_PSU, 1);  
              delayMicroseconds(pushPeriod);
              digitalWrite(READY_PSU, 0);
              delayMicroseconds(switchTurnOffTime);
              P_count++;
              accurate_measure_channel = ii++;
              break;
            }
          }

          break;
        }
      case 'T': 
        {
          digitalWrite(READY_VOLTAGE, 1);
          delayMicroseconds(pushPeriod);
          digitalWrite(READY_VOLTAGE, 0);
          digitalWrite(OFF_VOLTAGE, 0);
          delayMicroseconds(measureTurnOnTime);
          digitalWrite(OFF_VOLTAGE, 1);
          delayMicroseconds(measureTurnOffTime);
          break;
        }
      case 't':  
        {
          static int resistance_test_channel;
          static int resistance_test_wait;
          static int *switch_temp_resistance_test;
          resetREF();
          resetSerial();
          digitalWrite(READY_PSU, 1);
          delayMicroseconds(pushPeriod);
          digitalWrite(READY_PSU, 0);
          delayMicroseconds(switchTurnOffTime);
          while (Serial.available() == 0) {
          }
          resistance_test_channel = Serial.read();
          while (resistance_test_channel == -1) 
            resistance_test_channel = Serial.read();
          Serial.println(resistance_test_channel);
          while (Serial.available() == 0) {
          }
          resistance_test_wait = Serial.read() * 100;  
          switch_temp_resistance_test = new int[resistance_test_channel + 2];
          for (int ii = 0; ii < resistance_test_channel + 2; ii++) {
            switch_temp_resistance_test[ii] = 0;
          }
          switch_temp_resistance_test[resistance_test_channel] = 1;
          serialOut(DATA, PUSH_PIN, READY_PIN_CURRENT_POS, pushPeriod, switch_temp_resistance_test, resistance_test_channel + 2);
          delayMicroseconds(switchTurnOnTime);
          switch_temp_resistance_test[resistance_test_channel] = 0;
          switch_temp_resistance_test[resistance_test_channel + 1] = 1;
          serialOut(DATA, PUSH_PIN, READY_PIN_CURRENT_NEG, pushPeriod, switch_temp_resistance_test, resistance_test_channel + 2);
          delay(resistance_test_wait);
          serialOut(DATA, PUSH_PIN, READY_PSU, pushPeriod, switch_temp_resistance_test, resistance_test_channel + 2);
          delayMicroseconds(switchTurnOnTime);
          serialOut(DATA, PUSH_PIN, READY_VOLTAGE, pushPeriod, switch_temp_resistance_test, resistance_test_channel + 2);
          digitalWrite(OFF_VOLTAGE, 0);
          char t_temp = 0;
          while (t_temp != 'y') {
            while (Serial.available() == 0) {
            }
            t_temp = Serial.read();
            if (t_temp != 'y')
              if (t_temp == 'B') {
                digitalWrite(READY_VOLTAGE, 1);
                delayMicroseconds(pushPeriod);
                digitalWrite(READY_VOLTAGE, 0);
              } else
                errorCommand(&error_count, t_temp);
          }
          t_temp = 0;
          digitalWrite(OFF_VOLTAGE, 1);
          delayMicroseconds(switchTurnOffTime);
          switch_temp_resistance_test[resistance_test_channel] = 1;
          switch_temp_resistance_test[resistance_test_channel + 1] = 0;
          serialOut(DATA, PUSH_PIN, READY_VOLTAGE, pushPeriod, switch_temp_resistance_test, resistance_test_channel + 2);
          digitalWrite(OFF_VOLTAGE, 0);
          while (t_temp != 'y') {
            while (Serial.available() == 0) {
            }
            t_temp = Serial.read();
            if (t_temp != 'y')
              if (t_temp == 'B') {
                digitalWrite(READY_VOLTAGE, 1);
                delayMicroseconds(pushPeriod);
                digitalWrite(READY_VOLTAGE, 0);
              } else
                errorCommand(&error_count, t_temp);
          }
          t_temp = 0;
          digitalWrite(OFF_VOLTAGE, 1);
          delayMicroseconds(switchTurnOffTime);
          delete[] switch_temp_resistance_test;
        }
        resetSerial();               
        digitalWrite(READY_PSU, 1); 
        delayMicroseconds(pushPeriod);
        digitalWrite(READY_PSU, 0);
        delayMicroseconds(switchTurnOffTime);
        break;
      case 'r':  //Resistance caliration
        {
          resetREF();
          delayMicroseconds(switchTurnOffTime);
          digitalWrite(REF_PSU_NEG, 1);
          delayMicroseconds(switchTurnOnTime);
          digitalWrite(OFF_VOLTAGE, 1);
          while (Serial.available() == 0) {
          }                                                      
          int current_sense_resistance_channel = Serial.read();  
          resetSerial();
          static int *switch_temp_calibrate;
          switch_temp_calibrate = new int[current_sense_resistance_channel + 1];
          for (int ii = 0; ii < current_sense_resistance_channel + 1; ii++) {
            switch_temp_calibrate[ii] = 0;
          }
          switch_temp_calibrate[current_sense_resistance_channel] = 1;
          serialOut(DATA, PUSH_PIN, READY_PIN_CURRENT_NEG, pushPeriod, switch_temp_calibrate, current_sense_resistance_channel + 1);
          delayMicroseconds(switchTurnOnTime);
          serialOut(DATA, PUSH_PIN, READY_PIN_CURRENT_POS, pushPeriod, switch_temp_calibrate, current_sense_resistance_channel + 1);
          delayMicroseconds(10 * switchTurnOnTime); 
          serialOut(DATA, PUSH_PIN, READY_VOLTAGE, pushPeriod, switch_temp_calibrate, current_sense_resistance_channel + 1);
          digitalWrite(OFF_VOLTAGE, 0);
          delete[] switch_temp_calibrate;
        }
        break;
      case 'f': 
        {
          while (Serial.available() == 0) {
          }                                                   
          int resistance_test_channel_count = Serial.read(); 
          resetREF();
          resetSerial();
          digitalWrite(READY_PIN_CURRENT_POS, 1);
          delayMicroseconds(pushPeriod);
          digitalWrite(READY_PIN_CURRENT_POS, 0);
          delayMicroseconds(pushPeriod);
          digitalWrite(READY_PIN_CURRENT_NEG, 1);
          delayMicroseconds(pushPeriod);
          digitalWrite(READY_PIN_CURRENT_NEG, 0);
          delayMicroseconds(pushPeriod);
          digitalWrite(READY_PSU, 1);
          delayMicroseconds(pushPeriod);
          digitalWrite(READY_PSU, 0);
          delayMicroseconds(switchTurnOffTime);
          digitalWrite(DATA, 1);
          delayMicroseconds(pushPeriod);
          digitalWrite(PUSH_PIN, 1);
          delayMicroseconds(pushPeriod);
          digitalWrite(PUSH_PIN, 0);
          digitalWrite(DATA, 0);
          digitalWrite(READY_PSU, 1);
          delayMicroseconds(pushPeriod);
          digitalWrite(READY_PSU, 0);
          delayMicroseconds(switchTurnOnTime);
          digitalWrite(READY_VOLTAGE, 1);
          delayMicroseconds(pushPeriod);
          digitalWrite(READY_VOLTAGE, 0);
          digitalWrite(OFF_VOLTAGE, 0);
          delayMicroseconds(1100);
          digitalWrite(OFF_VOLTAGE, 1);
          delayMicroseconds(switchTurnOffTime);
          for (int ii = 0; ii < resistance_test_channel_count; ii++) {  

            digitalWrite(PUSH_PIN, 1);
            delayMicroseconds(pushPeriod);
            digitalWrite(PUSH_PIN, 0);
            digitalWrite(READY_VOLTAGE, 1);
            delayMicroseconds(pushPeriod);
            digitalWrite(READY_VOLTAGE, 0);
            digitalWrite(OFF_VOLTAGE, 0);
            delayMicroseconds(1100);
            digitalWrite(OFF_VOLTAGE, 1);
            delayMicroseconds(switchTurnOffTime);
            digitalWrite(READY_PSU, 1);
            delayMicroseconds(pushPeriod);
            digitalWrite(READY_PSU, 0);
            delayMicroseconds(switchTurnOnTime);
          }
        }
        break;
      case 'd': 
        {
          digitalWrite(OFF_VOLTAGE, 1);
          clearEveryOutput();
          Serial.println("####################");
          Serial.println("Current sense resistance calibration completed,\nplease remember to upload the value if you want.");
        }
        break;
      case 'D':  
        {
          digitalWrite(OFF_VOLTAGE, 1);
          clearEveryOutput();
          Serial.println("####################");
          Serial.println("Current sense resistance calibration completed,\nplease remember to upload the value if you want.");
        }
        break;
      case 's': 
        {
          int read_temp;
          int measuring_time_temp;
          pinMode(READY_VOLTAGE, OUTPUT);
          digitalWrite(READY_VOLTAGE, 0);
          switchTurnOnTime = USBread();
          switchTurnOffTime = USBread();
          int setting_temp = USBread();
          accurate_I_only = setting_temp % 2;
          enable_accurate = setting_temp / 2;
          read_temp = USBread();
          sample_number = USBread() + 256 * read_temp;
          scan_mode = USBread();
          read_temp = USBread();
          measuring_time_temp = USBread() + 256 * read_temp;
          if (measuring_time_temp > 210)  
            measuring_time_temp++;
          if (scan_mode > 1) {
            scan_turn_on_time = measuring_time_temp * sample_number + switchTurnOnTime + SCAN_BUFFER; 
            sample_number = 1;
          } else
            scan_turn_on_time = measuring_time_temp + switchTurnOnTime + SCAN_BUFFER;  
        }

        break;
      case '*':  
        {
          char tempc = 0;
          int i = 0;
          char commandTemp[10] = { 0 };
          while (tempc != '\n') {
            while (Serial.available() == 0) {
            }
            delayMicroseconds(10);
            tempc = Serial.read();
            commandTemp[i] = tempc;
            i++;
          }
          commandTemp[--i] = '\0';
          char target[10] = { 'I', 'D', 'N', '?' };
          if (strcmp(commandTemp, target) == 0)
            Serial.println("IDN= ESP32_2_9");
        }
        break;
      case 'L': 
        pinMode(READY_VOLTAGE, INPUT);
        break;
      case 'z':
        Serial.println("zzzzzzzz");
        Serial.println(current_state);
        break;
      default:
        {
          error_count++;
          Serial.println("!!!!!!!!!!!!!!!!!!");
          Serial.print("error count= ");
          Serial.println(error_count);
          Serial.print("error type: command'");
          Serial.print(commandRead);
          Serial.println("' is not a viable command");
          Serial.print("which ASCII value is '");
          int i = commandRead;
          Serial.println(i);
        }
        break;
    }
  } else {
    switch (receive_state) {
      case 'a':
        current_mode[receive_current_state] = commandRead;
        receive_current_state++;
        if (receive_current_state == channel_count) { 

          receive_state = 0;
          receive_current_state = 0;


          int switch_temp[channel_count];

          for (int ii = 0; ii < channel_count; ii++) {  
            switch_temp[ii] = 0;
          }
          serialOut(DATA, PUSH_PIN, READY_PIN_CURRENT_POS, pushPeriod, switch_temp, channel_count);
          delay(1);  


          for (int ii = 0; ii < channel_count; ii++) {
            if (current_mode[ii] == 2) {
              switch_temp[ii] = 1;
              N_channel_count++;
            } else
              switch_temp[ii] = 0;
          }
          serialOut(DATA, PUSH_PIN, READY_PIN_CURRENT_NEG, pushPeriod, switch_temp, channel_count);  
          //delay(100);  
          delay(1); 


          for (int ii = 0; ii < channel_count; ii++) {
            if (current_mode[ii] == 1) {
              switch_temp[ii] = 1;
              P_channel_count++;
            } else
              switch_temp[ii] = 0;
          }
          serialOut(DATA, PUSH_PIN, READY_PIN_CURRENT_POS, pushPeriod, switch_temp, channel_count);  
          if (current_state == 65535) {
            Serial.println("####################");
            Serial.println("Measure finished, remember to shut down power supply");
          } else {
            /*
            Serial.println("====================");
            Serial.print("current_state= ");
            */
            Serial.println(current_state);
            /*Serial.print("recieve current mode: ");
            for (int j = 0; j < channel_count; j++) {
              Serial.print(current_mode[j], DEC);
            }
            
            Serial.println("")
            ;*/
          }
        }
        break;
      default:

        error_count++;
        Serial.println("!!!!!!!!!!!!!!!!!!");
        Serial.print("error count= ");
        Serial.println(error_count);
        Serial.print("error type:current mode command'");
        Serial.print(commandRead);
        break;
    }
  }
}
