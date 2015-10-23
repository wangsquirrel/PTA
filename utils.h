#ifndef UTILS_H
#define UTILS_H
#include <string>
#include <vector>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <memory.h>
#include <assert.h>
#include <sstream>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include "Logger.hpp"
//used for url encode.Convert each char to visible Hexadecimal
std::string ToHexString(const uint8_t* buf,int len,std::string tok);
//scan the str for once and replace all old_value 
std::string & replace_all(std::string& str,const std::string& old_value,const std::string& new_value);
//encode url charactor not in the set 0-9, a-z, A-Z, '.', '-', '_' and '~',
std::string UrlEncode(const std::string& str);
std::string UrlEncode(unsigned char * t, int len);
//decode url
std::string UrlDecode(const std::string& str);
template <class T>
std::string integer2str(T t)
{
    std::stringstream ss;
    ss << t;
    return ss.str();
}

//read torrent file name from directory and store in vs
int read_dir(const char * dirname, std::vector<std::string> &vs);
std::string human_size(unsigned long long size);




#endif
