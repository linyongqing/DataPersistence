#ifndef __DOM_XMLPARSER_H__
#define __DOM_XMLPARSER_H_

#include "tinyxml2.h"
#include "cocos2d.h"

USING_NS_CC;

class DomxmlParser : public cocos2d::Ref
{
private:
	CC_SYNTHESIZE(cocos2d::ValueVector, list, List);
	cocos2d::ValueMap row;
	std::string content;  //XML ÄÚÈÝ
	void parset();

public:
	static DomxmlParser* createWithFile(const char *fileName);
	bool initWithFile(const char *xmlName);
};
#endif