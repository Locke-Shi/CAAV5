#include <iostream>
using namespace std;

#include <string>

#include "tinystr.h"
#include "tinyxml.h"

int main()
{
	/*
	XML文件有标签 属性 元素
	读取文件内容根据标签
	*/
	cout<<"Start Read XML"<<endl;
	char* pFilename = "F:\\我的资料\\xml\\Test1.xml";
	TiXmlDocument doc(pFilename);    // 读入XML文件
	if(!doc.LoadFile()) return -1;  // 如果无法读取文件，则返回
	TiXmlHandle hDoc(&doc);         // hDoc是&doc指向的对象
	TiXmlElement* pElem;            // 指向元素的指针
	pElem = hDoc.FirstChildElement().Element(); //指向根节点
	TiXmlHandle hRoot(pElem);       // hRoot是根节点
	
	cout<<"id = "<<pElem->Attribute("id")<<endl;//用于查询字符串属性
	cout<<"iid = "<<pElem->Attribute("iid")<<endl;

	// 读取x,y，它们放在network->nodes->node节点中
	TiXmlElement* nodeElem = hRoot.FirstChild("Name").Element(); //当前指向了node节点
	cout<<"Name = "<<nodeElem->GetText()<<endl;
	nodeElem = hRoot.FirstChild("Year").Element(); //当前指向了node节点 hRoot表示根节点  根据名字在根节点下获取到与名称相同的节点 然后获取信息
	cout<<"Year = "<<nodeElem->GetText()<<endl;
	nodeElem = hRoot.FirstChild("Month").Element(); //当前指向了node节点
	cout<<"Month = "<<nodeElem->GetText()<<endl;
	nodeElem = hRoot.FirstChild("Day").Element(); //当前指向了node节点
	cout<<"Day = "<<nodeElem->GetText()<<endl;
	
	nodeElem = hRoot.FirstChild("Name").Element()->NextSiblingElement()->NextSiblingElement(); //当前指向了Name节点的下一个节点 即Year
	cout<<"Day = "<<nodeElem->GetText()<<endl;
	/*
	TiXmlDocument：文件节点，把Xml文件的内容读入到该类型变量中
	TiXmlElement*：指向节点的指针
	TiXmlHandle：节点的实例，也就是TiXmlElement所指向的对象
	FirstChild("Name")：第一个名字为“Name”的子节点
	NextSiblingElement()：下一个兄弟节点元素，它们有相同的父节点
	QueryIntAttribute("attributeName", &var)：把节点属性名为attributeName的属性值以int类型赋值给var变量
	GetText()：获取当前节点元素的内容，即包含在<node>text</node>中的text
	*/
	return 0;
}