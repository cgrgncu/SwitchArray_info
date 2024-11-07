# R2MS_Lite_Manager 開發筆記  
+ 作者: HsiupoYeh  
+ 更新日期: 2024-11-07

## 開發環境  
+ Windows 10 22H2 64bit 企業版 繁體中文(SW_DVD9_Win_Pro_10_22H2.19_64BIT_ChnTrad_Pro_Ent_EDU_N_MLF_X23-74684.ISO)  
+ Lazarus 3.6 (lazarus-3.6-fpc-3.2.2-win64.exe)
  + 並安裝「Indy10」、「UniqueInstance」。
  + 有需要可以用「anchordockingdsgn 1.0」、「dockedformediteor 0.0」固定IDE。

## 運行需求  
- Windosw作業系統。  
- 可運行64位元應用程式。  

### 備忘  
+ 預設運作平台: Default，應該就是win10 64bit。
+ 依照官網建議，為了避免DPI問題，各項操作建議(安裝IDE、設計窗體、編寫程式碼)在縮放大小100%的情況下進行。編譯出來的軟體可以拿去其他DPI設定下的電腦測試。
  + 使用解析度: 1920x1080
  + 縮放大小: 100%

### 開發紀錄(製作APP Icon)  
+ 使用工具1: https://icon.kitchen/  
  + IOS Icon  
  + Text: 「Manager」  
  + BackGround>Type=「Gradient」  
  + More>Badge = 「R2MS LITE」  
+ 再使用工具2: https://tfin.ch/iosicon.html  
  + 輸出有圓角的圖片  
+ 再使用工具3: PNG轉ICO線上工具 例如:https://www.aconvert.com/tw/icon/png-to-ico/
  + 需要的多解析度包含:  
    + 全部清單中有的
