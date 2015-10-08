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


