# MSP430_BeanCounter

[![MIT License][mit-shield]][mit]

[mit]: https://opensource.org/licenses/MIT
[mit-shield]: https://img.shields.io/badge/License-MIT-yellow.svg

MSP430_BeanCounter 是一款小型 SMT 元件計數器。
支援 電池供電 與 USB 供電 兩種模式，可依使用場景彈性切換。USB 供電採用線性穩壓器 (LDO) ，確保外部電壓輸入至系統供電能夠穩定並降低雜訊干擾。

裝置內置 紅外線光遮斷器 (Photo Interrupter） ，用來精準偵測計數元件通過數量；同時提供實體按鈕操作介面，可依據不同的 Tape pitch 進行模式選擇，以對應不同元件間距需求。

此外，系統也整合溫濕度感測器，提供即時量測環境溫度與保存濕度。以上所有資訊，皆透過可視化顯示器即時呈現，提升使用便利性與現場可讀性。

##  Summary　（概要）
MSP430_BeanCounter 是由德州儀器（Texas Instruments）開發的 MSP430FR2433 為核心的 SMT 元件計數器，採用 RISC 架構的 16 位元微控制器，並且結合多種傳感器，以實現 SMT 元件的精準計數與周遭環境溫濕度監測功能。


該設備具有一顆 16 位元 MCU ，提供更快的處理速度，使系統整體反應更加即時，並能輕鬆應付高複雜度的功能需求。硬體內部配置 2 顆紅外線光遮斷器 (Photo Interrupter） ，用來精準辨別元件通過正確性，並透過 2-bit 編碼判斷機制，確認元件的行進方向。同時，設備還有提供實體按鈕操作介面，以便使用者依據不同的 Tape pitch 快速選擇對應的元件間距需求。

此外，設備中還嵌入一顆 SHT40 高精度低功耗溫濕度感測器，提供環境溫度與濕度資訊。上述所有量測與計數資訊，皆透過可視化顯示介面即時呈現，有效提升現場操作時的可讀性。

##  Installation　（安裝）
安裝 Energia IDE 軟體
- Energia IDE 軟體下載：https://energia.nu/

<img width="400" height="400" alt="image" src="https://github.com/user-attachments/assets/86b17ced-ae22-4933-86ae-5aa04901e767" />

##  Import data　（導入資料）
1. 下載 GitHub 資料 code 專案：
   - 你可以從目前瀏覽 GitHub 專案下載所需的專案，分別為 [2IRPT_OLED_VREF](https://github.com/BoomerChiao/MSP430_energy_toolbox/blob/main/Application/MSP430_BeanCounter/2IRPT_OLED_VREF/2IRPT_OLED_VREF.rar)、[2IRPT_OLEDm_SHT_VREF](https://github.com/BoomerChiao/MSP430_energy_toolbox/blob/main/Application/MSP430_BeanCounter/2IRPT_OLEDm_SHT_VREF/2IRPT_OLEDm_SHT_VREF.rar)，兩個版本，可依需求選擇其中之一。

     下載檔案：https://github.com/BoomerChiao/MSP430_energy_toolbox/tree/main/Application/MSP430_BeanCounter
     
     2IRPT_OLED_VREF　RAR當案：https://github.com/BoomerChiao/MSP430_energy_toolbox/blob/main/Application/MSP430_BeanCounter/2IRPT_OLED_VREF/2IRPT_OLED_VREF.rar
     
     2IRPT_OLEDm_SHT_VREF　RAR當案：https://github.com/BoomerChiao/MSP430_energy_toolbox/blob/main/Application/MSP430_BeanCounter/2IRPT_OLEDm_SHT_VREF/2IRPT_OLEDm_SHT_VREF.rar
     
    
2. 開啟 MSP430 程式：
   - 請至 GitHub 專案介面下，下載所需程式檔案，並將主程式檔案拖移至 Energia 應用程式中開啟即可。
   - (下圖以 2IRPT_OLEDm_SHT_VREF 為示例)

   <img width="947" height="514" alt="image" src="https://github.com/user-attachments/assets/036220f5-19ba-4166-b90a-9fcb79967f45" />

         

##  Prepare Electronic Materials　（準備電子材料）
### DEMO
1. MSP-EXP430FR2433
2. 0.96' OLED Display 128×64 4Pin IIC I2C
3. SHT40 (3.3V)
4. ROHM RPI-246
5. 330Ω *2
6. 10KΩ *2
7. Breadboard
8. Jumper Wires

<img width="1058" height="720" alt="image" src="https://github.com/user-attachments/assets/174e0eca-1dd0-4bd0-9759-4f87f0a501a5" />

##  Pin wiring　（引腳接線）
以下提供基礎引腳接線方式，請依據你的成品需求進行接線。
| MSP-EXP430FR2433 | OLED | SHT40 | RPI-246_A | RPI-246_B |
|-----| ----- | ----- | ----- | ----- |
| VCC | 3.3V | 3.3V |  |  |
| GND | GND | GND | 1、4 | 1、4 |
| P1.2 | SCL | SCK |  |  |
| P1.3 | SDA | SDA |  |  |
| P2.2 |  |  | 3 |  |
| P3.2 |  |  |  | 3 |

<img width="857" height="714" alt="image" src="https://github.com/user-attachments/assets/7b51b0dd-f1d1-47a8-be06-2a63a787354f" />

##  Software Demo　（成品展示）
### OLED畫面
<img width="1550" height="1595" alt="image" src="https://github.com/user-attachments/assets/c3b230e3-5cbe-4178-ae95-e3fe8aa8256b" />

- 上圖為 [2IRPT_OLED_VREF](https://github.com/BoomerChiao/MSP430_energy_toolbox/blob/main/Application/MSP430_BeanCounter/2IRPT_OLED_VREF/2IRPT_OLED_VREF.rar) 主畫面，提供數量、料帶間隔、電池耗電量、光遮斷器AB、及畫面延遲相關資訊。
   -  上圖 0000 為，實際經過值 / TAPE ，計算結果數量。
   -  TAPE 為，料帶間隔。
   -  BAT 為，電池電量 V 。 (需客製化板子，功能才有)
   -  上圖左下角顯示的 00 為，光遮斷器 A、B 的感測結果，其中 0 代表為遮蔽；1 表示未遮蔽。
   -  上圖最下面 0 為，實際經過光遮斷器 A、B ，計算的結果數量。
   -  上圖右下角顯示的 5 ms 為，畫面延遲值。

  　

<img width="1529" height="1515" alt="image" src="https://github.com/user-attachments/assets/878805b1-bd4e-4718-843c-d7752dccfef1" />

- 上圖為 [2IRPT_OLEDm_SHT_VREF](https://github.com/BoomerChiao/MSP430_energy_toolbox/blob/main/Application/MSP430_BeanCounter/2IRPT_OLEDm_SHT_VREF/2IRPT_OLEDm_SHT_VREF.rar) 主畫面，提供數量、料帶間隔、電池耗電量、光遮斷器AB、及畫面延遲相關資訊。
   -  上圖 0000 為，實際經過值 / TAPE ，計算結果數量。
   -  TAPE 為，料帶間隔。
   -  上圖 H 、 T ，為濕度百分比以及攝氏溫度。
   -  上圖左下角顯示的 00 為，光遮斷器 A、B 的感測結果，其中 0 代表為遮蔽；1 表示未遮蔽。
   -  上圖最下面 0 為，實際經過光遮斷器 A、B ，計算的結果數量。
   -  上圖右下角顯示的 5 ms 為，畫面延遲值。

### OLED顯示功能與視覺效果

<img width="320" height="240" alt="image" src="https://github.com/BoomerChiao/MSP430_energy_toolbox/blob/main/png/MSP430xSHT40xOLED_D3.gif" />
- 上圖畫面為正常開機運轉情況下，持續約莫10秒熄滅。

  　

<img width="320" height="240" alt="image" src="https://github.com/BoomerChiao/MSP430_energy_toolbox/blob/main/png/MSP430xSHT40xOLED_D2.gif" />
- 上圖畫面為　料帶經過光遮斷器　運轉情況下。

  　

## EXTREME　（進階設計）
1. MSP430FR2433
2. 0.96' OLED Display 128×64 4Pin IIC I2C
3. SHT40
4. ROHM RPI-246
5.

##  References　（參考資料）
1. https://energia.nu/
2. https://www.waveshare.net/wiki/2.13inch_e-Paper_HAT_Manual#Arduino