+ ICO下載位置: [右鍵另存](https://raw.githubusercontent.com/cgrgncu/SwitchArray_info/refs/heads/main/%E7%9B%A3%E6%B8%AC%E7%AB%99%E8%99%95%E7%90%86%E6%B5%81%E7%A8%8B/R2MS_Lite_Manager/ico/R2MS_Lite_Manager.ico)  

> ICO:  
>  ![image](https://raw.githubusercontent.com/cgrgncu/SwitchArray_info/refs/heads/main/%E7%9B%A3%E6%B8%AC%E7%AB%99%E8%99%95%E7%90%86%E6%B5%81%E7%A8%8B/R2MS_Lite_Manager/ico/R2MS_Lite_Manager.ico)  

## 開發紀錄(基礎框架部分)
1. 建立新專案。  
    + **1.1 按下「Project>New Project ...」。**  
    + **1.2 選擇「Project>Application 」之後按「OK」。**  
2. 獨立把專案存到指定資料夾中，以利日後管理。大部分自訂程式碼都會是相對路徑，未來只需要帶走這個資料夾即可在其他地方重新使用。  
    + **2.1 在桌面建立「R2MS_Lite_Manager」資料夾**  
    + **2.2 回到Lazarus，按下「Project>Save Project As」。**  
    + **2.3 將Project檔案(.lpi)存到桌面上的「R2MS_Lite_API_Server｣資料夾中，檔案命名為「R2MS_Lite_Manager.lpi」。**  
3. 專案設定需要調整。  
    + **3.1 選擇「Project>Project Options ...」設定「Application」頁面下利用「Load Icon 」按鈕更換自訂圖示。**  
      + 3.1.1 說明: 程式圖示。  
    + 3.2 檢查「Application」頁面下「Execution Level 」為「As Invoker」。  
      + 3.2.1 說明: 「As Invoker、Highest Available」都是普通權限就可以執行，「requireAdministrator」是執行前請求獲得管理者權限才能執行。
    + **3.3 選擇「Project>Project Options ...」設定「Compiler Options」頁面下，按下「Build modes」最右邊的「...」按鈕。再按「Create Debug and Release modes」，並將「Release」勾選「Active」，再按「OK」，再按「OK」**
      + 3.3.1 說明: 用Debug有時候防毒會報錯。  
4. 預設狀況下就有一個Form元件存在，預設名稱叫做「Form1」，先做一些基礎設定以利後續排版。  
    + 4.1 設定「Form1」的「properties」。這裡主要列出常用的一些。  
      + 4.1.1 檢查「Form1」的「properties」頁面下「BorderIcons」為「[biSystemMenu,biMinimize,biMaximize]」。  
        + 4.1.1.1 說明:設定窗體右上角的按鈕如果存在的話要不要被啟用。「[biSystemMenu,biMinimize,biMaximize]」表示這三個被打勾。  
      + 4.1.2 檢查「Form1」的「properties」頁面下「BorderStyle」為「bsSizeable」。  
        + 4.1.2.1 說明:設定窗體的樣式。可依需求嘗試不同風格決定是否符合需求。  
      + **4.1.2 設定「Form1」的「properties」頁面下「Caption」為「R2MS_Lite_Manager」。**  
        + 4.1.2.1 說明:設定窗體的標題列文字。  
      + **4.1.3 設定「Form1」的「properties」頁面下「Color」為「clWindow」。**  
        + 4.1.3.1 說明:設定成白色使工具列元件底色是白色。  
      + **4.1.4 設定「Form1」的「properties」頁面下「Height」為「600」。**  
        + 4.1.4.1 說明:設定窗體的外框高度。  
      + **4.1.5 設定「Form1」的「properties」頁面下「Position」為「poScreenCenter」。**  
        + 4.1.5.1 說明:設定窗體的出現位置，建議是用「poScreenCenter」，在螢幕中央。  
      + **4.1.6 設定「Form1」的「properties」頁面下「Width」為「800」。**  
        + 4.1.6.1 說明:設定窗體的外框寬度。  
    > 以上預設尺寸確定後就可以開始排版。  
5. 經典的Windows應用程式會在下方放置一個狀態列。如果不趕時間應該避免當作SimplePanel來使用。建議使用標準的(TStatusPanels)來規劃出多分隔的狀態列。可參考經典軟體「記事本」與「NotePad++」的狀態列規劃。  
    + **5.1 拖拉一個「Common Controls>TStatusBar」到「Form1」中。預設名稱會是「StatusBar1」。**  
    + 5.2 設定「TStatusBar」的「Properties」。這裡主要列出常用的一些。  
      + 5.2.1 檢查「StatusBar1」的「Properties」頁面下「Align」為「alBottom」。  
        + 5.2.1.1 說明:設定狀態列位置緊貼窗體下方。  
      + **5.2.2 設定「StatusBar1」的「Properties」頁面下「Panel」，按下「...」後會出現編輯介面。從編輯介面建立5個TStatusPanels。**  
        + 5.2.2.1 說明:建立狀態列中多個小版面。  
      + **5.2.3 設定各「TStatusPanels」的「Properties」。**  
        + 5.2.3.1 檢查「TStatusPanels」的「Properties」頁面下「Alignment」為「taLeftJustify」。  
          + 5.2.3.1.1 說明:「taLeftJustify」是文字靠左對齊，「taCenter」是文字水平置中，「taRightJustify」是文字靠右對齊。注意，如果有人改掉「BiDiMode」可能會顛倒，所以建議不要動「BiDiMode」這個屬性。  
        + 5.2.3.2 檢查「TStatusPanels」的「Properties」頁面下「Style」為「psText」。  
          + 5.2.3.2.1 說明:「psText」是可寫文字，「psOwnerDraw」是用另外的函數處理非文字。  
        + 5.2.3.3 設定「TStatusPanels」的「Properties」頁面下「Text」為「初始文字」。  
          + 5.2.3.3.1 說明:初始文字可以預先在排版階段測試顯示效果，其中最靠右會被吃掉字元，請依需求測試設定文字內容。  
        + **5.2.3.4 設定「TStatusPanels」的「Properties」頁面下「Width」為「120」。**  
          + 5.2.3.4.1 說明:可以搭配初始文字來調整Width，以利排版。預設只能靠右對齊來分配欄位，其他效果則需要利用程式碼做調整。  
      + **5.2.4 檢查「StatusBar1」的「Properties」頁面下「SimplePanel」為「false」。  
        + 5.2.4.1 說明:要使前面設定的TStatusPanels有效，須將「SimplePanel」設為「false」。  
    + 5.3 設定「TStatusBar」的「Event」。  
      + **5.3.1 設定「StatusBar1」的「Event」頁面下「OnResize」為如下程式碼。**  
      ```pascal  
        procedure TForm1.StatusBar1Resize(Sender: TObject);
        var
        temp_remain_width:Integer;
        begin
        temp_remain_width:=StatusBar1.Width;
        //--
        // 先配置最後一格，希望是200
        StatusBar1.Panels.Items[4].Width:=200;
        // 計算剩餘空間
        temp_remain_width:=temp_remain_width-StatusBar1.Panels.Items[4].Width;
        //--
        // 配置隔壁一格，希望是150
        StatusBar1.Panels.Items[3].Width:=150;
        if (temp_remain_width < StatusBar1.Panels.Items[3].Width) Then begin
        StatusBar1.Panels.Items[3].Width:=temp_remain_width;
        end;
        // 計算剩餘空間
        temp_remain_width:=temp_remain_width-StatusBar1.Panels.Items[3].Width;
        //--
        // 配置隔壁一格，希望是150
        StatusBar1.Panels.Items[2].Width:=150;
        if (temp_remain_width < StatusBar1.Panels.Items[2].Width) Then begin
        StatusBar1.Panels.Items[2].Width:=temp_remain_width;
        end;
        // 計算剩餘空間
        temp_remain_width:=temp_remain_width-StatusBar1.Panels.Items[2].Width;
        //--
        // 配置隔壁一格，希望是150
        StatusBar1.Panels.Items[1].Width:=150;
        if (temp_remain_width < StatusBar1.Panels.Items[1].Width) Then begin
        StatusBar1.Panels.Items[1].Width:=temp_remain_width;
        end;
        // 計算剩餘空間
        temp_remain_width:=temp_remain_width-StatusBar1.Panels.Items[1].Width;
        //--
        // 最前方一格享受最大空間
        StatusBar1.Panels.Items[0].Width:=temp_remain_width;
        //--
        end;
      ```  
6. 設定時鐘
    + **6.1 拖拉一個「System>TTimer」到「Form1」中。預設名稱會是「Timer1」。**  
    + 6.2 設定「TTimer」的「Event」。  
    + **6.2.1 設定「TTimer」的「Event」頁面下「OnTimer」為如下程式碼。**  
    ```pascal  
        procedure TForm1.Timer1Timer(Sender: TObject);
        var
          temp_str: AnsiString;
        begin
          temp_str:=FormatDateTime('yyyy-mm-dd HH:MM:SS' ,Now());
          StatusBar1.Panels.Items[4].Text:=temp_str;
        end;
    ```  
7. 設計主選單  
    + **7.1 拖拉一個「Standard>TMainMenu」到「Form1」中。預設名稱會是「MainMenu1」。**  
    + **7.2 點兩下元件，進入編輯模式，建立第一層第一個選單「說明(&H)」，「Caption」設為「說明(&H)」，「Name」設為「MainMenu1_1」。**  
    + **7.3 繼續建立子選單「說明(&H)->關於我(&A)」，「Caption」設為「關於我(&A)」，「Name」設為「MainMenu1_1_1」。**  
      + 7.3.1 設定「MainMenu1_1_1」的「Event」。  
        + **7.3.1.1 原始碼最前面部分先宣告為如下程式碼。**  
        ```pascal  
        var
          Form1: TForm1;
          //--
          //Global Variable add by HsiupoYeh
          version_str: AnsiString = 'v20241102a';
          //--  
        ```  
        + **7.3.1.2 設定「MainMenu1_1_1」的「Event」頁面下「OnClick」為如下程式碼。**  
        ```pascal  
        procedure TForm1.MainMenu1_1_1Click(Sender: TObject);
        var
          temp_str: AnsiString;
        begin
          temp_str:='作者: HsiuPoYeh.'+#13#10+'程式版本: '+version_str;
          Application.MessageBox(PChar(temp_str),'關於我',64);
        end;  
        ```  
8. 設定分頁  
    + **8.1 拖拉一個「Common Controls>TPageControl」到「Form1」中。預設名稱會是「PageControl1」。**  
    + **8.2 設定「PageControl1」的「Properties」頁面下「Align」選為「alClient」。**  
    + **8.3 用右鍵新增頁面，本專案要3頁，也可以先新增個10頁之後再刪掉不要用的。**  

    >以上頁面未來都可以調整順序。  

    + **8.4.把新增的第1頁「TabSheet1」的「Properties」頁面下「Caption」設定為「運行紀錄」。「Name」設定為「Log_TabSheet」。**  
    + **8.4.1 拖拉一個「Standard>TMemo」放到該頁中。設定「Properties」頁面下「Name」設定為「Log_Memo」。**  
    + **8.4.1.1 設定「Log_Memo」的「Properties」頁面下「Align」設定為「AlClient」。**  
    + **8.4.1.2 設定「Log_Memo」的「Properties」頁面下「Lines」的內容清空。**  
    + **8.4.1.3 設定「Log_Memo」的「Properties」頁面下「ReadOnly」設定為「true」。**  
    + **8.4.1.4 設定「Log_Memo」的「Properties」頁面下「ScrollBars」設定為「ssBoth」。**
    + **8.4.1.5 設定「Log_Memo」的「Properties」頁面下「WordWrap」設定為「false」。**  
    
     >以上是第1頁。  
    
    + **8.5.把新增的第2頁「TabPage2」的「Properties」頁面下「Caption」設定為「更新紀錄」。「Name」設定為「Update_TabSheet」。**  
    + **8.5.1 拖拉一個「Standard>TMemo」放到該頁中。設定「Properties」頁面下「Name」設定為「Update_Memo」。**  
    + **8.5.1.1 設定「Update_Memo」的「Properties」頁面下「Align」設定為「AlClient」。**     
    + **8.5.1.2 設定「Update_Memo」的「Properties」頁面下「ReadOnly」設定為「true」。**
    + **8.5.1.3 設定「Update_Memo」的「Properties」頁面下「Lines」的內容。清空後填入版本紀錄。**
    ```pascal  
    v20241102a:
    初版。
    ```  
    
    >以上是第2頁。  

    + **8.6.把新增的第3頁「TabPage3」的「Properties」頁面下「Caption」設定為「基本設定」。「Name」設定為「BasicSettings_TabSheet」。**  
    + **8.6.1拖拉一個「Standard>TPanel」到「BasicSettings_TabSheet」中。預設名稱會是「Panel1」。**
      + **8.6.1.1 設定「Anchors」。**
        + **8.6.1.1.1 「Top anchoring>Slbling」選為「BasicSettings_TabSheet:TTabSheet」。維持「Top anchoring>Enable」為打勾。選擇「Top anchoring」右側三個鈕選中間的。**  
        + **8.6.1.1.2 「Left anchoring>Slbling」選為「BasicSettings_TabSheet:TTabSheet」。維持「Left anchoring>Enable」為打勾。選擇「Left anchoring」右側三個鈕選左邊的。**
        + **8.6.1.1.3 「Right anchoring>Slbling」選為「BasicSettings_TabSheet:TTabSheet」。選擇「Right anchoring>Enable」為打勾。選擇「Right anchoring」右側三個鈕選右邊的。** 
        + **8.6.1.1.4 設定完後關閉Anchors設定視窗。**  
      + **8.6.1.2 設定「BevelOuter」為「bvNone」。**  
      + **8.6.1.3 設定「Caption」為「」。就是空白。**  
      + **8.6.1.4 設定「Height」為「10」。**  
      + **8.6.1.5 設定「Name」為「BasicSettings_Panel1」。**  
    + **8.6.2拖拉一個「Standard>TPanel」到「BasicSettings_TabSheet」中。預設名稱會是「Panel1」。**
      + **8.6.2.1 設定「Anchors」。**
        + **8.6.2.1.1 「Top anchoring>Slbling」選為「BasicSettings_TabSheet:TTabSheet」。維持「Top anchoring>Enable」為打勾。選擇「Top anchoring」右側三個鈕選上面的。**  
        + **8.6.2.1.2 「Left anchoring>Slbling」選為「BasicSettings_TabSheet:TTabSheet」。維持「Left anchoring>Enable」為打勾。選擇「Left anchoring」右側三個鈕選中間的。**
        + **8.6.2.1.3 「Bottom anchoring>Slbling」選為「BasicSettings_Panel1:TPanel」。選擇「Bottom anchoring>Enable」為打勾。選擇「Bottom anchoring」右側三個鈕選上面的。** 
        + **8.6.2.1.4 設定完後關閉Anchors設定視窗。**  
      + **8.6.2.2 設定「BevelOuter」為「bvNone」。**  
      + **8.6.2.3 設定「Caption」為「」。就是空白。**
      + **8.6.2.4 設定「Name」為「BasicSettings_Panel2」。**  
      + **8.6.2.5 設定「Width」為「10」。**  
    + **8.6.3 拖拉一個「Standard>TGroupBox」到「BasicSettings_TabSheet」中。預設名稱會是「GroupBox1」。**  
      + **8.6.3.1 設定「Anchors」。**  
        + **8.6.3.1.1 「Top anchoring>Slbling」選為「BasicSettings_TabSheet:TTabSheet」。維持「Top anchoring>Enable」為打勾。維持「Top anchoring」右側三個鈕選子上面的。**  
        + **8.6.3.1.2 「Left anchoring>Slbling」選為「BasicSettings_TabSheet:TTabSheet」。維持「Left anchoring>Enable」為打勾。維持「Left anchoring」右側三個鈕選左邊的。**
        + **8.6.3.1.3 「Right anchoring>Slbling」選為「BasicSettings_Panel2:TPanel」。維持「Left anchoring>Enable」為打勾。維持「Right anchoring」右側三個鈕選左邊的。**
        + **8.6.3.1.4 「Bottom anchoring>Slbling」選為「BasicSettings_Panel1:TPanel」。維持「Left anchoring>Enable」為打勾。維持「Bottom anchoring」右側三個鈕選上面的。**  
        + **8.6.3.1.5 「Border space」正中間那格填「0」，上面那格填「10」，左邊那格填「10」，右邊那格填「5」。**  
        + **8.6.3.1.6 設定完後關閉Anchors設定視窗。**  
      + **8.6.3.2 設定「Caption」為「預設值:」。**  
      + **8.6.3.3 設定「Name」為「BasicSettings_Default_GroupBox」。**
   + **8.6.4 拖拉一個「Standard>TMemo」到「BasicSettings_Default_GroupBox」中。預設名稱會是「Memo1」。**
      + **8.6.4.1 設定「Anchors」。**  
        + **8.6.4.1.1 「Top anchoring>Slbling」選為「BasicSettings_Default_GroupBox:TGroupBox」。維持「Top anchoring>Enable」為打勾。維持「Top anchoring」右側三個鈕選子上面的。**  
        + **8.6.4.1.2 「Left anchoring>Slbling」選為「BasicSettings_Default_GroupBox:TGroupBox」。維持「Left anchoring>Enable」為打勾。維持「Left anchoring」右側三個鈕選左邊的。**
        + **8.6.4.1.3 「Right anchoring>Slbling」選為「BasicSettings_Default_GroupBox:TGroupBox」。維持「Left anchoring>Enable」為打勾。維持「Right anchoring」右側三個鈕選右邊的。**
        + **8.6.4.1.4 「Bottom anchoring>Slbling」選為「BasicSettings_Default_GroupBox:TGroupBox」。維持「Left anchoring>Enable」為打勾。維持「Bottom anchoring」右側三個鈕選下面的。**  
        + **8.6.4.1.5 「Border space」正中間那格填「5」。**  
        + **8.6.4.1.6 設定完後關閉Anchors設定視窗。**
      + **8.6.4.2 設定「Lines」的內容清空。**.
      + **8.6.4.3 設定「Name」為「BasicSettings_Default_Memo」。**      + 
      + **8.6.4.4 設定「ReadOnly」為「true」。**
      + **8.6.4.5 設定「ScrollBars」為「ssBoth」。**
      + **8.6.4.6 設定「WordWrap」為「false」。**
    + **8.6.5 拖拉一個「Standard>TGroupBox」到「BasicSettings_TabSheet」中。預設名稱會是「GroupBox1」。**  
      + **8.6.5.1 設定「Anchors」。**  
        + **8.6.5.1.1 「Top anchoring>Slbling」選為「BasicSettings_TabSheet:TTabSheet」。維持「Top anchoring>Enable」為打勾。維持「Top anchoring」右側三個鈕選子上面的。**  
        + **8.6.5.1.2 「Left anchoring>Slbling」選為「BasicSettings_Panel2:TPanel」。維持「Left anchoring>Enable」為打勾。維持「Left anchoring」右側三個鈕選左邊的。**
        + **8.6.5.1.3 「Right anchoring>Slbling」選為「BasicSettings_TabSheet:TTabSheet」。維持「Left anchoring>Enable」為打勾。維持「Right anchoring」右側三個鈕選右邊的。**
        + **8.6.5.1.4 「Bottom anchoring>Slbling」選為「BasicSettings_Panel1:TPanel」。維持「Left anchoring>Enable」為打勾。維持「Bottom anchoring」右側三個鈕選上面的。**  
        + **8.6.5.1.5 「Border space」正中間那格填「0」，上面那格填「10」，左邊那格填「5」，右邊那格填「10」。**  
        + **8.6.5.1.6 設定完後關閉Anchors設定視窗。**  
      + **8.6.5.2 設定「Caption」為「目前值:」。**  
      + **8.6.5.3 設定「Name」為「BasicSettings_Current_GroupBox」。**
    + **8.6.6 拖拉一個「Standard>TMemo」到「BasicSettings_Current_GroupBox」中。預設名稱會是「Memo1」。**
      + **8.6.6.1 設定「Anchors」。**  
        + **8.6.6.1.1 「Top anchoring>Slbling」選為「BasicSettings_Current_GroupBox:TGroupBox」。維持「Top anchoring>Enable」為打勾。維持「Top anchoring」右側三個鈕選子上面的。**  
        + **8.6.6.1.2 「Left anchoring>Slbling」選為「BasicSettings_Current_GroupBox:TGroupBox」。維持「Left anchoring>Enable」為打勾。維持「Left anchoring」右側三個鈕選左邊的。**
        + **8.6.6.1.3 「Right anchoring>Slbling」選為「BasicSettings_Current_GroupBox:TGroupBox」。維持「Left anchoring>Enable」為打勾。維持「Right anchoring」右側三個鈕選右邊的。**
        + **8.6.6.1.4 「Bottom anchoring>Slbling」選為「BasicSettings_Current_GroupBox:TGroupBox」。維持「Left anchoring>Enable」為打勾。維持「Bottom anchoring」右側三個鈕選下面的。**  
        + **8.6.6.1.5 「Border space」正中間那格填「5」。**  
        + **8.6.6.1.6 設定完後關閉Anchors設定視窗。**
      + **8.6.6.2 設定「Lines」的內容清空。**.
      + **8.6.6.3 設定「Name」為「BasicSettings_Current_Memo」。**      + 
      + **8.6.6.4 設定「ReadOnly」為「true」。**
      + **8.6.6.5 設定「ScrollBars」為「ssBoth」。**
      + **8.6.6.6 設定「WordWrap」為「false」。**
   + **8.6.7 拖拉一個「Standard>TGroupBox」到「BasicSettings_TabSheet」中。預設名稱會是「GroupBox1」。**  
      + **8.6.7.1 設定「Anchors」。**  
        + **8.6.7.1.1 「Top anchoring>Slbling」選為「BasicSettings_Panel1:TPanel」。維持「Top anchoring>Enable」為打勾。維持「Top anchoring」右側三個鈕選子下面的。**  
        + **8.6.7.1.2 「Left anchoring>Slbling」選為「BasicSettings_TabSheet:TTabSheet」。維持「Left anchoring>Enable」為打勾。維持「Left anchoring」右側三個鈕選左邊的。**
        + **8.6.7.1.3 「Right anchoring>Slbling」選為「BasicSettings_TabSheet:TTabSheet」。維持「Left anchoring>Enable」為打勾。維持「Right anchoring」右側三個鈕選右邊的。**
        + **8.6.7.1.4 「Bottom anchoring>Slbling」選為「BasicSettings_TabSheet:TTabSheet」。維持「Left anchoring>Enable」為打勾。維持「Bottom anchoring」右側三個鈕選下面的。**  
        + **8.6.7.1.5 「Border space」正中間那格填「0」，下面那格填「10」，左邊那格填「10」，右邊那格填「10」。**  
        + **8.6.7.1.6 設定完後關閉Anchors設定視窗。**  
      + **8.6.7.2 設定「Caption」為「基本設定說明:」。**  
      + **8.6.7.3 設定「Name」為「BasicSettings_Notes_GroupBox」。**
    + **8.6.8 拖拉一個「Standard>TMemo」到「BasicSettings_Notes_GroupBox」中。預設名稱會是「Memo1」。**
      + **8.6.8.1 設定「Anchors」。**  
        + **8.6.8.1.1 「Top anchoring>Slbling」選為「BasicSettings_Notes_GroupBox:TGroupBox」。維持「Top anchoring>Enable」為打勾。維持「Top anchoring」右側三個鈕選子上面的。**  
        + **8.6.8.1.2 「Left anchoring>Slbling」選為「BasicSettings_Notes_GroupBox:TGroupBox」。維持「Left anchoring>Enable」為打勾。維持「Left anchoring」右側三個鈕選左邊的。**
        + **8.6.8.1.3 「Right anchoring>Slbling」選為「BasicSettings_Notes_GroupBox:TGroupBox」。維持「Left anchoring>Enable」為打勾。維持「Right anchoring」右側三個鈕選右邊的。**
        + **8.6.8.1.4 「Bottom anchoring>Slbling」選為「BasicSettings_Notes_GroupBox:TGroupBox」。維持「Left anchoring>Enable」為打勾。維持「Bottom anchoring」右側三個鈕選下面的。**  
        + **8.6.8.1.5 「Border space」正中間那格填「5」。**  
        + **8.6.8.1.6 設定完後關閉Anchors設定視窗。**
      + **8.6.8.2 設定「Lines」的內容清空。**.
      + **8.6.8.3 設定「Name」為「BasicSettings_Notes_Memo」。**      + 
      + **8.6.8.4 設定「ReadOnly」為「true」。**
      + **8.6.8.5 設定「ScrollBars」為「ssBoth」。**
      + **8.6.8.6 設定「WordWrap」為「false」。**

    >以上是第3頁。  
    
    + **8.7.把新增的第4頁「TabPage4」的「Properties」頁面下「Caption」設定為「Web Server」。「Name」設定為「Main_TabSheet」。**  
    + **8.7.1 設定「Main_TabSheet」的「Properties」頁面下「PageIndex」設定為「0」。**  
    + **8.7.2 開始進行設計...**  

    >以上是第4頁。單獨修改一個頁面的PageIndex會影響所有的頁面，可能使其他頁面的PageIndex值改變。
    設計時可考慮使用TPanel元件進行響應式設計，不想看到分隔線就把BevelOuter設為bvNone。

### 開發紀錄(排版常用技巧)
+ 不寫程式的做法: 
  + Align:
    + 讓元件對齊父層元件的邊界
  + Anchors:
    + 強控邊界，被選定的父層元件會配合排版，左右同時被控制時，用起來有點複雜且麻煩。用的好效果應該很不錯。
    + 但某些設定會影響父層甚至其他元件排版，用起來要很小心。
+ GroupBox1+Edit1
  ```
    procedure TForm1.Edit1Resize(Sender: TObject);
    var
      temp_remain_width:Integer;
    begin
      temp_remain_width:=GroupBox1.Width;
      Edit1.Left:=10;
      Edit1.Width:=temp_remain_width-Edit1.Left-15;
    end; 
  ```
### 開發紀錄(Web Server頁面)  
1. Server IP Address:  
    + **1.1 拖拉一個「Standard>TGroupBox」到「Web Server」標籤頁(物件名稱為「Main_TabSheet」)。預設名稱會是「GroupBox1」。**  
      + **1.1.1 設定「Anchors」。**  
        + **1.1.1.1 「Top anchoring>Slbling」選為「Main_TabSheet:TTabSheet」。維持「Top anchoring>Enable」為打勾。維持「Top anchoring」右側三個鈕選上面的。**  
        + **1.1.1.2 「Left anchoring>Slbling」選為「Main_TabSheet:TTabSheet」。維持「Left anchoring>Enable」為打勾。維持「Left anchoring」右側三個鈕選左邊的。**  
        + **1.1.1.3 「Border space」正中間那格填「10」。**  
        + **1.1.1.4 設定完後關閉Anchors設定視窗。**  
      + **1.1.2 設定「Caption」為「Server IP Address:」。**  
      + **1.1.3 設定「Height」為「60」。**  
      + **1.1.4 設定「Name」為「ServerIPAddress_GroupBox」。**  
      + **1.1.5 設定「Width」為「160」。**  
    + **1.2 拖拉一個「Standard>TEdit」到「ServerIPAddress_GroupBox」中。預設名稱會是「Edit1」。**  
      + **1.2.1 設定「Anchors」。**  
        + **1.2.1.1 「Top anchoring>Slbling」選為「ServerIPAddress_GroupBox:TGroupBox」。維持「Top anchoring>Enable」為打勾。選擇「Top anchoring」右側三個鈕選中間的。**  
        + **1.2.1.2 「Left anchoring>Slbling」選為「ServerIPAddress_GroupBox:TGroupBox」。維持「Left anchoring>Enable」為打勾。維持「Left anchoring」右側三個鈕選左邊的。**  
        + **1.2.1.3 「Right anchoring>Slbling」選為「ServerIPAddress_GroupBox:TGroupBox」。勾選「Right anchoring>Enable」為打勾。選擇「Right anchoring」右側三個鈕選右邊的。**  
        + **1.2.1.4 「Border space」正中間那格填「10」。**  
        + **1.2.1.5 設定完後關閉Anchors設定視窗。**  
      + **1.2.2 設定「Name」為「ServerIPAddress_Edit」。**  
      + **1.2.3 設定「ReadOnly」為「True」。**  
      + **1.2.4 設定「Text」為「127.0.0.1」。**  
2. Server Port:
    + **2.1 拖拉一個「Standard>TGroupBox」到「Web Server」標籤頁(物件名稱為「Main_TabSheet」)。預設名稱會是「GroupBox1」。**  
      + **2.1.1 設定「Anchors」。**  
        + **2.1.1.1 「Top anchoring>Slbling」選為「ServerIPAddress_GroupBox:TGroupBox」。維持「Top anchoring>Enable」為打勾。選擇「Top anchoring」右側三個鈕選下面的。**  
        + **2.1.1.2 「Left anchoring>Slbling」選為「Main_TabSheet:TTabSheet」。維持「Left anchoring>Enable」為打勾。維持「Left anchoring」右側三個鈕選左邊的。**  
        + **2.1.1.3 「Border space」正中間那格填「10」。**  
        + **2.1.1.4 設定完後關閉Anchors設定視窗。**  
      + **2.1.2 設定「Caption」為「Server Port:」。**  
      + **2.1.3 設定「Height」為「60」。**  
      + **2.1.4 設定「Name」為「ServerPort_GroupBox」。**  
      + **2.1.5 設定「Width」為「160」。**  
    + **2.2 拖拉一個「Standard>TEdit」到「ServerPort_GroupBox」中。預設名稱會是「Edit1」。**  
      + **2.2.1 設定「Anchors」。**  
        + **2.2.1.1 「Top anchoring>Slbling」選為「ServerPort_GroupBox:TGroupBox」。維持「Top anchoring>Enable」為打勾。選擇「Top anchoring」右側三個鈕選中間的。**  
        + **2.2.1.2 「Left anchoring>Slbling」選為「ServerPort_GroupBox:TGroupBox」。維持「Left anchoring>Enable」為打勾。維持「Left anchoring」右側三個鈕選左邊的。**  
        + **2.2.1.3 「Right anchoring>Slbling」選為「ServerPort_GroupBox:TGroupBox」。勾選「Right anchoring>Enable」為打勾。選擇「Right anchoring」右側三個鈕選右邊的。**  
        + **2.2.1.4 「Border space」正中間那格填「10」。**  
        + **2.2.1.5 設定完後關閉Anchors設定視窗。**  
      + **2.2.2 設定「Name」為「ServerPort_Edit」。**  
      + **2.2.3 設定「NumbersOnly」為「True」。**  
      + **2.2.4 設定「Text」為「18002」。**  
3. Server Status:
    + **3.1 拖拉一個「Standard>TGroupBox」到「Web Server」標籤頁(物件名稱為「Main_TabSheet」)。預設名稱會是「GroupBox1」。**  
      + **3.1.1 設定「Anchors」。**  
        + **3.1.1.1 「Top anchoring>Slbling」選為「Main_TabSheet:TTabSheet」。維持「Top anchoring>Enable」為打勾。選擇「Top anchoring」右側三個鈕選上面的。**  
        + **3.1.1.2 「Left anchoring>Slbling」選為「ServerIPAddress_GroupBox:TGroupBox」。維持「Left anchoring>Enable」為打勾。維持「Left anchoring」右側三個鈕選右邊的。**  
        + **3.1.1.3 「Border space」正中間那格填「10」。**  
        + **3.1.1.4 設定完後關閉Anchors設定視窗。**  
      + **3.1.2 設定「Caption」為「Server Status:」。**  
      + **3.1.3 設定「Height」為「60」。**  
      + **3.1.4 設定「Name」為「ServerStatus_GroupBox」。**  
      + **3.1.5 設定「Width」為「160」。**  
    + **3.2 拖拉一個「Standard>TLabel」到「ServerStatus_GroupBox」中。預設名稱會是「Label1」。**  
      + **3.2.1 設定「Anchors」。**  
        + **3.2.1.1 「Top anchoring>Slbling」選為「ServerStatus_GroupBox:TGroupBox」。維持「Top anchoring>Enable」為打勾。選擇「Top anchoring」右側三個鈕選中間的。**  
        + **3.2.1.2 「Left anchoring>Slbling」選為「ServerStatus_GroupBox:TGroupBox」。維持「Left anchoring>Enable」為打勾。維持「Left anchoring」右側三個鈕選左邊的。**  
        + **3.2.1.3 「Right anchoring>Slbling」選為「ServerStatus_GroupBox:TGroupBox」。勾選「Right anchoring>Enable」為打勾。選擇「Right anchoring」右側三個鈕選右邊的。**  
        + **3.2.1.4 「Border space」正中間那格填「10」。**  
        + **3.2.1.5 設定完後關閉Anchors設定視窗。**  
      + **3.2.2 設定「Name」為「ServerStatus_Label」。**  
      + **3.2.3 設定「Caption」為「伺服器狀態: 未知」。**  
4. 啟動按鈕:
    + **4.1 拖拉一個「Standard>TPanel」到「Web Server」標籤頁(物件名稱為「Main_TabSheet」)。預設名稱會是「Panel1」。**  
      + **4.1.1 設定「Anchors」。**  
        + **4.1.1.1 「Top anchoring>Slbling」選為「ServerStatus_GroupBox:TGroupBox」。維持「Top anchoring>Enable」為打勾。選擇「Top anchoring」右側三個鈕選下面的。**  
        + **4.1.1.2 「Left anchoring>Slbling」選為「ServerPort_GroupBox:TGroupBox」。維持「Left anchoring>Enable」為打勾。維持「Left anchoring」右側三個鈕選右邊的。**  
        + **4.1.1.3 「Border space」正中間那格填「10」。**  
        + **4.1.1.4 設定完後關閉Anchors設定視窗。**  
      + **4.1.2 設定「BevelOuter」為「bvNone」。**  
      + **4.1.2 設定「Caption」為「」。就是空白。**  
      + **4.1.3 設定「Height」為「60」。**  
      + **4.1.4 設定「Name」為「ServerRunStop_Panel」。**  
      + **4.1.5 設定「Width」為「160」。**  
    + **4.2 拖拉一個「Standard>TButton」到「ServerRunStop_Panel」中。預設名稱會是「Button1」。**  
      + **4.2.1 設定「Anchors」。**  
        + **4.2.1.1 「Top anchoring>Slbling」選為「StartServer_Panel:TPanel」。維持「Top anchoring>Enable」為打勾。選擇「Top anchoring」右側三個鈕選上面的。**  
        + **4.2.1.2 「Left anchoring>Slbling」選為「StartServer_Panel:TPanel」。維持「Left anchoring>Enable」為打勾。維持「Left anchoring」右側三個鈕選左邊的。**  
        + **4.2.1.3 「Right anchoring>Slbling」選為「StartServer_Panel:TPanel」。勾選「Right anchoring>Enable」為打勾。選擇「Right anchoring」右側三個鈕選右邊的。**  
        + **4.2.1.4 「Bottom anchoring>Slbling」選為「StartServer_Panel:TPanel」。勾選「Bottom anchoring>Enable」為打勾。選擇「Bottom anchoring」右側三個鈕選下面的。**  
        + **4.2.1.5 「Border space」正中間那格填「10」。**  
        + **4.2.1.6 設定完後關閉Anchors設定視窗。**  
      + **4.2.2 設定「Name」為「ServerRunStop_Button」。**  
      + **4.2.3 設定「Caption」為「按我啟動」。**  
5. API List:
    + **5.1 拖拉一個「Common Controls>TPageControl」到「Web Server」標籤頁(物件名稱為「Main_TabSheet」)。預設名稱會是「PageControl2」。**  
      + **5.1.1 設定「Anchors」。**  
        + **5.1.1.1 「Top anchoring>Slbling」選為「Main_TabSheet:TTabSheet」。維持「Top anchoring>Enable」為打勾。選擇「Top anchoring」右側三個鈕選上面的。**  
        + **5.1.1.2 「Left anchoring>Slbling」選為「ServerStatus_GroupBox:TGroupBox」。維持「Left anchoring>Enable」為打勾。維持「Left anchoring」右側三個鈕選右邊的。**  
        + **5.1.1.2 「Right anchoring>Slbling」選為「Main_TabSheet:TTabSheet」。選擇「Right anchoring>Enable」為打勾。選擇「Left anchoring」右側三個鈕選右邊的。**  
        + **5.1.1.3 「Border space」正中間那格填「10」。**  
        + **5.1.1.4 設定完後關閉Anchors設定視窗。**   
      + **5.1.3 設定「Height」為「130」。**  
      + **5.1.4 設定「Name」為「APIList_PageControl」。**  
      + **5.1.4 用右鍵新增頁面，新增個4頁。**  
        + **5.1.4.1 第1頁設定「Caption」為「hello」，「Name」為「API_hello_TabSheet」。**  
        + **5.1.4.2 第2頁設定「Caption」為「SwitchArray」，「Name」為「API_SwitchArray_TabSheet」。**  
        + **5.1.4.3 第3頁設定「Caption」為「DMM」，「Name」為「API_DMM_TabSheet」。**  
        + **5.1.4.4 第4頁設定「Caption」為「PSU」，「Name」為「API_PSU_TabSheet」。**  
    + **5.2 拖拉一個「Standard>TLabel」到「API_hello_TabSheet」中。預設名稱會是「Label1」。**  
      + **5.2.1 設定「Anchors」。**  
        + **5.2.1.1 「Top anchoring>Slbling」選為「API_hello_TabSheet:TTabSheet」。維持「Top anchoring>Enable」為打勾。選擇「Top anchoring」右側三個鈕選上面的。**  
        + **5.2.1.2 「Left anchoring>Slbling」選為「API_hello_TabSheet:TTabSheet」。維持「Left anchoring>Enable」為打勾。維持「Left anchoring」右側三個鈕選左邊的。**  
        + **5.2.1.3 「Border space」正中間那格填「10」。上面那格填「10」，左邊那格填「10」**  
        + **5.2.1.4 設定完後關閉Anchors設定視窗。**  
      + **5.2.2 設定「Name」為「API_hello_Label」。**  
      + **5.2.3 設定「Caption」為「API:」。**  
    + **5.3 拖拉一個「Standard>TEdit」到「API_hello_TabSheet」中。預設名稱會是「Edit1」。**  
      + **5.3.1 設定「Anchors」。**  
        + **5.3.1.1 「Top anchoring>Slbling」選為「API_hello_TabSheet:TTabSheet」。維持「Top anchoring>Enable」為打勾。選擇「Top anchoring」右側三個鈕選上面的。**  
        + **5.3.1.2 「Left anchoring>Slbling」選為「API_hello_Label:TLabel」。維持「Left anchoring>Enable」為打勾。維持「Left anchoring」右側三個鈕選右邊的。**  
        + **5.3.1.2 「Right anchoring>Slbling」選為「API_hello_TabSheet:TTabSheet」。選擇「Right anchoring>Enable」為打勾。選擇「Left anchoring」右側三個鈕選右邊的。**  
        + **5.3.1.4 「Border space」正中間那格填「10」。上面那格填「7」，右邊那格填「10」**  
        + **5.3.1.5 設定完後關閉Anchors設定視窗。**  
      + **5.3.2 設定「Name」為「API_hello_Edit」。**  
      + **5.3.3 設定「ReadOnly」為「true」。**  
      + **5.3.4 設定「text」為「/api/v1/hello」。**  
    + **5.4 拖拉一個「Standard>TLabel」到「API_hello_TabSheet」中。預設名稱會是「Label1」。**  
      + **5.4.1 設定「Anchors」。**  
        + **5.4.1.1 「Top anchoring>Slbling」選為「API_hello_Edit:TEdit」。維持「Top anchoring>Enable」為打勾。選擇「Top anchoring」右側三個鈕選下面的。**  
        + **5.4.1.2 「Left anchoring>Slbling」選為「API_hello_TabSheet:TTabSheet」。維持「Left anchoring>Enable」為打勾。維持「Left anchoring」右側三個鈕選左邊的。**  
        + **5.4.1.3 「Border space」正中間那格填「10」。上面那格填「10」，左邊那格填「10」**  
        + **5.4.1.4 設定完後關閉Anchors設定視窗。**  
      + **5.4.2 設定「Name」為「API_hello_URL_Label」。**  
      + **5.4.3 設定「Caption」為「API URL:」。**  
    + **5.5 拖拉一個「Standard>TEdit」到「API_hello_TabSheet」中。預設名稱會是「Edit1」。**  
      + **5.5.1 設定「Anchors」。**  
        + **5.5.1.1 「Top anchoring>Slbling」選為「API_hello_Edit:TEdit」。維持「Top anchoring>Enable」為打勾。選擇「Top anchoring」右側三個鈕選下面的。**  
        + **5.5.1.2 「Left anchoring>Slbling」選為「API_hello_URL_Label:TLabel」。維持「Left anchoring>Enable」為打勾。維持「Left anchoring」右側三個鈕選右邊的。**  
        + **5.5.1.2 「Right anchoring>Slbling」選為「API_hello_TabSheet:TTabSheet」。選擇「Right anchoring>Enable」為打勾。選擇「Left anchoring」右側三個鈕選右邊的。**  
        + **5.5.1.4 「Border space」正中間那格填「10」。上面那格填「7」，右邊那格填「10」**  
        + **5.5.1.5 設定完後關閉Anchors設定視窗。**  
      + **5.5.2 設定「Name」為「API_hello_URL_Edit」。**  
      + **5.3.3 設定「ReadOnly」為「true」。**  
      + **5.3.4 設定「text」為「```http://127.0.0.1:18002/api/v1/hello```」 。**
    + **5.4 複製相同設定到其他頁面，並修改其名稱與文字**  
      + **5.4.1 在左側「components」視窗內找到樹狀圖的「API_hello_TabSheet」元件，框選下方的四個子元件，按右鍵「Copy」。**  
      + **5.4.2 選到「API_SwitchArray_TabSheet」元件，按右鍵「Paste」。**     
      + **5.4.3 選到「API_DMM_TabSheet」元件，按右鍵「Paste」。**
      + **5.4.4 選到「API_PSU_TabSheet」元件，按右鍵「Paste」。**
      + **5.4.5 選到「API_SwitchArray_TabSheet」元件下的子元件「API_hello_Label1」，設定「Name」為「API_SwitchArray_Label」。**
      + **5.4.6 選到「API_SwitchArray_TabSheet」元件下的子元件「API_hello_Edit1」，設定「Name」為「API_SwitchArray_Edit」，設定「Text」為「/api/v1/SwitchArray」。**
      + **5.4.7 選到「API_SwitchArray_TabSheet」元件下的子元件「API_hello_URL_Label1」，設定「Name」為「API_SwitchArray_URL_Label」。**
      + **5.4.8 選到「API_SwitchArray_TabSheet」元件下的子元件「API_hello_URL_Edit1」，設定「Name」為「API_SwitchArray_URL_Edit」，設定「Text」為「```http://127.0.0.1:18002/api/v1/SwitchArray```」。**
      + **5.4.9 選到「API_DMM_TabSheet」元件下的子元件「API_hello_Label2」，設定「Name」為「API_DMM_Label」。**
      + **5.4.10 選到「API_DMM_TabSheet」元件下的子元件「API_hello_Edit2」，設定「Name」為「API_DMM_Edit」，設定「Text」為「/api/v1/DMM」。**
      + **5.4.11 選到「API_DMM_TabSheet」元件下的子元件「API_hello_URL_Label2」，設定「Name」為「API_DMM_URL_Label」。**
      + **5.4.12 選到「API_DMM_TabSheet」元件下的子元件「API_hello_URL_Edit2」，設定「Name」為「API_DMM_URL_Edit」，設定「Text」為「```http://127.0.0.1:18002/api/v1/DMM```」。**
      + **5.4.13 選到「API_PSU_TabSheet」元件下的子元件「API_hello_Label3」，設定「Name」為「API_PSU_Label」。**
      + **5.4.14 選到「API_PSU_TabSheet」元件下的子元件「API_hello_Edit3」，設定「Name」為「API_PSU_Edit」，設定「Text」為「/api/v1/PSU」。**
      + **5.4.15 選到「API_PSU_TabSheet」元件下的子元件「API_hello_URL_Label3」，設定「Name」為「API_PSU_URL_Label」。**
      + **5.4.16 選到「API_PSU_TabSheet」元件下的子元件「API_hello_URL_Edit3」，設定「Name」為「API_PSU_URL_Edit」，設定「Text」為「```http://127.0.0.1:18002/api/v1/PSU```」。**
6. API_Notes:  
    + **6.1 拖拉一個「Standard>TGroupBox」到「Web Server」標籤頁(物件名稱為「Main_TabSheet」)。預設名稱會是「GroupBox1」。**  
      + **6.1.1 設定「Anchors」。**  
        + **6.1.1.1 「Top anchoring>Slbling」選為「APIList_PageControl:TPageControl」。維持「Top anchoring>Enable」為打勾。維持「Top anchoring」右側三個鈕選子下面的。**  
        + **6.1.1.2 「Left anchoring>Slbling」選為「Main_TabSheet:TTabSheet」。維持「Left anchoring>Enable」為打勾。維持「Left anchoring」右側三個鈕選左邊的。**
        + **6.1.1.3 「Right anchoring>Slbling」選為「Main_TabSheet:TTabSheet」。維持「Left anchoring>Enable」為打勾。維持「Right anchoring」右側三個鈕選右邊的。**
        + **6.1.1.4 「Bottom anchoring>Slbling」選為「Main_TabSheet:TTabSheet」。維持「Left anchoring>Enable」為打勾。維持「Bottom anchoring」右側三個鈕選下邊的。**  
        + **6.1.1.5 「Border space」正中間那格填「10」。**  
        + **6.1.1.6 設定完後關閉Anchors設定視窗。**  
      + **6.1.2 設定「Caption」為「API命令說明:」。**  
      + **6.1.3 設定「Name」為「API_Notes_GroupBox」。**
    + **6.2 拖拉一個「Standard>TMemo」到「API_Notes_GroupBox」中。預設名稱會是「Memo1」。**
      + **6.2.1 設定「Anchors」。**  
        + **6.2.1.1 「Top anchoring>Slbling」選為「API_Notes_GroupBox:TGroupBox」。維持「Top anchoring>Enable」為打勾。維持「Top anchoring」右側三個鈕選子上面的。**  
        + **6.2.1.2 「Left anchoring>Slbling」選為「API_Notes_GroupBox:TGroupBox」。維持「Left anchoring>Enable」為打勾。維持「Left anchoring」右側三個鈕選左邊的。**
        + **6.2.1.3 「Right anchoring>Slbling」選為「API_Notes_GroupBox:TGroupBox」。維持「Left anchoring>Enable」為打勾。維持「Right anchoring」右側三個鈕選右邊的。**
        + **6.2.1.4 「Bottom anchoring>Slbling」選為「API_Notes_GroupBox:TGroupBox」。維持「Left anchoring>Enable」為打勾。維持「Bottom anchoring」右側三個鈕選下邊的。**  
        + **6.2.1.5 「Border space」正中間那格填「5」。**  
        + **6.2.1.6 設定完後關閉Anchors設定視窗。**
      + **6.2.2 設定「Lines」的內容清空。並填入以下內容:**
        ```
        運行需求:
        Windosw作業系統。
        可運行64位元應用程式。
        允許程式通過防火牆。
        Server Port預設值為18002。
        --
        ```
      + **6.2.3 設定「Name」為「API_Notes_Memo」。** 
      + **6.2.4 設定「ReadOnly」為「true」。**
      + **6.2.5 設定「ScrollBars」為「ssBoth」。**
      + **6.2.6 設定「WordWrap」為「false」。**
7. IdHTTPServer1:  
    + **7.1 拖拉一個「System>TUniqueInstance」到「Web Server」標籤頁(物件名稱為「Main_TabSheet」)。預設名稱會是「UniqueInstance1」。設定「Enabled」為「true」。**
      + 因為使用「IdHTTPServer1」建立Server，不希望重複啟動Server，所以不允許使用者重複開啟此應用程式。
    + **7.2 拖拉一個「System>TProcess」到「Web Server」標籤頁(物件名稱為「Main_TabSheet」)。預設名稱會是「Process1」。**
      + 因為需要使用「RunCommand」，拖拉這個元件可以省去一些「uses」的程式碼。
    + **7.3 拖拉一個「Indy Servers Protocols (am)>IdHTTPServer1」到「Web Server」標籤頁(物件名稱為「Main_TabSheet」)。預設名稱會是「IdHTTPServer1」。**
    + **設定「IdHTTPServer1」的「Event」頁面下「OnCommandGet」為如下程式碼。**
      ```pascal
      procedure TForm1.IdHTTPServer1CommandGet(AContext: TIdContext;
        ARequestInfo: TIdHTTPRequestInfo; AResponseInfo: TIdHTTPResponseInfo);
      var
        api_return_json_str: AnsiString;
      begin
        //--------------------------------------------------------------------------
        Log_Memo.Lines.Add('==============================');
        Log_Memo.Lines.Add(FormatDateTime('yyyy-mm-dd HH:MM:SS',Now()));
        Log_Memo.Lines.Add('IdHTTPServer1CommandGet:');
        Log_Memo.Lines.Add('RawHTTPCommand: '+ARequestInfo.RawHTTPCommand);
        Log_Memo.Lines.Add('Command: '+ARequestInfo.Command);
        Log_Memo.Lines.Add('URI: '+ARequestInfo.URI);
        Log_Memo.Lines.Add('RemoteIP: '+ARequestInfo.RemoteIP);
        Log_Memo.Lines.Add('--');
        //--------------------------------------------------------------------------
        //--------------------------------------------------------------------------
        // 簡單的API回應設計
        //--
        // 只回應以下條件:
        // 1. GET 方法
        // 2. API命名
        //--
        // 回應方式:
        //成功時回傳JSON資料:
        //{
        //"status": "success",
        //"data": { ... },
        //"message": null
        //}
        // 錯誤時回傳JSON資料:
        //{
        //"status": "error",
        //"data": null,
        //"message": "Error xxx has occurred"
        //}
        //--
        // 實際狀況:
        // 成功時回傳JSON資料:
        // {"status":"success","data":"Hello!","message":null}
        // 錯誤時回傳JSON資料:
        // {"status":"error","data":null,"message":"錯誤!只接受GET方法!"}
        // {"status":"error","data":null,"message":"錯誤!不合法的API!"}
        //--------------------------------------------------------------------------
        // 1. GET 方法
        if (CompareStr(ARequestInfo.Command,'GET')=0) Then begin//命令是GET方法時
          //不做任何事
        end
        else begin
          //--
          // 準備回傳資料內容
          api_return_json_str:='{"status":"error","data":null,"message":"錯誤!只接受GET方法!"}';
          Log_Memo.Lines.Add('api_return_json_str:');
          Log_Memo.Lines.Add(api_return_json_str);
          //--
          // 回傳資料給客戶端
          AResponseInfo.ContentType:='application/json';
          AResponseInfo.CharSet:='utf-8';
          AResponseInfo.ContentStream:=TStringStream.Create(api_return_json_str, TEncoding.UTF8);
          Log_Memo.Lines.Add('==============================');
          Exit;
        end;
        //--------------------------------------------------------------------------
        // 2.1. API: /api/v1/hello
        if (CompareStr(ARequestInfo.URI,API_hello_Edit.Text)=0) Then begin//API正確時
          //--
          // 準備回傳資料內容
          api_return_json_str:='{"status":"success","data":"Hello!","message":null}';
          Log_Memo.Lines.Add('api_return_json_str:');
          Log_Memo.Lines.Add(api_return_json_str);
          //--
          // 回傳資料給客戶端
          AResponseInfo.ContentType:='application/json';
          AResponseInfo.CharSet:='utf-8';
          AResponseInfo.ContentStream:=TStringStream.Create(api_return_json_str, TEncoding.UTF8);
          Log_Memo.Lines.Add('==============================');
          Exit;
        end
        //--
        // 2.2. API: /api/v1/SwitchArray
        else if (CompareStr(ARequestInfo.URI,API_SwitchArray_Edit.Text)=0) Then begin//API正確時
          //--
          // 準備回傳資料內容
          api_return_json_str:='{"status":"success","data":"SwitchArray!","message":null}';
          //Log_Memo.Lines.Add('api_return_json_str:');
          //Log_Memo.Lines.Add(api_return_json_str);
          //--
          // 呼叫PowerShell進行查詢
          if RunCommand('cmd.exe', ['/c', 'PowerShell "Get-WMIObject -Class Win32_PnPEntity | Where-Object { $_.PNPClass -Match ''Ports''} | Where-Object { $_.Name -Match ''CH340''} | Select-Object Name | ConvertTo-Json -Compress"'],api_return_json_str,[],swoHIDE) then begin
            //--
            // 檢視回傳結果
            Log_Memo.Lines.Add('api_return_json_str:');
            Log_Memo.Lines.Add(api_return_json_str);
            // PowerShell的ConvertTo-Json會把一些字元變成unicode編碼，看了有點討厭，用簡單暴力的方法取代一下。
            api_return_json_str:=StringReplace(api_return_json_str,'\u0026','&',[rfReplaceAll]);// '\u0026' => '&'
            api_return_json_str:=StringReplace(api_return_json_str,'\u0027','&',[rfReplaceAll]);// '\u0026' => '''
            api_return_json_str:=StringReplace(api_return_json_str,'\u003c','&',[rfReplaceAll]);// '\u0026' => '<'
            api_return_json_str:=StringReplace(api_return_json_str,'\u003e','&',[rfReplaceAll]);// '\u0026' => '>'
            //--
            // 換行和空白字元很討厭就去掉...
            api_return_json_str:=Trim(api_return_json_str);
            // 檢視替代後結果
            Log_Memo.Lines.Add(api_return_json_str);
            //--
          end;
          // 限制只能有一個ESP32裝置，進行驗證:
          // 回傳的JSON，沒資料預期是:空字串
          // 回傳的JSON，有資料預期是:
          // {"Name":"USB-SERIAL CH340 (COM3)"}
          // 用骯髒的方式解讀JSON資料，並不是真的驗證JSON內容
          // 驗證字串長度、驗證字串是否為「{"」開頭
          if (api_return_json_str.Length=0) Then begin
            Log_Memo.Lines.Add('PowerShell回傳的是空字串!');
            api_return_json_str:='{"SwitchArray_CHECK":"FAIL","message":"PowerShell回傳的是空字串!"}';
            Log_Memo.Lines.Add(api_return_json_str);
          end
          else if (CompareStr(api_return_json_str.Substring(0,2),'{"')=0) Then begin
            Log_Memo.Lines.Add('PowerShell回傳的是「{"」開頭!');
            // 骯髒的方式取出COM資訊
            api_return_json_str:=StringReplace(api_return_json_str,'{"Name":"USB-SERIAL CH340 (','{"SwitchArray_SerialPort":"',[]);// 只取代一次
            api_return_json_str:=StringReplace(api_return_json_str,')"}','"}',[]);// 只取代一次
            // 骯髒的方式增加JSON資訊
            api_return_json_str:=StringReplace(api_return_json_str,'{"','{"SwitchArray_CHECK":"PASS","',[]);// 只取代一次
            api_return_json_str:=StringReplace(api_return_json_str,'"}','","message":null}',[]);// 只取代一次
          end
          else begin
            Log_Memo.Lines.Add('PowerShell回傳的內容不通過驗證!');
            api_return_json_str:='{"SwitchArray_CHECK":"FAIL","message":"PowerShell回傳的內容不通過驗證!"}';
            Log_Memo.Lines.Add(api_return_json_str);
          end;
          //--
          // 返回結果
          AResponseInfo.ContentType:='application/json';
          AResponseInfo.CharSet:='utf-8';
          AResponseInfo.ContentStream:=TStringStream.Create(api_return_json_str, TEncoding.UTF8);
          Log_Memo.Lines.Add('==============================');
          Exit;
        end
        //--
        // 2.3. API: /api/v1/DMM
        else if (CompareStr(ARequestInfo.URI,API_DMM_Edit.Text)=0) Then begin//API正確時
          //--
          // 準備回傳資料內容
          api_return_json_str:='{"status":"success","data":"DMM!","message":null}';
          //Log_Memo.Lines.Add('api_return_json_str:');
          //Log_Memo.Lines.Add(api_return_json_str);
          //--
          // 呼叫PowerShell進行查詢
          if RunCommand('cmd.exe', ['/c', 'PowerShell "Get-WMIObject -Class Win32_PnPEntity | Where-Object { $_.PNPClass -Match ''USBTestAndMeasurementDevice''} | Select-Object PNPDeviceID | ConvertTo-Json -Compress"'],api_return_json_str,[],swoHIDE) then begin
            //--
            // 檢視回傳結果
            Log_Memo.Lines.Add('api_return_json_str:');
            Log_Memo.Lines.Add(api_return_json_str);
            // PowerShell的ConvertTo-Json會把一些字元變成unicode編碼，看了有點討厭，用簡單暴力的方法取代一下。
            api_return_json_str:=StringReplace(api_return_json_str,'\u0026','&',[rfReplaceAll]);// '\u0026' => '&'
            api_return_json_str:=StringReplace(api_return_json_str,'\u0027','&',[rfReplaceAll]);// '\u0026' => '''
            api_return_json_str:=StringReplace(api_return_json_str,'\u003c','&',[rfReplaceAll]);// '\u0026' => '<'
            api_return_json_str:=StringReplace(api_return_json_str,'\u003e','&',[rfReplaceAll]);// '\u0026' => '>'
            //--
            // 換行和空白字元很討厭就去掉...
            api_return_json_str:=Trim(api_return_json_str);
            // 檢視替代後結果
            Log_Memo.Lines.Add(api_return_json_str);
            //--
          end;
          // 限制只能有一個DMM裝置，進行驗證:
          // 回傳的JSON，沒資料預期是:空字串
          // 回傳的JSON，有資料預期是:
          // {"PNPDeviceID":"USB\\VID_2A8D&PID_0101\\MY60090449"}
          // 用骯髒的方式解讀JSON資料，並不是真的驗證JSON內容
          // 驗證字串長度、驗證字串是否為「{"」開頭
          if (api_return_json_str.Length=0) Then begin
            Log_Memo.Lines.Add('PowerShell回傳的是空字串!');
            api_return_json_str:='{"DMM_CHECK":"FAIL","message":"PowerShell回傳的是空字串!"}';
            Log_Memo.Lines.Add(api_return_json_str);
          end
          else if (CompareStr(api_return_json_str.Substring(0,2),'{"')=0) Then begin
            Log_Memo.Lines.Add('PowerShell回傳的是「{"」開頭!');
            api_return_json_str:=StringReplace(api_return_json_str,'{"','{"DMM_CHECK":"PASS",',[]);// 只取代一次
          end;
          //--
          // 返回結果
          AResponseInfo.ContentType:='application/json';
          AResponseInfo.CharSet:='utf-8';
          AResponseInfo.ContentStream:=TStringStream.Create(api_return_json_str, TEncoding.UTF8);
          Log_Memo.Lines.Add('==============================');
          Exit;
        end
        //--
        // 2.4. API: /api/v1/PSU
        else if (CompareStr(ARequestInfo.URI,API_PSU_Edit.Text)=0) Then begin//API正確時
          //--
          // 準備回傳資料內容
          api_return_json_str:='{"status":"success","data":"PSU!","message":null}';
          //Log_Memo.Lines.Add('api_return_json_str:');
          //Log_Memo.Lines.Add(api_return_json_str);
          //--
          // 呼叫PowerShell進行查詢
          if RunCommand('cmd.exe', ['/c', 'PowerShell "Get-WMIObject -Class Win32_PnPEntity | Where-Object { $_.PNPClass -Match ''Ports''} | Where-Object { $_.Name -Match ''CP210x''} | Select-Object Name | ConvertTo-Json -Compress"'],api_return_json_str,[],swoHIDE) then begin
            //--
            // 檢視回傳結果
            Log_Memo.Lines.Add('api_return_json_str:');
            Log_Memo.Lines.Add(api_return_json_str);
            // PowerShell的ConvertTo-Json會把一些字元變成unicode編碼，看了有點討厭，用簡單暴力的方法取代一下。
            api_return_json_str:=StringReplace(api_return_json_str,'\u0026','&',[rfReplaceAll]);// '\u0026' => '&'
            api_return_json_str:=StringReplace(api_return_json_str,'\u0027','&',[rfReplaceAll]);// '\u0026' => '''
            api_return_json_str:=StringReplace(api_return_json_str,'\u003c','&',[rfReplaceAll]);// '\u0026' => '<'
            api_return_json_str:=StringReplace(api_return_json_str,'\u003e','&',[rfReplaceAll]);// '\u0026' => '>'
            //--
            // 換行和空白字元很討厭就去掉...
            api_return_json_str:=Trim(api_return_json_str);
            // 檢視替代後結果
            Log_Memo.Lines.Add(api_return_json_str);
            //--
          end;
          // 限制只能有一個PSU裝置，進行驗證:
          // 回傳的JSON，沒資料預期是:空字串
          // 回傳的JSON，有資料預期是:
          // {"Name":"Silicon Labs CP210x USB to UART Bridge (COM6)"}
          // 用骯髒的方式解讀JSON資料，並不是真的驗證JSON內容
          // 驗證字串長度、驗證字串是否為「{"」開頭
          if (api_return_json_str.Length=0) Then begin
            Log_Memo.Lines.Add('PowerShell回傳的是空字串!');
            api_return_json_str:='{"PSU_CHECK":"FAIL","message":"PowerShell回傳的是空字串!"}';
            Log_Memo.Lines.Add(api_return_json_str);
          end
          else if (CompareStr(api_return_json_str.Substring(0,2),'{"')=0) Then begin
            Log_Memo.Lines.Add('PowerShell回傳的是「{"」開頭!');
            // 骯髒的方式取出COM資訊
            api_return_json_str:=StringReplace(api_return_json_str,'{"Name":"Silicon Labs CP210x USB to UART Bridge (','{"SwitchArray_SerialPort":"',[]);// 只取代一次
            api_return_json_str:=StringReplace(api_return_json_str,')"}','"}',[]);// 只取代一次
            // 骯髒的方式增加JSON資訊
            api_return_json_str:=StringReplace(api_return_json_str,'{"','{"PSU_CHECK":"PASS","',[]);// 只取代一次
            api_return_json_str:=StringReplace(api_return_json_str,'"}','","message":null}',[]);// 只取代一次
          end
          else begin
            Log_Memo.Lines.Add('PowerShell回傳的內容不通過驗證!');
            api_return_json_str:='{"PSU_CHECK":"FAIL","message":"PowerShell回傳的內容不通過驗證!"}';
            Log_Memo.Lines.Add(api_return_json_str);
          end;
          //--
          // 返回結果
          AResponseInfo.ContentType:='application/json';
          AResponseInfo.CharSet:='utf-8';
          AResponseInfo.ContentStream:=TStringStream.Create(api_return_json_str, TEncoding.UTF8);
          Log_Memo.Lines.Add('==============================');
          Exit;
        end
        //--
        else begin
          api_return_json_str:='{"status":"error","data":null,"message":"錯誤!不合法的API!"} ';
          Log_Memo.Lines.Add('api_return_json_str:');
          Log_Memo.Lines.Add(api_return_json_str);
          AResponseInfo.ContentType:='text/plain';
          AResponseInfo.CharSet:='utf-8';
          AResponseInfo.ContentStream:=TStringStream.Create(api_return_json_str, TEncoding.UTF8);
          Log_Memo.Lines.Add('==============================');
          Exit;
        end;
      end;       
      ```  
    + **設定「ServerRunStop_Button」的「Event」頁面下「OnClick」為如下程式碼。**  
      ```pascal
      procedure TForm1.ServerRunStop_ButtonClick(Sender: TObject);
      begin
        if (IdHTTPServer1.Active=false) Then begin
          // 調整UI
          ServerPort_Edit.Enabled:=false;
          // 設定Server Port
          IdHTTPServer1.DefaultPort:=StrToInt(ServerPort_Edit.Text);
          // 提示訊息
          Log_Memo.Lines.Add('啟動Server...');
          // 啟動Server
          IdHTTPServer1.Active:=true;
          // 調整按鈕文字
          ServerRunStop_Button.Caption:='按我停止';
          // 調整狀態文字
          ServerStatus_Label.Caption:='伺服器狀態: 運行中';
          // 調整狀態列資訊
          StatusBar1.Panels.Items[1].Text:='Server運行中...';
        end
        else begin
          // 停止Server
          IdHTTPServer1.Active:=false;
          // 提示訊息
          Log_Memo.Lines.Add('關閉Server...');
          // 調整按鈕文字
          ServerRunStop_Button.Caption:='按我啟動';
          // 調整狀態文字
          ServerStatus_Label.Caption:='伺服器狀態: 停止';
          // 調整狀態列資訊
          StatusBar1.Panels.Items[1].Text:='Server停止...';
          // 調整UI
          ServerPort_Edit.Enabled:=true;
        end;
      end;     
      ```  
    + **設定「ServerPort_Edit」的「Event」頁面下「OnChange」為如下程式碼。**  
      ```pascal
      procedure TForm1.ServerPort_EditChange(Sender: TObject);
      begin
        API_hello_URL_Edit.Text:='http://'+ServerIPAddress_Edit.Text+':'+ServerPort_Edit.Text+API_hello_Edit.Text;
        API_SwitchArray_URL_Edit.Text:='http://'+ServerIPAddress_Edit.Text+':'+ServerPort_Edit.Text+API_SwitchArray_Edit.Text;
        API_DMM_URL_Edit.Text:='http://'+ServerIPAddress_Edit.Text+':'+ServerPort_Edit.Text+API_DMM_Edit.Text;
        API_PSU_URL_Edit.Text:='http://'+ServerIPAddress_Edit.Text+':'+ServerPort_Edit.Text+API_PSU_Edit.Text;
      end;   
      ```  
8. 基本設定:
  + **8.1 找到「BasicSettings_TabSheet」中的「BasicSettings_Default_Memo」。**
    + **8.1.1 設定「Lines」為以下內容:**
      ```
      [Program]
      Version="v20241102a"
      
      [API_Server]
      AutoStart="false"
      ```  
  + **8.2 找到「BasicSettings_TabSheet」中的「BasicSettings_Notes_Memo」。**
    + **8.2.1 設定「Lines」為以下內容:**
      ```
      基本設定檔案的檔案命名為:「主程式名稱.ini」，例如:「R2MS_Lite_API_Server.ini」。
      基本設定檔案的存放路徑為:與主程式同個資料夾中。
      當基本設定檔案不存在時，將使用預設值製作檔案。請確保該檔案名稱沒有被占用且可寫入。
      當基本設定檔案存在時，將載入並應用設定至主程式中。
      基本設定檔案為參考標準INI檔案格式之自訂格式。主要增加以下規則:
      1.參數存放的行數不可變更。
      2.鍵值組一律使用英數字並避開跳脫字元。也避免檔案編碼造成的問題(希望UTF-8與ANSI都可用)。值一律用字串處理，並且不論長短都要放在雙引號中。
      3.不允許寫註解。
      ```
  + **8.3 找到「Form1」。**
    + **8.3.1 設定「Form1」的「Event」頁面下「OnCreate」為如下程式碼:**  
      ```pascal
      procedure TForm1.FormCreate(Sender: TObject);
      begin
        If FileExists(ChangeFileExt(Application.ExeName,'.ini')) Then begin
          Log_Memo.Lines.Add('INI檔案存在!載入檔案並依內容調整設定...');
          BasicSettings_Current_Memo.Lines.LoadFromFile(ChangeFileExt(Application.ExeName,'.ini'));
          If BasicSettings_Current_Memo.Lines.Count=5 Then begin
            //Log_Memo.Lines.Add(BasicSettings_Current_Memo.Lines.Strings[4]);
            if (CompareStr(BasicSettings_Current_Memo.Lines.Strings[4],'AutoStart="true"')=0) Then begin
              Log_Memo.Lines.Add('目前設定:伺服器自動啟動!');
              ServerRunStop_Button.Click;
            end;
            Log_Memo.Lines.Add('INI檔案存在!載入檔案並依內容調整設定...完成!');
          end
          else begin
            Log_Memo.Lines.Add('INI檔案存在!載入檔案並依內容調整設定...失敗!(錯誤的檔案內容嗎?)');
            BasicSettings_Current_Memo.Enabled:=false;
            Application.MessageBox('基本設定載入失敗!使用預設值!','提示',64);
          end;
        end
        else begin
          Log_Memo.Lines.Add('INI檔案不存在!產生預設INI檔案...');
          BasicSettings_Default_Memo.Lines.SaveToFile(ChangeFileExt(Application.ExeName,'.ini'));
          Log_Memo.Lines.Add('INI檔案不存在!產生預設INI檔案...完成!');
        end;
      end;  
      ```  
