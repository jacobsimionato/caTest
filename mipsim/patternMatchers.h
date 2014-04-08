//
//  patternMatchers.h
//  mipsim
//
//  Created by Jacob Simionato on 31/03/2014.
//  Copyright (c) 2014 Jacob. All rights reserved.
//

#ifndef __mipsim__patternMatchers__
#define __mipsim__patternMatchers__

#include <iostream>
#include <regex>
#include <vector>
#include <string>
#include <sstream>

bool isInChars(char inputChar, std::string checkList);

void removeComment(std::string &input, char separator = '#');

void padEquals(std::string &input);

std::vector<std::string> explode(std::string input, std::string separators = " \n\r");

void printStrVector(const std::vector<std::string> input);

void printStrInts(const std::string input);

//int decStrToInt(std::string input);

//int hexStrToInt(std::string input);

bool hexStrToInt(const std::string &input, unsigned int &output);

bool decStrToInt(const std::string &input, unsigned int &output);


bool parseRegExp(std::string inputLine, std::string instrPatternString, std::vector<std::string> &result);

bool saveCharImmediate(std::string &input, int &pos, std::vector<int> &output); //to find inital character

bool checkCharImmediate(std::string &input, int &pos, char checkChar);

//bool saveDecImmediate(std::string &input, int &pos, std::vector<int> &output);

bool checkAdvanceEquals(std::string &input, int &pos);

//bool saveHexImmediate(std::string &input, int &pos, std::vector<int> &output);

bool advancePastWhiteSpace(std::string &input, int pos); //returns false if we reach end of line

std::vector<int> parseInput(std::string input);

//bool checkLetterImmediate(

#endif /* defined(__mipsim__patternMatchers__) */

/*
1. char saveCharImmediate(string input, int pos, vector<int> output) //to find inital character
bool checkCharImmediate(string input, int pos, char checkChar)
2. bool saveDecImmediate(string input, int pos, vector<int> output)
3. bool checkAdvanceEquals(string input, int pos)
4. bool saveHexImmediate(string input, int pos, vector<int> output
 bool advancePastWhiteSpace(string input, int pos) //returns false if we reach end of line

*/