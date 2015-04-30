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

	this->parset(); //开始解析
	return true;
}

void DomxmlParser::parset()
{
	tinyxml2::XMLDocument xmlDoc;  //声明tinyxml文档对象

	xmlDoc.Parse(content.c_str()); //开始解析XML文档
	tinyxml2::XMLElement *root = xmlDoc.RootElement(); //获取文档对象的根元素对象
	tinyxml2::XMLElement *note = root->FirstChildElement("Note"); //从根元素取出名字为Note的子元素

	while (note)
	{
		row = ValueMap();

		//取id属性
		const tinyxml2::XMLAttribute *att = note->FirstAttribute(); //取出note节点的第一个属性
		std::pair<std::string, Value> idPair("id", Value(att->Value())); //att->Value() 将属性值包装成Value类型

		row.insert(idPair);

		//取cDate元素内容 
		tinyxml2::XMLElement *dateElement = note->FirstChildElement("CDate");
		row["CDate"] = Value(dateElement->GetText());

		//取Content元素内容
		tinyxml2::XMLElement *contentElement = note->FirstChildElement("Content");
		row["Content"] = Value(dateElement->GetText());

		//取userID元素内容
		tinyxml2::XMLElement *userIDElement = note->FirstChildElement("UserID");
		row["UserID"] = Value(dateElement->GetText());

		list.push_back(Value(row));
		if (note->NextSibling() == nullptr)
			break;
		else note = note->NextSibling()->ToElement(); //note->NextSibling()获取下一个兄弟节点
		//note->NextSibling()->ToElement() 返回XMLElment *类型
	}
}