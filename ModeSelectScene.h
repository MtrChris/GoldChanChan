#pragma once

/*
*  选择单人模式/多人模式的界面
*/

#ifndef __MODESELECTSCENE_H__
#define __MODESELECTSCENE_H__

#include "GoldChan.h"

class ModeSelectScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void SingleStartCallback(Ref* pSender);
	void MultiPlayerStartCallback(Ref* pSender);
	void BackButtonCallback(Ref* pSender); // 返回按钮的回调函数

	CREATE_FUNC(ModeSelectScene)

	/* 以下为与选择界面一些图形参数的定义 */
	const float BoxYDif = 20;                               // 选择框的纵坐标上移量
	const cocos2d::Size BoxSize = cocos2d::Size(200, 200);
	const float BoxTextSize = 20;                           // 选择框字体的大小
	cocos2d::Color3B TextColor = cocos2d::Color3B::BLACK;   // 字体颜色
	const cocos2d::Size ButtonSize = cocos2d::Size(50, 20); // 返回按钮的大小
	const cocos2d::Vec2 ButtonPos = cocos2d::Vec2(20, 20);  // 返回按钮相对右下方的位置
	const char* TextFont = "宋体";                          // 文字的字体
	const float ButtonTextSize = 10;                        // 返回按钮字体的大小
};

#endif // !__MODESELECTSCENE_H__