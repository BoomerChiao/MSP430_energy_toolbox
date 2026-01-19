#include <Wire.h>
#include "Font.h"
#include <string.h>
#include "images.h"


#define OLED_Write_Address 0x3C
#define VOLT_PIN A6     // P1.6 = ADC channel 2
#define NMOS 2 //P1.0 = N-MOS
const int SENSOR_A = 18;   // 假設接到 P2.2 → Energia pin 18
const int SENSOR_B = 17;   // 假設接到 P3.2 → Energia pin 17
const int BUTTON_A = 8;   // 假設接到 P2.7 → Energia pin 8
const int BUTTON_B = 21;   // 假設接到 P2.3 → Energia pin 21

const float R1 = 200000;  // 分壓電阻值（單位：歐姆）
const float R2 = 100000;  // 分壓電阻值（單位：歐姆）
/*const float R1 = 30000;  // 分壓電阻值（單位：歐姆）
const float R2 = 7500;  // 分壓電阻值（單位：歐姆）*/

const float VREF = 3.3;  // ADC 參考電壓（預設使用 VCC = 3.3V）


void OLED_Data(char *DATA) /* Function for sending data to OLED */
{
  int len = strlen(DATA);
  for (int g=0; g<len; g++)
  {    
    for (int index=0; index<5; index++)
    {     
      Wire.beginTransmission(OLED_Write_Address); /* Begin transmission to slave device */
    /* Queue data to be transmitted */
      Wire.write(0x40); /* For Data Transmission, C = 0 and D/C = 1 */ 
      Wire.write(ASCII[DATA[g] - 0x20][index]); 
      Wire.endTransmission(); /* Transmit the queued bytes and end transmission to slave device */ 
    }    
  }
}

void OLED_Command(char DATA) /* Function for sending command to OLED */
{
  Wire.beginTransmission(OLED_Write_Address); /* Begin transmission to slave device */
  /* Queue data to be transmitted */
  Wire.write(0x00); /* For Data Transmission, C = 0 and D/C = 0 */ 
  Wire.write(DATA); 
  Wire.endTransmission(); /* Transmit the queued bytes and end transmission to slave device */
}

void OLED_clear(void) /* Function for clearing OLED */   
{
  OLED_setXY(0x00, 0x7F, 0x00, 0x07); /* Column Start Address 0, Column End Address 127, Page Start Address 0, Page End Address 7  */
  for (int k=0; k<=1023; k++)
  {
    Wire.beginTransmission(OLED_Write_Address); /* Begin transmission to slave device */
  /* Queue data to be transmitted */
    Wire.write(0x40); /* For Data Transmission, C = 0 and D/C = 1 */ 
    Wire.write(0x00); 
    Wire.endTransmission(); /* Transmit the queued bytes and end transmission to slave device */  
  }  
}

void OLED_setXY(char col_start, char col_end, char page_start, char page_end) /* Function for setting cursor for writing data */  
{
  Wire.beginTransmission(OLED_Write_Address); /* Begin transmission to slave device */
  /* Queue data to be transmitted */
  Wire.write(0x00); /* For Data Transmission, C = 0 and D/C = 0 */
  Wire.write(0x21); /* Set Column Start and End Address */ 
  Wire.write(col_start); /* Column Start Address col_start */
  Wire.write(col_end); /* Column End Address col_end */
  Wire.write(0x22); /* Set Page Start and End Address */ 
  Wire.write(page_start); /* Page Start Address page_start */
  Wire.write(page_end); /* Page End Address page_end */
  Wire.endTransmission(); /* Transmit the queued bytes and end transmission to slave device */
}

