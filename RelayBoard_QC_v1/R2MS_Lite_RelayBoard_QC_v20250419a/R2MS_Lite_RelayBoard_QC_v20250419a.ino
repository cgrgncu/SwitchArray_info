//**************************************************************************
//   Name: R2MS_Lite_RelayBoard_QC_v20250419a.ino  
//   Copyright (C) 2025 HsiupoYeh. All rights reserved.
//   Author: HsiupoYeh 
//   Version: v20250419a
//   Description: 
//   使用模塊: 小霸王 NMK99 二合一開發板（基於 ESP32-S 系列微控制器）
//
//      - 腳位介紹:
//        - **GPIO0（BOOT 按鈕）**:
//          - 用於進入 **下載模式**，可用來燒錄程序。
//          - 若用於偵測按鈕是否按下，避免將其拉低，否則會干擾燒錄過程。
//        - **GPIO2**: 保留給綠色 LED 燈。  
//          - 腳位建議使用方式：const int GREEN_LED_PIN = 2;  // 內建綠色 LED 所使用的腳位 (GPIO2)，HIGH=關燈，LOW=開燈。使用SD卡時，此腳位被占用。
//        - **GPIO32**: 保留給 NeoPixel LED 燈。
//          - 腳位建議使用方式：const int NEO_LED_PIN = 32;  // 用於控制 NeoPixel LED 的腳位 (GPIO32)。使用相機時，此腳位被占用。
//          - 建議使用函式庫：#include <Adafruit_NeoPixel.h>  // 使用 NeoPixel LED 時，請先安裝 Adafruit_NeoPixel 函式庫。
//        - **5V (VCC)**: 供應板子運行所需的 5V 電壓。
//        - **GND**: 地線，所有電路的參考電壓。
//        - **MicroUSB (CH340)**: 用於供電和串口通信的接口。
//   
//      - **SD 卡佔用的腳位**（使用 SDMMC 介面）:
//        - **SDMMC_CLK (GPIO14)**: SD 卡的時鐘信號。
//        - **SDMMC_CMD (GPIO15)**: SD 卡的命令信號。
//        - **SDMMC_DATA0 (GPIO2)**: SD 卡的數據位 D0。
//        - **SDMMC_DATA1 (GPIO4)**: SD 卡的數據位 D1。
//        - **SDMMC_DATA2 (GPIO12)**: SD 卡的數據位 D2。
//        - **SDMMC_DATA3 (GPIO13)**: SD 卡的數據位 D3。
//        - **VCC (5V)**: 供電。
//        - **GND**: 地線。
//          - 建議使用函式庫：#include "FS.h"  // 用於 SD 卡操作，支持 SDMMC 介面。
//          - 建議使用函式庫：#include "SD_MMC.h"  // 用於操作 SD 卡，使用 SDMMC 介面。
//   
//      - **OV2640 相機佔用的腳位**（使用並行接口）:
//        - **D0 (GPIO5)**: 影像數據位 D0。
//        - **D1 (GPIO18)**: 影像數據位 D1。
//        - **D2 (GPIO19)**: 影像數據位 D2。
//        - **D3 (GPIO21)**: 影像數據位 D3。
//        - **D4 (GPIO36)**: 影像數據位 D4。
//        - **D5 (GPIO39)**: 影像數據位 D5。
//        - **D6 (GPIO34)**: 影像數據位 D6。
//        - **D7 (GPIO35)**: 影像數據位 D7。
//        - **XCLK (GPIO0)**: 影像時鐘信號 XCLK。
//        - **PCLK (GPIO22)**: 逐行時鐘信號 PCLK。
//        - **VSYNC (GPIO25)**: 垂直同步信號 VSYNC。
//        - **HREF (GPIO23)**: 水平同步信號 HREF。
//        - **SSCB SDA (GPIO26)**: I2C 數據線（用於相機控制設定）
//        - **SSCB SCL (GPIO27)**: I2C 時鐘線（用於相機控制設定）
//        - **PWDN (GPIO32)**: 相機電源控制腳位。
//        - **RESET (-1)**: 相機重設腳位，不使用。
//          - 建議使用函式庫：#include "esp_camera.h"  // 用於配置和控制相機，支持並行接口。
//   
//   供電方式: MicroUSB (CH340)
//   開發環境: Arduino IDE (選擇開發板:ESP32 Wrover Module)
//
//   目標: 檢測待測電路板 R2MS_Lite_RelayBoard 功能是否正常。
//   共設計 5 項檢測工作：
//    1. 全部檢測 - 電壓檢測 GND (細黑)
//    2. 第 1 排單獨檢測 - 電阻檢測 PSU+ (粗橙)
//    3. 第 2 排單獨檢測 - 電阻檢測 PSU- (粗灰)
//    4. 第 3 排單獨檢測 - 電阻檢測 DMM- (粗黑)
//    5. 第 4 排單獨檢測 - 電阻檢測 DMM+ (粗紅)
//**************************************************************************
//--------------------------------------------------------
// 全域宣告
#include <Adafruit_NeoPixel.h>  // 引入 NeoPixel 函式庫
//--
const int BOOT_BUTTON_PIN = 0; // GPIO0 作為 BOOT 按鈕
const int GREEN_LED_PIN = 2;  // 內建綠色 LED 所使用的腳位 (GPIO2)，HIGH=關燈，LOW=開燈。使用SD卡時，此腳位被占用。
const int NEO_LED_PIN = 32;   // 用於控制 NeoPixel LED 的腳位 (GPIO32)。使用相機時，此腳位被占用。
const int NEO_LED_COUNT = 1;  // NeoPixel LED 的數量 (1顆)
//--
// 初始化 NeoPixel 控制
Adafruit_NeoPixel pixels(NEO_LED_COUNT, NEO_LED_PIN, NEO_GRB + NEO_KHZ800);
//--
// 待測物的硬體架構: 4 顆 SN74HC595 並接
// 在並接架構中，所有 SN74HC595 的 SRCLR_PIN、SER_PIN 和 SRCLK_PIN 是共用的。
// 每顆 SN74HC595 會有自己獨立的 RCLK_PIN，用來鎖存資料。
// 這意味著資料會同時傳送到四顆 IC，但是每顆 IC 會根據其自己的 RCLK_PIN 獨立鎖存資料。
// 實際連接腳位如下:
// 設定 SN74HC595 連接到 ESP32S 的腳位 (4 顆 SN74HC595都接相同的 ESP32S腳位)
const int SRCLR_PIN = 14;  // 控制清除暫存器（SRCLR），接到 ESP32S 的 GPIO14
const int SER_PIN = 21;    // 資料輸入端（SER），接到 ESP32S 的 GPIO21
const int SRCLK_PIN = 23;  // 移位時脈（SRCLK），接到 ESP32S 的 GPIO23

