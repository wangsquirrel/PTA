#include <iostream>
#include <stdio.h>  

#include "Bencode.h"
#include "sha1.h"
#include "Torrent.h"
#include "HttpSender.h"
#include "utils.h"
#include "ConfigFile.h"

int main(int argc, char** argv) {
    ConfigFile c("pta.conf");

    if (c.load())
        c.PrintConfig();
    else
        std::cout<<"\nerror";


    /*
	Torrent t("multi-files.torrent");

	std::cout<<ToHexString(t.info_hash, 20, "")<<std::endl;;
	std::cout<<t.length<<std::endl;
	std::cout<<t.name<<std::endl;
	HttpSender hs;
	std::string result;
	std::string req_str;
	
	req_str = t.tracker + "&info_hash=" + ToHexString(t.info_hash, 20, "")  + "&peer_id=-UT2000-%1CD%E6%9B%E7%26%B02-%D5%CFz&port=11111&\
	ipv6=i2001%3ada8%3a215%3a3f0%3a20c%3a29ff%3afee5%3a9276\
	&uploaded=9900000&downloaded=9900000\
	&left=0&numwant=0&compact=1&no_peer_id=1";

	std::cout<<req_str<<std::endl;
	std::vector<std::string> headers;
	headers.push_back("User-Agent: uTorrent/2000(18934)");
	int r = hs.Gets(req_str ,headers, result);
	std::cout << r;
	std::cout << result;
	return 0;
    */
}
