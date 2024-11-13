# 監測站處理流程

### 事前準備
+ 準備 WIN7_64_R2MS_ServerNAT.ova
+ 從野外設置幾何製作*.geo檔案。
+ 取出*.v299.csv檔案
+ 取得相關檔案:
  + https://github.com/cgrgncu/R2MS_Tools

### 單筆CSV2URF
+ 儀器「R2MS_Lite」在連續發送訊號(同時多組發射訊號)時，依照控制軟體版本不同，會紀錄原生CSV資料，ERT_ver2_9_7軟體所儲存的原生資料稱為「v297rawcsv」。
+ 使用「R2MS_Lite_v297rawcsv_to_v297csv.exe」轉檔。將進一步轉檔為「v297csv」，是有檔頭的CSV格式(命名為:「*.v297.csv」)。
+ 為了相容過去的「R2MS_CsvtoUrf_MultipleTx_Chu2019_v20211125a.exe」，需要使用「R2MS_Lite_v297csv_to_v297Ecsv.exe」把「v297csv」轉檔為「v297Ecsv」(命名為:「*.v297E.csv」)。
+ 目前給一般使用者會建議使用有圖形化使用者介面的「R2MS ERT 分析精靈(伺服器版)」，英文:「R2MS_ERT_Wizard_Web_Server.exe」，則需要使用者自行調整檔案名稱與資料夾結構。
  + 該軟體強迫規定的資料夾結構與命名方式有助於資料歸檔與交換。
+ 「R2MS_Lite_v297rawcsv_to_v297csv_Release_v20240403a」轉檔說明:
  + 建議依照範例程式調整輸出檔名。
  + XP1使用S001，XP2使用S002。
  + 這裡選用XP1的原始CSV檔案為範例「2024_04_15_20_01.csv」，放到Input資料夾中。
  + 編寫BATCH為
  ```
  R2MS_Lite_v297rawcsv_to_v297csv.exe "Input\2024_04_15_20_01.csv" "Output" "S001202404152001"
  PAUSE
    ```
  + 會取得「S001202404152001.v297.csv」檔案。
+ 「R2MS_Lite_v297csv_to_v297Ecsv_Release_v20240408a」轉檔說明:
  + 建議依照範例程式調整輸出檔名。
  + XP1使用S001，XP2使用S002。
  + 這裡選用XP1的v297csv檔案為範例「S001202404152001.v297.csv」，放到Input資料夾中。
  + 編寫BATCH為
  ```
  R2MS_Lite_v297csv_to_v297Ecsv.exe "Input\S001202404152001.v297.csv" "Output" "S001202404152001"
  PAUSE
  ```
  + 會取得「S001202404152001.v297E.csv」檔案
+ 「R2MS ERT 分析精靈(伺服器版)」操作說明:
  + 請使用「*.v297E.csv」作為輸入檔案。每個檔案代表一次智能施測(通常耗時約18分鐘)
  + 軟體規畫至少要有3次智能施測，也就是3次不同的「*.v297E.csv」檔案。每次要4個檔案。
    + R2MS Lite開始，不依照時間長度切割檔案，因此要另外手動製作3個空白csv檔案，來滿足資料夾結構。
    + 例如建立empty_A.v297E.csv、empty_B.v297E.csv、empty_C.v297E.csv檔案，檔名可任意調整，但仍建議照此命名。
  + 以本案來說，專案資料夾命名為:「[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)-CSV2URF-solo」
  + 單筆的情況下只好複製3份一樣的資料，並調整成以下資料夾結構:
  ```
  ...\Recorder\XP1\Part01\1\empty_A.v297E.csv
  ...\Recorder\XP1\Part01\1\empty_B.v297E.csv
  ...\Recorder\XP1\Part01\1\empty_C.v297E.csv
  ...\Recorder\XP1\Part01\1\S001202404152001.v297E.csv
  ...\Recorder\XP1\Part01\1\XP1.geo
  ...\Recorder\XP1\Part01\2\empty_A.v297E.csv
  ...\Recorder\XP1\Part01\2\empty_B.v297E.csv
  ...\Recorder\XP1\Part01\2\empty_C.v297E.csv
  ...\Recorder\XP1\Part01\2\S001202404152001.v297E.csv
  ...\Recorder\XP1\Part01\2\XP1.geo
  ...\Recorder\XP1\Part01\3\empty_A.v297E.csv
  ...\Recorder\XP1\Part01\3\empty_B.v297E.csv
  ...\Recorder\XP1\Part01\3\empty_C.v297E.csv
  ...\Recorder\XP1\Part01\3\S001202404152001.v297E.csv
  ...\Recorder\XP1\Part01\3\XP1.geo
  ```
