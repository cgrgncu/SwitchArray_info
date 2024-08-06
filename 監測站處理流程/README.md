# 監測站處理流程

### 事前準備
+ 準備 WIN7_64_R2MS_ServerNAT.ova
+ 從野外設置幾何製作*.geo檔案。
+ 取出*.v299.csv檔案
+ 取得相關檔案:
  + https://github.com/cgrgncu/R2MS_Tools

# 單筆CSV2URF
+ 受限「R2MS_CsvtoUrf_MultipleTx_Chu2019_Release_v20211125a」程式限制，僅支援R2MS版本的CSV檔案，為了相容，所以須動一點手腳:
  + R2MS_Lite若是v297版本，檔案內容格式較不完整，請使用「R2MS_Lite_v297rawcsv_to_v297csv.exe」轉檔。依賴MATLAB 2014a Runtimes。
    + 建議依照範例程式調整輸出檔名。
    + XP1使用S001，XP2使用S002。
    + 這裡選用XP1的原始CSV檔案為範例「2024_04_15_20_01.csv」，放到Input資料夾中。
    + 編寫BATCH為
    ```
    R2MS_Lite_v297rawcsv_to_v297csv.exe "Input\2024_04_15_20_01.csv" "Output" "S001202404152001"
    PAUSE
    ```
    + 會取得「S001202404152001.v297.csv」檔案。
  + 將「\Part01\1\」資料夾內放好所需檔案:
    + S001202404152001.v297.csv
    + Empty_A.csv
    + Empty_B.csv
    + Empty_C.csv
+ 受限「R2MS_CsvtoUrf_MultipleTx_Chu2019_Release_v20211125a」程式限制必須要有三筆資料再計算Urf_Quality_Info(*.uqi)，此時只有一筆，故要作弊複製成三份一樣的。
+ 製作3份放到 
