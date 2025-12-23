# MSP430_epd2in13_V4

本程式碼是由 [waveshare](https://www.waveshare.net/wiki/2.13inch_e-Paper_HAT_Manual#Arduino
) 所提供的 E-paper 範例代碼進行改寫，並透過 Energia 開發環境進行程式編譯。


程式代碼邏輯基於 [waveshare](https://www.waveshare.net/wiki/2.13inch_e-Paper_HAT_Manual#Arduino
) 所提供原始範例一致，並未修改其內部核心代碼內容，僅針對 MSP430FR2433 所需 I/O 引腳進行調整。

<img width="1380" height="394" alt="image" src="https://github.com/user-attachments/assets/04b68058-f406-4d84-bf7a-c731578a3c8a" />

依據 Arduino 提供的引腳定義的， DIN 腳位對應至 MOSI，CLK 腳位對應至 SCK； 其餘未指定之控制腳位，可依實際需求自由配置。
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

如需修改引腳定義，請於 epdif.h 文件中，自行調整腳位配置，參考下圖。

<img width="721" height="521" alt="image" src="https://github.com/user-attachments/assets/19f09264-9a4a-48dc-8c06-3acee29f13a9" />


# 如何運行程式

請於 GitHub 專案介面下，下載「MSP430_energy_toolbox」程式碼，然後解壓縮進入 Driver 資料夾，選擇 MSP430_epd2in13_V4 專案，並開啟「epd2in13_V4」目錄文件。

- 請於 epd2in13_V4 目錄文件中找到 epd2in13_V4.ino 測試程式，並將該檔案拖移至 Energia 應用程式開啟即可。

<img width="728" height="461" alt="image" src="https://github.com/user-attachments/assets/325c68df-7961-4934-9b11-1758225df6e9" />

　　　

- 在 Energia IDE 中需要注意工具列（Tools）選擇對應的開發板（Board）和連接埠（Port），是否為本次燒入控制器。
下圖為展示 MSP-EXP430FR2433 開發板。

<img width="424" height="268" alt="image" src="https://github.com/user-attachments/assets/3d228c4d-6f23-4527-be57-288896dece93" />

　　　

- 需要特別注意一點，本次專案採用 [waveshare](https://www.waveshare.net/wiki/2.13inch_e-Paper_HAT_Manual#Arduino) 開發程式碼，因此　ROM 需要確保有 15K 及 RAM 1.5~2K 以上存儲空間，才能確保正常運作。
下圖為 MSP430_epd2in13_V4 存儲使用空間。

<img width="676" height="193" alt="image" src="https://github.com/user-attachments/assets/ceb9dc9d-371b-40e2-8084-bea8d00aa3ef" />

　　　

- 最後點選上傳即可。
下圖為 Energia IDE 上傳成功如下。

<img width="675" height="290" alt="image" src="https://github.com/user-attachments/assets/ce25895a-5626-4d9b-9b91-b19db4e1a7e3" />







##  References　（參考資料）
1. https://energia.nu/
2. https://www.waveshare.net/wiki/2.13inch_e-Paper_HAT_Manual#Arduino