// 每顆 SN74HC595 的鎖存引腳（RCLK）分別設定
const int RCLK_PIN_P_ready = 13;   // 第一顆 SN74HC595 鎖存引腳(對應最上排LED燈)
const int RCLK_PIN_N_ready = 12;   // 第二顆 SN74HC595 鎖存引腳(對應第二排LED燈)
const int RCLK_PIN_V_PSU_ready = 22;   // 第三顆 SN74HC595 鎖存引腳(對應第三排LED燈)
const int RCLK_PIN_V_ready = 26;   // 第四顆 SN74HC595 鎖存引腳(對應第四排LED燈)

// 第一顆 SN74HC595 OE引腳(對應第四排LED燈) 已經接地不用設定
// 第二顆 SN74HC595 OE引腳(對應第四排LED燈) 已經接地不用設定
// 第三顆 SN74HC595 OE引腳(對應第四排LED燈) 已經接地不用設定
const int OE_PIN_V_enable = 25;   // 第四顆 SN74HC595 OE引腳(對應第四排LED燈)

// 記錄當前狀態，從 0 開始（預設為狀態1）
int current_state = 0; // 初始狀態為 0 (狀態 1)

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
void set_LED_Data(String LED_n_01, String LED_n_02, String LED_n_03, String LED_n_04, String LED_n_05, String LED_n_06, String LED_n_07, String LED_n_08, int RCLK_PIN) {
  // 把傳入的 8 個字串按倒序拼接成一個新的資料字串
  String LED_data = LED_n_08 + LED_n_07 + LED_n_06 + LED_n_05 + LED_n_04 + LED_n_03 + LED_n_02 + LED_n_01;

  // 逐位傳送資料
  for (int i = 0; i < LED_data.length(); i++) {
    // 判斷每一位的資料是否為 "1"，如果是，則點亮 LED
    if (LED_data[i] == '1') {
      digitalWrite(SER_PIN, HIGH);  // 傳送 "1" (亮 LED)
    } else {
      digitalWrite(SER_PIN, LOW);   // 傳送 "0" (關 LED)
    }

    // 發送移位時脈
    digitalWrite(SRCLK_PIN, HIGH);  // 拉高 SRCLK，移位資料
    delayMicroseconds(2);           // 等待時脈脈衝
    digitalWrite(SRCLK_PIN, LOW);   // 拉低 SRCLK，完成移位
    delayMicroseconds(2);           // 控制每位資料移位的速度
  }

  // 鎖存資料到輸出寄存器
  digitalWrite(RCLK_PIN, HIGH);  // 發送鎖存時脈
  delayMicroseconds(2);          // 等待鎖存完成
  digitalWrite(RCLK_PIN, LOW);   // 拉低鎖存時脈，完成鎖存操作
}

