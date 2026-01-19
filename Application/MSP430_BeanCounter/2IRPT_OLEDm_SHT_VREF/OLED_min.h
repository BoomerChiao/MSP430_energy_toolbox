#ifndef OLED_MIN_H
#define OLED_MIN_H

#include <Wire.h>
#include "Font.h"
#include "Font12.h"
#include "images.h"

#define OLED_Write_Address 0x3C

void OLED_Command(char DATA) {
    Wire.beginTransmission(OLED_Write_Address);
    Wire.write(0x00);
    Wire.write(DATA);
    Wire.endTransmission();
}

void OLED_setXY(char col_start, char col_end, char page_start, char page_end) {
    Wire.beginTransmission(OLED_Write_Address);
    Wire.write(0x00);
    Wire.write(0x21); // set column
    Wire.write(col_start);
    Wire.write(col_end);
    Wire.write(0x22); // set page
    Wire.write(page_start);
    Wire.write(page_end);
    Wire.endTransmission();
}

void OLED_Data(const char *DATA) {
    int len = strlen(DATA);
    for (int g=0; g<len; g++) {
        for (int index=0; index<5; index++) {
            Wire.beginTransmission(OLED_Write_Address);
            Wire.write(0x40);
            Wire.write(ASCII[DATA[g] - 0x20][index]);
            Wire.endTransmission();
        }
    }
}

void OLED_clear() {
    OLED_setXY(0x00,0x7F,0x00,0x07);
    for(int k=0;k<=1023;k++){
        Wire.beginTransmission(OLED_Write_Address);
        Wire.write(0x40);
        Wire.write(0x00);
        Wire.endTransmission();
    }
}

void OLED_init() {
    OLED_Command(0xAE); OLED_Command(0xD5); OLED_Command(0x80);
    OLED_Command(0xA8); OLED_Command(0x3F); OLED_Command(0xD3);
    OLED_Command(0x00); OLED_Command(0x40); OLED_Command(0x8D);
    OLED_Command(0x14); OLED_Command(0x20); OLED_Command(0x00);
    OLED_Command(0xA1); OLED_Command(0xC8); OLED_Command(0xDA);
    OLED_Command(0x12); OLED_Command(0x81); OLED_Command(0x80);
    OLED_Command(0xD9); OLED_Command(0xF1); OLED_Command(0xDB);
    OLED_Command(0x20); OLED_Command(0xA4); OLED_Command(0xA6);
    OLED_Command(0x2E); OLED_Command(0xAF);
}

void OLED_setContrast(uint8_t contrast) {
    OLED_Command(0x81);
    OLED_Command(contrast);
}

void OLED_image(const uint8_t *image_data) {
    OLED_setXY(0x00,0x7F,0x00,0x07);
    for(int k=0;k<=1023;k++){
        Wire.beginTransmission(OLED_Write_Address);
        Wire.write(0x40);
        Wire.write(image_data[k]);
        Wire.endTransmission();
    }
}

void OLED_Draw18x23(const uint8_t *img, uint8_t col, uint8_t page) {
    for(uint8_t p=0;p<3;p++){
        OLED_setXY(col, col+17, page+p, page+p);
        for(uint8_t x=0;x<18;x++){
            Wire.beginTransmission(OLED_Write_Address);
            Wire.write(0x40);
            Wire.write(img[p*18+x]);
            Wire.endTransmission();
        }
    }
}

void OLED_DrawCounter(long counter, uint8_t col, uint8_t page){
    char buf[5];
    if(counter<0) counter=-counter;
    sprintf(buf,"%04ld", counter%10000);
    for(int i=0;i<4;i++){
        int num = buf[i]-'0';
        OLED_Draw18x23(digitImages[num], col+i*20, page);
    }
}

#endif
