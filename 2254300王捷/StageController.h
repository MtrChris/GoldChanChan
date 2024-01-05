#pragma once

#ifndef __STAGECONTROLLER_H__
#define __STAGECONTROLLER_H__

#include "GoldChan.h"

enum Stage
{
	CREEP_PRE, CREEP, PREPARE, FIGHT
};

class GameScene;
class StageController : public cocos2d::Node
{
	friend class GameScene;
private:
	int CurStage;
	int CurTime; // 当前阶段剩余的时间
	int StageTime;
	int Round;
	GameScene* gscene;
	cocos2d::Label* StageName; // 当前阶段
	cocos2d::Label* StageTimeLeft; // 阶段剩余时间
	cocos2d::ui::LoadingBar* StageBar; // 阶段计时条
	//cocos2d::Label* CoinMsg;
	int interest; // 回合的利息
public:
	virtual bool init();
	CREATE_FUNC(StageController)
	void initWithScene(GameScene* m_gscene);
	void initGraph(); // 初始化图像
	void ResetTimer(int rtime); // 重置计时器的时间 
	void UpdateTimer(float dt);
	void NextStage(); // 开始下一个阶段
	void StartNewRound(); // 开始新的回合
	const int getStage(); // 获取当前阶段
	const int getCurTime();
	const int getRound(); // 获取回合数

	const char* StageDefaultName[4] = { "起始阶段", "野怪阶段", "备战阶段", "战斗阶段" };
	const int StageDefaultTime[4] = { 30, 20, 30, 20}; // 每个阶段的默认时间
	const float TimerY = 10; // 阶段计时器距离顶部的距离
	const float TimerCntX = 10; // 阶段计时器读秒距离进度条的距离
	const cocos2d::Size StageBarSize = cocos2d::Size(100, 10); // 进度条的大小
	const float StageTextSize = 10; // 阶段名称的字体大小
	const cocos2d::Color3B StageTextColor = cocos2d::Color3B::BLACK; // 阶段文字的颜色
	const char* TextFont = "宋体";
	const float BarOutlineScale = 1.2f; // 进度条外框与内框的面积比
	const float InterestRate = 0.1f; // 每轮结束后增加的金币收益
	const float MaxInterest = 5; // 最大的金币收益
};

#endif // !__STAGECONTROLLER_H__