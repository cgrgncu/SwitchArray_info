# SwitchArray序號設計
+ 作者: HsiupoYeh
+ 更新日期: 2024-10-26

### 序號名稱:
+ 完整序號為四碼年份+「-S」+三碼數字，共9個字元；簡易序號為「S」+三碼數字，共4個字元。
  + 例如:「2024-S003」，簡易序號為｢S003」。
  + 我相信這輩子做不出900台以上，三碼數字很夠用了。
  + 年份只是提醒，用來追蹤生產材料來源。
  + 分析軟體只認簡易序號。

### 困難
+ 原作者不願意在韌體中設計序號，所對應的軟體使用LabView編寫，溝通模式不完善，很難修改。
+ SwitchArray機構上只有一個「USB-A」介面，利用USB介面與ESP32溝通。
  + 我不喜歡這個設計，供電來自PC，可以直接燒錄，會看到韌體啟動資訊等狀況都容易造成不可預期的錯誤。

### 解決方案(v20241026a)
+ 版本: v20241026a
+ 更新日期: 2024-10-26
+ 硬體修改: 新增一個USB-HUB在SwitchArray中。
  + 若體積允許，將USB-HUB固定在SwitchArray內部。
  + USB-HUB接到SwitchArray上的USB防水連接器(母對母)上。
  + ESP32接到USB-HUB第1個Port。
  + 每台SwitchArray準備一個USB隨身碟接到USB-HUB第2個Port。
+ USB隨身碟製作規範:
  + 採用32GB隨身碟，格式化為exFAT，能夠放置大於4GB的檔案。支援熱插拔，比較不會壞。
    + 用exFAT，配置單位大小32[KB]。
    + exFAT與FAT32的檔案系統格式都只允許磁碟區標籤上限為11個字元。
    + 參考SwitchArray簡易序號來命名磁碟區標籤為:「R2MS_」+簡易序號，共9個字元。
      + 例如「R2MS_S003」。
    + 目前規劃不由軟體去檢測隨身碟檔案系統格式，也不會檢查容量，故只要能讀寫檔案就沒問題。
    + 選擇32[GB]是考量現在隨身碟價格，目前低於32[GB]的隨身碟並不會比較便宜，大量採購下32[GB]常常有更好的性價比。
    + 此隨身碟根目錄下的指定檔案名稱必須被保留，供分析軟體使用，檔案容量小於10[MB]。其餘容量規劃存存放軟體、技術文件、野外備忘錄。也可供使用者暫時儲存檔案使用。
     + 「R2MS_Lite_SwitchArray_Info.txt」，用途請參閱後文。
     + 「R2MS_Lite_SwitchArray_SerialPort.json」，用途請參閱後文。
### R2MS_Lite_SwitchArray_SerialPort.json
+ SerialPort在Windows上會被註記為COM裝置，命名通常為「COM」+數字，總字元數不是固定值會變化，例如「COM3｣、「COM16」。
  + 目前會被識別為COM裝置的包含SwitchArray用的CH340、PSU用的CP2106。
+ 在特殊情況下，當主機連接的ESP32設備數量大於1時，以目前架構可找出CH340對應的COM裝置，但無法分辨哪個CH340才是要用的。
  + 此時，若「R2MS_Lite_SwitchArray_SerialPort.json」檔案存在，則內容須描述SwitchArray的簡易序號、偵測的COM裝置為何。
  + 範例:
    + 建立「R2MS_Lite_SwitchArray_SerialPort.json」檔案，內容全部限制使用英文，以避免編碼問題(ANSI/UTF-8在軟體讀取時中文可能亂碼)。
    + 檔案內容限制為最小壓縮情況的J單層SON檔案。
      + 磁碟區標籤為「R2MS_S003」，則「SwitchArray_SN」為「S003」。
      + 從檔案管理員找到識別的COM裝置為「COM3」，則「SwitchArray_SerialPort」為「COM3」。
      + 內容如下:
      ```json
      {"SwitchArray_SN":"S003","SwitchArray_SerialPort":"COM3"}
      ```
    + 軟體工作(使用者指定序號)，例如:指定序號「S003」，進行下列驗證:
      + 1.是否存在符合的磁碟機標籤。例如:「R2MS_S003」。若是，則進行2.；若否，則驗證失敗。
      + 2.查詢該磁碟機標籤的磁碟機代號，例如「D」。這表示掛接為「D槽」，路徑為「D:\」。若查找成功，則進行3.；若查找失敗，則驗證失敗。
      + 3.讀取「R2MS_Lite_SwitchArray_SerialPort.json」。例如:「D:\R2MS_Lite_SwitchArray_SerialPort.json」。若讀取內容可解析則進行4.；若解析失敗則驗證失敗。
      + 4.檢查Json內容中「SwitchArray_SN」的值。例如:「{"SwitchArray_SN":"S003","SwitchArray_SerialPort":"COM3"}」要與「S003」一致。若是，則進行5.；若否，則驗證失敗。
      + 5.檢查Json內容中「SwitchArray_SerialPort」的值。例如:「{"SwitchArray_SN":"S003","SwitchArray_SerialPort":"COM3"}」要去檢查「COM3」裝置是否為「USB-SERIAL CH340」。若是，則驗證成功；若否，則驗證失敗。

