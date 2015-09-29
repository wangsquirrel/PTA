#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <iterator>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdlib.h>  
#include <string.h>  
#include <stdio.h>  
#include <assert.h>  
#include <stdint.h>

#include "Bencode.h"
#include "sha1.h"
#include "Torrent.h"

std::string ToHexString(const uint8_t* buf,int len,std::string tok = "")  
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
int main(int argc, char** argv) {

	//std::map<std::string, Any> va = any_cast<std::map<std::string, Any> >(b.inter_obj);
	//std::cout<<   any_cast<std::string>(    va[std::string("created by")]     ); 
	
	Torrent t("single-file.torrent");

	std::cout<<ToHexString(t.info_hash, 20, "")<<std::endl;;
	std::cout<<t.length;

	/*
	
	//Bencode b("d3:efg3:efg3:abc3:abce");
	//std::cout<<b.dump();
	unsigned char p[6] = "aaaaa";
	unsigned char result[20] ={0};
	sha1(p,5,result);
	for (int i = 0; i < 20; i++)
         {
         	printf(" *%c* ", result[i]);
		 }
	//std::map<std::string, Any> va = any_cast<std::map<std::string, Any> >(b.inter_obj);
	//std::cout<<   any_cast<std::string>(    va[std::string("announce")]     );  
*/	
	return 0;
}
