#include "ExceptionClasses.h"
#include "AdditionalFunc.h"
USING_NS_CC;
using namespace std;

LoadFailure::LoadFailure() : filename(string("unknown file")), filetype(string("unknown type"))
{
	error_content = "Error while loading: \nFilename: \"" + filename +
		"\", Filetype: " + filetype + "\n";
}

LoadFailure::LoadFailure(string& fname, string& ftype) : filename(fname), filetype(ftype)
{
	error_content = "Error while loading: \nFilename: \"" + filename +
		"\", Filetype: " + filetype + "\n";
}

LoadFailure::LoadFailure(const char* fname, const char* ftype)
{
	filename = string(fname);
	filetype = string(ftype);
	error_content = "Error while loading: \nFilename: \"" + filename +
		"\", Filetype: " + filetype + "\n";
}

const char* LoadFailure::what() const
{
	return error_content.c_str();
}

LoadFailure::~LoadFailure()
{
	exception::~exception();
}

bool ErrorScene::init()
{
	if (!Sprite::init())
	{
		Director::getInstance()->end();
		return false;
	}
	return true;
}

void ErrorScene::initScene(exception& exp)
{
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* ErrorScreen = Sprite::create("ErrorScreen.png");
	if (ErrorScreen != nullptr)
	{
		ResizePic(ErrorScreen, visibleSize.width, visibleSize.height);
		ErrorScreen->setPosition(origin + visibleSize / 2);
		this->addChild(ErrorScreen, 0);
	}
	std::string InfoHeaderstr = "oops! 程序崩溃了，错误信息如下：";
	GBKToUTF8(InfoHeaderstr, "gb2312", "utf-8");
	
	Vec2 CurPos = origin + Vec2(TextStart.x, -TextStart.y) + 
		Vec2(0, visibleSize.height - TextSize / 2);
	Label* InfoHeader = Label::createWithSystemFont(InfoHeaderstr, TextFont, TextSize);
	InfoHeader->setColor(TextColor1);
	InfoHeader->setPosition(CurPos + Vec2(InfoHeader->getContentSize().width / 2, 0));
	//InfoHeader->setPosition(Vec2::ZERO);
	this->addChild(InfoHeader, 1);

	CurPos.y -= TextGap;
	std::string Msgstr = exp.what();
	GBKToUTF8(Msgstr, "gb2312", "utf-8");
	Label* ErrorMsg = Label::createWithSystemFont(Msgstr, TextFont, TextSize);
	ErrorMsg->setPosition(CurPos + Vec2(ErrorMsg->getContentSize().width / 2, 0));
	ErrorMsg->setColor(TextColor2);
	this->addChild(ErrorMsg, 1);

	CurPos.y -= TextGap;
	Msgstr = "欢迎向开发者报告错误问题";
	GBKToUTF8(Msgstr, "gb2312", "utf-8");
	Label* AddMsg = Label::createWithSystemFont(Msgstr, TextFont, TextSize);
	AddMsg->setPosition(CurPos + Vec2(AddMsg->getContentSize().width / 2, 0));
	AddMsg->setColor(TextColor1);
	this->addChild(AddMsg, 1);

	CurPos.y -= TextGap;
	Msgstr = "点击此处退出程序";
	GBKToUTF8(Msgstr, "gb2312", "utf-8");
	Label* ExitMsg = Label::createWithSystemFont(Msgstr, TextFont, TextSize);
	MenuItemLabel* ExitLabel = MenuItemLabel::create(ExitMsg, [&](Ref* pSender){
			Director::getInstance()->end();
		});
	ExitLabel->setPosition(CurPos + Vec2(ExitMsg->getContentSize().width / 2, 0));
	ExitLabel->setColor(TextColor3);
	Menu* ExitMenu = Menu::create(ExitLabel, NULL);
	ExitMenu->setPosition(Vec2::ZERO);
	this->addChild(ExitMenu, 1);
}

ErrorScene* ErrorScene::CreateWithException(std::exception& exp)
{
	ErrorScene* ret = ErrorScene::create();
	ret->initScene(exp);
	return ret;
}