#ifndef _DATAPERSISTENCE_USINGFILEUTILS_H__
#define _DATAPERSISTENCE_USINGFILEUTILS_H__

#include "cocos2d.h"
USING_NS_CC;

class UsingFileUtils : public Layer
{
public:
	static Scene *createScene();
	virtual bool init();
	CREATE_FUNC(UsingFileUtils);

	void onClickMenu1(Ref *pSender); //测试资源目录信息
	void onClickMenu2(Ref *pSender); //测试可写目录信息
	void onClickMenu3(Ref *pSender); //读文件
	void onClickMenu4(Ref *pSender); //写文件
	void onClickMenu5(Ref *pSender);  //使用UserDefault实例
	void onClickMenu6(Ref *pSender);  //使用SAX解析XML文档
	void onClickMenu7(Ref *pSender); //使用DOM解析XML文档
private:

};
#endif