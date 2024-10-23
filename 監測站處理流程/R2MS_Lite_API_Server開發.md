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
4. 預設狀況下就有一個Form元件存在，預設名稱叫做「Form1」，先做一些基礎設定以利後續排版。
   4.1 設定「Form1」的「properties」。這裡主要列出常用的一些。
     4.1.1 檢查「Form1」的「properties」頁面下「BorderIcons」為「[biSystemMenu,biMinimize,biMaximize]」。
       4.1.1.1 說明:設定窗體右上角的按鈕如果存在的話要不要被啟用。「[biSystemMenu,biMinimize,biMaximize]」表示這三個被打勾。
     4.1.2 檢查「Form1」的「properties」頁面下「BorderStyle」為「bsSizeable」。
       4.1.2.1 說明:設定窗體的樣式。可依需求嘗試不同風格決定是否符合需求。
     4.1.2 設定「Form1」的「properties」頁面下「Caption」為「R2MS_Lite_API_Server」。
       4.1.2.1 說明:設定窗體的標題列文字。
     4.1.3 設定「Form1」的「properties」頁面下「Color」為「clWindow」。
       4.1.3.1 說明:設定成白色使工具列元件底色是白色。
     4.1.4 設定「Form1」的「properties」頁面下「Height」為「600」。
       4.1.4.1 說明:設定窗體的外框高度。
     4.1.5 設定「Form1」的「properties」頁面下「Position」為「poScreenCenter」。
       4.1.5.1 說明:設定窗體的出現位置，建議是用「poScreenCenter」，在螢幕中央。
     4.1.6 設定「Form1」的「properties」頁面下「Width」為「800」。
       4.1.6.1 說明:設定窗體的外框寬度。
     > 以上預設尺寸確定後就可以開始排版。
