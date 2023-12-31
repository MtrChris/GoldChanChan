#include "SettingScene.h"
#include "cocos\editor-support\cocostudio\SimpleAudioEngine.h"
#include "MainMenu.h"
#include "ui\CocosGUI.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* SettingScene::createScene()
{
	return SettingScene::create();
}

bool SettingScene::init()
{
	if(!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// �������ñ���
	auto SettingSceen = CreateBackground(this, "SettingBg.png", visibleSize, origin);

	// ��������
	Label* label = CreateLabel("����", TextFont, 
		Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - TitleSize / 2 - TitleY),
		TitleSize, TitleColor);

	// ���ذ�ť
	auto BackImage = CreateButton(origin + BackButtonPos + BackButtonSize / 2, BackButtonSize);
	BackImage->setCallback(CC_CALLBACK_1(SettingScene::BackButtonCallback, this));
	Label* BackText = CreateLabel("����", TextFont, 
		Vec2(origin.x, origin.y) + BackButtonPos + BackButtonSize / 2, BackTextSize);
	ButtonList.pushBack(BackImage);
	ButtonTextList.pushBack(BackText);

	float ButtonPosX = origin.x + visibleSize.width - ButtonX - ButtonSize.width;
	float TextPosX = origin.x + TextX;
	float ButtonPosY = origin.x + visibleSize.height - StartY;

	// ���ֿ���
	MenuItemImage* MusicImage = CreateButton(Vec2(ButtonPosX, ButtonPosY), ButtonSize);
	ButtonList.pushBack(MusicImage);
	Label* MusicButtonText = CreateLabel("�ر�", ButtonTextFont, Vec2(ButtonPosX, ButtonPosY), ButtonTextSize, ButtonTextColor);
	this->addChild(MusicButtonText, 2);
	ButtonTextList.pushBack(MusicButtonText);
	Label* MusicText = CreateLabel("�������֣�", SettingInfoFont, Vec2::ZERO, SettingInfoSize, SettingInfoColor);
	MusicText->setPosition(Vec2(TextPosX + MusicText->getContentSize().width / 2, ButtonPosY));
	this->addChild(MusicText);
	MusicImage->setCallback(CC_CALLBACK_1(SettingScene::MusicButtonCallBack, this));
	MusicImage->selected();

	/* �ڴ˴�������ð�ť */
	//ui::Slider* slider = ui::Slider::create();

	// �����а�ť�����ɲ˵�
	Menu* menu = Menu::createWithArray(ButtonList);
	menu->setPosition(Vec2::ZERO);

	this->addChild(menu, 1);
	this->addChild(BackText, 2);
	this->addChild(label, 2);
	return true;
}

void SettingScene::BackButtonCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(MainMenu::createScene());
}

void SettingScene::MusicButtonCallBack(Ref* pSender)
{
	static auto audio = SimpleAudioEngine::getInstance();
	if (audio->isBackgroundMusicPlaying())
	{
		ButtonList.at(1)->unselected();
		SetLabelText(ButtonTextList.at(1), "��");
		audio->stopBackgroundMusic();
	}
	else
	{
		ButtonList.at(1)->selected();
		SetLabelText(ButtonTextList.at(1), "�ر�");
		audio->playBackgroundMusic("BgMusic.mp3", true);
	}
}