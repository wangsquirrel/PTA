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
    std::map<std::string, Any> msa = any_cast<std::map<std::string, Any> >(b.inter_obj);
    t.interval = any_cast<unsigned long long>(msa["interval"]);
    t.min_interval = any_cast<unsigned long long>(msa["min interval"]);
    t.complete = any_cast<unsigned long long>(msa["complete"]);
    t.incomplete = any_cast<unsigned long long>(msa["incomplete"]);
    return 0;
}

TorrentController::TorrentController()
{
    headers.push_back("User-Agent: uTorrent/2000(18934)");
}

