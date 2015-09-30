#include "Bencode.h"
#include <iostream>
#include <memory>
#include <vector>
Any Bencode::load(std::string &str, std::string::iterator  &ci)
{
	//Integer type
	//Warning, a c++ int type may not satisfy the size of Bencode integet so we use unsigned long long 
	//All the integer type is considered to Unsigned long long
	//Every load will go to next interator.
	if (*ci == 'i')
	{
		auto start = ++ci;
		for (; *ci != 'e'; ++ci);
		std::string ss(start, ci);
		ci++;
		return Any(strtoull(ss.c_str(), NULL, 10));
		
	}
	else if (*ci >='0' && *ci <= '9')
	{
		auto start = ci;
		for (; *ci != ':'; ++ci);
		std::string ss(start, ci);
		unsigned long long len = strtoull(ss.c_str(), NULL, 10);
		++ci;// skip ':'
		ci += len;
		return Any(std::string(ci - len, ci));
	}
	
	else if (*ci == 'l')
	{
		std::vector<Any> va;
		ci++;
		while (*ci != 'e')
			va.push_back(load(str, ci));
		ci++;
		return va;
	}
	else if (*ci == 'd')
	{
		std::map<std::string, Any> maa;
		ci++;
		while ( *ci != 'e')
		{
			std::string first  = any_cast<std::string>(load(str, ci));
			Any second = load(str, ci);
			maa[first] = second;
		
		}
		ci++;
		return maa;
		
	}
	else
		assert(0);
	
		
}
Bencode::Bencode(std::string r)
{
	std::string::iterator si = r.begin();
	inter_obj = load(r, si);
}

std::string Bencode::dump()
{
	if (inter_obj.type().name() == typeid(unsigned long long).name())
	{
		std::stringstream ss;
		ss << any_cast<unsigned long long>(inter_obj);
		std::string integer;
		ss >> integer;
		std::string result = "";
		result = result + "i" + integer + "e";
		return result;
	}
	else if (inter_obj.type().name() == typeid(std::string).name())
	{
		std::string result = ""; 
		std::string tmp = any_cast<std::string>(inter_obj);
		std::stringstream ss;
		ss << tmp.length();
		std::string len;
		ss >> len;
		result = result + len + ":" + tmp;
		return result;
		
	}
	else if (inter_obj.type().name() == typeid(std::vector<Any>).name())
	{
		std::string result;
		std::vector<Any> va = any_cast<std::vector<Any> >(inter_obj);
		result += "l";
		for (auto i : va)
		{
			result = result + Bencode(i).dump();
		}
		result += "e";
		return result;
	}
	else if (inter_obj.type().name() == typeid(std::map<std::string, Any>).name()) 
	{
		std::string result;
		result += "d";
		std::map<std::string, Any> msa = any_cast<std::map<std::string, Any> >(inter_obj);
		for (auto i : msa)
		{
			Any first(i.first);
			result = result + Bencode(first).dump();
			result = result + Bencode(i.second).dump();
		}
		result += "e";
		return result;
	}
	else
		assert(0);
}
