#ifndef __CONTROL_H__
#define __CONTROL_H__

#include "cocos2d.h"
USING_NS_CC;

class ContentLayer : public Layer
{
public:
	static Scene *createScene();
	virtual bool init();
	CREATE_FUNC(ContentLayer);

	void onClickMenu1(Ref *pSender); //ControlExtension
	void onClickMenu2(Ref *pSender); //Êý¾Ý
	
private:

};
#endif