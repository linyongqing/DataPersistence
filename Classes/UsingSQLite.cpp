#include "UsingSQLite.h"
#include "NoteDAO.h"
#include "MyUtility.h"

Scene *UsingSQLite::createScene()
{
	Scene *scene = Scene::create();
	Layer *layer = UsingSQLite::create();
	scene->addChild(layer);
	return scene;
}

bool UsingSQLite::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	auto pItmLabel1 = Label::createWithBMFont("fonts/fnt8.fnt", "Init DB");
	auto pItmMenu1 = MenuItemLabel::create(pItmLabel1, CC_CALLBACK_1(UsingSQLite::OnClickMenu1, this));

	auto pItmLabel2 = Label::createWithBMFont("fonts/fnt8.fnt", "Insert Data");
	auto pItmMenu2 = MenuItemLabel::create(pItmLabel2, CC_CALLBACK_1(UsingSQLite::OnClickMenu2, this));

	auto pItmLabel3 = Label::createWithBMFont("fonts/fnt8.fnt", "Delete Data");
	auto pItmMenu3 = MenuItemLabel::create(pItmLabel3, CC_CALLBACK_1(UsingSQLite::OnClickMenu3, this));

	auto pItmLabel4 = Label::createWithBMFont("fonts/fnt8.fnt", "Update Data");
	auto pItmMenu4 = MenuItemLabel::create(pItmLabel4, CC_CALLBACK_1(UsingSQLite::OnClickMenu4, this));

	auto pItmLabel5 = Label::createWithBMFont("fonts/fnt8.fnt", "Read Data");
	auto pItmMenu5 = MenuItemLabel::create(pItmLabel5, CC_CALLBACK_1(UsingSQLite::OnClickMenu5, this));

	Menu* mn = Menu::create(pItmMenu1, pItmMenu2, pItmMenu3, pItmMenu4, pItmMenu5, NULL);
	mn->alignItemsVertically();
	this->addChild(mn);

	return true;
}

void UsingSQLite::OnClickMenu1(Ref *pSender)
{
	NoteDAO::initDB();
	NoteDAO::create("2015-4-22", "初始化数据");
}

void UsingSQLite::OnClickMenu2(Ref *pSender)
{
	NoteDAO::create("2015-4-22", "初始化数据");
}

void UsingSQLite::OnClickMenu3(Ref *pSender)
{
	NoteDAO::remove("2015-4-22");
}

void UsingSQLite::OnClickMenu4(Ref *pSender)
{
	NoteDAO::modeify("2015-4-22", "this is today");
}

void UsingSQLite::OnClickMenu5(Ref *pSender)
{
	auto arry = NoteDAO::findAll();
	for (auto& v : arry)
	{
		log("-----------------");
		ValueMap row = v.asValueMap();
		string date = row["date"].asString();
		string content = row["content"].asString();

		log("===>date: : %s", date.c_str());
		log("===>content: : %s", content.c_str());
	}
}