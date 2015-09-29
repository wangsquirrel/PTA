#include <string>
#include <memory>
#include <vector>
class Torrent
{
public:
	std::string name;
	unsigned char info_hash[20];
	unsigned long long length;
	std::string tracker;
	Torrent(std::string file_name);
};

