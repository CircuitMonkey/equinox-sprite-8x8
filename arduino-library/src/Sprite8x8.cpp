/*
 * Sprite8x8 Arduino Library
 * Version 0.0  Jan 2019
 * Copyright 2019 Circuit Monkey
 * MIT License
 *
 * Class API based upon:
 * MaxMatrix
 * Version 1.0 Feb 2013
 * Copyright 2013 Oscar Kin-Chung Au
 * https://code.google.com/archive/p/arudino-maxmatrix-library/
 */


#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include "Sprite8x8.h"

Sprite8x8::Sprite8x8(byte _data /*, byte _load, byte _clock, byte _num */) {
    data = _data;

    // Max in use, from older code.  ???
    num = 1;

    //load = _load;
    //clock = _clock;
    //num = _num;
    for (int i=0; i<80; i++)
        buffer[i] = 0;
}

void Sprite8x8::init() {

    pinMode(data,  OUTPUT); // Call AdaFruit NeoPixel init here.

    //pinMode(clock, OUTPUT);
    //pinMode(load,  OUTPUT);
    //digitalWrite(clock, HIGH);

    //setCommand(max7219_reg_scanLimit, 0x07);
    //setCommand(max7219_reg_decodeMode, 0x00);  // using an led matrix (not digits)
    //setCommand(max7219_reg_shutdown, 0x01);    // not in shutdown mode
    //setCommand(max7219_reg_displayTest, 0x00); // no display test

    // empty registers, turn all LEDs off
    clear();

    setIntensity(0x0f);    // the first 0x0f is the value you can set
}

void Sprite8x8::setIntensity(byte intensity)
{
    //setCommand(max7219_reg_intensity, intensity);

    // TODO: NeopPixel Set Brightness
}

void Sprite8x8::clear()
{
    for (int i=0; i<8; i++)
        setColumnAll(i,0);

    for (int i=0; i<80; i++)
        buffer[i] = 0;
}

// What does this do?
void Sprite8x8::setCommand(byte command, byte value) {
    // AdaFruit NeoPixel foo.

    /*
     digitalWrite(load, LOW);
     for (int i=0; i<num; i++)
     {
     shiftOut(data, clock, MSBFIRST, command);
     shiftOut(data, clock, MSBFIRST, value);
     }
     digitalWrite(load, LOW);
     digitalWrite(load, HIGH);

     */
}


void Sprite8x8::setColumn(byte col, byte value) {
    // AdaFruit NepPixel foo.

    /*
     int n = col / 8;
     int c = col % 8;
     digitalWrite(load, LOW);
     for (int i=0; i<num; i++)
     {
     if (i == n)
     {
     shiftOut(data, clock, MSBFIRST, c + 1);
     shiftOut(data, clock, MSBFIRST, value);
     }
     else
     {
     shiftOut(data, clock, MSBFIRST, 0);
     shiftOut(data, clock, MSBFIRST, 0);
     }
     }
     digitalWrite(load, LOW);
     digitalWrite(load, HIGH);

     */
    buffer[col] = value;
}

void Sprite8x8::setColumnAll(byte col, byte value) {
    // TODO: AdaFruit NeoPixel foo.

    /*
     digitalWrite(load, LOW);
     for (int i=0; i<num; i++)
     {
     shiftOut(data, clock, MSBFIRST, col + 1);
     shiftOut(data, clock, MSBFIRST, value);
     buffer[col * i] = value;
     }
     digitalWrite(load, LOW);
     digitalWrite(load, HIGH);

     */
}

void Sprite8x8::setDot(byte col, byte row, byte value) {
    // TODO AdaFruit Neopixel foo.
    /*
     bitWrite(buffer[col], row, value);

     int n = col / 8;
     int c = col % 8;
     digitalWrite(load, LOW);

     for (int i=0; i<num; i++) {
     if (i == n) {
     shiftOut(data, clock, MSBFIRST, c + 1);
     shiftOut(data, clock, MSBFIRST, buffer[col]);
     } else {
     shiftOut(data, clock, MSBFIRST, 0);
     shiftOut(data, clock, MSBFIRST, 0);
     }
     }

     digitalWrite(load, LOW);
     digitalWrite(load, HIGH);


     */
}

void Sprite8x8::writeSprite(int x, int y, const byte* sprite) {
    int w = sprite[0];
    int h = sprite[1];

    if (h == 8 && y == 0) {
        for (int i=0; i<w; i++) {
            int c = x + i;
            if (c>=0 && c<80)
                setColumn(c, sprite[i+2]);
        }
    } else {
        for (int i=0; i<w; i++) {
            for (int j=0; j<h; j++) {
                int c = x + i;
                int r = y + j;
                if (c>=0 && c<80 && r>=0 && r<8)
                    setDot(c, r, bitRead(sprite[i+2], j));
            }
        }
    }
}

void Sprite8x8::reload() {
    /*   ADA Fruit buffer -> array foo.
     for (int i=0; i<8; i++) {
     int col = i;
     digitalWrite(load, LOW);

     for (int j=0; j<num; j++) {
     shiftOut(data, clock, MSBFIRST, i + 1);
     shiftOut(data, clock, MSBFIRST, buffer[col]);
     col += 8;
     }

     digitalWrite(load, LOW);
     digitalWrite(load, HIGH);
     }
     */
}

void Sprite8x8::shiftLeft(bool rotate, bool fill_zero) {
    byte old = buffer[0];
    int i;
    for (i=0; i<80; i++)
        buffer[i] = buffer[i+1];
    if (rotate) buffer[num*8-1] = old;
    else if (fill_zero) buffer[num*8-1] = 0;

    reload();
}

void Sprite8x8::shiftRight(bool rotate, bool fill_zero) {
    int last = num*8-1;
    byte old = buffer[last];
    int i;
    for (i=79; i>0; i--)
        buffer[i] = buffer[i-1];
    if (rotate) buffer[0] = old;
    else if (fill_zero) buffer[0] = 0;

    reload();
}

void Sprite8x8::shiftUp(bool rotate) {
    for (int i=0; i<num*8; i++)
    {
        bool b = buffer[i] & 1;
        buffer[i] >>= 1;
        if (rotate) bitWrite(buffer[i], 7, b);
    }
    reload();
}

void Sprite8x8::shiftDown(bool rotate) {
    for (int i=0; i<num*8; i++)
    {
        bool b = buffer[i] & 128;
        buffer[i] <<= 1;
        if (rotate) bitWrite(buffer[i], 0, b);
    }
    reload();
}
