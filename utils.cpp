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