void setup() {
  //--------------------------------------------------------
  // 初始化:
  //-- 
  Serial.begin(115200);  // 設置波特率為115200，根據需要調整
  pinMode(BOOT_BUTTON_PIN, INPUT_PULLUP);  // 設定 BOOT 按鈕為輸入模式，假設按鈕接地，所以使用 INPUT_PULLUP
  pinMode(GREEN_LED_PIN, OUTPUT);  // 設定內建綠色LED為輸出
  pixels.begin(); // 初始化 NeoPixel LED
  pixels.setBrightness(10);  // 設定 NeoPixel LED 亮度為 10 (0-255)
  //-- 
  // 設定SN74HC595共用腳位為輸出模式
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
  //--------------------------------------------------------

  //--------------------------------------------------------
  // 印出韌體相關資訊
  Serial.println("**************************************");
  Serial.println("R2MS_Lite_RelayBoard_QC Firmware");
  Serial.println("**************************************");
  Serial.println("Author: HsiupoYeh");
  Serial.println("Version: v20250419a");
  Serial.println("目標: 檢測待測電路板 R2MS_Lite_RelayBoard 功能是否正常。");
  Serial.println("共設計 5 項檢測工作：");
  Serial.println("1. 全部檢測 - 電壓檢測 GND (細黑)");
  Serial.println("2. 第 1 排單獨檢測 - 電阻檢測 PSU+ (粗橙)");
  Serial.println("3. 第 2 排單獨檢測 - 電阻檢測 PSU- (粗灰)");
  Serial.println("4. 第 3 排單獨檢測 - 電阻檢測 DMM- (粗黑)");
  Serial.println("5. 第 4 排單獨檢測 - 電阻檢測 DMM+ (粗紅)");
  Serial.println("**************************************");
  //--------------------------------------------------------

  //--------------------------------------------------------
  // 開機 LED 歡迎燈號(控制閃爍)  
  digitalWrite(GREEN_LED_PIN, LOW);  // 開啟綠色 LED
  delay(100);  // 100 毫秒
  digitalWrite(GREEN_LED_PIN, HIGH); // 關閉綠色 LED
  delay(100);  // 100 毫秒
  digitalWrite(GREEN_LED_PIN, LOW);  // 開啟綠色 LED
  delay(100);  // 100 毫秒
  digitalWrite(GREEN_LED_PIN, HIGH); // 關閉綠色 LED
  delay(100);  // 100 毫秒
  digitalWrite(GREEN_LED_PIN, LOW);  // 開啟綠色 LED
  delay(100);  // 100 毫秒
  digitalWrite(GREEN_LED_PIN, HIGH); // 關閉綠色 LED
  delay(100);  // 100 毫秒
  // 開啟 LED 1 秒鐘，表示開機完成
  digitalWrite(GREEN_LED_PIN, LOW);  // 開啟綠色 LED
  delay(1000);  // 1000 毫秒
  digitalWrite(GREEN_LED_PIN, HIGH); // 綠色 LED 保持熄滅
  //--------------------------------------------------------

  //--------------------------------------------------------
  // 開機 NeoPixel LED 歡迎燈號(控制顏色變換) 
  pixels.setPixelColor(0, pixels.Color(255, 70, 0)); // 顯示橙色
  pixels.show();
  delay(500);  // 500 毫秒
  pixels.setPixelColor(0, pixels.Color(100, 100, 100)); // 顯示灰色
  pixels.show();
  delay(500);  // 500 毫秒
  pixels.setPixelColor(0, pixels.Color(0, 0, 255)); // 顯示藍色
  pixels.show();
  delay(500);  // 500 毫秒  
  pixels.setPixelColor(0, pixels.Color(255, 0, 0)); // 顯示紅色
  pixels.show();  
  delay(500);  // 500 毫秒
  // 關閉 NeoPixel LED，顯示結束
  pixels.setPixelColor(0, pixels.Color(0, 0, 0)); // 關閉 NeoPixel LED
  pixels.show();
  //--------------------------------------------------------

  //--------------------------------------------------------
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
  //--------------------------------------------------------

  //------------------------------------------------------
  // 使用 set_LED_Data 函數傳送資料
  // 第一顆 SN74HC595
  set_LED_Data("0", "0", "0", "0", "0", "0", "0", "0", RCLK_PIN_P_ready);

  // 第二顆 SN74HC595
  set_LED_Data("0", "0", "0", "0", "0", "0", "0", "0", RCLK_PIN_N_ready);

  // 第三顆 SN74HC595
  set_LED_Data("0", "0", "0", "0", "0", "0", "0", "0", RCLK_PIN_V_PSU_ready);

  // 第四顆 SN74HC595
  set_LED_Data("0", "0", "0", "0", "0", "0", "0", "0", RCLK_PIN_V_ready);
  //------------------------------------------------------
}

