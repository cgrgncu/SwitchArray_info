# NAS(DS224+)

+ ### 3140104-07-01823 單據: 11311A3124
+ 群輝科技 網路儲存伺服器(型別DS224+)
+ 單價: 35950
+ Synology DS224+ 網路儲存伺服器 (含Synology HAT3310 12TB*2顆) 約27900元 
  + MAC#1: 9009D0734EDD
  + MAC#2: 9009D0734EDE
  + S/N: 2490VVBRMHEFVVT
+ UPS(Cp1000pfclcda) 約4490元

### 3140104-07-01824 單據: 11311A3124
+ 單價: 35950
+ Synology DS224+ 網路儲存伺服器 (含Synology HAT3310 12TB*2顆)
  + MAC#1: 9009D0735D81
  + MAC#2: 9009D0735D82
  + S/N: 2490VVBRKKC6CK
+ UPS(Cp1000pfclcda) 約4490元
+ 這台拿去MT長期觀測站使用。

#### 安裝步驟
+ 安裝Synology Drive Server
  + 過程中會安裝 Universal Viewer, Node.js v20, Synology應用程式服務。
+ 建立一個普通的使用者，「CGRG_S000」。密碼:4500。
+ 用PC安裝桌面板，然後填入正確IP用帳號密碼登入。然後選右邊的「備份任務」。
+ 搞錯就要刪除任務重來。
+ 備份任務>打勾XXX\Local資料夾>備份改成/home/R2MS_Lite_Drive/S000
+ 然後再找FTP下載回來。
