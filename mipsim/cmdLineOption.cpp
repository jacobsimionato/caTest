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

cmdLineOption::cmdLineOption(std::string tag, int numArgs){
    m_found = false;
    m_tag = tag;
    m_numArgs = numArgs;
}

/*
 Keeps track of current argument by argnum passed by reference across calls
 Returns true if option was tagged and enough arguments were detected, else returns false
 */
bool cmdLineOption::parse(int &argc, int &argnum, const char *argv[]){
    if(string(argv[argnum]) == m_tag){
        m_found = true;
        if(argc-argnum < m_numArgs+1){
            return false;
        }else{
            argnum++;
            for(int i=0; i<m_numArgs; i++){
                m_valStrings.push_back(string(argv[argnum+i]));
            }
            argnum += m_numArgs;
            return true;
        }
    }
    return false;
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

bool cmdLineOption::wasFound(){
    return m_found;
}

void cmdLineOption::print(){
    cout << "Arg: '" << m_tag << "'" << endl;
    cout << "   Found: " << wasFound();
    if(m_numArgs > 0 && m_found){
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

//Defines a new command line option, and returns a pointer to it
//void cmdLineOption::defineNew(std::string flag, int numArgs){
//    m_cmdLineOptions.insert(pair<string, cmdLineOption>(flag, cmdLineOption(flag, numArgs)));
//}


//Clear all defined options - to allow testing
void cmdLineOption::clearAllOptions(){
    cmdLineOption::m_cmdLineOptions.clear();
}


/*
 Parses arguments using currently defined options
 */
void cmdLineOption::parseCmdLineOptions(int argc,  const char * argv[]){
    int argnum = 0;
    map<string, cmdLineOption>::iterator iter;
    while(argnum < argc){
        bool done;
        for (iter = m_cmdLineOptions.begin(); iter != m_cmdLineOptions.end(); ++iter){
            done = iter->second.parse(argc, argnum, argv);
            if(done){
                break;
            }
        }
        if(!done){
            argnum++;
        }
    }
    if(m_verbose){
        printAll();
    }
}

void cmdLineOption::printAll(){
    map<string, cmdLineOption>::iterator iter;
    for (iter = m_cmdLineOptions.begin(); iter != m_cmdLineOptions.end(); ++iter){
        iter->second.print();
    }
}

cmdLineOption* cmdLineOption::checkOption(std::string key){
    cmdLineOption* output;
    try{
        output = &m_cmdLineOptions.at(key);
    }
    catch (const out_of_range &outOfRangeE) {
        return NULL;
    }
    return output;
}
