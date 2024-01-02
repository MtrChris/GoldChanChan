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
	int CurTime; // ��ǰ�׶�ʣ���ʱ��
	int StageTime;
	int Round;
	GameScene* gscene;
	cocos2d::Label* StageName; // ��ǰ�׶�
	cocos2d::Label* StageTimeLeft; // �׶�ʣ��ʱ��
	cocos2d::ui::LoadingBar* StageBar; // �׶μ�ʱ��
	//cocos2d::Label* CoinMsg;
	int interest; // �غϵ���Ϣ
public:
	virtual bool init();
	CREATE_FUNC(StageController)
	void initWithScene(GameScene* m_gscene);
	void initGraph(); // ��ʼ��ͼ��
	void ResetTimer(int rtime); // ���ü�ʱ����ʱ�� 
	void UpdateTimer(float dt);
	void NextStage(); // ��ʼ��һ���׶�
	void StartNewRound(); // ��ʼ�µĻغ�
	const int getStage(); // ��ȡ��ǰ�׶�
	const int getCurTime();
	const int getRound(); // ��ȡ�غ���

	const char* StageDefaultName[4] = { "��ʼ�׶�", "Ұ�ֽ׶�", "��ս�׶�", "ս���׶�" };
	const int StageDefaultTime[4] = { 30, 20, 30, 20}; // ÿ���׶ε�Ĭ��ʱ��
	const float TimerY = 10; // �׶μ�ʱ�����붥���ľ���
	const float TimerCntX = 10; // �׶μ�ʱ���������������ľ���
	const cocos2d::Size StageBarSize = cocos2d::Size(100, 10); // �������Ĵ�С
	const float StageTextSize = 10; // �׶����Ƶ������С
	const cocos2d::Color3B StageTextColor = cocos2d::Color3B::BLACK; // �׶����ֵ���ɫ
	const char* TextFont = "����";
	const float BarOutlineScale = 1.2f; // ������������ڿ�������
	const float InterestRate = 0.1f; // ÿ�ֽ��������ӵĽ������
	const float MaxInterest = 5; // ���Ľ������
};

#endif // !__STAGECONTROLLER_H__