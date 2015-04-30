#ifndef __XMLPARSER_H__
#define __XMLPARSER_H__

#include "cocos2d.h"
USING_NS_CC;

class XmlParser : public Ref, public SAXDelegator
{
public:
	static XmlParser *createWithFile(const char *fileName);
	bool initWithFile(const char *fileName);

	//SAXDelegator �������ص�����
	virtual void startElement(void *ctx, const char *name, const char **atts); //����һ����ʼ��ǩ����
	virtual void endElement(void *ctx, const char *name);	//����������ǩ�Ǵ���
	virtual void textHandler(void *ctx, const char *s, int len);	//�����ַ���ʱ����

private:
	CC_SYNTHESIZE(ValueVector, list, List); //����������������
	
	std::string startElementName; //��¼��ǩ
	ValueMap row;

};
#endif