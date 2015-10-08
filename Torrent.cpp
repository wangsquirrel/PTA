#include "Torrent.h"
#include "Bencode.h"
#include "sha1.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdlib.h>

Torrent::Torrent(std::string file_name)
{
	//load torrent from a file
	std::ifstream in(file_name.c_str());
	std::string str;
	copy( std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>(), back_inserter(str));
	in.close();
	Bencode b(str);
	std::map<std::string, Any> msa = any_cast<std::map<std::string, Any> >(b.inter_obj);

	//extarct tracker
	tracker = any_cast<std::string>(msa["announce"]);
	std::cout<<tracker<<std::endl;

	// extract info and calc info_hash
	Bencode info_Bencode(msa["info"]);
	std::string bs = info_Bencode.dump();
	sha1((const unsigned char *)bs.c_str(), bs.length(), info_hash);

	// extract length include 2 cases
	std::map<std::string, Any> info = any_cast<std::map<std::string, Any> >(msa["info"]);
	// multiple file mode
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
	//single file mode
	else 
	{
		length = any_cast<unsigned long long>(info["length"]);
		
	}

	//extract name
	name = any_cast<std::string>(info["name"]);
	

}
bool Torrent::scrapable()
{
    int index;
    index = tracker.find_last_of('/');
    if (tracker.substr(index + 1, 8) == "announce")
        return true;
    else
        return false;
}
