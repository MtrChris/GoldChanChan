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

	// ��������
	auto SelectionBg = CreateBackground(this, "SelectionBg.png", visibleSize, origin);

	// ��������ѡ���
	float BoxX = origin.x + visibleSize.width / 2 - BoxSize.width / 2 - 10;
	float BoxY = origin.y + visibleSize.height / 2 + BoxYDif;
	MenuItemImage* SingleImage = CreateButton(Vec2(BoxX, BoxY), BoxSize, "ModeUnselect.png", "ModeSelect.png");
	SingleImage->setCallback(CC_CALLBACK_1(ModeSelectScene::SingleStartCallback, this));
	Label* SingleText = CreateLabel("����ģʽ", TextFont, Vec2(BoxX, BoxY + 50), BoxTextSize, TextColor);
	BoxX = origin.x + visibleSize.width / 2 + BoxSize.width / 2 + 10;
	MenuItemImage* MultiPlayerImage = CreateButton(Vec2(BoxX, BoxY), BoxSize, "ModeUnselect.png", "ModeSelect.png");
	MultiPlayerImage->setCallback(CC_CALLBACK_1(ModeSelectScene::MultiPlayerStartCallback, this));
	Label* MultiPlayerText = CreateLabel("����ģʽ", TextFont, Vec2(BoxX, BoxY + 50), BoxTextSize, TextColor);
	
	// ��ӷ��ذ�ť
	MenuItemImage* BackImage = CreateButton(Vec2::ZERO, ButtonSize);
	BackImage->setPosition(Vec2(origin.x + ButtonPos.x, origin.y + ButtonPos.y) + ButtonSize / 2);
	BackImage->setCallback(CC_CALLBACK_1(ModeSelectScene::BackButtonCallback, this));
	Label* BackText = CreateLabel("����", TextFont, Vec2(origin.x + ButtonPos.x, origin.y + ButtonPos.y) + ButtonSize / 2,
		ButtonTextSize, TextColor);

	// ������Ԫ�ط��������
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
		throw std::exception("��д����д��");
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