//
//  cacheBlock.h
//  mipsim
//
//  Created by Jacob Simionato on 20/05/2014.
//  Copyright (c) 2014 Jacob. All rights reserved.
//

#ifndef __mipsim__cacheBlock__
#define __mipsim__cacheBlock__

#include <iostream>
#include "mipsTypes.h"

class CacheTag{
public:
    void init(int sizeBytes);
    int useOrder; //Higher means more recently used. -1 for invalid (cold)
    bool isDirty;
    int tag;
    //wordT* data;
};

#endif /* defined(__mipsim__cacheBlock__) */
