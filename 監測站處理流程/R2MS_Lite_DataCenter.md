# 先用虛擬機開發看看 R2MS_Lite_DataCenter

### 使用開發環境:
+ Win10_64_CHT_START_v20241022a.ova

### XAMPP
+ (X)目前Synology NAS已經可以支援 PHP8.2，選擇使用「xampp-windows-x64-8.2.12-0-VS16-installer.exe」，希望相容性好。
  + 只安裝最少內容
  + 用管理員權限開Service。點那個紅色叉讓他變綠色。
+ (O)PHP8.2的ZIP功能有問題，退回使用「xampp-windows-x64-7.4.27-2-VC15-installer.exe」。
  + 只安裝最少內容
  + 用管理員權限開Service。點那個紅色叉讓他變綠色。
    
### 連接埠轉發
+ 0.0.0.0:80->0.0.0.0:80
