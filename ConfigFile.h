#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#define COMMENT_CHAR '#'
class ConfigFile
{
public:
    ConfigFile(std::string fname) : file_name(fname) {}
    bool load();
    std::string get(std::string first) { return m[first]; }
    void PrintConfig();

private:
    //An object to save configure items
    std::map<std::string, std::string> m;
    std::string file_name;
    bool IsSpace(char c);
    bool IsCommentChar(char c);
    void Trim(std::string & str);
    bool AnalyseLine(const std::string & line,std::string & key,std::string & value);
};

	
