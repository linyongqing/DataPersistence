#include "XMLParser.h"

XmlParser *XmlParser::createWithFile(const char *fileName)
{
	XmlParser *pXmlParser = new XmlParser();
	if (pXmlParser && pXmlParser->initWithFile(fileName))
	{
		pXmlParser->autorelease();
		return pXmlParser;
	}
	CC_SAFE_DELETE(pXmlParser);
	return nullptr;
}

bool XmlParser::initWithFile(const char *fileName)
{
	SAXParser parser;  //������������
	if (!parser.init("UTF_8")) //ʹ��UTF-8�����ʼ����������parser
	{
		log("please use utf-8 format");
		return false;
	}
	parser.setDelegator(this);  //����SAXParserί��Ϊ��ǰ����

	auto shareFileUtils = FileUtils::getInstance();
	std::string path = shareFileUtils->fullPathForFilename(fileName);
	return parser.parse(path); //ͨ��ָ����ʼ����XML�ĵ�
}

void XmlParser::startElement(void *ctx, const char *name, const char **atts)
{
	CC_UNUSED_PARAM(ctx);  //�ĺ���Բ�ʹ�õĲ������ڱ���ʱ�����о��� ctxʵ�ʾ��ǽ����Ķ���parser

	startElementName = (char *)name;
	if (startElementName == "Note")
	{
		row = ValueMap();
		for (int i = 0; atts[i]; i += 2)
		{
			std::string key = (char *)atts[i];
			std::string value = (char *)atts[i + 1];
			log("%s === %s", key.c_str(), value.c_str());
			std::pair<std::string, Value> pair(key, Value(value));
			row.insert(pair);
		}
	}
}

//�����ַ���ʱ�ص�
void XmlParser::textHandler(void *ctx, const char *s, int len)
{
	CC_UNUSED_PARAM(ctx);

	std::string currElementValue = std::string((char *)s, 0, len);
	log("%s == %s", startElementName.c_str(), currElementValue.c_str());
	std::pair<std::string, Value> pair(startElementName, Value(currElementValue));
	row.insert(pair);
}

void XmlParser::endElement(void *ctx, const char *name)
{
	CC_UNUSED_PARAM(ctx);

	std::string endElementName = (char *)name;
	if (endElementName == "Note")
	{
		list.push_back(Value(row));
	}
}