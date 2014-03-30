//
//  mipsInterpreter.h
//  mipsim
//
//  Created by Jacob Simionato on 30/03/2014.
//  Copyright (c) 2014 Jacob. All rights reserved.
//

#ifndef __mipsim__mipsInterpreter__
#define __mipsim__mipsInterpreter__

#include <iostream>
#include <vector>
#include <map>

#include "mipsTypes.h"
#include "mipsInstructionDef.h"

class MipsInstructionDef;

class MipsInterpreter{
public:
    int fetchAndInterpret(int num = 0);
    int interpret(wordT instructionBin);
    //friend MipsInstructionDef;
private:
    int getOpcode(wordT instructionBin);
    int getModifier(wordT instructionBin);
    void decodeInstImm(wordT instructionBin, int* destArr);
    void decodeInstJump(wordT instructionBin, int* destArr);
    void decodeInstReg(wordT instructionBin, int* destArr);
    wordT m_regPc;
    wordT m_regGp[32];
    
    std::map<int, MipsInstructionDef> instructionDefs;
};

#endif /* defined(__mipsim__mipsInterpreter__) */
