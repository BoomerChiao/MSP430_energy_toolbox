# MSP430_BeanCounter

MSP430_BeanCounter 是一款小型 SMT 元件計數器。
支援 電池供電 與 USB 供電 兩種模式，可依使用場景彈性切換。USB 供電採用線性穩壓器 (LDO) ，確保外部電壓輸入至系統供電能夠穩定並降低雜訊干擾。

裝置內置 紅外線光遮斷器 (Photo Interrupter） ，用來精準偵測計數元件通過數量；同時提供按鈕操作介面，可依據不同的 Tape pitch 進行模式選擇，以對應不同元件間距需求。

此外，系統也整合溫濕度感測器，提供即時量測環境溫度與保存濕度。以上所有資訊，皆透過可視化顯示器即時呈現，提升使用便利性與現場可讀性。







##  References　（參考資料）
1. https://energia.nu/
2. https://www.waveshare.net/wiki/2.13inch_e-Paper_HAT_Manual#Arduino

