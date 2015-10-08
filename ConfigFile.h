#include <string>
#include <iostream>
#include <fstream>
#include <map>
#define COMMENT_CHAR '#'
class ConfigFile
{
public:
    ConfigFile(std::string fname) : file_name(fname) {}
    bool load();
    std::map<std::string, std::string> get() { return m; }
    void PrintConfig();

private:
    std::map<std::string, std::string> m;
    std::string file_name;
    bool IsSpace(char c);
    bool IsCommentChar(char c);
    void Trim(std::string & str);
    bool AnalyseLine(const std::string & line,std::string & key,std::string & value);
};

	
