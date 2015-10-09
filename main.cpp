#include <iostream>
#include <stdio.h>  
#include <time.h>
#include <unistd.h>

#include "Bencode.h"
#include "sha1.h"
#include "Torrent.h"
#include "HttpSender.h"
#include "utils.h"
#include "ConfigFile.h"
#include "Logger.hpp"

int main(int argc, char** argv) {
    ConfigFile c("pta.conf");

    //if (c.load())   c.PrintConfig();
	Torrent t("single-file.torrent");

	LogInfo("info hash: %s", UrlEncode(t.info_hash, 20).c_str());
	LogInfo("file length: %llu", t.length);
	LogInfo("file  name : %s", t.name.c_str());
	LogInfo("scrapble : %s", (t.scrapable() ? "yes":"no"));

	HttpSender hs;
	std::vector<std::string> headers;
	headers.push_back("User-Agent: uTorrent/2000(18934)");
	std::string result;
	std::string req_str;
    unsigned long long up = 0, down = 0;
    
    while (true)
    {
	
	    req_str = t.tracker + "&info_hash=" + UrlEncode(t.info_hash, 20)  + "&peer_id=-UT2000-%1CD%E6%9B%E7%26%B02-%D5%CFz&port=11111&\
ipv6=i2001%3ada8%3a215%3a3f0%3a20c%3a29ff%3afee5%3a9276\
&uploaded=" + integer2str(up) + "&downloaded=" + integer2str(down) + \
"&left=0&numwant=0&compact=1&no_peer_id=1";

    //req_str = req_str + replace_all(t.tracker, "announce", "scrape") + "&info_hash=" + UrlEncode(t.info_hash, 20);

	LogInfo("req_str : %s", req_str.c_str());
	int resp_code = hs.Gets(req_str ,headers, result);
	LogInfo("curl response code: %d", resp_code);
	//std::cout << r;
    result = UrlEncode(result);
	LogInfo("resp: %s", result.c_str());
    up += 6000000;
    down += 3000000;
    LogInfo("sleep 60s...\n");
    sleep(60);
    }

#ifdef SCRAPE
    Bencode b(result);
    std::string ss;
    char * sd = (char*)t.info_hash;
    ss.assign(sd, 20);
    std::map<std::string, Any> qqq = any_cast<std::map<std::string, Any> >(b.inter_obj);
    std::map<std::string, Any> www = any_cast<std::map<std::string, Any> >(qqq["files"]);
    std::map<std::string, Any> rrr = any_cast<std::map<std::string, Any> >(www[ss]);
    unsigned long long  eee = any_cast<unsigned long long>(rrr["downloaded"]);
    std::cout << "complete: " << eee;
#endif
	return 0;
}
