# SwitchArray-2026-S003 維修檢測完成紀錄
+ 室內維修完成日期: 2026-04-30
+ 室外檢測完成日期: 2026-05-04
+ 維修內容:
  + RelayBoard的固態繼電器(AB30S-C)檢測出損壞後更換新品。
  + 重新整理連接線壓接頭，使用歐規端子(CE0.75-10)搭配R型端子(型號R1.25-4)。
  + 更換博士端子頭，並使用螺絲固定劑。

### 時間序列檢視
| 室內浮接測試時間序列 |
| :---: |
| ![室內浮接測試時間序列](https://github.com/cgrgncu/SwitchArray_info/raw/main/production/SwitchArray/SwitchArray-2026-S003/20260504/S003202604301608_Floating.png) |

| 室內標準地層測試時間序列 |
| :---: |
| ![室內標準地層測試時間序列](https://github.com/cgrgncu/SwitchArray_info/raw/main/production/SwitchArray/SwitchArray-2026-S003/20260504/S003202604301616_StandardResistor.png) |

| 野外測試時間序列 |
| :---: |
| ![野外測試時間序列](https://github.com/cgrgncu/SwitchArray_info/raw/main/production/SwitchArray/SwitchArray-2026-S003/20260504/S003202605041307_FieldTest.png) |

| NCU草坪時間序列 |
| :---: |
| ![NCU草坪時間序列](https://github.com/cgrgncu/SwitchArray_info/raw/main/production/SwitchArray/SwitchArray-2026-S003/20260504/S003202605041313_NCUQC.png) |

### 順推分析
+ 用預設值順推，時間序列解算手動選用實際資料「S003202605041313.v299S.csv」。

### 逆推分析(S003202605041313.v299S.WS.ohm)
+ 測線名稱改為「S003202605041313.v299S.WS」
+ 資料剔除數量改為「1」
+ 色階範圍改為「[50,2000]」
+ 其他維持預設值。  
  | S003202605041313.v299S.WS 逆推結果 |
  | :---: |
  | ![逆推結果](https://github.com/cgrgncu/SwitchArray_info/raw/main/production/SwitchArray/SwitchArray-2026-S003/20260504/S003202605041313.v299S.WS_R01_L01_I05_INV3.png) |

### 逆推分析(S003202605041313.v299S.MPR.ohm)
+ 測線名稱改為「S003202605041313.v299S.MPR」
+ 資料剔除數量改為「1」
+ 色階範圍改為「[50,2000]」
+ 其他維持預設值。  
  | S003202605041313.v299S.MPR 逆推結果 |
  | :---: |
  | ![逆推結果](https://github.com/cgrgncu/SwitchArray_info/raw/main/production/SwitchArray/SwitchArray-2026-S003/20260504/S003202605041313.v299S.MPR_R01_L01_I05_INV3.png) |
   
### 逆推分析(S003202605041313.v299S.MGD.ohm)
+ 測線名稱改為「S003202605041313.v299S.MGD」
+ 資料剔除數量改為「1」
+ 色階範圍改為「[50,2000]」
+ 其他維持預設值。  
  | S003202605041313.v299S.MGD 逆推結果 |
  | :---: |
  | ![逆推結果](https://github.com/cgrgncu/SwitchArray_info/raw/main/production/SwitchArray/SwitchArray-2026-S003/20260504/S003202605041313.v299S.MGD_R01_L01_I06_INV3.png) |


### 逆推分析(S003202605041313.v299S.GD.ohm)
+ 測線名稱改為「S003202605041313.v299S.GD」
+ 資料剔除數量改為「1」
+ 色階範圍改為「[50,2000]」
+ 其他維持預設值。  
  | S003202605041313.v299S.GD 逆推結果 |
  | :---: |
  | ![逆推結果](https://github.com/cgrgncu/SwitchArray_info/raw/main/production/SwitchArray/SwitchArray-2026-S003/20260504/) |
