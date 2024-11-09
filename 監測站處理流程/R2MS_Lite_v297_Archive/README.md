# R2MS_Lite_v297_Archive_v20241109a
+ 參數寫在INI中，限制使用ANSI編碼的INI。純英文內文各種編碼都不會發生錯誤。


+ 原來檔案結構:
```
...\DATA\2024_07_01_20_01.csv
...\DATA\2024_07_02_20_01.csv
...\DATA\2024_07_03_20_01.csv
```

+ 整理成:
```
...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)
...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\Recorder
...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\Recorder\XP1
...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\Recorder\XP1\2024
...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\Recorder\XP1\2024\07
...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\Recorder\XP1\2024\07\01
...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\Recorder\XP1\2024\07\01\2001.json
...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\Recorder\XP1\2024\07\01\2001.zip
...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\Recorder\XP1\2024\07\02
...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\Recorder\XP1\2024\07\02\2001.json
...\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\Recorder\XP1\2024\07\02\2001.zip
```

+ json裡面會寫:
```
{"Software":"R2MS_Lite_v297_Archive","Version":"v20241109a","FileName":"2001.zip","FileBytes":"3964250","FileMD5":"974ec20d02b7681dc2c9f63025205373","FileUpload":"Ready","v297csvFileName":"S001202407012001.v297.csv","v297csvBytes":"17767437"}
```

+ 利用JSON檢查檔案狀態，目前節省時間只檢查檔案名稱一致。其他欄位供其他程式使用。