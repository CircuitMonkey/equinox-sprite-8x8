
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

#ifndef _Sprite8x8_H_
#define _Sprite8x8_H_

#include "Arduino.h"

class Sprite8x8
{
private:
    byte data;
    byte num;
    byte buffer[80];

    void reload();

public:
    Sprite8x8(byte data);

    void init();
    void clear();
    void setCommand(byte command, byte value);
    void setIntensity(byte intensity);
    void setColumn(byte col, byte value);
    void setColumnAll(byte col, byte value);
    void setDot(byte col, byte row, byte value);
    void writeSprite(int x, int y, const byte* sprite);

    void shiftLeft(bool rotate = false, bool fill_zero = true);
    void shiftRight(bool rotate = false, bool fill_zero = true);
    void shiftUp(bool rotate = false);
    void shiftDown(bool rotate = false);
};

#endif
