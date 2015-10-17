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
    std::cout<<"~~~~~~~~~"<<std::endl;
    std::map<std::string, Any> msa = any_cast<std::map<std::string, Any> >(b.inter_obj);
    t.interval = any_cast<unsigned long long>(msa["interval"]);
    t.min_interval = any_cast<unsigned long long>(msa["min interval"]);
    t.complete = any_cast<unsigned long long>(msa["complete"]);
    t.incomplete = any_cast<unsigned long long>(msa["incomplete"]);
	t.last_commit = time(NULL);
	t.event = "noevent";
	LogInfo("last commit : %d", t.last_commit);
    return 0;
}

TorrentController::TorrentController() : tb(12 * 3 * 1000 * 1000, 3 * 1000 * 10000)
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
	    LogInfo("file length: %llu", t.length);
	    LogInfo("file  name : %s", t.name.c_str());
	    LogInfo("scrapble : %s", (t.scrapable() ? "yes":"no"));
    }
    return 0;
}

void TorrentController::run()
{
    int r = get_torrents();
    while (true)
    {
        for (auto &t : torrent_list)
        {
			printf("aaaaaa %lf\n",difftime(time(NULL), t.last_commit));
			if (difftime(time(NULL), t.last_commit) < 9)
			    continue;
            std::string result;
            unsigned long long the = tb.get_token(6000000 * 10);
            std::cout << "this time : "<<the<<std::endl;
            std::cout << "tokens : "<<tb.tokens<<std::endl;
			t.total_upload += the;
            commit(t, result);
            update_torrent(t, result);
            std::cout<<"~~~"<<t.interval<<"\n";
            std::cout<<"~~~"<<t.min_interval<<"\n";
            std::cout<<"~~~"<<t.complete<<"\n";
            std::cout<<"~~~"<<t.incomplete<<"\n";
            result.clear();
        }
        LogInfo("sleep 60s...\n");
        sleep(10);
    
    }
}
