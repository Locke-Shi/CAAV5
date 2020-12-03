#include <iostream>
using namespace std;

#include <string>

#include "tinystr.h"
#include "tinyxml.h"

int main()
{
	/*
	XML�ļ��б�ǩ ���� Ԫ��
	��ȡ�ļ����ݸ��ݱ�ǩ
	*/
	cout<<"Start Read XML"<<endl;
	char* pFilename = "F:\\�ҵ�����\\xml\\Test1.xml";
	TiXmlDocument doc(pFilename);    // ����XML�ļ�
	if(!doc.LoadFile()) return -1;  // ����޷���ȡ�ļ����򷵻�
	TiXmlHandle hDoc(&doc);         // hDoc��&docָ��Ķ���
	TiXmlElement* pElem;            // ָ��Ԫ�ص�ָ��
	pElem = hDoc.FirstChildElement().Element(); //ָ����ڵ�
	TiXmlHandle hRoot(pElem);       // hRoot�Ǹ��ڵ�
	
	cout<<"id = "<<pElem->Attribute("id")<<endl;//���ڲ�ѯ�ַ�������
	cout<<"iid = "<<pElem->Attribute("iid")<<endl;

	// ��ȡx,y�����Ƿ���network->nodes->node�ڵ���
	TiXmlElement* nodeElem = hRoot.FirstChild("Name").Element(); //��ǰָ����node�ڵ�
	cout<<"Name = "<<nodeElem->GetText()<<endl;
	nodeElem = hRoot.FirstChild("Year").Element(); //��ǰָ����node�ڵ� hRoot��ʾ���ڵ�  ���������ڸ��ڵ��»�ȡ����������ͬ�Ľڵ� Ȼ���ȡ��Ϣ
	cout<<"Year = "<<nodeElem->GetText()<<endl;
	nodeElem = hRoot.FirstChild("Month").Element(); //��ǰָ����node�ڵ�
	cout<<"Month = "<<nodeElem->GetText()<<endl;
	nodeElem = hRoot.FirstChild("Day").Element(); //��ǰָ����node�ڵ�
	cout<<"Day = "<<nodeElem->GetText()<<endl;
	
	nodeElem = hRoot.FirstChild("Name").Element()->NextSiblingElement()->NextSiblingElement(); //��ǰָ����Name�ڵ����һ���ڵ� ��Year
	cout<<"Day = "<<nodeElem->GetText()<<endl;
	/*
	TiXmlDocument���ļ��ڵ㣬��Xml�ļ������ݶ��뵽�����ͱ�����
	TiXmlElement*��ָ��ڵ��ָ��
	TiXmlHandle���ڵ��ʵ����Ҳ����TiXmlElement��ָ��Ķ���
	FirstChild("Name")����һ������Ϊ��Name�����ӽڵ�
	NextSiblingElement()����һ���ֵܽڵ�Ԫ�أ���������ͬ�ĸ��ڵ�
	QueryIntAttribute("attributeName", &var)���ѽڵ�������ΪattributeName������ֵ��int���͸�ֵ��var����
	GetText()����ȡ��ǰ�ڵ�Ԫ�ص����ݣ���������<node>text</node>�е�text
	*/
	return 0;
}