#include<map>
#include<string>
#include<memory>
#include "Any.h"
#include <sstream>
#include "Logger.hpp"

#ifndef BENCODE_H
#define BENCODE_H
class Bencode
{
	
public:
	//internal object of Bencode
	Any inter_obj;
	Bencode(std::string r);
	Bencode(Any &a):inter_obj(a) {}
	//load from string to internal object
	Any load(std::string &str, std::string::iterator  &ci);
	//serilize the internal object to string
	std::string dump();
    int is_fail();
    int is_empty();

};

#endif
