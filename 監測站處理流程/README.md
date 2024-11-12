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
+ 1.將原始資料(*.csv)歸檔，符合以下的資料結構:
  ```
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringRecorder\XP1\2024\04\15\2001\Part01\1\S001202404152001.v297.csv
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringRecorder\XP1\2024\04\16\2001\Part01\1\S001202404162001.v297.csv
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringRecorder\XP1\2024\04\17\2001\Part01\1\S001202404172001.v297.csv
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringRecorder\XP1\2024\04\18\2001\Part01\1\S001202404182001.v297.csv
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringRecorder\XP1\2024\04\19\2001\Part01\1\S001202404192001.v297.csv
  ...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\MonitoringRecorder\XP1\2024\04\20\2001\Part01\1\S001202404202001.v297.csv
  ```  
  > 每個「DD資料夾」內可能存在多個「HHNN資料夾」。DD表示兩碼的日期，HH表示兩碼的小時，NN表示兩碼的分鐘。  
  > 以上方6天為例，資料大小約101[MB]。  
+ 2.將(*.csv)壓縮為zip檔案，並將製作紀錄存為json檔案，符合以下的資料結構:
  ```
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
  ```  
  > json原則上是UTF-8編碼，但考量部分軟體支援程度不同，內容僅使用ASCII碼。  
  > 以上方6天為例，資料大小約22.7[MB]。大幅節省空間。  
  
### MonitoringUrf

### vFramePlayer
https://github.com/vmllab-js/vFramePlayer?tab=readme-ov-file