+ 依照指示操作，有用的檔案:
  + 「...\Urf\Level0\XP1\Part01\1\XP1_part01_1_Level0.urf」。
    + 這筆Urf檔案會有187767筆資料。
    + 對應轉檔紀錄為「...\Urf\Level0\XP1\Part01\1\XP1_part01_1_Level0.urflog」。
  + 注意，千萬不要去用任何「*.Level1.urf」，因為qui是沒有意義的。
    + 這筆Urf只有50000筆資料，其實只是取187767筆資料的前50000筆，基本上只有編號較靠前的電極資料。
    + 請回去用187767筆的，在後續分析亂數取樣再降數量。
  + 當資料數量真的不夠3筆才需要使用這個方法。

### N筆CSV2URF
+ 「R2MS ERT 分析精靈(伺服器版)」操作說明:
  + 請使用「*.v297E.csv」作為輸入檔案。每個檔案代表一次智能施測(通常耗時約18分鐘)
  + 軟體規畫至少要有3次智能施測，也就是3次不同的「*.v297E.csv」檔案。每次要4個檔案。
    + R2MS Lite開始，不依照時間長度切割檔案，因此要另外手動製作3個空白csv檔案，來滿足資料夾結構。
    + 例如建立empty_A.v297E.csv、empty_B.v297E.csv、empty_C.v297E.csv檔案，檔名可任意調整，但仍建議照此命名。
  + 以本案來說，專案資料夾命名為:「[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)-CSV2URF」
  + 本案選擇N=3。3筆的情況下選擇指定的3個「*.v297E.csv」，並調整成以下資料夾結構:
  ```
  ...\Recorder\XP1\Part01\1\empty_A.v297E.csv
  ...\Recorder\XP1\Part01\1\empty_B.v297E.csv
  ...\Recorder\XP1\Part01\1\empty_C.v297E.csv
  ...\Recorder\XP1\Part01\1\S001202404152001.v297E.csv
  ...\Recorder\XP1\Part01\1\XP1.geo
  ...\Recorder\XP1\Part01\2\empty_A.v297E.csv
  ...\Recorder\XP1\Part01\2\empty_B.v297E.csv
  ...\Recorder\XP1\Part01\2\empty_C.v297E.csv
  ...\Recorder\XP1\Part01\2\S001202404162001.v297E.csv
  ...\Recorder\XP1\Part01\2\XP1.geo
  ...\Recorder\XP1\Part01\3\empty_A.v297E.csv
  ...\Recorder\XP1\Part01\3\empty_B.v297E.csv
  ...\Recorder\XP1\Part01\3\empty_C.v297E.csv
  ...\Recorder\XP1\Part01\3\S001202404172001.v297E.csv
  ...\Recorder\XP1\Part01\3\XP1.geo
  ```
+ 依照指示操作，有用的檔案:
  + 「...\Urf\Level0\XP1\Part01\1\XP1_part01_1_Level0.urf」、「...\Urf\Level0\XP1\Part01\2\XP1_part01_2_Level0.urf」、「...\Urf\Level0\XP1\Part01\3\XP1_part01_3_Level0.urf」。
    + 這些Urf檔案各自會有187767筆資料。
    + 對應轉檔紀錄為「*.urflog」。
  + 可使用「*.Level1.urf」。
    + 這種Urf只有50000筆資料，可以選各自的，也可以選最外層平均的來進行逆推。
    + 對應轉檔紀錄為「*.urflog」。

### N筆CSV2URF鎖定qui
+ 「R2MS ERT 分析精靈(伺服器版)」操作說明:
  + 請使用「*.v297E.csv」作為輸入檔案。每個檔案代表一次智能施測(通常耗時約18分鐘)
  + 軟體規畫至少要有3次智能施測，也就是3次不同的「*.v297E.csv」檔案。每次要4個檔案。
    + R2MS Lite開始，不依照時間長度切割檔案，因此要另外手動製作3個空白csv檔案，來滿足資料夾結構。
    + 例如建立empty_A.v297E.csv、empty_B.v297E.csv、empty_C.v297E.csv檔案，檔名可任意調整，但仍建議照此命名。
  + 以本案來說，專案資料夾命名為:「[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)-CSV2URF-fixqui-3」
  + 本案選擇N=3。3筆的情況下選擇指定的3個「*.v297E.csv」，並調整成以下資料夾結構:
  ```
  ...\Recorder\XP1\Part01\1\empty_A.v297E.csv
  ...\Recorder\XP1\Part01\1\empty_B.v297E.csv
  ...\Recorder\XP1\Part01\1\empty_C.v297E.csv
  ...\Recorder\XP1\Part01\1\S001202404152001.v297E.csv
  ...\Recorder\XP1\Part01\1\XP1.geo
  ...\Recorder\XP1\Part01\2\empty_A.v297E.csv
  ...\Recorder\XP1\Part01\2\empty_B.v297E.csv
  ...\Recorder\XP1\Part01\2\empty_C.v297E.csv
  ...\Recorder\XP1\Part01\2\S001202404162001.v297E.csv
  ...\Recorder\XP1\Part01\2\XP1.geo
  ...\Recorder\XP1\Part01\3\empty_A.v297E.csv
  ...\Recorder\XP1\Part01\3\empty_B.v297E.csv
  ...\Recorder\XP1\Part01\3\empty_C.v297E.csv
  ...\Recorder\XP1\Part01\3\S001202404172001.v297E.csv
  ...\Recorder\XP1\Part01\3\XP1.geo
  ```
