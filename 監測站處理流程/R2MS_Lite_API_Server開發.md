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
  + 1.1 按下「Project>New Project ...」。  
  1.2 選擇「Project>Application 」之後按「OK」。  
2. 獨立把專案存到指定資料夾中，以利日後管理。大部分自訂程式碼都會是相對路徑，未來只需要帶走這個資料夾即可在其他地方重新使用。  
  2.1 按下「File->Save Project As」。  
3. 專案設定需要調整。  
  3.1.1 設定「Application」頁面下利用「Load Icon 」按鈕更換自訂圖示。  
    3.1.1.1 說明: 程式圖示。  
  3.1.2 檢查「Application」頁面下「Execution Level 」為「As Invoker」。  
    3.1.2.1 說明: 「As Invoker、Highest Available」都是普通權限就可以執行，「requireAdministrator」是執行前請求獲得管理者權限才能執行。  
5. 預設狀況下就有一個Form元件存在，預設名稱叫做「Form1」，先做一些基礎設定以利後續排版。  
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
6. 經典的Windows應用程式會在下方放置一個狀態列。如果不趕時間應該避免當作SimplePanel來使用。建議使用標準的(TStatusPanels)來規劃出多分隔的狀態列。可參考經典軟體「記事本」與「NotePad++」的狀態列規劃。  
  5.1 拖拉一個「TStatusBar」到「Form1」中。預設名稱會是「StatusBar1」。  
  5.2 設定「TStatusBar」的「Properties」。這裡主要列出常用的一些。  
    5.2.1 檢查「StatusBar1」的「Properties」頁面下「Align」為「alBottom」。  
      5.2.1.1 說明:設定狀態列位置緊貼窗體下方。  
    5.2.2 設定「StatusBar1」的「Properties」頁面下「Panel」，按下「...」後會出現編輯介面。從編輯介面建立5個TStatusPanels。  
      5.2.2.1 說明:建立狀態列中多個小版面。  
    5.2.3 設定各「TStatusPanels」的「Properties」。  
      5.2.3.1 檢查「TStatusPanels」的「Properties」頁面下「Alignment」為「taLeftJustify」。  
        5.2.3.1.1 說明:「taLeftJustify」是文字靠左對齊，「taCenter」是文字水平置中，「taRightJustify」是文字靠右對齊。注意，如果有人改掉「BiDiMode」可能會顛倒，所以建議不要動「BiDiMode」這個屬性。  
      5.2.3.2 檢查「TStatusPanels」的「Properties」頁面下「Style」為「psText」。  
        5.2.3.2.1 說明:「psText」是可寫文字，「psOwnerDraw」是用另外的函數處理非文字。  
      5.2.3.3 設定「TStatusPanels」的「Properties」頁面下「Text」為「初始文字」。  
        5.2.3.3.1 說明:初始文字可以預先在排版階段測試顯示效果，其中最靠右會被吃掉字元，請依需求測試設定文字內容。  
      5.2.3.4 設定「TStatusPanels」的「Properties」頁面下「Width」為「120」。  
        5.2.3.4.1 說明:可以搭配初始文字來調整Width，以利排版。預設只能靠右對齊來分配欄位，其他效果則需要利用程式碼做調整。  
    5.2.4 設定「StatusBar1」的「Properties」頁面下「SimplePanel」為「false」。  
      5.2.4.1 說明:要使前面設定的TStatusPanels有效，須將「SimplePanel」設為「false」。  
  5.3 設定「TStatusBar」的「Event」。  
    5.3.1 設定「StatusBar1」的「Event」頁面下「OnResize」為如下程式碼。  
