#ifndef SHT40_MIN_H
#define SHT40_MIN_H

#include <Wire.h>

#define SHT40_ADDR 0x44

// 讀取 SHT40，並把溫度/濕度轉成 0.1 精度整數
bool readSHT40(int16_t &t10, int16_t &h10) {
  Wire.beginTransmission(SHT40_ADDR);
  Wire.write(0xFD); // 高精度單次測量
  if(Wire.endTransmission() != 0) return false;

  delay(15); // 等待測量完成

  Wire.requestFrom(SHT40_ADDR, 6);
  if(Wire.available() != 6) return false;

  uint8_t d[6];
  for(int i = 0; i < 6; i++) d[i] = Wire.read();

  uint16_t rawT = (d[0] << 8) | d[1];
  uint16_t rawH = (d[3] << 8) | d[4];

  // 轉成 0.1°C / 0.1%RH 整數
  t10 = (int16_t)((((int32_t)rawT * 1750) / 65535) - 450);
  h10 = (int16_t)((((int32_t)rawH * 1000) / 65535));

  return true;
}

#endif