+ 依照指示操作，至此會得到許多可用於逆推的檔案。
  + 「...\Urf\Level0\XP1\Part01\1\XP1_part01_1_Level0.urf」、「...\Urf\Level0\XP1\Part01\2\XP1_part01_2_Level0.urf」、「...\Urf\Level0\XP1\Part01\3\XP1_part01_3_Level0.urf」。
    + 這些Urf檔案各自會有187767筆資料。
    + 對應轉檔紀錄為「*.urflog」。
  + 可使用「*.Level1.urf」。
    + 這種Urf只有50000筆資料，可以選各自的，也可以選最外層平均的來進行逆推。
    + 對應轉檔紀錄為「*.urflog」。
+ 但應用於監測時，將以此N筆作為基礎，計算qui，並鎖定使用此qui。這樣可以固定後續監測索取用的資料範圍，排除量測結果較不穩定的資料。
  + 接著放入下一筆監測資料「S001202404182001.v297E.csv」，也就是調整資料夾結構:
  ```
  ...\Recorder\XP1\Part01\1\empty_A.v297E.csv
  ...\Recorder\XP1\Part01\1\empty_B.v297E.csv
  ...\Recorder\XP1\Part01\1\empty_C.v297E.csv
  ...\Recorder\XP1\Part01\1\S001202404152001.v297E.csv
  ...\Recorder\XP1\Part01\1\XP1.geo
  ...\Recorder\XP1\Part01\2\empty_A.v297E.csv
  ...\Recorder\XP1\Part01\2\empty_B.v297E.csv
  ...\Recorder\XP1\Part01\2\empty_C.v297E.csv
  ...\Recorder\XP1\Part01\2\S001202404162001.v297E.csv
  ...\Recorder\XP1\Part01\2\XP1.geo
  ...\Recorder\XP1\Part01\3\empty_A.v297E.csv
  ...\Recorder\XP1\Part01\3\empty_B.v297E.csv
  ...\Recorder\XP1\Part01\3\empty_C.v297E.csv
  ...\Recorder\XP1\Part01\3\S001202404172001.v297E.csv
  ...\Recorder\XP1\Part01\3\XP1.geo
  ...\Recorder\XP1\Part01\4\empty_A.v297E.csv
  ...\Recorder\XP1\Part01\4\empty_B.v297E.csv
  ...\Recorder\XP1\Part01\4\empty_C.v297E.csv
  ...\Recorder\XP1\Part01\4\S001202404182001.v297E.csv
  ...\Recorder\XP1\Part01\4\XP1.geo
  ```
+ 依照指示操作，有用的檔案:
  + 「...\Urf\Level0\XP1\Part01\4\XP1_part01_4_Level0.urf」
    + 此Urf檔案會有187767筆資料。
    + 對應轉檔紀錄為「*.urflog」。
    + 自行取出後，依需求重新命名。
  + 「...\Urf\Level1\XP1\Part01\4\XP1_part01_4_Level1.urf」
    + 此Urf檔案會有50000筆資料。
    + 自行取出後，依需求重新命名。
    + 對應轉檔紀錄為「*.urflog」。
+ 若要再放入另一筆資料，可以繼續建立資料夾(名稱需為整數遞增)，也可以替換「\Recorder\XP1\Part01\4\*.v297E.csv」，並刪除「...\Urf\Level0\XP1\Part01\4\*.urf」「...\Urf\Level1\XP1\Part01\4\*.urf」，再依照前述操作再次運行。

