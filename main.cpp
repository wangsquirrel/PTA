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

Global global;
void stop(int signo)
{
    global.running = 0;
}
int main(int argc, char** argv) {

    ConfigFile c("pta.conf");
    if (c.load())   
        //c.PrintConfig();
    global.total_speed = strtoull(c.get("total_speed").c_str(), NULL, 10);
    global.torrent_speed = strtoull(c.get("torrent_speed").c_str(), NULL, 10);
    TorrentController tc;
    signal(SIGINT, stop);
    tc.run();    

	return 0;
}
