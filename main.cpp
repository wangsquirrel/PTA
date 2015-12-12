#include "HttpSender.h"

#include<string>
#include<iostream>
#include<vector>
#include <xpath_static.h>
#include <htmlutil.h>
#include<fstream>
using namespace std;
using namespace TinyXPath;

int main()
{
	HttpSender hs;
	vector<string> headers;
	string resp;
	ofstream of("test.txt", ios::out);
	int code = hs.Get("http://www.baidu.com", headers, resp);


	cout << resp;
	of << resp;
	of.close();
    TiXmlDocument *myDocument = new TiXmlDocument("test.txt");
    myDocument->LoadFile();
     //获得根元素，即definitions。
    TiXmlElement *RootElement = myDocument->RootElement();
/*
    int types_num = i_xpath_int(RootElement,"count(//a)");//types元素个数。
    std::cout<<types_num<<std::endl;
    string oper_name = XAp_xpath_attribute(RootElement,"/a/x/@target")->Value();
    cout<<oper_name<<endl;
*/
    string a;
    cout<<a.assign(S_xpath_string (RootElement, "//title/text()").c_str());


}