### 歸檔
+ 利用已經有的工具，就需要先照前述方案把資料依照指定結構擺放後運行工具才能進行需要的分析，但分析完要歸檔，以利未來進一步分析與資料交換。
### MonitoringRecorder
+ 1.將原始資料(*.v297.csv)歸檔，符合以下的資料結構:
  ```
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringRecorder\XP1\XP1.geo
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringRecorder\XP1\XP1.trn
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringRecorder\XP1\2024\04\15\2001\Part01\1\S001202404152001.v297.csv
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringRecorder\XP1\2024\04\16\2001\Part01\1\S001202404162001.v297.csv
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringRecorder\XP1\2024\04\17\2001\Part01\1\S001202404172001.v297.csv
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringRecorder\XP1\2024\04\18\2001\Part01\1\S001202404182001.v297.csv
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringRecorder\XP1\2024\04\19\2001\Part01\1\S001202404192001.v297.csv
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringRecorder\XP1\2024\04\20\2001\Part01\1\S001202404202001.v297.csv
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringRecorder\XP2\XP2.geo
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringRecorder\XP2\XP2.trn
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringRecorder\XP2\2024\04\15\2031\Part01\1\S002202404152031.v297.csv
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringRecorder\XP2\2024\04\16\2031\Part01\1\S002202404162031.v297.csv
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringRecorder\XP2\2024\04\17\2031\Part01\1\S002202404172031.v297.csv
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringRecorder\XP2\2024\04\18\2031\Part01\1\S002202404182031.v297.csv
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringRecorder\XP2\2024\04\19\2031\Part01\1\S002202404192031.v297.csv
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringRecorder\XP2\2024\04\20\2031\Part01\1\S002202404202031.v297.csv
  ```  
  > + 「.v297.csv」要利用R2MS_Lite_v297csv_to_v297Ecsv_Release_v20240408a轉檔為「.v297E.csv」才能給ERT分析精靈使用。
  > + 每個「DD資料夾」內可能存在多個「HHNN資料夾」。DD表示兩碼的日期，HH表示兩碼的小時，NN表示兩碼的分鐘。  
  > + 以上方6天為例，資料大小約200[MB]。
  > + 可從結構中判別XP1使用S001，並於20:01開始放電；XP2使用S002，並於20:31開始放電
+ 2.將(*.csv)壓縮為zip檔案，並將製作紀錄存為json檔案，符合以下的資料結構:
  ```
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringRecorder\XP1\XP1.geo
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringRecorder\XP1\XP1.trn
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringRecorder\XP1\2024\04\15\2001.json
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringRecorder\XP1\2024\04\15\2001.zip
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringRecorder\XP1\2024\04\16\2001.json
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringRecorder\XP1\2024\04\16\2001.zip
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringRecorder\XP1\2024\04\17\2001.json
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringRecorder\XP1\2024\04\17\2001.zip
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringRecorder\XP1\2024\04\18\2001.json
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringRecorder\XP1\2024\04\18\2001.zip
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringRecorder\XP1\2024\04\19\2001.json
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringRecorder\XP1\2024\04\19\2001.zip
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringRecorder\XP1\2024\04\20\2001.json
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringRecorder\XP1\2024\04\20\2001.zip
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringRecorder\XP2\XP1.geo
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringRecorder\XP2\XP1.trn
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringRecorder\XP2\2024\04\15\2031.json
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringRecorder\XP2\2024\04\15\2031.zip
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringRecorder\XP2\2024\04\16\2031.json
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringRecorder\XP2\2024\04\16\2031.zip
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringRecorder\XP2\2024\04\17\2031.json
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringRecorder\XP2\2024\04\17\2031.zip
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringRecorder\XP2\2024\04\18\2031.json
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringRecorder\XP2\2024\04\18\2031.zip
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringRecorder\XP2\2024\04\19\2031.json
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringRecorder\XP2\2024\04\19\2031.zip
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringRecorder\XP2\2024\04\20\2031.json
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringRecorder\XP2\2024\04\20\2031.zip
  ```  
  > + json原則上是UTF-8編碼，但考量部分軟體支援程度不同，內容僅使用ASCII碼。  
  > + 以上方6天為例，資料大小約46[MB]。大幅節省空間。  
  
### MonitoringQualityInfo
+ 監測站不儲存完整18萬筆資料的Urf檔案，有需要的時候請重新利用CSV檔案分析。監測站只儲存分析用的保留資料，例如50000筆。
+ 監測站將選用N次穩定資料來擇定有限數量的Urf檔案進行長期分析。一般而言，遵守如下策略:
  + N至少3次，選擇天氣穩定無風無雨的時段，先當作一次性調查分析，審視原始資料與逆推剖面，確認合理後決定N。
  + 選擇品質篩選公式，預設使用公式B。
  + 選擇保留資料量，預設保留50000筆資料。現場環境惡劣、干擾顯著時，可嘗試降低資料筆數，以確保逆推運算能收斂。
