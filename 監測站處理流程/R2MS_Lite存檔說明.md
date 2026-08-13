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
+ 使用MATLAB zip的方法:
```matlab
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
+ 運行結果
```
運行命令: zip('Recorder\XP1\2025\05\01\1402.zip', 'Recorder\XP1\2025\05\01\1402');
運行命令結束!
=== ZIP 檔案內部結構：Recorder\XP1\2025\05\01\1402.zip ===
Recorder/XP1/2025/05/01/1402/Part01/1/S001202505011402.Current Mode.csv
Recorder/XP1/2025/05/01/1402/Part01/1/S001202505011402.Project1.ini
Recorder/XP1/2025/05/01/1402/Part01/1/S001202505011402.setting.txt
Recorder/XP1/2025/05/01/1402/Part01/1/S001202505011402.v299.csv
```

## 歸檔腳本
+ MATLAB歸檔腳本:
```matlab
%**************************************************************************
%   Name: R2MS_Lite_v299_Archive_v20260813a.m
%   Copyright:  
%   Author: HsiupoYeh 
%   Version: v20260813a
%   Description: 針對 R2MS Lite 原始觀測資料進行自動化備份管理。
%       遍歷指定月份內的所有日期與時段資料夾，在執行安全衝突檢查後，
%       將時段資料夾（包含底層 Part01\1\ 結構與 4 個原始檔案）遞迴壓縮為 .zip 檔，
%       確認壓縮檔成功建立後，即安全刪除原始資料夾以釋放硬碟空間。
%
%   腳本擺放位置:
%       請將此腳本放置於專案根目錄（與 Recorder 資料夾同級）：
%       [20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)/
%       ├── R2MS_Lite_v299_Archive_v20260813a.m  <-- 本腳本位置
%       └── Recorder/
%            └── XP1/
%                 └── 2025/05/01/1402/Part01/1/
%
%   資料路徑變化對照:
%       [歸檔前原始路徑]
%       .\Recorder\XP1\2025\05\01\1402\Part01\1\S001202505011402.v299.csv
%       [歸檔後最終路徑]
%       .\Recorder\XP1\2025\05\01\1402.zip
%
%   呼叫方式:
%       切換 MATLAB 當前工作目錄至專案根目錄後直接執行。
%       可在腳本開頭調整 Profile_Name、Survey_Year 與 Survey_Month。
%**************************************************************************
clear; clc; close all
% =========================================================================
% 基礎參數設定（可依需求修改測線、年份與月份）
% =========================================================================
Profile_Name = 'XP1';    % 測線代碼
Survey_Year  = '2025';   % 量測年份 (4 位數)
Survey_Month = '05';     % 量測月份 (2 位數)

    % -------------------------------------------------------------------------
    % 步驟 1: 取得目標月份下的日期資料夾清單
    % -------------------------------------------------------------------------
    % 建立當月資料夾的相對路徑：Recorder\XP1\2025\05
    Target_Month_Folder = fullfile('Recorder', Profile_Name, Survey_Year, Survey_Month);
    disp(['[目標路徑] 月資料夾: ', Target_Month_Folder])

    % 使用 dir 讀取該月份目錄下的所有項目
    temp_dir_result = dir(Target_Month_Folder);

    % 篩選條件：必須為資料夾 (isdir == true) 且名稱不能為 '.' (當前目錄) 或 '..' (上層目錄)
    temp_dir_result = temp_dir_result([temp_dir_result.isdir] & ~ismember({temp_dir_result.name}, {'.', '..'}));

    % 提取篩選後的日期資料夾名稱（例如 "01", "02"）轉為 Cell 陣列
    Survey_Day_List = {temp_dir_result.name}';

    disp(['[掃描結果] 天資料夾總數量 = ', num2str(length(Survey_Day_List))])
    disp('-------------------------------------------------------------------')

    % -------------------------------------------------------------------------
    % 步驟 2: 逐日遍歷並進行衝突檢查與資料歸檔
    % -------------------------------------------------------------------------
    for i_Survey_Day_List = 1:length(Survey_Day_List)
        % 取得單一日期名稱並建立該日期的完整相對路徑
        Survey_Day = Survey_Day_List{i_Survey_Day_List};
        path_Day   = fullfile('Recorder', Profile_Name, Survey_Year, Survey_Month, Survey_Day);
        disp(['[開始處理] 天資料夾: ', path_Day])

        % --- 2.1 歷史紀錄安全審查：尋找當前日期資料夾下已存在的 .zip 檔 ---
        disp(['[歷史審查] 查詢天資料夾下的壓縮檔案清單 (', fullfile(path_Day, '*.zip'), ')'])
        temp_zip_result = dir(fullfile(path_Day, '*.zip'));

        % 若該日期資料夾底下發現既有的 .zip 檔案
        if ~isempty(temp_zip_result)
            zip_names = {temp_zip_result.name}';

            % 針對每個發現的 zip 檔案，檢查是否有對應的同名原始資料夾殘留
            for i_zip = 1:length(zip_names)
                % 剖析檔名，取得不含副檔名的時段名稱 (例如 "1402.zip" -> "1402")
                [~, name_only, ~] = fileparts(zip_names{i_zip}); 

                % 組成預期可能的衝突資料夾路徑
                conflict_folder_path = fullfile(path_Day, name_only);
                disp(['[歷史紀錄] 發現既有 zip 檔案: ', conflict_folder_path, '.zip'])

                % --- 2.2 衝突檢查：若 zip 檔與原始同名資料夾同時存在，觸發中斷機制 ---
                if exist(conflict_folder_path, 'dir')
                    % 發現異常狀態：壓縮檔已存在，但原始資料夾卻未被清理。
                    % 為避免二次覆蓋或資料寫入不完整，立即彈出錯誤並中斷執行。
                    error(['[結構錯誤] 發現衝突：\n路徑：%s\n', ...
                           '原因：已存在壓縮檔 "%s"，但資料夾 "%s" 尚未刪除。\n', ...
                           '為確保數據安全，程式已終止。'], ...
                           path_Day, zip_names{i_zip}, name_only);
                end
            end
        end

        % --- 2.3 獲取時段資料夾清單 (必須完全通過上述安全審查後才執行) ---
        temp_dir_result = dir(path_Day);

        % 篩選出未壓縮的時段資料夾（例如 "1402"，排除 '.' 與 '..'）
        temp_dir_result = temp_dir_result([temp_dir_result.isdir] & ~ismember({temp_dir_result.name}, {'.', '..'}));
        Survey_HourMinute_List = {temp_dir_result.name}';

        % --- 2.4 執行遞迴壓縮與安全刪除 ---
        for i_Survey_HourMinute_List = 1:length(Survey_HourMinute_List)
            Survey_HourMinute = Survey_HourMinute_List{i_Survey_HourMinute_List};

            % 定義來源資料夾路徑與目標 zip 檔案路徑
            target_folder = fullfile(path_Day, Survey_HourMinute); % 例如: Recorder/.../01/1402
            zip_filename  = [target_folder, '.zip'];               % 例如: Recorder/.../01/1402.zip

            fprintf('  └─ 正在壓縮時段資料夾: %s ... ', Survey_HourMinute);

            % 執行壓縮指令
            % MATLAB 的 zip 函式會自動遞迴打包 target_folder 底下的所有子目錄 (Part01\1\) 與檔案
            zip(zip_filename, target_folder);

            % 防禦性確認：必須嚴格落實「看到 zip 實體檔案已成功寫入硬碟」，才允許刪除原始資料夾
            if exist(zip_filename, 'file')
                % rmdir 的 's' 參數會將該時段及其下所有子目錄 (Part01\1\) 強制且完整地刪除
                rmdir(target_folder, 's'); 
                fprintf('完成歸檔，並已安全刪除原始資料夾。\n');
            else
                warning('時段 %s 的 zip 檔案建立失敗，取消刪除動作以保護原始資料。', Survey_HourMinute);
            end
        end
        disp('-------------------------------------------------------------------')
    end
    % -------------------------------------------------------------------------
```
