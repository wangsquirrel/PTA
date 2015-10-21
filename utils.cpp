#include "utils.h"

/*
 * convert a char vector to a '%' joined HEX string
*/
std::string ToHexString(const uint8_t* buf, int len, std::string tok = "")  
{  
    std::string output;  
	char temp[8];  
	for (int i = 0; i < len; ++i)  
	{
		sprintf(temp,"%%%.2X",(uint8_t)buf[i]);  
		output.append(temp,3);  
		output.append(tok);  
	} 
	return output;
}
std::string & replace_all(std::string& str,const std::string& old_value,const std::string& new_value)     
{     
    for(std::string::size_type pos(0); pos!=std::string::npos; pos += new_value.length())
    {     
        if ((pos=str.find(old_value,pos)) != std::string::npos)     
            str.replace(pos,old_value.length(),new_value);     
        else
            break;     
    }
    return str;     
}     


unsigned char ToHex(unsigned char x) 
{ 
    return  x > 9 ? x + 55 : x + 48; 
}

unsigned char FromHex(unsigned char x) 
{ 
    unsigned char y;
    if (x >= 'A' && x <= 'Z') y = x - 'A' + 10;
    else if (x >= 'a' && x <= 'z') y = x - 'a' + 10;
    else if (x >= '0' && x <= '9') y = x - '0';
    else assert(0);
    return y;
}

std::string UrlEncode(const std::string& str)
{
    std::string strTemp = "";
    size_t length = str.length();
    for (size_t i = 0; i < length; i++)
    {
        if (isalnum((unsigned char)str[i]) || 
            (str[i] == '-') ||
            (str[i] == '_') || 
            (str[i] == '.') || 
            (str[i] == '~'))
            strTemp += str[i];
        else if (str[i] == ' ')
            strTemp += "+";
        else
        {
            strTemp += '%';
            strTemp += ToHex((unsigned char)str[i] >> 4);
            strTemp += ToHex((unsigned char)str[i] % 16);
        }
    }
    return strTemp;
}
std::string UrlEncode(unsigned char * t, int len)
{
    std::string s;
    //can not use string constructor, in case of %00
    s.assign((char *)t, len);
    return UrlEncode(s);
}

std::string UrlDecode(const std::string& str)
{
    std::string strTemp = "";
    size_t length = str.length();
    for (size_t i = 0; i < length; i++)
    {
        if (str[i] == '+') strTemp += ' ';
        else if (str[i] == '%')
        {
            assert(i + 2 < length);
            unsigned char high = FromHex((unsigned char)str[++i]);
            unsigned char low = FromHex((unsigned char)str[++i]);
            strTemp += high*16 + low;
        }
        else strTemp += str[i];
    }
    return strTemp;
}

int read_dir(const char * dirname, std::vector<std::string> &vs)
{
    DIR *dir;
    struct dirent *ptr;
    struct stat st;
    if ((dir = opendir(dirname)) == NULL)
    {
        LogError("Torrent dirctory does not exist");
        return 1;
    }
    while((ptr = readdir(dir)) != NULL)
    {
        stat(ptr->d_name, &st);
        if (!S_ISDIR(st.st_mode))
            if (std::string(ptr->d_name).find(".torrent") != std::string::npos)
                vs.push_back(std::string(ptr->d_name));
    }
    closedir(dir); 
    return 0;
}

std::string human_size(unsigned long long size)
{
    char *result = (char *) malloc(sizeof(char) * 20);
    static int GB = 1024 * 1024 * 1024;
    static int MB = 1024 * 1024;
    static int KB = 1024;
    if (size >= GB) {
      if (size % GB == 0)
        sprintf(result, "%d GB", size / GB);
      else
        sprintf(result, "%.1f GB", (float) size / GB);
    }
    else if (size >= MB) {
      if (size % MB == 0)
        sprintf(result, "%d MB", size / MB);
      else
        sprintf(result, "%.1f MB", (float) size / MB);
    }
    else {
      if (size == 0) {
        result[0] = '0';
        result[1] = '\0';
      }
      else {
        if (size % KB == 0)
          sprintf(result, "%d KB", size / KB);
        else
          sprintf(result, "%.1f KB", (float) size / KB);
      }
    }
    std::string r(result);
    free(result);
  
    return r;
}
  
