#include <Wire.h>
#include "Font.h"
#include <string.h>
#include "images.h"
#include "SHT40_min.h"
#include "OLED_min.h"

const int VOLT_PIN = A6;     // P1.6 = ADC channel 2
const int NMOS = 2; // Energia pin 2 = P1.0   N-MOS 
const int VCCNMOS = 19; // Energia pin 19 = P1.1   N-MOS
const int SENSOR_A = 18;   // 假設接到 P2.2 → Energia pin 18
const int SENSOR_B = 17;   // 假設接到 P3.2 → Energia pin 17
const int BUTTON_A = 8;   // 假設接到 P2.7 → Energia pin 8
const int BUTTON_B = 21;   // 假設接到 P2.3 → Energia pin 21

//int AIR,loop;
unsigned long loopStartTime;
unsigned long loopEndTime;
unsigned long loopDuration;
unsigned long lastActiveTime = 1000; // 紀錄最後活動時間
volatile int  counter= 0; //原始計算數值
int counter_2 =0; //對應原始計算數值除上TAPE
const int sleepTimeout = 10000; //10 秒沒動就休眠
const int idleDelay = 500; // 靜止多少毫秒才刷新
int lastCounter,lastState = 0;

const int settingValues[] = {2,4,8,12,16,20,24,28,32,36,40,44,48,52,56};
const int settingCount = sizeof(settingValues) / sizeof(settingValues[0]);
int settingIndex = 0; //按鈕計算次數
int value_AB = 2; //儲存對應按鈕數值settingValues
const float R1 = 200000;  // 分壓電阻值（單位：歐姆）
const float R2 = 100000;  // 分壓電阻值（單位：歐姆）
/*const float R1 = 30000;  // 分壓電阻值（單位：歐姆）
const float R2 = 7500;  // 分壓電阻值（單位：歐姆）*/

const float VREF = 3.3;  // ADC 參考電壓（預設使用 VCC = 3.3V）

int v_inDA,v_inDB,v_inDC;

void setup() {
  pinMode(NMOS, OUTPUT); //NMOS 開關
  pinMode(VCCNMOS, INPUT_PULLUP); //VCC_NMOS 開關
  pinMode(SENSOR_A, INPUT_PULLUP);
  pinMode(SENSOR_B, INPUT_PULLUP);
  pinMode(BUTTON_A, INPUT_PULLUP); // 按鈕接地
  pinMode(BUTTON_B, INPUT_PULLUP); // 按鈕接地


  digitalWrite(NMOS, HIGH); //NMOS 開
  Wire.begin(); /* Initiate wire library and join I2C bus as a master */
  //Wire.setClock(400000); // 設定 I2C 速度為 400kHz
  OLED_init(); /* Initialize OLED */  
  OLED_clear(); /* Clear OLED */
  delay(100);
  OLED_image(Launchpad_Logo);
  delay(2000);
  OLED_clear();
  delay(100);

  OLED_clear();
  OLED_DrawCounter(counter, 20, 1);
  OLED_setXY(0x00, 0x7F, 0x05, 0x02);
  OLED_Data("TAPE: 2");
  OLED_setXY(0x74, 0x7F, 0x07, 0x02);
  OLED_Data("ms");

}



