# R2MS_Lite_API_Server開發

### 開發環境
+ 作業系統: Win10 64bit
+ 使用lazarus 3.6 (lazarus-3.6-fpc-3.2.2-win64.exe)

### 目標環境
+ Win10 64bit

### 筆記
+ 預設運作平台: Default，應該就是win10 64bit。

## 開發紀錄
1. 建立新專案。
   1.1 按下「Project>New Project ...」。
   1.2 選擇「Project>Application 」之後按「OK」。
2. 獨立把專案存到指定資料夾中，以利日後管理。大部分自訂程式碼都會是相對路徑，未來只需要帶走這個資料夾即可在其他地方重新使用。
   2.1 按下「File->Save Project As」。
3. 專案設定需要調整。
  3.1.1 設定「Application」頁面下利用「Load Icon 」按鈕更換自訂圖示。
    3.1.1.1 說明: 程式圖示。
    3.1.2 檢查「Application」頁面下「Execution Level 」為「As Invoker」。
      3.1.2.1 說明: 「As Invoker、Highest Available」都是普通權限就可以執行，「requireAdministrator」是執行前請求獲得管理者權限才能執行。
