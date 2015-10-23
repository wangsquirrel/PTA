#ifndef GLOBAL_H
#define GLOBAL_H
#include <string>
class Global
{
public:
    static unsigned long long total_speed;
    static unsigned long long torrent_speed;
    static unsigned long long sleep_time;
    static bool allow_running ;
    static std::string torrent_dir;
};

#endif
