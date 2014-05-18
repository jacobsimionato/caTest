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
    std::string getArgStr(int argIdx);
    int getArgPosInt(int argIdx); //returns -1 if not possible
    int getArgPwr2(int argIdx); //returns -1 if not possible
    int getNumArgs();
    void print();
    
    /*
     =============== For global control ===============
     */
    
    //Clear all defined options - to allow testing
    static void clearAllOptions();

    //Parses argument vector grouping by -tags
    static void parseCmdLineOptions(int argc,  const char * argv[]);
    
    //Print all the currently discovered command line options
    static void printAll();
    
    //Find a command line option by tag
    static cmdLineOption* findOpt(std::string key);
private:
    cmdLineOption();
    std::vector<std::string> m_valStrings;

    static bool m_verbose;

    static std::string m_lastAddedTag;
    //vector containing every command line option
    static std::map<std::string, cmdLineOption> m_cmdLineOptions;
};


#endif /* defined(__mipsim__cmdLineOption__) */
