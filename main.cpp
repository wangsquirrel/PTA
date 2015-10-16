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
#include "TorrentController.h"
#include "TokenBucket.h"

int main(int argc, char** argv) {

    //TorrentController tc;
    TokenBucket tb(400000000000, 50000000000);
    while (1)
    {
    std::cout << "get "<<tb.get_token(50000000000);
    std::cout<< " token "<<tb.tokens<<std::endl;
    sleep(3);
    }

    //ConfigFile c("pta.conf");
    //if (c.load())   c.PrintConfig();
    //tc.run();    

#ifdef SCRAPE
    //req_str = req_str + replace_all(t.tracker, "announce", "scrape") + "&info_hash=" + UrlEncode(t.info_hash, 20);

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
