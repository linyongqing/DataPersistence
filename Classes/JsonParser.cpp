//#include "JsonParser.h"
//
//JsonParser *JsonParser::createWithFile(const char *fileName)
//{
//	JsonParser *pJsonParser = new JsonParser();
//	if (pJsonParser && pJsonParser->initWithFile(fileName))
//	{
//		pJsonParser->autorelease();
//		return pJsonParser;
//	}
//	CC_SAFE_DELETE(pJsonParser);
//	return nullptr; 
//}