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

	void onClickMenu1(Ref *pSender); //������ԴĿ¼��Ϣ
	void onClickMenu2(Ref *pSender); //���Կ�дĿ¼��Ϣ
	void onClickMenu3(Ref *pSender); //���ļ�
	void onClickMenu4(Ref *pSender); //д�ļ�
	void onClickMenu5(Ref *pSender);  //ʹ��UserDefaultʵ��
	void onClickMenu6(Ref *pSender);  //ʹ��SAX����XML�ĵ�
	void onClickMenu7(Ref *pSender); //ʹ��DOM����XML�ĵ�
private:

};
#endif