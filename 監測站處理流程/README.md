# 監測站處理流程

### 事前準備
+ 準備 WIN7_64_R2MS_ServerNAT.ova
+ 從野外設置幾何製作*.geo檔案。
+ 取出*.v299.csv檔案
+ 取得相關檔案:
  + https://github.com/cgrgncu/R2MS_Tools

# 單筆CSV2URF
+ 儀器「R2MS_Lite」在連續發送訊號(同時多組發射訊號)時，依照控制軟體版本不同，會紀錄原生CSV資料，ERT_ver2_9_7軟體所儲存的原生資料稱為「v297rawcsv」。
+ 使用「R2MS_Lite_v297rawcsv_to_v297csv.exe」轉檔。將進一步轉檔為「v297csv」，是有檔頭的CSV格式(命名為:「*.v297.csv」)。
+ 為了相容過去的「R2MS_CsvtoUrf_MultipleTx_Chu2019_v20211125a.exe」，需要使用「R2MS_Lite_v297csv_to_v297Ecsv_v20240408a.exe」把「v297csv」轉檔為「v297Ecsv」(命名為:「*.v297E.csv」)。
+ 「R2MS_Lite_v297rawcsv_to_v297csv.exe」轉檔說明:
  + 建議依照範例程式調整輸出檔名。
  + XP1使用S001，XP2使用S002。
  + 這裡選用XP1的原始CSV檔案為範例「2024_04_15_20_01.csv」，放到Input資料夾中。
  + 編寫BATCH為
  ```
  R2MS_Lite_v297rawcsv_to_v297csv.exe "Input\2024_04_15_20_01.csv" "Output" "S001202404152001"
  PAUSE
    ```
  + 會取得「S001202404152001.v297.csv」檔案。
  + 再使用
  + 將「\Part01\1\」資料夾內放好所需檔案:
    + S001202404152001.v297.csv
    + Empty_A.csv
    + Empty_B.csv
    + Empty_C.csv
+ 受限「R2MS_CsvtoUrf_MultipleTx_Chu2019_Release_v20211125a」程式限制必須要有三筆資料再計算Urf_Quality_Info(*.uqi)，此時只有一筆，故要作弊複製成三份一樣的。
+ 製作3份放到 