void loop() {
  int16_t t10, h10; //SHT40 _T and _H
  counter_2 = counter/value_AB;
  loopStartTime = millis();

  int A = digitalRead(SENSOR_A);
  int B = digitalRead(SENSOR_B);
  int BUTT_A = digitalRead(BUTTON_A);
  int BUTT_B = digitalRead(BUTTON_B);

  
  int state = (A << 1) | B; // 編碼成 2-bit (00,01,10,11)
  // 判斷是否發生變化
  if (state != lastState && millis() - lastActiveTime < sleepTimeout) {
    
    if ((lastState == 0b00 && state == 0b01) ||
        (lastState == 0b01 && state == 0b11) ||
        (lastState == 0b11 && state == 0b10) ||
        (lastState == 0b10 && state == 0b00)) {
      counter--;  // 正向
    }
    else if ((lastState == 0b00 && state == 0b10) ||
             (lastState == 0b10 && state == 0b11) ||
             (lastState == 0b11 && state == 0b01) ||
             (lastState == 0b01 && state == 0b00)) {
      counter++;  // 反向
    }    
    
    OLED_Command(0xAF); // 每次有動作都強制亮屏
    
    lastState = state;  // 更新狀態
    lastActiveTime = millis(); //有動作就更新 lastActiveTime
  }



  if (millis() - lastActiveTime  < sleepTimeout) {
  if (BUTT_A == LOW){
    counter = 0;
    settingIndex++;
    if (settingIndex >= settingCount) settingIndex = 0; // 循環
    value_AB = settingValues[settingIndex];
    char BUTT_TEXT[10];
    sprintf(BUTT_TEXT,"TAPE: %d", value_AB);  // 把秒數轉成字串
    OLED_setXY(0x00, 0x7F, 0x05, 0x02);
    OLED_Data("TAPE:   ");
    OLED_setXY(0x00, 0x7F, 0x05, 0x02);
    OLED_Data(BUTT_TEXT);
    //OLED_Command(0xAF); // 每次有動作都強制亮屏

    /*lastActiveTime = millis(); //有動作就更新 lastActiveTime
    digitalWrite(NMOS, HIGH);
    delay(400);*/
  }

  if (BUTT_B == LOW){
    counter = 0;
    settingIndex--;
    if (settingIndex < 0) settingIndex = settingCount - 1; // 循環到最後
    value_AB = settingValues[settingIndex];
    char BUTT_TEXT[10];
    sprintf(BUTT_TEXT,"TAPE: %d", value_AB);  // 把秒數轉成字串
    OLED_setXY(0x00, 0x7F, 0x05, 0x02);
    OLED_Data("TAPE:   ");
    OLED_setXY(0x00, 0x7F, 0x05, 0x02);
    OLED_Data(BUTT_TEXT);
    //OLED_Command(0xAF); // 每次有動作都強制亮屏
    
  }}
  if (BUTT_B == LOW || BUTT_A == LOW){
    OLED_Command(0xAF); // 每次有動作都強制亮屏
    lastActiveTime = millis(); //有動作就更新 lastActiveTime
    digitalWrite(NMOS, HIGH);
    delay(300);
    }

  
  // 如果 counter 靜止超過 idleDelay，就刷新 OLED
  if ( millis() - lastActiveTime > idleDelay) { 
    if (counter != lastCounter) {
      OLED_DrawCounter(counter_2, 20, 1);  // 從 col=20, page=1 畫四位數0000
      lastCounter = counter;
      OLED_setXY(0x30, 0x7F, 0x07, 0x02);
      OLED_Data("      "); // 清空該區域
      }}
      
      
  OLED_setXY(0x00, 0x7F, 0x07, 0x02);
  char AIRO[10],counterr[10];
  sprintf(AIRO,"%d%d", A,B);  // 把秒數轉成字串
  OLED_Data(AIRO);
  OLED_setXY(0x30, 0x7F, 0x07, 0x02);
  sprintf(counterr,"%d", counter);  // 把秒數轉成字串
  OLED_Data(counterr);
  

  //閒置超越2000ms，開啟BAT感測
  if (millis() - lastActiveTime  > 2000) {
    int SHTT_inD,SHTT_in2F,SHTH_inD,SHTH_in2F ;
    int v_in = ((analogRead(VOLT_PIN) * VREF) / 1023.0) * ((R1 + R2) / R2)*10;
    int v_inD = v_in/10 ;
    int v_in2F = ((v_in - v_inD*10));
    
    if (v_in > 55 || v_in < 16 ){
      v_inD =0;
      v_in2F=0;
    }  
    
    if(readSHT40(t10, h10)){
      SHTT_inD = t10/10; 
      SHTT_in2F = t10%10;
      SHTH_inD = h10/10; 
      SHTH_in2F = h10%10;
    }else{
      SHTT_inD =0; 
      SHTT_in2F =0;
      SHTH_inD = h10/10; 
      SHTH_in2F = h10%10;
    }

    OLED_setXY(0x30, 0x7F, 0x05, 0x02);
    char VREFF[10];
    sprintf(VREFF,"H:%d.%d", SHTH_inD,SHTH_in2F);  // 把秒數轉成字串
    //sprintf(VREFF,"H:%d.%d  T:%d.%d", SHTH_inD,SHTH_in2F, SHTT_inD,SHTT_in2F);  // 把秒數轉成字串
    OLED_Data(VREFF);
    
    OLED_setXY(0x61, 0x7F, 0x05, 0x02);
    sprintf(VREFF,"T:%d.%d", SHTT_inD,SHTT_in2F);  // 把秒數轉成字串
    OLED_Data(VREFF);
    
    
    if (v_inD >= 1){
      OLED_setXY(0x58, 0x7F, 0x04, 0x02);
      sprintf(VREFF,"BATT:%d.%d", v_inD,v_in2F);// 把秒數轉成字串
      OLED_Data(VREFF);
    }   
  }

  //閒置超越sleepTimeout，進入OLED休眠狀態
  if (millis() - lastActiveTime  > sleepTimeout) {
    OLED_Command(0xAE); // Display OFF
    digitalWrite(NMOS, LOW); //NMOS 關
    OLED_setXY(0x58, 0x7F, 0x04, 0x02);
    OLED_Data("        ");
    sleep(200);
  }
  
  
  char buf[10]; //計算MS/s
  sprintf(buf,"%d ", loopDuration);  // 把秒數轉成字串
  if(loopDuration>99){  //破百刷新清空MS/s
    OLED_setXY(0x60, 0x7F, 0x07, 0x02);
    OLED_Data("    ");
  }
  OLED_setXY(0x60, 0x7F, 0x07, 0x02);
  OLED_Data(buf);
  
  loopEndTime = millis();
  // 計算差值
  loopDuration = loopEndTime - loopStartTime;
  // 顯示結果 
}
