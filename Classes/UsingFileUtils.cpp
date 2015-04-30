#include "UsingFileUtils.h"
#include "UsingSQLite.h"
#include "XMLParser.h"
#include "DOMXMLParser.h"

Scene *UsingFileUtils::createScene()
{
	Scene *scene = Scene::create();
	Layer *layer = UsingFileUtils::create();
	scene->addChild(layer);
	return scene;
}


bool UsingFileUtils::init()
{
	if (!Layer::init())
		return false;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	auto pItmLabel1 = Label::createWithBMFont("fonts/fnt8.fnt", "Test ResourcesDir Info");
	auto pItmMenu1 = MenuItemLabel::create(pItmLabel1, CC_CALLBACK_1(UsingFileUtils::onClickMenu1, this));

	auto pItmLabel2 = Label::createWithBMFont("fonts/fnt8.fnt", "Test WritablePath Info");
	auto pItmMenu2 = MenuItemLabel::create(pItmLabel2, CC_CALLBACK_1(UsingFileUtils::onClickMenu2, this));

	auto pItmLabel3 = Label::createWithBMFont("fonts/fnt8.fnt", "Read File");
	auto pItmMenu3 = MenuItemLabel::create(pItmLabel3, CC_CALLBACK_1(UsingFileUtils::onClickMenu3, this));

	auto pItmLabel4 = Label::createWithBMFont("fonts/fnt8.fnt", "Write File");
	auto pItmMenu4 = MenuItemLabel::create(pItmLabel4, CC_CALLBACK_1(UsingFileUtils::onClickMenu4, this));

	auto pItmLabel5 = Label::createWithBMFont("fonts/fnt8.fnt", "Using SQLite");
	auto pItmMenu5 = MenuItemLabel::create(pItmLabel5, CC_CALLBACK_1(UsingFileUtils::onClickMenu5, this));

	auto pItmLabel6 = Label::createWithBMFont("fonts/fnt8.fnt", "USING SAX Parsing XMLData");
	auto pItmMenu6 = MenuItemLabel::create(pItmLabel6, CC_CALLBACK_1(UsingFileUtils::onClickMenu6, this));

	auto pItmLabel7 = Label::createWithBMFont("fonts/fnt8.fnt", "USING DOM Parsing XMLData");
	auto pItmMenu7 = MenuItemLabel::create(pItmLabel7, CC_CALLBACK_1(UsingFileUtils::onClickMenu7, this));

	Menu* mn = Menu::create(pItmMenu1, pItmMenu2, pItmMenu3, pItmMenu4, pItmMenu5, pItmMenu6, pItmMenu7, NULL);
	mn->alignItemsVertically();
	this->addChild(mn);
	return true;
}


void UsingFileUtils::onClickMenu1(Ref *pSender)
{
	FileUtils *pShareFileUtils = FileUtils::getInstance();
	std::string fullPathForFileName = pShareFileUtils->fullPathForFilename("test.txt"); //访问目录
	log("fullPathForFileName Path = %s", fullPathForFileName.c_str());

	bool isExist = false;
	isExist = pShareFileUtils->isFileExist("test.txt");  //判断文件是否存在
	log("%s", isExist ? "test.txt exists" : "test.txt doesn't exist");
}

void UsingFileUtils::onClickMenu2(Ref *pSender)
{
	FileUtils *pShareFileUtils = FileUtils::getInstance();
	std::string writablePath = pShareFileUtils->getWritablePath(); //获取可写路径
	log("writablePath = %s", writablePath.c_str());
}

void UsingFileUtils::onClickMenu3(Ref *pSender)
{
	FileUtils *pShareFileUtile = FileUtils::getInstance();
	std::string writablePath = pShareFileUtile->getWritablePath();
	std::string fileName = writablePath + "test.txt";
	log("fullPathForFileName Path = %s", fileName.c_str());

	Data data = pShareFileUtile->getDataFromFile(fileName);
	//从data构建string
	std::string content1 = std::string((const char*)data.getBytes(), 0, data.getSize());
	log("content1 : %s", content1.c_str());

	std::string content2 = pShareFileUtile->getStringFromFile(fileName);
	log("content2 : %s", content2.c_str());
}

void UsingFileUtils::onClickMenu4(Ref *pSender)
{
	FileUtils *pShareFileUtile = FileUtils::getInstance();
	std::string writablePath = pShareFileUtile->getWritablePath();
	std::string fileName = writablePath + "test.txt";
	log("writablePath = %s", writablePath.c_str());

	char szBuf[100] = "Testing Write to file."; 
	FILE *fp = fopen(fileName.c_str(), "wb"); //打开一个文件
	if (fp)
	{
		//向一个文件中写入数据
		size_t ret = fwrite(szBuf, 1, strlen(szBuf), fp);
		fclose(fp);  //关闭文件
		if (ret != 0)
			log("Writing file to  path succeed.");
	}
}

void UsingFileUtils::onClickMenu5(Ref *pSender)
{
	Director::getInstance()->replaceScene(UsingSQLite::createScene());
}

void UsingFileUtils::onClickMenu6(Ref *pSender)
{
	auto parser = XmlParser::createWithFile("Notes.xml");

	auto list = parser->getList();
	int index = 0;
	for (auto& v : list)
	{
		log("---------------- [%d] -------------------", ++index);
		ValueMap row = v.asValueMap();
		for (auto& pair : row)
		{
			log("===> %s = %s", pair.first.c_str(), pair.second.asString().c_str());
		}
	}
}

void UsingFileUtils::onClickMenu7(Ref *pSender)
{
	auto parser = DomxmlParser::createWithFile("Notes.xml");

	auto list = parser->getList();
	int index = 0;
	for (auto& v : list)
	{
		log("---------------- [%d] -------------------", ++index);
		ValueMap row = v.asValueMap();
		for (auto& pair : row)
		{
			log("===> %s = %s", pair.first.c_str(), pair.second.asString().c_str());
		}
	}
}


