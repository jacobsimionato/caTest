//
//  patternMatchers.h
//  mipsim
//  Computer Architecture Assignment 1 2014
//  Jacob Simionato a1175808

#ifndef __mipsim__patternMatchers__
#define __mipsim__patternMatchers__

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

/*
 =================== Pattern Matching ===================
 Process input command strings and match patterns to interpret commands
 */

//Takes a string and tokenizes it using the provided delimiters, returning a vector of strings representing each token. Inspired by the PHP "explode" function.
std::vector<std::string> explode(std::string input, std::string separators = " \n\r");

//Returns true if the input character matches any characters in the string. Used by explode to check for delimiters.
bool isInChars(char inputChar, std::string checkList);

//Takes an input string and checks if there is a comment at the end of the line indicated by the provided separator character. If a comment is found, the string is truncated to remove it.
void removeComment(std::string &input, char separator = '#');

//Takes an input string and returns a new string where each equals sign in the string has a space character inserted immediately before and after it. eg "num=5" becomes "num = 5"
void padEquals(std::string &input);

//Attempts to convert a string containing hex digits to an integer
bool hexStrToInt(const std::string &input, unsigned int &output);

//Attempts to convert a string containing decimal digits to an integer
bool decStrToInt(const std::string &input, unsigned int &output);


/*
 =================== Pattern Matching Debug Helpers ===================
 */

//Prints a string vector to help debug the results of 'explode'
void printStrVector(const std::vector<std::string> input);

//Prints a string as the integer character values to help debug input
void printStrInts(const std::string input);

#endif /* defined(__mipsim__patternMatchers__) */