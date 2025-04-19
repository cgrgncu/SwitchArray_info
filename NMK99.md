# 小霸王 NMK99 二合一開發板 使用安信可原廠晶片 品質保證 esp32 esp32cam 支援Wifi BLE
+ 購買位置: https://shopee.tw/product/5742314/22959591391/
+ 教材: https://twgo.io/nmk99
+ 教學影片: https://youtu.be/1VpUTSRZySM

### 使用前準備工作
+ 拆掉包裝，貼貼紙，參考網頁說明。
+ 準備好MicroUSB線，必須要可以傳輸資料的。
+ 接上電腦，確認電腦上CH340驅動是否安裝。

### 開發注意事項
+ 模塊: 小霸王 NMK99 二合一開發板（基於 ESP32-S 系列微控制器）
  - 供電方式: MicroUSB (CH340)
  - 開發環境: Arduino IDE (選擇開發板:ESP32 Wrover Module)
  - 特殊腳位介紹:
    - **GPIO0（BOOT 按鈕）**:
    - 用於進入 **下載模式**，可用來燒錄程序。
      - 若用於偵測按鈕是否按下，避免將其拉低，否則會干擾燒錄過程。
    - **GPIO2**: 接到板上的內建 綠色 LED 燈。  
      - 腳位建議使用方式：
      ```c
      const int GREEN_LED_PIN = 2;  // 內建綠色 LED 所使用的腳位 (GPIO2)，HIGH=關燈，LOW=開燈。使用SD卡時，此腳位被占用。
      ```
    - **GPIO32**: 接到板上的內建 NeoPixel LED 燈(WS2812燈珠)。
      - 腳位建議使用方式：
      ```c
      const int NEO_LED_PIN = 32;  // 用於控制 NeoPixel LED 的腳位 (GPIO32)。使用相機時，此腳位被占用。
      ```
      - 建議使用函式庫：
      ```c
      #include <Adafruit_NeoPixel.h>  // 使用 NeoPixel LED 時，請先安裝 Adafruit_NeoPixel 函式庫。
      ```
    - **MicroUSB (CH340)**: 用於供電和串口通信的接口。
    - **SD 卡佔用的腳位**（使用 SDMMC 介面）:
      - **SDMMC_CLK (GPIO14)**: SD 卡的時鐘信號。
      - **SDMMC_CMD (GPIO15)**: SD 卡的命令信號。
      - **SDMMC_DATA0 (GPIO2)**: SD 卡的數據位 D0。
      - **SDMMC_DATA1 (GPIO4)**: SD 卡的數據位 D1。
      - **SDMMC_DATA2 (GPIO12)**: SD 卡的數據位 D2。
      - **SDMMC_DATA3 (GPIO13)**: SD 卡的數據位 D3。
      - **VCC (5V)**: 供電。
      - **GND**: 地線。
      - 建議使用函式庫：
      ```c
      #include "FS.h"  // 用於 SD 卡操作，支持 SDMMC 介面。
      #include "SD_MMC.h"  // 用於操作 SD 卡，使用 SDMMC 介面。
      ```
    - **OV2640 相機佔用的腳位**（使用並行接口）:
      - **D0 (GPIO5)**: 影像數據位 D0。
      - **D1 (GPIO18)**: 影像數據位 D1。
      - **D2 (GPIO19)**: 影像數據位 D2。
      - **D3 (GPIO21)**: 影像數據位 D3。
      - **D4 (GPIO36)**: 影像數據位 D4。
      - **D5 (GPIO39)**: 影像數據位 D5。
      - **D6 (GPIO34)**: 影像數據位 D6。
      - **D7 (GPIO35)**: 影像數據位 D7。
      - **XCLK (GPIO0)**: 影像時鐘信號 XCLK。
      - **PCLK (GPIO22)**: 逐行時鐘信號 PCLK。
      - **VSYNC (GPIO25)**: 垂直同步信號 VSYNC。
      - **HREF (GPIO23)**: 水平同步信號 HREF。
      - **SSCB SDA (GPIO26)**: I2C 數據線（用於相機控制設定）
      - **SSCB SCL (GPIO27)**: I2C 時鐘線（用於相機控制設定）
      - **PWDN (GPIO32)**: 相機電源控制腳位。
      - **RESET (-1)**: 相機重設腳位，不使用。
      - 建議使用函式庫：
      ```c
      #include "esp_camera.h"  // 用於配置和控制相機，支持並行接口。
      ```
