#include <string>
#include <iostream>
#include <fstream>
#include <map>
#define COMMENT_CHAR '#'
class ConfigFile
{
public:
    std::string file_name;
    std::map<std::string, std::string> m;
    ConfigFile(std::string fname) : file_name(fname) {}
    bool load();
private:
    bool IsSpace(char c);
    bool IsCommentChar(char c);

    void Trim(std::string & str);
    bool AnalyseLine(const std::string & line,std::string & key,std::string & value);
public:
    void PrintConfig();
};

	