+ 小油坑平台站的操作範例:
  + 在虛擬機中建立如下資料結構:
  ```
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\1\XP1.geo
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\1\XP1.trn  
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\1\empty_A.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\1\empty_B.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\1\empty_C.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\1\S001202404152001.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\2\XP1.geo
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\2\XP1.trn
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\2\empty_A.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\2\empty_B.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\2\empty_C.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\2\S001202404162001.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\3\XP1.geo
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\3\XP1.trn 
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\3\empty_A.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\3\empty_B.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\3\empty_C.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\3\S001202404172001.v297E.csv

  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\1\XP2.geo
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\1\XP2.trn  
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\1\empty_A.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\1\empty_B.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\1\empty_C.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\1\S002202404152031.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\2\XP2.geo
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\2\XP2.trn
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\2\empty_A.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\2\empty_B.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\2\empty_C.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\2\S002202404162031.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\3\XP2.geo
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\3\XP2.trn 
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\3\empty_A.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\3\empty_B.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\3\empty_C.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\3\S002202404172031.v297E.csv
  ```  
  
  + 本案例取得的Quality_Info: 
  ```
  Quality_Info="Quality_Info_B[%]"
  Remaining_Number="50000"
  Reduce_Condition_in_percent="0.97282"
  ```
  > + 採用B方法在排名第50000筆的資料品質指標為0.97%，可簡單理解為此指標越小，排名內的電極重複量測結果差異越小，推測是屬於有效量測。  
  > + 品質較差的場址，此指標可能遠大於5%。  

  + 分析後會多得到如下資料夾結構:
  ```
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP1\XP1_S3_R4_B50000_Level1.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP1\Part01\XP1_Part01.uqi  
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP1\Part01\1\XP1_Part01_1_Level0.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP1\Part01\1\XP1_Part01_1_Level0.urflog
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP1\Part01\2\XP1_Part01_2_Level0.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP1\Part01\2\XP1_Part01_2_Level0.urflog
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP1\Part01\3\XP1_Part01_3_Level0.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP1\Part01\3\XP1_Part01_3_Level0.urflog
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP1\Part01\XP1_Part01_Level1.urf  
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP1\Part01\1\XP1_Part01_1_Level1.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP1\Part01\1\XP1_Part01_1_Level1.urflog
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP1\Part01\2\XP1_Part01_2_Level1.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP1\Part01\2\XP1_Part01_2_Level1.urflog
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP1\Part01\3\XP1_Part01_3_Level1.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP1\Part01\3\XP1_Part01_3_Level1.urflog

  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP2\XP2_S3_R4_B50000_Level1.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP2\Part01\XP2_Part01.uqi  
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP2\Part01\1\XP2_Part01_1_Level0.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP2\Part01\1\XP2_Part01_1_Level0.urflog
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP2\Part01\2\XP2_Part01_2_Level0.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP2\Part01\2\XP2_Part01_2_Level0.urflog
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP2\Part01\3\XP2_Part01_3_Level0.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP2\Part01\3\XP2_Part01_3_Level0.urflog
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP2\Part01\XP2_Part01_Level1.urf  
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP2\Part01\1\XP2_Part01_1_Level1.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP2\Part01\1\XP2_Part01_1_Level1.urflog
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP2\Part01\2\XP2_Part01_2_Level1.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP2\Part01\2\XP2_Part01_2_Level1.urflog
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP2\Part01\3\XP2_Part01_3_Level1.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP2\Part01\3\XP2_Part01_3_Level1.urflog 
  ```
  > + 會將以上所有資料歸檔至資料夾中，以利後人檢驗。  
  > + 這裡主要利用「XP1_S3_R4_B50000_Level1.urf」、「XP2_S3_R4_B50000_Level1.urf」進行逆推，若RMS低且主觀認定剖面地表分布合理，則確定參數。若否，則重新調整參數並檢視CSV檔案。  
  > + 後續分析主要利用的檔案則為「XP1_Part01.uqi」、「XP2_Part01.uqi」。

+ 將「[20240409A]Stable-CSV2URF(XYKP)」壓縮後歸檔，符合以下的資料結構:
  ```
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP).zip
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\1\empty_A.v297E.csv
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\1\empty_B.v297E.csv
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\1\empty_C.v297E.csv
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\1\S001202404152001.v297E.csv
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\1\XP1.geo
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\1\XP1.trn
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\2\empty_A.v297E.csv
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\2\empty_B.v297E.csv
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\2\empty_C.v297E.csv
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\2\S001202404162001.v297E.csv
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\2\XP1.geo
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\2\XP1.trn
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\3\empty_A.v297E.csv
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\3\empty_B.v297E.csv
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\3\empty_C.v297E.csv
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\3\S001202404172001.v297E.csv
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\3\XP1.geo
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\3\XP1.trn

  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\1\empty_A.v297E.csv
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\1\empty_B.v297E.csv
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\1\empty_C.v297E.csv
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\1\S001202404152031.v297E.csv
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\1\XP1.geo
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\1\XP1.trn
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\2\empty_A.v297E.csv
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\2\empty_B.v297E.csv
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\2\empty_C.v297E.csv
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\2\S001202404162031.v297E.csv
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\2\XP1.geo
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\2\XP1.trn
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\3\empty_A.v297E.csv
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\3\empty_B.v297E.csv
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\3\empty_C.v297E.csv
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\3\S001202404172031.v297E.csv
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\3\XP2.geo
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\3\XP2.trn

  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP1\XP1_S3_R4_B50000_Level1.urf
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP1\Part01\XP1_Part01.uqi  
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP1\Part01\1\XP1_Part01_1_Level0.urf
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP1\Part01\1\XP1_Part01_1_Level0.urflog
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP1\Part01\2\XP1_Part01_2_Level0.urf
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP1\Part01\2\XP1_Part01_2_Level0.urflog
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP1\Part01\3\XP1_Part01_3_Level0.urf
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP1\Part01\3\XP1_Part01_3_Level0.urflog
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP1\Part01\XP1_Part01_Level1.urf  
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP1\Part01\1\XP1_Part01_1_Level1.urf
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP1\Part01\1\XP1_Part01_1_Level1.urflog
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP1\Part01\2\XP1_Part01_2_Level1.urf
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP1\Part01\2\XP1_Part01_2_Level1.urflog
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP1\Part01\3\XP1_Part01_3_Level1.urf
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP1\Part01\3\XP1_Part01_3_Level1.urflog

  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP2\XP2_S3_R4_B50000_Level1.urf
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP2\Part01\XP2_Part01.uqi  
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP2\Part01\1\XP2_Part01_1_Level0.urf
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP2\Part01\1\XP2_Part01_1_Level0.urflog
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP2\Part01\2\XP2_Part01_2_Level0.urf
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP2\Part01\2\XP2_Part01_2_Level0.urflog
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP2\Part01\3\XP2_Part01_3_Level0.urf
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP2\Part01\3\XP2_Part01_3_Level0.urflog
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP2\Part01\XP2_Part01_Level1.urf  
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP2\Part01\1\XP2_Part01_1_Level1.urf
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP2\Part01\1\XP2_Part01_1_Level1.urflog
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP2\Part01\2\XP2_Part01_2_Level1.urf
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP2\Part01\2\XP2_Part01_2_Level1.urflog
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP2\Part01\3\XP2_Part01_3_Level1.urf
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringQualityInfo\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP2\Part01\3\XP2_Part01_3_Level1.urflog 
  ```  
