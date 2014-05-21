//
//  cacheBlock.cpp
//  mipsim
//
//  Created by Jacob Simionato on 20/05/2014.
//  Copyright (c) 2014 Jacob. All rights reserved.
//

#include "cacheBlock.h"

using namespace std;

void CacheTag::init(int sizeBytes){
    useOrder = -1;
    isDirty = false;
//    if(sizeBytes < 4){
//        cout << "CacheBlock:: Cannot initialize block smaller than 4 bytes" << endl;
//    }
//    int sizeWords = sizeBytes / 4;
//    data = new wordT[sizeWords];
}