#pragma once

#ifndef __SETTINGSCENE_H__
#define __SETTINGSCENE_H__

#include "GoldChan.h"

class SettingScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	cocos2d::Vector<cocos2d::MenuItem*> ButtonList;
	cocos2d::Vector<cocos2d::Label*> ButtonTextList;

	virtual bool init();
	void BackButtonCallback(Ref* pSender); // 返回按钮的回调函数
	void MusicButtonCallBack(Ref* pSender);

	CREATE_FUNC(SettingScene)

	/* 以下为与选择界面一些图形参数的定义 */
	const char* TextFont = "宋体";								 // 字体
	const float TitleY = 10;								     // 标题的位置与顶部的距离
	const float TitleSize = 20;								     // 标题字体的大小
	const cocos2d::Color3B TitleColor = cocos2d::Color3B::BLACK; // 标题颜色
	const cocos2d::Vec2 BackButtonPos = cocos2d::Vec2(20, 20);   // 返回按钮的位置
	const cocos2d::Size BackButtonSize = cocos2d::Size(50, 20);  // 返回按钮的大小
	const float BackTextSize = 10;                               // 返回字体的大小
	const float StartY = 20; // 按钮位置
	const float TextX = 100; // 设置说明按钮的位置
	const float ButtonX = 100; // 按钮的位置（相对右边界）
	const float RowGap = 5; // 行距
	const cocos2d::Size ButtonSize = cocos2d::Size(50, 20);
	const float ButtonTextSize = 10; // 按钮文字的大小
	const char* ButtonTextFont = "宋体";
	const cocos2d::Color3B ButtonTextColor = cocos2d::Color3B::BLACK;
	const float SettingInfoSize = 10;
	const char* SettingInfoFont = "宋体";
	const cocos2d::Color3B SettingInfoColor = cocos2d::Color3B::YELLOW;
};

#endif // !__SETTINGSCENE_H__