void OLED_init(void) /* Function for initializing OLED */
{
  OLED_Command(0xAE); /* Entire Display OFF */
  OLED_Command(0xD5); /* Set Display Clock Divide Ratio and Oscillator Frequency */
  OLED_Command(0x80); /* Default Setting for Display Clock Divide Ratio and Oscillator Frequency that is recommended */
  OLED_Command(0xA8); /* Set Multiplex Ratio */
  OLED_Command(0x3F); /* 64 COM lines */
  OLED_Command(0xD3); /* Set display offset */
  OLED_Command(0x00); /* 0 offset */
  OLED_Command(0x40); /* Set first line as the start line of the display */
  OLED_Command(0x8D); /* Charge pump */
  OLED_Command(0x14); /* Enable charge dump during display on */
  OLED_Command(0x20); /* Set memory addressing mode */
  OLED_Command(0x00); /* Horizontal addressing mode */
  OLED_Command(0xA1); /* Set segment remap with column address 127 mapped to segment 0 */
  OLED_Command(0xC8); /* Set com output scan direction, scan from com63 to com 0 */
  OLED_Command(0xDA); /* Set com pins hardware configuration */
  OLED_Command(0x12); /* Alternative com pin configuration, disable com left/right remap */
  OLED_Command(0x81); /* Set contrast control */
  OLED_Command(0x80); /* Set Contrast to 128 */
  OLED_Command(0xD9); /* Set pre-charge period */
  OLED_Command(0xF1); /* Phase 1 period of 15 DCLK, Phase 2 period of 1 DCLK */
  OLED_Command(0xDB); /* Set Vcomh deselect level */
  OLED_Command(0x20); /* Vcomh deselect level ~ 0.77 Vcc */
  OLED_Command(0xA4); /* Entire display ON, resume to RAM content display */
  OLED_Command(0xA6); /* Set Display in Normal Mode, 1 = ON, 0 = OFF */
  OLED_Command(0x2E); /* Deactivate scroll */
  OLED_Command(0xAF); /* Display on in normal mode */
}
void OLED_setContrast(uint8_t contrast) {
    // contrast: 0~255，數字越小越暗，越大越亮
    OLED_Command(0x81); // SSD1306 對比度指令
    OLED_Command(contrast);
}
void OLED_image(const unsigned char *image_data)   /* Function for sending image data to OLED */
{
  OLED_setXY(0x00, 0x7F, 0x00, 0x07);    
  for (int k=0; k<=1023; k++)
  {    
    Wire.beginTransmission(OLED_Write_Address); /* Begin transmission to slave device */
  /* Queue data to be transmitted */
    Wire.write(0x40); /* For Data Transmission, C = 0 and D/C = 1 */
    Wire.write(image_data[k]);
    Wire.endTransmission(); /* Transmit the queued bytes and end transmission to slave device */ 
  }   
}



#include "Font12.h"
void OLED_Data12(const char *DATA, uint8_t page_start, uint8_t col_start) {
    int len = strlen(DATA);
    uint8_t page = page_start;
    uint8_t col = col_start;

    for (int g=0; g<len; g++) {
        char c = DATA[g];
        uint8_t idx;
        if (c >= '0' && c <= '9') idx = c - '0';
        else if (c == '.') idx = 10;
        else continue;

        // 上半部分 8px
        OLED_setXY(col, col+7, page, page);
        for (int i=0; i<8; i++) {
            uint8_t b = 0;
            for (int bit=0; bit<8; bit++) {
                if (Font12[idx][bit] & (1<<(7-i))) b |= (1<<bit);
            }
            Wire.beginTransmission(OLED_Write_Address);
            Wire.write(0x40);
            Wire.write(b);
            Wire.endTransmission();
        }

        // 下半部分 4px
        OLED_setXY(col, col+7, page+1, page+1);
        for (int i=8; i<12; i++) {
            uint8_t b = 0;
            for (int bit=0; bit<8; bit++) {
                if (Font12[idx][i] & (1<<(7-bit))) b |= (1<<bit);
            }
            Wire.beginTransmission(OLED_Write_Address);
            Wire.write(0x40);
            Wire.write(b);
            Wire.endTransmission();
        }

        col += 8;
        if (col > 127) { col = 0; page += 2; }
    }
}


/*void OLED_Draw20x20(const uint8_t *img, uint8_t col, uint8_t page) {
  for (uint8_t p = 0; p < 3; p++) { // 分三個 page
    OLED_setXY(col, col + 19, page + p, page + p); // 設定 20 寬、1 高 page 區塊

    for (uint8_t x = 0; x < 20; x++) {
      Wire.beginTransmission(OLED_Write_Address);
      Wire.write(0x40);
      Wire.write(img[p * 20 + x]); // 每個 column 的一個 byte
      Wire.endTransmission();
    }
  }
}*/