void loop() {
  // 主要的程式邏輯
  // 偵測 BOOT 按鈕是否被按下
  if (digitalRead(BOOT_BUTTON_PIN) == LOW) {  // 按鈕按下時 GPIO0 拉低
    delay(200);  // 防抖，避免重複觸發

    // 切換狀態
    current_state = (current_state + 1) % 6;  // 確保狀態在 0 到 5 之間循環

    // 根據當前狀態更新 LED 顯示
    switch (current_state) {
      case 0:  // 狀態 1: 四排都是 0
        set_LED_Data("0", "0", "0", "0", "0", "0", "0", "0", RCLK_PIN_P_ready);  // 第一顆 LED
        set_LED_Data("0", "0", "0", "0", "0", "0", "0", "0", RCLK_PIN_N_ready);  // 第二顆 LED
        set_LED_Data("0", "0", "0", "0", "0", "0", "0", "0", RCLK_PIN_V_PSU_ready);  // 第三顆 LED
        set_LED_Data("0", "0", "0", "0", "0", "0", "0", "0", RCLK_PIN_V_ready);  // 第四顆 LED
        digitalWrite(GREEN_LED_PIN, HIGH);  // 關閉綠色 LED
        pixels.setPixelColor(0, pixels.Color(0, 0, 0)); // 關閉 NeoPixel LED
        pixels.show();
        break;

      case 1:  // 狀態 2: 四排都是 1
        set_LED_Data("1", "1", "1", "1", "1", "1", "1", "1", RCLK_PIN_P_ready);  // 第一顆 LED
        set_LED_Data("1", "1", "1", "1", "1", "1", "1", "1", RCLK_PIN_N_ready);  // 第二顆 LED
        set_LED_Data("1", "1", "1", "1", "1", "1", "1", "1", RCLK_PIN_V_PSU_ready);  // 第三顆 LED
        set_LED_Data("1", "1", "1", "1", "1", "1", "1", "1", RCLK_PIN_V_ready);  // 第四顆 LED
        digitalWrite(GREEN_LED_PIN, LOW);  // 開啟綠色 LED
        pixels.setPixelColor(0, pixels.Color(0, 0, 0)); // 關閉 NeoPixel LED
        pixels.show();
        break;

      case 2:  // 狀態 3: 第一排是 1，其他都是 0
        set_LED_Data("1", "1", "1", "1", "1", "1", "1", "1", RCLK_PIN_P_ready);  // 第一顆 LED
        set_LED_Data("0", "0", "0", "0", "0", "0", "0", "0", RCLK_PIN_N_ready);  // 第二顆 LED
        set_LED_Data("0", "0", "0", "0", "0", "0", "0", "0", RCLK_PIN_V_PSU_ready);  // 第三顆 LED
        set_LED_Data("0", "0", "0", "0", "0", "0", "0", "0", RCLK_PIN_V_ready);  // 第四顆 LED
        digitalWrite(GREEN_LED_PIN, HIGH);  // 關閉綠色 LED
        pixels.setPixelColor(0, pixels.Color(255, 70, 0)); // 顯示橙色
        pixels.show();
        break;

      case 3:  // 狀態 4: 第二排是 1，其他都是 0
        set_LED_Data("0", "0", "0", "0", "0", "0", "0", "0", RCLK_PIN_P_ready);  // 第一顆 LED
        set_LED_Data("1", "1", "1", "1", "1", "1", "1", "1", RCLK_PIN_N_ready);  // 第二顆 LED
        set_LED_Data("0", "0", "0", "0", "0", "0", "0", "0", RCLK_PIN_V_PSU_ready);  // 第三顆 LED
        set_LED_Data("0", "0", "0", "0", "0", "0", "0", "0", RCLK_PIN_V_ready);  // 第四顆 LED
        digitalWrite(GREEN_LED_PIN, HIGH);  // 關閉綠色 LED
        pixels.setPixelColor(0, pixels.Color(100, 100, 100)); // 顯示灰色
        pixels.show();
        break;

      case 4:  // 狀態 5: 第三排是 1，其他都是 0
        set_LED_Data("0", "0", "0", "0", "0", "0", "0", "0", RCLK_PIN_P_ready);  // 第一顆 LED
        set_LED_Data("0", "0", "0", "0", "0", "0", "0", "0", RCLK_PIN_N_ready);  // 第二顆 LED
        set_LED_Data("1", "1", "1", "1", "1", "1", "1", "1", RCLK_PIN_V_PSU_ready);  // 第三顆 LED
        set_LED_Data("0", "0", "0", "0", "0", "0", "0", "0", RCLK_PIN_V_ready);  // 第四顆 LED
        digitalWrite(GREEN_LED_PIN, HIGH);  // 關閉綠色 LED
        pixels.setPixelColor(0, pixels.Color(0, 0, 255)); // 顯示藍色
        pixels.show();
        break;

      case 5:  // 狀態 6: 第四排是 1，其他都是 0
        set_LED_Data("0", "0", "0", "0", "0", "0", "0", "0", RCLK_PIN_P_ready);  // 第一顆 LED
        set_LED_Data("0", "0", "0", "0", "0", "0", "0", "0", RCLK_PIN_N_ready);  // 第二顆 LED
        set_LED_Data("0", "0", "0", "0", "0", "0", "0", "0", RCLK_PIN_V_PSU_ready);  // 第三顆 LED
        set_LED_Data("1", "1", "1", "1", "1", "1", "1", "1", RCLK_PIN_V_ready);  // 第四顆 LED
        digitalWrite(GREEN_LED_PIN, HIGH);  // 關閉綠色 LED        
        pixels.setPixelColor(0, pixels.Color(255, 0, 0)); // 顯示紅色
        pixels.show();
        break;
    }
  }  
}

