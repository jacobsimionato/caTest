//
//  main.cpp
//  mipsim
//
//  Created by Jacob Simionato on 30/03/2014.
//  Copyright (c) 2014 Jacob. All rights reserved.
//

#include <iostream>
#include "memorySystem.h"

using namespace std;

int main(int argc, const char * argv[]){
    MemorySystem memorySystem;
    memorySystem.setWord(3400, 4667);
    memorySystem.setWord(50000, 12345);
    memorySystem.setWord(0, 3);
    memorySystem.printSummary();
    cout << memorySystem.retrieveWord(3400) << endl;
    
    return 0;
}

