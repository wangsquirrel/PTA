#ifndef UTILS_H
#define UTILS_H
#include <string>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <memory.h>
std::string ToHexString(const uint8_t* buf,int len,std::string tok);
std::string & replace_all(std::string& str,const std::string& old_value,const std::string& new_value);


#endif
