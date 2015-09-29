#include "Torrent.h"
#include "Bencode.h"
#include "sha1.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdlib.h>

Torrent::Torrent(std::string file_name)
{
	std::ifstream in(file_name.c_str());
	std::string str;
	copy( std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>(), back_inserter(str));
	in.close();
	Bencode b(str);
	std::map<std::string, Any> msa = any_cast<std::map<std::string, Any> >(b    .inter_obj);
	Bencode info_Bencode(msa["info"]);
	std::string bs = info_Bencode.dump();
	sha1((const unsigned char *)bs.c_str(), bs.length(), info_hash);
	std::map<std::string, Any> info = any_cast<std::map<std::string, Any> >(msa["info"]);
	// multi-files
	if (info.count("files") == 1)
	{
		unsigned long long uuu = 0;
		std::vector<Any> files = any_cast<std::vector<Any> >(info["files"]);
		for (auto d : files)
		{
			std::map<std::string, Any> dic = any_cast<std::map<std::string, Any> >(d);
			uuu = uuu + any_cast<unsigned long long>(dic["length"]);
			length = uuu;
		}
	}
	else 
	{
		length = any_cast<unsigned long long>(info["length"]);
		
	}
	//length = strtoull(slen.c_str(), NULL, 10);

}
