// 硬體架構: 4 顆 SN74HC595 並接
// 在並接架構中，所有 SN74HC595 的 SRCLR_PIN、SER_PIN 和 SRCLK_PIN 是共用的。
// 每顆 SN74HC595 會有自己獨立的 RCLK_PIN，用來鎖存資料。
// 這意味著資料會同時傳送到四顆 IC，但是每顆 IC 會根據其自己的 RCLK_PIN 獨立鎖存資料。

// 設定 SN74HC595 連接到 ESP32S 的腳位
const int SRCLR_PIN = 14;  // 控制清除暫存器（SRCLR），接到 ESP32S 的 GPIO14
const int SER_PIN = 21;    // 資料輸入端（SER），接到 ESP32S 的 GPIO21
const int SRCLK_PIN = 23;  // 移位時脈（SRCLK），接到 ESP32S 的 GPIO23

// 每顆 SN74HC595 的鎖存引腳（RCLK）分別設定
const int RCLK_PIN_P_ready = 13;   // 第一顆 SN74HC595 鎖存引腳(對應最上排LED燈)
const int RCLK_PIN_N_ready = 12;   // 第二顆 SN74HC595 鎖存引腳(對應第二排LED燈)
const int RCLK_PIN_V_PSU_ready = 22;   // 第三顆 SN74HC595 鎖存引腳(對應第三排LED燈)
const int RCLK_PIN_V_ready = 26;   // 第四顆 SN74HC595 鎖存引腳(對應第四排LED燈)

// 其他OE已接地
const int OE_PIN_V_enable = 25;   // 第四顆 SN74HC595 OE引腳(對應第四排LED燈)

