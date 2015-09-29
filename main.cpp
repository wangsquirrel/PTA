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
#include "HttpSender.h"

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
	HttpSender hs;
	std::string result;
	/*
	std::string s = ("https://hdbiger.org/announce.php?passkey=a67facee9cf7e0b7878ecb421ec3d7bc&info_hash=%DE%EE%F7%FB%90%8F%54%0D%BF%74%F4%BC%EC%5E%75%8D%E5%C8%38%10&peer_id=-UT2000-%1CD%E6%9B%E7%26%B02-%D5%CFz&port=11111&ipv6=i2001%3ada8%3a215%3a3f0%3a20c%3a29ff%3afee5%3a9276&uploaded=30000&downloaded=100000&left=0&numwant=0&compact=1&no_peer_id=1");
	//std::string s("http://www.baidu.com");
	std::vector<std::string> headers;
	headers.push_back("User-Agent: uTorrent/2000(18934)");
	int r = hs.Gets(s ,headers, result);
	std::cout << r;
	std::cout << result;
    return 0;
}

	
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
