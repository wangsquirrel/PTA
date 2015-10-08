#ifndef UTILS_H
#define UTILS_H
#include <string>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <memory.h>
//used for url encode.Convert each char to visible Hexadecimal
std::string ToHexString(const uint8_t* buf,int len,std::string tok);
//scan the str for once and replace all old_value 
std::string & replace_all(std::string& str,const std::string& old_value,const std::string& new_value);

#endif
