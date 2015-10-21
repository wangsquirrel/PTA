#include "Torrent.h"
#include "Bencode.h"
#include "sha1.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdlib.h>

Torrent::Torrent(std::string file_name) : total_upload(0), total_download(0),
                                          event("started"), interval(30), min_interval(30),
                                          complete(0), incomplete(0), last_commit(0)
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
	//std::cout<<tracker<<std::endl;

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
std::string Torrent::make_req_str()
{
    std::string req_string;
    req_string = tracker + "&info_hash=" + UrlEncode(info_hash, 20)  + "&peer_id=-UT2000-%1CD%E6%9B%E7%26%B02-%D5%CFz&port=11111&" + 
                "ipv6=i2001%3ada8%3a215%3a3f0%3a20c%3a29ff%3afee5%3a9276" + 
                "&uploaded=" + integer2str(total_upload) + "&downloaded=" + integer2str(total_download) + 
                "&left=0&numwant=0&compact=1&no_peer_id=1" + (event=="noevent" ? "" : "&event=" + event);
    return req_string; 
}
std::string Torrent::make_scrape_req_string()
{    
    std::string req_string;
    req_string = req_string + replace_all(tracker, "announce", "scrape") + "&info_hash=" + UrlEncode(info_hash, 20);
    return req_string;
}
/*
 * this is a test for scrape, now we dont need this feature
 *
 *
    //req_str = req_str + replace_all(t.tracker, "announce", "scrape") + "&info_hash=" + UrlEncode(t.info_hash, 20);
    Bencode b(result);
    std::map<std::string, Any> qqq = any_cast<std::map<std::string, Any> >(b.inter_obj);
    std::map<std::string, Any> www = any_cast<std::map<std::string, Any> >(qqq["files"]);
    std::map<std::string, Any> rrr = any_cast<std::map<std::string, Any> >(www[ss]);
    unsigned long long  eee = any_cast<unsigned long long>(rrr["downloaded"]);
    std::cout << "complete: " << eee;


*/

