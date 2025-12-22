# MSP430_epd2in13_V4

本程式碼是由 [waveshare](https://www.waveshare.net/wiki/2.13inch_e-Paper_HAT_Manual#Arduino
) 所提供的 E-paper 範例程式代碼進行改寫的程式碼，並透過 Energia 開發環境進行程式編譯。


程式代碼邏輯基本於 [waveshare](https://www.waveshare.net/wiki/2.13inch_e-Paper_HAT_Manual#Arduino
) 提供原始範例一致，並未修改其內部核心代碼驅動內容，僅針對 MSP430FR2433 所需 I/O 引腳進行調整。

<img width="1380" height="394" alt="image" src="https://github.com/user-attachments/assets/04b68058-f406-4d84-bf7a-c731578a3c8a" />

以下為本專案所調整腳位配置說明。

| Series | MSP430FR2433 |  |  | 
|-----| ----- | ----- | ----- |
| VCC | 3.3V |  |  |
| GND | GND |  |  |
| DIN | 15 (P2_6) |  |  |
| CLK | 7 (P2_4) |  |  |
| CS | 6 (P1_7) |  |  |
| DC | 8 (P2_7) |  |  |
| RST | 2 (P1_0) |  |  |
| BUSY | 5 (P1_6) |  |  |











##  References　（參考資料）
1. https://energia.nu/
2. https://www.waveshare.net/wiki/2.13inch_e-Paper_HAT_Manual#Arduino

