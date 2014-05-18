//
//  cmdLineOption.cpp
//  mipsim
//
//  Created by Jacob Simionato on 15/05/2014.
//  Copyright (c) 2014 Jacob. All rights reserved.
//

#include "cmdLineOption.h"
#include "patternMatchers.h"

#include <sstream>

using namespace std;

/*
 =================== Member Functions ===================
 */

bool cmdLineOption::m_verbose = false;
map<string, cmdLineOption> cmdLineOption::m_cmdLineOptions;
string cmdLineOption::m_lastAddedTag;

cmdLineOption::cmdLineOption(){
    
}

string cmdLineOption::getArgStr(int argIdx){
    return m_valStrings[argIdx];
}

/*
 Returns an integer if a valid integer can be found, else returns -1
 */
int cmdLineOption::getArgPosInt(int argIdx){
    unsigned int output;
    bool success = decStrToInt(getArgStr(argIdx), output);
    if(success){
        return output;
    }else{
        return -1;
    }
}

/*
 Returns an integer of power of 2 if we have one, else returns -1
 */
int cmdLineOption::getArgPwr2(int argIdx){
    int argInt = getArgPosInt(argIdx);
    bool success = (argInt > 0) && ((argInt & (argInt - 1)) == 0);
    if(success){
        return argInt;
    }
    return -1;
}

int cmdLineOption::getNumArgs(){
    return m_valStrings.size();
}

void cmdLineOption::print(){
    //cout << "Arg: '" << m_tag << "'" << endl;
    //cout << "   Found: " << wasFound();
    if(m_valStrings.size() > 0){
        cout << "   Arguments: ";
        for(int i=0; i<m_valStrings.size(); i++){
            cout << m_valStrings[i] << " ";
        }
        cout << endl;
    }
    cout << endl;
}


/*
 =================== Static Functions ===================
 */
//Clear all defined options - to allow testing
void cmdLineOption::clearAllOptions(){
    cmdLineOption::m_cmdLineOptions.clear();
    m_lastAddedTag.clear();
}


/*
 Parses arguments using currently defined options
 */
void cmdLineOption::parseCmdLineOptions(int argc,  const char * argv[]){
    int argnum = 1;
    map<string, cmdLineOption>::iterator iter;
    while(argnum < argc){
        string argTag(argv[argnum]);
        if(argTag[0] == '-'){
            m_cmdLineOptions.insert(pair<string, cmdLineOption>(argTag, cmdLineOption()));
            m_lastAddedTag = argTag;
        }else if(!m_cmdLineOptions.empty()){
            findOpt(m_lastAddedTag)->m_valStrings.push_back(argTag);
        }else{
            if(m_verbose){
                cout << "cmdLineOption:: Error - argument value does not follow '-' option name" << endl;
            }
        }
        argnum++;
    }
    if(m_verbose){
        printAll();
    }
}

void cmdLineOption::printAll(){
    map<string, cmdLineOption>::iterator iter;
    for (iter = m_cmdLineOptions.begin(); iter != m_cmdLineOptions.end(); ++iter){
        cout << "Arg: '" << iter->first << "'" << endl;
        iter->second.print();
    }
}

cmdLineOption* cmdLineOption::findOpt(std::string key){
    cmdLineOption* output;
    try{
        output = &m_cmdLineOptions.at(key);
    }
    catch (const out_of_range &outOfRangeE) {
        return NULL;
    }
    return output;
}
