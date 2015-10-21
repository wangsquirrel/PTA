#include "TorrentController.h"

int TorrentController::commit(Torrent &t, std::string &resp_str)
{
    std::string req_str = t.make_req_str();
    LogInfo("Request string : %s", req_str.c_str());
	int resp_code = hs.Gets(req_str ,headers, resp_str);
	LogInfo("Curl response code: %d", resp_code);
	LogInfo("Response string: %s", resp_str.c_str());
	//LogInfo("Response string: %s", UrlEncode(resp_str).c_str());
    return resp_code;

}

int TorrentController::update_torrent(Torrent &t, std::string &resp_str)
{
    Bencode b(resp_str);
    if (b.is_empty())
        return 1;
    if (b.is_fail())
    {
        LogError("get -=fail reason=- error");
        return 1;
    }
    std::map<std::string, Any> msa = any_cast<std::map<std::string, Any> >(b.inter_obj);
    t.interval = any_cast<unsigned long long>(msa["interval"]);
    t.min_interval = any_cast<unsigned long long>(msa["min interval"]);
    t.complete = any_cast<unsigned long long>(msa["complete"]);
    t.incomplete = any_cast<unsigned long long>(msa["incomplete"]);
	t.last_commit = time(NULL);
	t.event = "noevent";
    return 0;
}

// normal interval is 2700, so we use 3000
// it may be not regorous!!!
TorrentController::TorrentController() : tb( 3000 * global.total_speed, global.total_speed)
{
    headers.push_back("User-Agent: uTorrent/2000(18934)");
}
int TorrentController::get_torrents()
{
    std::vector<std::string> filenames;
    std::string torrent_dir = "./torrents/";
    int c = read_dir(torrent_dir.c_str(), filenames);
    if (c != 0)
        return 1;
    for (auto i : filenames)
        torrent_list.push_back(Torrent(torrent_dir + i));
    for (auto t : torrent_list)
    {

    	LogInfo("info hash: %s", UrlEncode(t.info_hash, 20).c_str());
	    LogInfo("file length: %s", human_size(t.length).c_str());
	    LogInfo("file  name : %s", t.name.c_str());
	    LogInfo("scrapble : %s", (t.scrapable() ? "yes":"no"));
    }
    return 0;
}

void TorrentController::run()
{
    int r = get_torrents();
    if (r != 0)
    {
        LogInfo("Torrent directory open failed");
    }
    while (true)
    {
        //shuffle to be added
        for (auto &t : torrent_list)
        {
			printf("seconds until last commit :%ds...\n",int(difftime(time(NULL), t.last_commit)));
            if (!global.running)
            {
                stop();
            }
			if (difftime(time(NULL), t.last_commit) < t.interval)
            {
                std::cout<<"too soon try after 60s"<<std::endl;
			    continue;
            }
            std::string result;
            //when first time the token we want will be huge because last_time was init 0
            //it will be fine because of tokenbucket is init 0 and event:started's upload bytes will not be care
            //can be fix last_time init by time(NULL)
            unsigned long long the = tb.get_token(global.torrent_speed * 2 * int(difftime(time(NULL), t.last_commit)));
            std::cout << "get this time : "<<human_size(the)<<std::endl;
            std::cout << "left tokens : "<<human_size(tb.tokens)<<std::endl;
			t.total_upload += the;
            commit(t, result);
            update_torrent(t, result);
            result.clear();
        }
        LogInfo("sleep 60s...\n");
        sleep(60);
    
    }
}
void TorrentController::stop()
{
   for (auto &t : torrent_list)
   {
       std::string result;
       t.event="stopped";
       commit(t, result);
       LogInfo("Stop response : %s", result.c_str());
   }
   LogInfo("The program is stopped gracefully~~~");
   exit(0);
}
