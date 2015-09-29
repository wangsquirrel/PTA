#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stdio.h>  

#include "Bencode.h"
#include "sha1.h"
#include "Torrent.h"
#include "HttpSender.h"
#include "utils.h"

int main(int argc, char** argv) {

	//std::map<std::string, Any> va = any_cast<std::map<std::string, Any> >(b.inter_obj);
	//std::cout<<   any_cast<std::string>(    va[std::string("created by")]     ); 
	
	Torrent t("single-file.torrent");

	std::cout<<ToHexString(t.info_hash, 20, "")<<std::endl;;
	std::cout<<t.length<<std::endl;
	HttpSender hs;
	std::string result;
	return 0;
}
