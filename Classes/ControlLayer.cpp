#include "ControlLayer.h"
#include "UsingFileUtils.h"

Scene *ContentLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = ContentLayer::create();
	scene->addChild(layer);
	return scene;
}

bool ContentLayer::init()
{
	if (!Layer::init())
		return false;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	auto pItmLabel1 = Label::createWithBMFont("fonts/fnt8.fnt", "ControlExtensionTest");
	auto pItmMenu1 = MenuItemLabel::create(pItmLabel1, CC_CALLBACK_1(ContentLayer::onClickMenu1, this));

	auto pItmLabel2 = Label::createWithBMFont("fonts/fnt8.fnt", "DataTest");
	auto pItmMenu2 = MenuItemLabel::create(pItmLabel2, CC_CALLBACK_1(ContentLayer::onClickMenu2, this));

	Menu* mn = Menu::create(pItmMenu1, pItmMenu2, NULL);
	mn->alignItemsVertically();
	this->addChild(mn);

	return true;
}

void ContentLayer::onClickMenu1(Ref *pSender)
{
	//Director::getInstance()->replaceScene();
}

void ContentLayer::onClickMenu2(Ref *pSender)
{
	Director::getInstance()->replaceScene(UsingFileUtils::createScene());
}