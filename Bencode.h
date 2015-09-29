#include<map>
#include<string>
#include<memory>
#include "Any.h"
#include <sstream>
class Bencode
{
	
public:
	Any inter_obj;
	Bencode(std::string r);
	Bencode(Any &a):inter_obj(a) {}
	Any load(std::string &str, std::string::iterator  &ci);
	std::string dump();
	//operator[](std::string s);

};
