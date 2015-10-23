#include <iostream>
#include <stdio.h>  
#include <time.h>
#include <unistd.h>
#include <signal.h>

#include "Bencode.h"
#include "sha1.h"
#include "Torrent.h"
#include "HttpSender.h"
#include "utils.h"
#include "ConfigFile.h"
#include "Logger.hpp"
#include "TorrentController.h"
#include "Global.h"

void stop(int signo)
{
    Global::allow_running = false;
}
int main(int argc, char** argv) {

    ConfigFile c("pta.conf");
    if (c.load())   
        //c.PrintConfig();
    Global::total_speed = strtoull(c.get("total_speed").c_str(), NULL, 10);
    Global::torrent_speed = strtoull(c.get("torrent_speed").c_str(), NULL, 10);
    Global::sleep_time = strtoull(c.get("sleep_time").c_str(), NULL, 10);
    Global::torrent_dir = c.get("torrent_dir");
    LogInfo("%s", Global::torrent_dir.c_str());

    TorrentController tc;
    signal(SIGINT, stop);
    tc.run();    

	return 0;
}
