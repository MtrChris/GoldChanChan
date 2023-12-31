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

	// 创建设置背景
	auto SettingSceen = CreateBackground(this, "SettingBg.png", visibleSize, origin);

	// 标题文字
	Label* label = CreateLabel("设置", TextFont, 
		Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - TitleSize / 2 - TitleY),
		TitleSize, TitleColor);

	// 返回按钮
	auto BackImage = CreateButton(origin + BackButtonPos + BackButtonSize / 2, BackButtonSize);
	BackImage->setCallback(CC_CALLBACK_1(SettingScene::BackButtonCallback, this));
	Label* BackText = CreateLabel("返回", TextFont, 
		Vec2(origin.x, origin.y) + BackButtonPos + BackButtonSize / 2, BackTextSize);
	ButtonList.pushBack(BackImage);
	ButtonTextList.pushBack(BackText);

	float ButtonPosX = origin.x + visibleSize.width - ButtonX - ButtonSize.width;
	float TextPosX = origin.x + TextX;
	float ButtonPosY = origin.x + visibleSize.height - StartY;

	// 音乐开关
	MenuItemImage* MusicImage = CreateButton(Vec2(ButtonPosX, ButtonPosY), ButtonSize);
	ButtonList.pushBack(MusicImage);
	Label* MusicButtonText = CreateLabel("关闭", ButtonTextFont, Vec2(ButtonPosX, ButtonPosY), ButtonTextSize, ButtonTextColor);
	this->addChild(MusicButtonText, 2);
	ButtonTextList.pushBack(MusicButtonText);
	Label* MusicText = CreateLabel("背景音乐：", SettingInfoFont, Vec2::ZERO, SettingInfoSize, SettingInfoColor);
	MusicText->setPosition(Vec2(TextPosX + MusicText->getContentSize().width / 2, ButtonPosY));
	this->addChild(MusicText);
	MusicImage->setCallback(CC_CALLBACK_1(SettingScene::MusicButtonCallBack, this));
	MusicImage->selected();

	/* 在此处添加设置按钮 */
	//ui::Slider* slider = ui::Slider::create();

	// 将所有按钮创建成菜单
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
		SetLabelText(ButtonTextList.at(1), "打开");
		audio->stopBackgroundMusic();
	}
	else
	{
		ButtonList.at(1)->selected();
		SetLabelText(ButtonTextList.at(1), "关闭");
		audio->playBackgroundMusic("BgMusic.mp3", true);
	}
}