// LED狀態資料
String LED_data;
//------------------------------------------------------
// SN74HC595 #1 LED，預設值為0=滅
String LED_1_01 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
String LED_1_02 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
String LED_1_03 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
String LED_1_04 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
String LED_1_05 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
String LED_1_06 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
String LED_1_07 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
String LED_1_08 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
//--
String LED_2_01 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
String LED_2_02 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
String LED_2_03 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
String LED_2_04 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
String LED_2_05 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
String LED_2_06 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
String LED_2_07 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
String LED_2_08 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
//--
String LED_3_01 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
String LED_3_02 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
String LED_3_03 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
String LED_3_04 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
String LED_3_05 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
String LED_3_06 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
String LED_3_07 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
String LED_3_08 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
//--
String LED_4_01 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
String LED_4_02 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
String LED_4_03 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
String LED_4_04 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
String LED_4_05 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
String LED_4_06 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
String LED_4_07 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
String LED_4_08 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
//------------------------------------------------------
void setup() {
  // 設定所有腳位為輸出模式
  pinMode(SRCLR_PIN, OUTPUT);  // 設定 SRCLR 引腳為輸出，控制清除暫存器
  pinMode(SER_PIN, OUTPUT);    // 設定 SER 引腳為輸出，傳送資料到移位暫存器
  pinMode(SRCLK_PIN, OUTPUT);  // 設定 SRCLK 引腳為輸出，控制移位時脈

  // 設定每個 SN74HC595 的鎖存引腳（RCLK）為輸出
  pinMode(RCLK_PIN_P_ready, OUTPUT);   // 第一顆 SN74HC595 鎖存引腳
  pinMode(RCLK_PIN_N_ready, OUTPUT);   // 第二顆 SN74HC595 鎖存引腳
  pinMode(RCLK_PIN_V_PSU_ready, OUTPUT);   // 第三顆 SN74HC595 鎖存引腳
  pinMode(RCLK_PIN_V_ready, OUTPUT);   // 第四顆 SN74HC595 鎖存引腳

  // 設定第四顆 SN74HC595 OE引腳為輸出
  pinMode(OE_PIN_V_enable, OUTPUT);   // 第四顆 SN74HC595 OE引腳

  // **初始化 SN74HC595，清除所有資料**
  digitalWrite(SRCLR_PIN, LOW);  // 拉低 SRCLR 引腳，清除移位暫存器和輸出寄存器的資料
  delay(10);          // 確保資料被清除
  digitalWrite(SRCLR_PIN, HIGH); // 拉高 SRCLR 引腳，恢復正常工作狀態

  // 清除所有 RCLK 引腳，確保資料不被誤鎖存
  digitalWrite(RCLK_PIN_P_ready, LOW);   
  digitalWrite(RCLK_PIN_N_ready, LOW);   
  digitalWrite(RCLK_PIN_V_PSU_ready, LOW);   
  digitalWrite(RCLK_PIN_V_ready, LOW);   

  // 設定第四顆 SN74HC595 OE引腳為LOW
  digitalWrite(OE_PIN_V_enable, LOW); 
  
  String LED_data;
  //------------------------------------------------------
  // **手動傳送資料到 SN74HC595 #1**
  LED_1_01 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
  LED_1_02 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
  LED_1_03 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
  LED_1_04 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
  LED_1_05 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
  LED_1_06 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
  LED_1_07 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
  LED_1_08 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮

  LED_data = LED_1_08 + LED_1_07 + LED_1_06 + LED_1_05 + LED_1_04 + LED_1_03 + LED_1_02 + LED_1_01;

  // 逐位傳送資料
  for (int i = 0; i < LED_data.length(); i++) {
    // 直接在條件語句中判斷資料位
    if (LED_data[i] == '1') {
      digitalWrite(SER_PIN, HIGH);  // 傳送 "1" (亮 LED)
    } else {
      digitalWrite(SER_PIN, LOW);   // 傳送 "0" (關 LED)
    }

    // 發送移位時脈
    digitalWrite(SRCLK_PIN, HIGH);  // 拉高 SRCLK，移位資料
    delayMicroseconds(2);           // 確保時脈脈衝的寬度
    digitalWrite(SRCLK_PIN, LOW);   // 拉低 SRCLK，完成移位

    delayMicroseconds(2);           // 控制每位資料移位的速度（這裡使用 2 微秒的延遲）
  }  
  
  // **鎖存資料到輸出寄存器**
  // 每顆 SN74HC595 的資料傳送完畢後，將其鎖存到輸出寄存器

  // 將資料從移位暫存器鎖存到第1顆 SN74HC595 的輸出寄存器
  digitalWrite(RCLK_PIN_P_ready, HIGH);  // 發送鎖存時脈
  delayMicroseconds(2);          // 等待鎖存完成
  digitalWrite(RCLK_PIN_P_ready, LOW);   // 拉低鎖存時脈，完成鎖存操作
  //------------------------------------------------------

  //------------------------------------------------------
  // **手動傳送資料到 SN74HC595 #2**
  LED_2_01 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
  LED_2_02 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
  LED_2_03 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
  LED_2_04 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
  LED_2_05 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
  LED_2_06 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
  LED_2_07 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
  LED_2_08 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮

  LED_data = LED_2_08 + LED_2_07 + LED_2_06 + LED_2_05 + LED_2_04 + LED_2_03 + LED_2_02 + LED_2_01;

  // 逐位傳送資料
  for (int i = 0; i < LED_data.length(); i++) {
    // 直接在條件語句中判斷資料位
    if (LED_data[i] == '1') {
      digitalWrite(SER_PIN, HIGH);  // 傳送 "1" (亮 LED)
    } else {
      digitalWrite(SER_PIN, LOW);   // 傳送 "0" (關 LED)
    }

    // 發送移位時脈
    digitalWrite(SRCLK_PIN, HIGH);  // 拉高 SRCLK，移位資料
    delayMicroseconds(2);           // 確保時脈脈衝的寬度
    digitalWrite(SRCLK_PIN, LOW);   // 拉低 SRCLK，完成移位

    delayMicroseconds(2);           // 控制每位資料移位的速度（這裡使用 2 微秒的延遲）
  }  
  
  // **鎖存資料到輸出寄存器**
  // 每顆 SN74HC595 的資料傳送完畢後，將其鎖存到輸出寄存器

  // 將資料從移位暫存器鎖存到第2顆 SN74HC595 的輸出寄存器
  digitalWrite(RCLK_PIN_N_ready, HIGH);  // 發送鎖存時脈
  delayMicroseconds(2);          // 等待鎖存完成
  digitalWrite(RCLK_PIN_N_ready, LOW);   // 拉低鎖存時脈，完成鎖存操作
  //------------------------------------------------------

  //------------------------------------------------------
  // **手動傳送資料到 SN74HC595 #3**
  LED_3_01 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
  LED_3_02 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
  LED_3_03 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
  LED_3_04 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
  LED_3_05 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
  LED_3_06 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
  LED_3_07 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮
  LED_3_08 = "0"; // 資料表示為文字 "0"=滅 和 "1"=亮

  LED_data = LED_3_08 + LED_3_07 + LED_3_06 + LED_3_05 + LED_3_04 + LED_3_03 + LED_3_02 + LED_3_01;

  // 逐位傳送資料
  for (int i = 0; i < LED_data.length(); i++) {
    // 直接在條件語句中判斷資料位
    if (LED_data[i] == '1') {
      digitalWrite(SER_PIN, HIGH);  // 傳送 "1" (亮 LED)
    } else {
      digitalWrite(SER_PIN, LOW);   // 傳送 "0" (關 LED)
    }

    // 發送移位時脈
    digitalWrite(SRCLK_PIN, HIGH);  // 拉高 SRCLK，移位資料
    delayMicroseconds(2);           // 確保時脈脈衝的寬度
    digitalWrite(SRCLK_PIN, LOW);   // 拉低 SRCLK，完成移位

    delayMicroseconds(2);           // 控制每位資料移位的速度（這裡使用 2 微秒的延遲）
  }  
  
  // **鎖存資料到輸出寄存器**
  // 每顆 SN74HC595 的資料傳送完畢後，將其鎖存到輸出寄存器

  // 將資料從移位暫存器鎖存到第3顆 SN74HC595 的輸出寄存器
  digitalWrite(RCLK_PIN_V_PSU_ready, HIGH);  // 發送鎖存時脈
  delayMicroseconds(2);          // 等待鎖存完成
  digitalWrite(RCLK_PIN_V_PSU_ready, LOW);   // 拉低鎖存時脈，完成鎖存操作
  //------------------------------------------------------

  //------------------------------------------------------
  // **手動傳送資料到 SN74HC595 #4**
  LED_4_01 = "1"; // 資料表示為文字 "0"=滅 和 "1"=亮
  LED_4_02 = "1"; // 資料表示為文字 "0"=滅 和 "1"=亮
  LED_4_03 = "1"; // 資料表示為文字 "0"=滅 和 "1"=亮
  LED_4_04 = "1"; // 資料表示為文字 "0"=滅 和 "1"=亮
  LED_4_05 = "1"; // 資料表示為文字 "0"=滅 和 "1"=亮
  LED_4_06 = "1"; // 資料表示為文字 "0"=滅 和 "1"=亮
  LED_4_07 = "1"; // 資料表示為文字 "0"=滅 和 "1"=亮
  LED_4_08 = "1"; // 資料表示為文字 "0"=滅 和 "1"=亮

  LED_data = LED_4_08 + LED_4_07 + LED_4_06 + LED_4_05 + LED_4_04 + LED_4_03 + LED_4_02 + LED_4_01;

  // 逐位傳送資料
  for (int i = 0; i < LED_data.length(); i++) {
    // 直接在條件語句中判斷資料位
    if (LED_data[i] == '1') {
      digitalWrite(SER_PIN, HIGH);  // 傳送 "1" (亮 LED)
    } else {
      digitalWrite(SER_PIN, LOW);   // 傳送 "0" (關 LED)
    }

    // 發送移位時脈
    digitalWrite(SRCLK_PIN, HIGH);  // 拉高 SRCLK，移位資料
    delayMicroseconds(2);           // 確保時脈脈衝的寬度
    digitalWrite(SRCLK_PIN, LOW);   // 拉低 SRCLK，完成移位

    delayMicroseconds(2);           // 控制每位資料移位的速度（這裡使用 2 微秒的延遲）
  }  
  
  // **鎖存資料到輸出寄存器**
  // 每顆 SN74HC595 的資料傳送完畢後，將其鎖存到輸出寄存器

  // 將資料從移位暫存器鎖存到第4顆 SN74HC595 的輸出寄存器
  digitalWrite(RCLK_PIN_V_ready, HIGH);  // 發送鎖存時脈
  delayMicroseconds(2);          // 等待鎖存完成
  digitalWrite(RCLK_PIN_V_ready, LOW);   // 拉低鎖存時脈，完成鎖存操作
  //------------------------------------------------------

}

void loop() {
  // 因為我們只需要執行一次資料傳送，所以 loop 這裡不需要進行任何操作
}
