#include "DOMXMLParser.h"

DomxmlParser *DomxmlParser::createWithFile(const char *fileName)
{
	DomxmlParser *pRet = new DomxmlParser();
	if (pRet && pRet->initWithFile(fileName))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return nullptr;
}

bool DomxmlParser::initWithFile(const char *xmlName)
{
	FileUtils *pFileUtils = FileUtils::getInstance();
	std::string path = pFileUtils->fullPathForFilename(xmlName);

	Data data = pFileUtils->getDataFromFile(path);
	content = std::string((const char*)data.getBytes(), 0, data.getSize());
	log("content = %s", content.c_str());

	this->parset(); //��ʼ����
	return true;
}

void DomxmlParser::parset()
{
	tinyxml2::XMLDocument xmlDoc;  //����tinyxml�ĵ�����

	xmlDoc.Parse(content.c_str()); //��ʼ����XML�ĵ�
	tinyxml2::XMLElement *root = xmlDoc.RootElement(); //��ȡ�ĵ�����ĸ�Ԫ�ض���
	tinyxml2::XMLElement *note = root->FirstChildElement("Note"); //�Ӹ�Ԫ��ȡ������ΪNote����Ԫ��

	while (note)
	{
		row = ValueMap();

		//ȡid����
		const tinyxml2::XMLAttribute *att = note->FirstAttribute(); //ȡ��note�ڵ�ĵ�һ������
		std::pair<std::string, Value> idPair("id", Value(att->Value())); //att->Value() ������ֵ��װ��Value����

		row.insert(idPair);

		//ȡcDateԪ������ 
		tinyxml2::XMLElement *dateElement = note->FirstChildElement("CDate");
		row["CDate"] = Value(dateElement->GetText());

		//ȡContentԪ������
		tinyxml2::XMLElement *contentElement = note->FirstChildElement("Content");
		row["Content"] = Value(dateElement->GetText());

		//ȡuserIDԪ������
		tinyxml2::XMLElement *userIDElement = note->FirstChildElement("UserID");
		row["UserID"] = Value(dateElement->GetText());

		list.push_back(Value(row));
		if (note->NextSibling() == nullptr)
			break;
		else note = note->NextSibling()->ToElement(); //note->NextSibling()��ȡ��һ���ֵܽڵ�
		//note->NextSibling()->ToElement() ����XMLElment *����
	}
}