#include "Torrent.h"
#include "utils.h"
#include "HttpSender.h"
#include "Logger.hpp"
#include "Bencode.h"
#include "Any.h"
class TorrentController
{
public:

    std::vector<Torrent> torrent_list;
    HttpSender hs;
	std::vector<std::string> headers;
    int commit(Torrent &t, std::string& resp_str);
    int update_torrent(Torrent &t, std::string& resp_str);
    TorrentController();
};