### MonitoringInversion
+ 監測站分析資料不使用Level0.urf(18萬筆資料)，而是使用Level1.urf(例如5萬筆資料)。
+ 「R2MS_CsvtoUrf_MultipleTx_Chu2019_Release_v20211125a」軟體輸入｢.v297E.csv」輸出「Level0.urf」。
+ 「Urf_Reduce_By_QualityInfo_Release_v20211126a」軟體輸入｢Level0.urf」、「Quality_Info.qui」輸出「Level1.urf」。
  + 監測站只保存「Level1.urf」及其運作紀錄「Level1.urflog」。
+ 上述細節也可以用特殊的步驟操作ERT精靈而達到目的。
+ 小油坑平台站的操作範例:
  + 1.用ERT分析精靈來做，若不確定環境，請使用全新虛擬機。取得前述歸檔的「[20240409A]Stable-CSV2URF(XYKP).zip」，解壓縮至目錄中，符合以下檔案結構:
  ```
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\1\XP1.geo
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\1\XP1.trn  
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\1\empty_A.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\1\empty_B.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\1\empty_C.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\1\S001202404152001.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\2\XP1.geo
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\2\XP1.trn
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\2\empty_A.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\2\empty_B.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\2\empty_C.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\2\S001202404162001.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\3\XP1.geo
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\3\XP1.trn 
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\3\empty_A.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\3\empty_B.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\3\empty_C.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\3\S001202404172001.v297E.csv

  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\1\XP2.geo
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\1\XP2.trn  
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\1\empty_A.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\1\empty_B.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\1\empty_C.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\1\S002202404152031.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\2\XP2.geo
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\2\XP2.trn
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\2\empty_A.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\2\empty_B.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\2\empty_C.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\2\S002202404162031.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\3\XP2.geo
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\3\XP2.trn 
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\3\empty_A.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\3\empty_B.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\3\empty_C.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\3\S002202404172031.v297E.csv

  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP1\XP1_S3_R4_B50000_Level1.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP1\Part01\XP1_Part01.uqi  
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP1\Part01\1\XP1_Part01_1_Level0.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP1\Part01\1\XP1_Part01_1_Level0.urflog
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP1\Part01\2\XP1_Part01_2_Level0.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP1\Part01\2\XP1_Part01_2_Level0.urflog
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP1\Part01\3\XP1_Part01_3_Level0.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP1\Part01\3\XP1_Part01_3_Level0.urflog
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP1\Part01\XP1_Part01_Level1.urf  
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP1\Part01\1\XP1_Part01_1_Level1.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP1\Part01\1\XP1_Part01_1_Level1.urflog
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP1\Part01\2\XP1_Part01_2_Level1.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP1\Part01\2\XP1_Part01_2_Level1.urflog
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP1\Part01\3\XP1_Part01_3_Level1.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP1\Part01\3\XP1_Part01_3_Level1.urflog

  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP2\XP2_S3_R4_B50000_Level1.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP2\Part01\XP2_Part01.uqi  
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP2\Part01\1\XP2_Part01_1_Level0.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP2\Part01\1\XP2_Part01_1_Level0.urflog
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP2\Part01\2\XP2_Part01_2_Level0.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP2\Part01\2\XP2_Part01_2_Level0.urflog
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP2\Part01\3\XP2_Part01_3_Level0.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP2\Part01\3\XP2_Part01_3_Level0.urflog
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP2\Part01\XP2_Part01_Level1.urf  
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP2\Part01\1\XP2_Part01_1_Level1.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP2\Part01\1\XP2_Part01_1_Level1.urflog
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP2\Part01\2\XP2_Part01_2_Level1.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP2\Part01\2\XP2_Part01_2_Level1.urflog
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP2\Part01\3\XP2_Part01_3_Level1.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP2\Part01\3\XP2_Part01_3_Level1.urflog 
  ```  
  + 接著追加一個CSV檔案進去，符合以下檔案結構:
  ```
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\1\XP1.geo
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\1\XP1.trn  
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\1\empty_A.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\1\empty_B.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\1\empty_C.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\1\S001202404152001.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\2\XP1.geo
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\2\XP1.trn
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\2\empty_A.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\2\empty_B.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\2\empty_C.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\2\S001202404162001.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\3\XP1.geo
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\3\XP1.trn 
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\3\empty_A.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\3\empty_B.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\3\empty_C.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\3\S001202404172001.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\4\XP1.geo
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\4\XP1.trn 
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\4\empty_A.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\4\empty_B.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\4\empty_C.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\4\S001202404182001.v297E.csv

  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\1\XP2.geo
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\1\XP2.trn  
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\1\empty_A.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\1\empty_B.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\1\empty_C.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\1\S002202404152031.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\2\XP2.geo
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\2\XP2.trn
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\2\empty_A.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\2\empty_B.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\2\empty_C.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\2\S002202404162031.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\3\XP2.geo
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\3\XP2.trn 
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\3\empty_A.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\3\empty_B.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\3\empty_C.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\3\S002202404172031.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\4\XP2.geo
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\4\XP2.trn 
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\4\empty_A.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\4\empty_B.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\4\empty_C.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\4\S002202404172031.v297E.csv

  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP1\XP1_S3_R4_B50000_Level1.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP1\Part01\XP1_Part01.uqi  
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP1\Part01\1\XP1_Part01_1_Level0.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP1\Part01\1\XP1_Part01_1_Level0.urflog
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP1\Part01\2\XP1_Part01_2_Level0.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP1\Part01\2\XP1_Part01_2_Level0.urflog
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP1\Part01\3\XP1_Part01_3_Level0.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP1\Part01\3\XP1_Part01_3_Level0.urflog
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP1\Part01\XP1_Part01_Level1.urf  
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP1\Part01\1\XP1_Part01_1_Level1.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP1\Part01\1\XP1_Part01_1_Level1.urflog
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP1\Part01\2\XP1_Part01_2_Level1.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP1\Part01\2\XP1_Part01_2_Level1.urflog
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP1\Part01\3\XP1_Part01_3_Level1.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP1\Part01\3\XP1_Part01_3_Level1.urflog

  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP2\XP2_S3_R4_B50000_Level1.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP2\Part01\XP2_Part01.uqi  
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP2\Part01\1\XP2_Part01_1_Level0.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP2\Part01\1\XP2_Part01_1_Level0.urflog
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP2\Part01\2\XP2_Part01_2_Level0.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP2\Part01\2\XP2_Part01_2_Level0.urflog
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP2\Part01\3\XP2_Part01_3_Level0.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP2\Part01\3\XP2_Part01_3_Level0.urflog
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP2\Part01\XP2_Part01_Level1.urf  
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP2\Part01\1\XP2_Part01_1_Level1.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP2\Part01\1\XP2_Part01_1_Level1.urflog
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP2\Part01\2\XP2_Part01_2_Level1.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP2\Part01\2\XP2_Part01_2_Level1.urflog
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP2\Part01\3\XP2_Part01_3_Level1.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP2\Part01\3\XP2_Part01_3_Level1.urflog 
  ```
  + 分析完之後，符合以下檔案結構:
  ```
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\1\XP1.geo
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\1\XP1.trn  
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\1\empty_A.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\1\empty_B.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\1\empty_C.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\1\S001202404152001.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\2\XP1.geo
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\2\XP1.trn
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\2\empty_A.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\2\empty_B.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\2\empty_C.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\2\S001202404162001.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\3\XP1.geo
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\3\XP1.trn 
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\3\empty_A.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\3\empty_B.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\3\empty_C.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\3\S001202404172001.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\4\XP1.geo
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\4\XP1.trn 
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\4\empty_A.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\4\empty_B.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\4\empty_C.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP1\Part01\4\S001202404182001.v297E.csv

  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\1\XP2.geo
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\1\XP2.trn  
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\1\empty_A.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\1\empty_B.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\1\empty_C.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\1\S002202404152031.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\2\XP2.geo
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\2\XP2.trn
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\2\empty_A.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\2\empty_B.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\2\empty_C.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\2\S002202404162031.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\3\XP2.geo
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\3\XP2.trn 
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\3\empty_A.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\3\empty_B.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\3\empty_C.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\3\S002202404172031.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\4\XP2.geo
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\4\XP2.trn 
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\4\empty_A.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\4\empty_B.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\4\empty_C.v297E.csv
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Recorder\XP2\Part01\4\S002202404172031.v297E.csv

  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP1\XP1_S3_R4_B50000_Level1.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP1\Part01\XP1_Part01.uqi  
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP1\Part01\1\XP1_Part01_1_Level0.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP1\Part01\1\XP1_Part01_1_Level0.urflog
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP1\Part01\2\XP1_Part01_2_Level0.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP1\Part01\2\XP1_Part01_2_Level0.urflog
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP1\Part01\3\XP1_Part01_3_Level0.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP1\Part01\3\XP1_Part01_3_Level0.urflog
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP1\Part01\4\XP1_Part01_4_Level0.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP1\Part01\4\XP1_Part01_4_Level0.urflog
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP1\Part01\XP1_Part01_Level1.urf  
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP1\Part01\1\XP1_Part01_1_Level1.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP1\Part01\1\XP1_Part01_1_Level1.urflog
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP1\Part01\2\XP1_Part01_2_Level1.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP1\Part01\2\XP1_Part01_2_Level1.urflog
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP1\Part01\3\XP1_Part01_3_Level1.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP1\Part01\3\XP1_Part01_3_Level1.urflog
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP1\Part01\4\XP1_Part01_4_Level1.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP1\Part01\4\XP1_Part01_4_Level1.urflog

  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP2\XP2_S3_R4_B50000_Level1.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP2\Part01\XP2_Part01.uqi  
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP2\Part01\1\XP2_Part01_1_Level0.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP2\Part01\1\XP2_Part01_1_Level0.urflog
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP2\Part01\2\XP2_Part01_2_Level0.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP2\Part01\2\XP2_Part01_2_Level0.urflog
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP2\Part01\3\XP2_Part01_3_Level0.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP2\Part01\3\XP2_Part01_3_Level0.urflog
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP2\Part01\4\XP2_Part01_4_Level0.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level0\XP2\Part01\4\XP2_Part01_4_Level0.urflog
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP2\Part01\XP2_Part01_Level1.urf  
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP2\Part01\1\XP2_Part01_1_Level1.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP2\Part01\1\XP2_Part01_1_Level1.urflog
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP2\Part01\2\XP2_Part01_2_Level1.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP2\Part01\2\XP2_Part01_2_Level1.urflog
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP2\Part01\3\XP2_Part01_3_Level1.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP2\Part01\3\XP2_Part01_3_Level1.urflog
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP2\Part01\4\XP2_Part01_4_Level1.urf
  C:\R2MS_ERT_Web_Server\Projects\[20240409A]Stable-CSV2URF(XYKP)\Urf\Level1\XP2\Part01\4\XP2_Part01_4_Level1.urflog 
  ```
  > + 至此，我們需要的「Level1.urf」均已輸出，請自行改名。
  > + 以本例來說:
  >   + 「XP1_Part01_1_Level0.urf」須改為「S001202404152001_Level1.urf」。
  >   + 「XP1_Part01_1_Level0.urflog」須改為「S001202404152001_Level1.urflog」。
  >   + 「XP1_Part01_2_Level0.urf」須改為「S001202404162001_Level1.urf」。
  >   + 「XP1_Part01_2_Level0.urflog」須改為「S001202404162001_Level1.urflog」。
  >   + 「XP1_Part01_3_Level0.urf」須改為「S001202404172001_Level1.urf」。
  >   + 「XP1_Part01_3_Level0.urflog」須改為「S001202404172001_Level1.urflog」。
  >   + 「XP1_Part01_4_Level0.urf」須改為「S001202404182001_Level1.urf」。
  >   + 「XP1_Part01_4_Level0.urflog」須改為「S001202404182001_Level1.urflog」。
  >   + 「XP2_Part01_1_Level0.urf」須改為「S001202404152001_Level1.urf」。
  >   + 「XP2_Part01_1_Level0.urflog」須改為「S001202404152031_Level1.urflog」。
  >   + 「XP2_Part01_2_Level0.urf」須改為「S001202404162031_Level1.urf」。
  >   + 「XP2_Part01_2_Level0.urflog」須改為「S001202404162031_Level1.urflog」。
  >   + 「XP2_Part01_3_Level0.urf」須改為「S001202404172031_Level1.urf」。
  >   + 「XP2_Part01_3_Level0.urflog」須改為「S001202404172031_Level1.urflog」。
  >   + 「XP2_Part01_4_Level0.urf」須改為「S001202404182031_Level1.urf」。
  >   + 「XP2_Part01_4_Level0.urflog」須改為「S001202404182031_Level1.urflog」。

  + 改名的URF進行逆推後歸檔。


### vFramePlayer
https://github.com/vmllab-js/vFramePlayer?tab=readme-ov-file
