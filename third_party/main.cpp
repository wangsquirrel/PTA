#include <iostream>
#include "tinyxml.h"
#include "tinystr.h"
#include "xpath_static.h"
#include "xpath_processor.h"
#include <string>

using namespace std;
using namespace TinyXPath;

void ReadXmlFile(string& szFileName)
{
	//读取Xml文件，并遍历。
	
    //创建一个XML的文档对象。
    TiXmlDocument *myDocument = new TiXmlDocument(szFileName.c_str());
    myDocument->LoadFile();

	//获得根元素，即definitions。
	TiXmlElement *RootElement = myDocument->RootElement();

	int types_num = i_xpath_int(RootElement,"count(//a)");//types元素个数。
	std::cout<<types_num<<std::endl;
	string oper_name = XAp_xpath_attribute(RootElement,"/a/x/@target")->Value();
	cout<<oper_name<<endl;
	string a;
	cout<<a.assign(S_xpath_string (RootElement, "a/text()").c_str());
	/*
	int mess_num = i_xpath_int(RootElement,"count(//message)");//message元素个数。
	int port_num = i_xpath_int(RootElement,"count(/definitions/portType)");//portType元素个数。
	int elem_num = i_xpath_int(RootElement,"count(//types/schema/element[2]/complexType/all/element)");//element元素个数。

	//获取第一个operation的name属性值。
	string oper_name = XAp_xpath_attribute(RootElement,"/definitions/portType/operation/@name")->Value();
	cout<<oper_name<<endl;

	//获取第一个operation的input节点的message属性值。
	string inputMess_name = XAp_xpath_attribute(RootElement,"/definitions/portType/operation/input/@message")->Value();
	inputMess_name = inputMess_name.substr(4);
	cout<<inputMess_name<<endl;

	//到所有message元素中去找name属性与inputMess_name相等的message元素。
	for(int i=1; i<mess_num+1; i++)
	{
		string mess_name = XAp_xpath_attribute(RootElement,"/definitions/message[2]/@name")->Value();//message元素中去找name属性
		cout<<mess_name<<endl;
		if(inputMess_name.compare(mess_name)==0)
		{
			//获得message元素子元素part的element属性值。
			string elem_name = XAp_xpath_attribute(RootElement,"/definitions/message[i]/part/@element")->Value();//???此处不能使用变量i,该怎么办？
			cout<<elem_name<<endl;
			return;
		}	}

	//获取第一个operation的output节点的message属性值。
	string outputMess_name = XAp_xpath_attribute(RootElement,"/definitions/portType/operation/output/@message")->Value();
	outputMess_name = outputMess_name.substr(4);
	cout<<outputMess_name<<endl;
	*/
}

int main()
{
	string fileName = "./test.xml";
    ReadXmlFile(fileName);
}


