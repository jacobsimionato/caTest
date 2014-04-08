//
//  debugHelperFunctions.cpp
//  mipsim
//
//  Created by Jacob Simionato on 30/03/2014.
//  Copyright (c) 2014 Jacob. All rights reserved.
//

#include "debugHelperFunctions.h"
#include "mipsTypes.h"

/*
 Set the bit fields in register and immediate format instructions.
 Used within the instruction generation functions which are used for debugging.
 */
int setInstFieldsReg(int input, int s, int t, int d){
    input = input & ~(32767 << 11);
    input += s << 21;
    input += t << 16;
    input += d << 11;
    return input;
}

int setInstFieldsImm(int input, int s, int t, int C){
    input = input & ~(67108863);
    input += s << 21;
    input += t << 16;
    input += C;
    return input;
}

/*
 Instruction generation functions used for debugging purposes
 */
wordT genInstAdd(int s, int t, int d){
    return setInstFieldsReg(0x20, s, t, d);
}

wordT genInstAddi(int s, int t, int C){
    return setInstFieldsImm(0x20000000, s, t, C);
}

wordT genInstSw(int s, int t, int C){
    return setInstFieldsImm(0xAC000000, s, t, C);
}

wordT genInstLw(int s, int t, int C){
    return setInstFieldsImm(0x8C000000, s, t, C);
}
