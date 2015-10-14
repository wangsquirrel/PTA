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

int main(int argc, char** argv) {

    TorrentController tc;

    std::vector<std::string> filenames;
    std::string torrent_dir = "./torrents/";
    read_dir(torrent_dir.c_str(), filenames);
    std::vector<Torrent> torrent_list;
    for (auto i : filenames)
        torrent_list.push_back(Torrent(torrent_dir + i));
        
    //ConfigFile c("pta.conf");
    //if (c.load())   c.PrintConfig();
    for (auto t : torrent_list)
    {

	LogInfo("info hash: %s", UrlEncode(t.info_hash, 20).c_str());
	LogInfo("file length: %llu", t.length);
	LogInfo("file  name : %s", t.name.c_str());
	LogInfo("scrapble : %s", (t.scrapable() ? "yes":"no"));
    }

    
    while (true)
    {

    for (auto &t : torrent_list)
    {
        std::string result;
	
        tc.commit(t, result);
        tc.update_torrent(t, result);
        std::cout<<"~~~"<<t.interval<<"\n";
        std::cout<<"~~~"<<t.min_interval<<"\n";
        std::cout<<"~~~"<<t.complete<<"\n";
        std::cout<<"~~~"<<t.incomplete<<"\n";
        result.clear();

    //req_str = req_str + replace_all(t.tracker, "announce", "scrape") + "&info_hash=" + UrlEncode(t.info_hash, 20);
    }
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
