//
//  cacheGeneric.cpp
//  mipsim
//
//  Created by Jacob Simionato on 18/05/2014.
//  Copyright (c) 2014 Jacob. All rights reserved.
//

#include "cacheGeneric.h"

CacheGeneric::CacheGeneric(MemorySystemGeneric* parent){
    m_parent = parent;
}

int CacheGeneric::getAddressAccessCycles(){
    return 0;
}

int CacheGeneric::getMissCycleCount(){
    return m_missCycleCount;
}

int CacheGeneric::getMissCount(){
    return m_missCount;
}

int CacheGeneric::getAccessCount(){
    return m_accessCount;
}

float CacheGeneric::getMissRate(){
    return static_cast<float>(m_accessCount) / m_accessCount;
}

float CacheGeneric::getDirtyOnReplacementRate(){
    return static_cast<float>(m_dirtyOnReplacementInstrs) / m_accessCount;
}

int CacheGeneric::getDirtyOnReplacementInstrs(){
    return m_dirtyOnReplacementInstrs;
}

void CacheGeneric::resetStats(){
    m_missCycleCount = 0;
    m_missCount = 0;
    m_accessCount = 0;
    m_dirtyOnReplacementInstrs = 0;
}

MemorySystemGeneric* CacheGeneric::getParent(){
    return m_parent;
}