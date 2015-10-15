#include <string>
#include <memory>
#include <vector>
#include "utils.h"

#ifndef TORRENT_H
#define TORRENT_H
class Torrent
{
public:
    //Torrent name
	std::string name;
	unsigned char info_hash[20];
	unsigned long long length;
	std::string tracker;
    unsigned long long total_upload;
    unsigned long long total_download;
    std::string event;
    unsigned long long interval;
    unsigned long long min_interval;
    unsigned long long complete;
    unsigned long long incomplete;
	Torrent(std::string file_name);
	bool scrapable();
    std::string make_req_str();
};


#endif
