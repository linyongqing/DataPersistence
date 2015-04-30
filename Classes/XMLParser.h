#ifndef __XMLPARSER_H__
#define __XMLPARSER_H__

#include "cocos2d.h"
USING_NS_CC;

class XmlParser : public Ref, public SAXDelegator
{
public:
	static XmlParser *createWithFile(const char *fileName);
	bool initWithFile(const char *fileName);

	//SAXDelegator 的三个回调函数
	virtual void startElement(void *ctx, const char *name, const char **atts); //遇到一个开始标签触发
	virtual void endElement(void *ctx, const char *name);	//遇到结束标签是触发
	virtual void textHandler(void *ctx, const char *s, int len);	//遇到字符串时触发

private:
	CC_SYNTHESIZE(ValueVector, list, List); //声明返回数据属性
	
	std::string startElementName; //记录标签
	ValueMap row;

};
#endif