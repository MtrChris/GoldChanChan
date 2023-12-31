#pragma once

#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "GoldChan.h"
#include "Player_and_Heroes.h"

class Store;
class StageController;
class HeroHandler;
class Player;

class GameScene : public cocos2d::Scene
{
	friend class Store;
	friend class StageController;
	friend class HeroHandler;
	friend class myHero;
	friend class Player;
private:
	Store* st;
	StageController* sc;
	HeroHandler* hh;
	Player* me;
	Player* enemy;
	bool isQuitBoxOpen;

	cocos2d::Vector<cocos2d::MenuItemImage*> ButtonList;
	cocos2d::Label* StoreText; // 商店按钮的名称
	cocos2d::MenuItemImage* StoreButton; // 商店按钮
	cocos2d::Label* CoinNum;   // 显示持有金币数的文本
	void SetButtonState(const bool state);

public:
	static cocos2d::Scene* CreateScene();
	virtual bool init(); 
	CREATE_FUNC(GameScene)

	void initGraph(); // 初始化图形界面
	void ExitButtonCallback(cocos2d::Ref* pSender); // 退出按钮的函数
	void QuitCancelCallback(cocos2d::Ref* pSender); // 退出取消按钮的函数
	void DisplayResult(bool state); // 结果界面
	void RetryCallback(Ref* pSender); // 重试按钮
	void MainMenuCallback(Ref* pSender); // 主菜单按钮

	/* 以下为与图形界面有关的宏定义 */
	const cocos2d::Size ButtonSize = cocos2d::Size(50, 50); // 商店和经验按钮的大小
	const cocos2d::Size ExpBarSize = cocos2d::Size(50, 5);  // 进度条的大小 
	const cocos2d::Size ExitButtonSize = cocos2d::Size(15, 15); // 退出按钮的大小
	const cocos2d::Vec2 ExpPos = cocos2d::Vec2(10, 10);   // 经验按钮的位置（相对左下角）
	const cocos2d::Vec2 ShopPos = cocos2d::Vec2(-10, 10); // 商店按钮的位置（相对右下角）
	const cocos2d::Vec2 ExitPos = cocos2d::Vec2(-10, -10);  // 退出按钮的位置（相对右上角）
	const float ExpGap = 20; // 经验条与经验按钮之间的位置
	const float ButtonTextSize = 8; // 按钮上文字的大小
	const cocos2d::Color3B ButtonTextColor = cocos2d::Color3B::BLACK; // 按钮文字的颜色
	const char* TextFont = "宋体";
	const cocos2d::Size QuitBoxSize = cocos2d::Size(300, 150);        // 退出弹窗的大小
	const cocos2d::Size QuitButtonSize = cocos2d::Size(100, 40);      // 退出确认按钮的大小
	const float QuitTextSize = 15;                                    // 按钮文字的大小
	const float QuitMessageSize = 20;                                 // 退出提示信息的大小
	const cocos2d::Size CoinBgSize = cocos2d::Size(50, 15);           // 显示金币数量背景的大小
	const cocos2d::Vec2 CoinBgPos = cocos2d::Vec2(10, 10);            // 显示金币数量背景的位置（相对于左上角）
	const float CoinImgX = 10; // 金币图像相对于边缘的位置
	const float CoinNumX = 10; // 金币数量相对于边缘的位置
	const float CoinNumSize = 10; // 金币数量的文本大小
	const cocos2d::Size CoinSize = cocos2d::Size(10, 10); // 金币图像的大小
	const cocos2d::Color3B InfoTextColor = cocos2d::Color3B::BLACK; // 信息文字的颜色
	const float BarOutlineScale = 1.2f; // 进度条外框与内框的面积比
	const int PlayerHP = 100;
	const cocos2d::Size ResSize = cocos2d::Size(300, 180);
	const float ResButtonY = 40;
	const float ResButtonX = 50;
	const cocos2d::Size ResButtonSize = cocos2d::Size(50, 20);
	const char* ResTextFont = "宋体";
	const float ResTextSize = 10;
	const cocos2d::Color3B ResTextColor = cocos2d::Color3B::BLACK;
};

class FadingText : public cocos2d::Label
{
private:
	cocos2d::Node* parent;
	float deltaTime;
	int alpha;
public:
	static FadingText* FastCreate(cocos2d::Node* m_parent, const char* display, const char* font, const cocos2d::Vec2& pos,
		const float size, const cocos2d::Color3B& color = cocos2d::Color3B::BLACK, float dt = 0.01f);
	virtual bool init();
	void FastInit(cocos2d::Node* m_parent, const char* display, const char* font, const cocos2d::Vec2& pos,
		const float size, const cocos2d::Color3B& color = cocos2d::Color3B::BLACK, float dt = 0.01f);
	CREATE_FUNC(FadingText)
	
	void FadeFunc(float dt); // 隐藏函数
};

#endif // !__GAMESCENE_H__