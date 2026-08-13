# R2MS Lite 原始資料存放結構說明 (v2.9.9無壓縮版)

## 基礎目錄結構總覽
+ 一個完整的原始資料路徑範例如下：  
  + 「[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\Recorder\XP1\2026\08\03\1402\Part01\1\」。

### 1. 專案/測點根目錄 
+ 格式：[建置日期+批號]國家-城市-觀測地點名稱(地點簡稱)
+ 範例：「[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)」
+ 說明：定義該觀測站點的地理資訊與設立時間。其中「批號」以大寫英文字母表示，A 為當日第一次調查，B 為當日第二次調查，依此類推。

### 2. 固定系統目錄 
+ 固定名稱：「Recorder」
+ 說明：儀器記錄器的固定專用資料夾。

### 3. 測線代碼 
+ 範例：「XP1」
+ 說明：定義該觀測站點的測線代碼。

### 4. 時間戳記分層 
+ 資料依據量測時間進行嚴格的時間序列分層：
  + 年 (Year)：4 位數（例如「2026」）。
  + 月 (Month)：2 位數（例如「08」）。
  + 日 (Day)：2 位數（例如「03」）。
  + 時分 (Hour & Minute)：4 位數，代表該觀測時段的啟動時間（例如「1402」表示 14 點 02 分）。

### 5. 固定批次層 (Part)
+ 固定批次層名稱：「Part01」
+ 說明：預留用於同一個測線分段或交錯測量，但目前規定不會分段或交錯量測。

### 6. 固定索引層 (Index)
+ 固定批次層名稱：「1」
+ 說明：預留用於區分同一個時段內的多段連續量測，但目前規定只會有一次量測。

---

## 底層檔案命名與格式規範

### 檔名解析範例
+ 範例：「S001202608031402.v299.csv」。
  + S001：儀器編號。
  + 202608031402：對應的量測時間（2026年08月03日 14時02分）。
  + .v299.csv：檔案型態後綴與副檔名。

### 檔案列表

| 完整檔案後綴 | 檔案格式 | 說明 |
| :--- | :---: | :--- |
| S001202608031402.Current Mode.csv | CSV 檔案 | 放電參數。 |
| S001202608031402.Project1.ini | INI 設定檔 | 排程設定檔案。 |
| S001202608031402.setting.txt | TXT 文字檔 | 量測參數檔案。 |
| S001202608031402.v299.csv | CSV 檔案 | 原始資料檔案。 |

---

## 歸檔後檔案格式
+ 一個完整的歸檔後檔案格式範例如下：  
  + 「[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\Recorder\XP1\2026\08\03\1402.zip」。
+ 使用MATLAB zip的方法
```
%------------------------------------------
% 運行腳本的位置
% .\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\Recorder\XP1\2026\08\03\1402.zip
% .\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\Run_Script.m
% zip(zip_filename, target_folder) 會遞迴封裝 target_folder 底下的所有內容並儲存到指定位置
zip('Recorder\XP1\2025\05\01\1402.zip', 'Recorder\XP1\2025\05\01\1402');
%------------------------------------------
%------------------------------------------
% 檢視ZIP內部結構
%--
% zip檔案名稱
zip_filename = 'Recorder\XP1\2025\05\01\1402.zip';
% 透過 Java API 開啟壓縮檔
zipFile = java.util.zip.ZipFile(zip_filename);
% 透過 Java API 取得列舉物件
entries = zipFile.entries();
fprintf('=== ZIP 檔案內部結構：%s ===\n', zip_filename);
% 走訪並印出所有項目相對路徑
while entries.hasMoreElements()
    fprintf('%s\n', char(entries.nextElement().getName()));
end
% 確保關閉檔案串流以釋放硬碟資源
zipFile.close();
%------------------------------------------
```
