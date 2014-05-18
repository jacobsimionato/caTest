//
//  cmdLineOption.h
//  mipsim
//
//  Created by Jacob Simionato on 15/05/2014.
//  Copyright (c) 2014 Jacob. All rights reserved.
//

#ifndef __mipsim__cmdLineOption__
#define __mipsim__cmdLineOption__

#include <iostream>
#include <vector>
#include <string>
#include <map>

class cmdLineOption{
public:
    
    //Parses
    bool parse(int &argc, int &argnum, const char * argv[]);
    
    
    std::string getArgStr(int argIdx);
    int getArgPosInt(int argIdx); //returns -1 if not possible
    int getArgPwr2(int argIdx); //returns -1 if not possible
    bool wasFound();
    void print();
    
    //For global control
    
    //static void defineNew(std::string flag, int numArgs = 0);
    
    //Clear all defined options - to allow testing
    static void clearAllOptions();
    
    /*
     Parses arguments using currently defined options
     */
    static void parseCmdLineOptions(int argc,  const char * argv[]);
    
    static void printAll();
    
    static cmdLineOption* checkOption(std::string key);
private:
    //private constructor can only be called by define:
    std::string m_tag;
    int m_numArgs;
    std::vector<std::string> m_valStrings;
    bool m_found;
    static bool m_verbose;
    
    cmdLineOption(std::string flag, int numArgs = 0);
    
    //vector containing every command line option
    static std::map<std::string, cmdLineOption> m_cmdLineOptions;
};


#endif /* defined(__mipsim__cmdLineOption__) */
