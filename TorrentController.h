#include "Torrent.h"
#include "utils.h"
#include "HttpSender.h"
#include "Logger.hpp"
#include "Bencode.h"
#include "Any.h"
#include "TokenBucket.h"
#include "Global.h"

//global configure
extern Global global;
class TorrentController
{
public:

    std::vector<Torrent> torrent_list;
    HttpSender hs;
	std::vector<std::string> headers;
    TokenBucket tb;
    //commit http request and restore response in resp_str
    int commit(Torrent &t, std::string& resp_str);
    //update the information of a torrent according to its response
    int update_torrent(Torrent &t, std::string& resp_str);
    TorrentController();
    int get_torrents();
    void run();

    void stop();
};