void OLED_Draw18x23(const uint8_t *img, uint8_t col, uint8_t page) {
  // 高度 23 → 需要 3 page
  for (uint8_t p = 0; p < 3; p++) {
    OLED_setXY(col, col + 17, page + p, page + p); // 寬 18, 高 1 page

    for (uint8_t x = 0; x < 18; x++) {
      Wire.beginTransmission(OLED_Write_Address);
      Wire.write(0x40);

      // 取出對應的資料
      // 每個 page 有 18 個 byte
      Wire.write(img[p * 18 + x]);

      Wire.endTransmission();
    }
  }
}

/*void OLED_DrawCounter(long counter, uint8_t col, uint8_t page) {
  char buf[5];
  sprintf(buf, "%04ld", counter % 10000); // 固定 4 位數 (0000~9999)

  for (int i=0; i<4; i++) {
    int num = buf[i] - '0'; // 取出數字
    OLED_Draw18x23(digitImages[num], col + i*20, page);
  }
}*/

void OLED_DrawCounter(long counter, uint8_t col, uint8_t page) {
  char buf[5];

  // 如果是負數就取絕對值
  if (counter < 0) counter = -counter;

  sprintf(buf, "%04ld", counter % 10000); // 固定 4 位數 (0000~9999)

  for (int i=0; i<4; i++) {
    int num = buf[i] - '0'; // 取出數字 (0~9)
    OLED_Draw18x23(digitImages[num], col + i*20, page);
  }
}


//int AIR,loop;
unsigned long loopStartTime;
unsigned long loopEndTime;
unsigned long loopDuration;
unsigned long lastActiveTime = 1000; // 紀錄最後活動時間
volatile int  counter= 0; //原始計算數值
int counter_2 =0; //對應原始計算數值除上TAPE
int sleepTimeout = 10000; //10 秒沒動就休眠
int idleDelay = 500; // 靜止多少毫秒才刷新
int lastCounter,lastState = 0;

const int settingValues[] = {2,4,8,12,16,20,24,28,32,36,40,44,48,52,56};
const int settingCount = sizeof(settingValues) / sizeof(settingValues[0]);
int settingIndex = 0; //按鈕計算次數
int value_AB = 2; //儲存對應按鈕數值settingValues





void setup() {
  pinMode(NMOS, OUTPUT); //NMOS 開關
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
  OLED_setXY(0x55, 0x7F, 0x05, 0x02);
  OLED_Data("BAT: ");

}



void loop() {
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
    OLED_Command(0xAF); // 每次有動作都強制亮屏

   /* lastActiveTime = millis(); //有動作就更新 lastActiveTime
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
    OLED_Command(0xAF); // 每次有動作都強制亮屏

    /*lastActiveTime = millis(); //有動作就更新 lastActiveTime
    digitalWrite(NMOS, HIGH);
    delay(400);*/
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
    
    // 換算實際輸入電壓
    int v_in = ((analogRead(VOLT_PIN) * VREF) / 1023.0) * ((R1 + R2) / R2)*10;
    int v_inD = v_in/10 ;
    int v_in2F = ((v_in - v_inD*10));
/*
    int adc = analogRead(VOLT_PIN);        // 0~1023
long temp = (long)adc * 3300L * (R1 + R2) / R2 / 1023; // 單位 mV
int v_inD = temp / 1000;               // 整數 V
int v_in2F = (temp % 1000) / 10;       // 小數 2 位*/

    OLED_setXY(0x55, 0x7F, 0x05, 0x02);
    char VREFF[10];
    sprintf(VREFF,"BAT: %d.%d", v_inD,v_in2F);  // 把秒數轉成字串
    OLED_Data(VREFF);

    
  }

  //閒置超越sleepTimeout，進入OLED休眠狀態
  if (millis() - lastActiveTime  > sleepTimeout) {
    OLED_Command(0xAE); // Display OFF
    digitalWrite(NMOS, LOW); //NMOS 關
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
