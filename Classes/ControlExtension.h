#ifndef __ControlExtension_H__
#define __ControlExtension_H__

#include "cocos2d.h"
USING_NS_CC;

class ControlExtension : public Layer
{
public:
	
	static Scene *createScene();
	virtual bool init();
	CREATE_FUNC(ControlExtension);

	void valueChanger(Ref *sender, Control::EventType type);
private:

};



#endif