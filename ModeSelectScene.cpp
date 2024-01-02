#include "ModeSelectScene.h"
#include "GameScene.h"
#include "MainMenu.h"

USING_NS_CC;

Scene* ModeSelectScene::createScene()
{
	return ModeSelectScene::create();
}

bool ModeSelectScene::init()
{
	TEST_INIT
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 创建背景
	auto SelectionBg = CreateBackground(this, "SelectionBg.png", visibleSize, origin);

	// 创建两个选择框
	float BoxX = origin.x + visibleSize.width / 2 - BoxSize.width / 2 - 10;
	float BoxY = origin.y + visibleSize.height / 2 + BoxYDif;
	MenuItemImage* SingleImage = CreateButton(Vec2(BoxX, BoxY), BoxSize, "ModeUnselect.png", "ModeSelect.png");
	SingleImage->setCallback(CC_CALLBACK_1(ModeSelectScene::SingleStartCallback, this));
	Label* SingleText = CreateLabel("单人模式", TextFont, Vec2(BoxX, BoxY + 50), BoxTextSize, TextColor);
	BoxX = origin.x + visibleSize.width / 2 + BoxSize.width / 2 + 10;
	MenuItemImage* MultiPlayerImage = CreateButton(Vec2(BoxX, BoxY), BoxSize, "ModeUnselect.png", "ModeSelect.png");
	MultiPlayerImage->setCallback(CC_CALLBACK_1(ModeSelectScene::MultiPlayerStartCallback, this));
	Label* MultiPlayerText = CreateLabel("联机模式", TextFont, Vec2(BoxX, BoxY + 50), BoxTextSize, TextColor);
	
	// 添加返回按钮
	MenuItemImage* BackImage = CreateButton(Vec2::ZERO, ButtonSize);
	BackImage->setPosition(Vec2(origin.x + ButtonPos.x, origin.y + ButtonPos.y) + ButtonSize / 2);
	BackImage->setCallback(CC_CALLBACK_1(ModeSelectScene::BackButtonCallback, this));
	Label* BackText = CreateLabel("返回", TextFont, Vec2(origin.x + ButtonPos.x, origin.y + ButtonPos.y) + ButtonSize / 2,
		ButtonTextSize, TextColor);

	// 将上述元素放入界面中
	Menu* menu = Menu::create(SingleImage, MultiPlayerImage, BackImage, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(SingleText, 1);
	this->addChild(MultiPlayerText, 1);
	this->addChild(BackText, 1);
	this->addChild(menu, 0);

	CATCH_INIT
	return true;
}

void ModeSelectScene::SingleStartCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(GameScene::CreateScene());
}

void ModeSelectScene::MultiPlayerStartCallback(Ref* pSender)
{
	try
	{
		throw std::exception("在写了在写了");
	}
	catch (std::exception& exp)
	{
		this->removeAllChildren();
		this->addChild(ErrorScene::CreateWithException(exp), 10);
	}

}

void ModeSelectScene::BackButtonCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(MainMenu::createScene());
}