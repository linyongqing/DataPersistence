//SQLite π”√

#include "cocos2d.h"

USING_NS_CC;

class UsingSQLite : public Layer
{
public:
	static Scene *createScene();
	virtual bool init();
	CREATE_FUNC(UsingSQLite);

	//Init DB
	void OnClickMenu1(cocos2d::Ref* pSender);
	//Insert Data
	void OnClickMenu2(cocos2d::Ref* pSender);
	//Delete Data
	void OnClickMenu3(cocos2d::Ref* pSender);
	//Update Data
	void OnClickMenu4(cocos2d::Ref* pSender);
	//Read Data
	void OnClickMenu5(cocos2d::Ref* pSender);
};