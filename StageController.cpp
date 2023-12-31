#include "GoldChan.h"
#include "StageController.h"
#include "GameScene.h"
#include "Store.h"
#include "HeroHandler.h"
#include "Player_and_Heroes.h"

USING_NS_CC;

bool StageController::init()
{
	if (!Node::init())
	{
		return false;
	}
	return true;
}

void StageController::initWithScene(GameScene* m_gscene)
{
	gscene = m_gscene;
	gscene->addChild(this);
	initGraph();
	CurStage = CREEP_PRE;
	StageTime = CurTime = StageDefaultTime[CurStage];
	this->schedule(CC_SCHEDULE_SELECTOR(StageController::UpdateTimer), 1.0f);
	SetLabelText(StageName, StageDefaultName[CurStage]);
	std::string s_CurTime = std::to_string(CurTime);
	StageTimeLeft->setString(s_CurTime);
}

void StageController::initGraph()
{
	// 创建阶段信息
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 StageBarPos = origin + Vec2(visibleSize.width / 2,
		visibleSize.height - StageBarSize.height / 2 - TimerY);
	StageBar = CreateLoadingBar("StageBar.png", StageBarPos, StageBarSize, 100);
	StageName = CreateLabel("", TextFont, StageBarPos, StageTextSize, StageTextColor);
	StageTimeLeft = CreateLabel("", TextFont, StageBarPos + Vec2(StageBarSize.width / 2 + TimerCntX, 0),
		StageTextSize, StageTextColor);
	float OutlineScale = (BarOutlineScale - 1) * StageBarSize.height;
	Sprite* TimerBarOutline = CreateSprite(this, StageBarPos, Size(OutlineScale, OutlineScale) + StageBarSize,
		"BarOutline.png");
	this->addChild(StageBar, 1);
	this->addChild(StageName, 1);
	this->addChild(StageTimeLeft, 1);
}

void StageController::ResetTimer(int rtime)
{
	CurTime = StageTime = rtime;
}

void StageController::NextStage()
{
	if (CurStage == PREPARE || CurStage == CREEP_PRE)
	{
		CurStage++;
		for (Vector<myHero*>::iterator it = gscene->me->HeroesOnBoard.begin();
			it < gscene->me->HeroesOnBoard.end(); it++)
		{
			(*it)->start_battle();
		}
		for (Vector<myHero*>::iterator it = gscene->enemy->HeroesOnBoard.begin();
			it < gscene->enemy->HeroesOnBoard.end(); it++)
		{
			(*it)->start_battle();
		}
	}
	else if (CurStage == FIGHT || CurStage == CREEP)
	{
		if(CurStage == FIGHT)
		{
			StartNewRound();
		}
		else
		{
			CurStage++;
		}
		for (Vector<myHero*>::iterator it = gscene->me->HeroesOnBoard.begin();
			it < gscene->me->HeroesOnBoard.end(); it++)
		{
			(*it)->end_battle();
		}
		for (Vector<myHero*>::iterator it = gscene->enemy->HeroesOnBoard.begin();
			it < gscene->enemy->HeroesOnBoard.end(); it++)
		{
			(*it)->end_battle();
		}
		gscene->me->get_attack(gscene->enemy->HeroesOnBoard.size());
		gscene->enemy->get_attack(gscene->me->HeroesOnBoard.size());
		if (!gscene->me->get_condition())
		{
			unscheduleAllCallbacks();
			gscene->DisplayResult(false);
		}
		else if (!gscene->enemy->get_condition())
		{
			unscheduleAllCallbacks();
			gscene->DisplayResult(true);
		}
		gscene->enemy->AIAction();
	}
	else
	{
		CurStage++;
	}
	gscene->hh->CheckButtonState();
	SetLabelText(StageName, StageDefaultName[CurStage]);
	ResetTimer(StageDefaultTime[CurStage]);
	StageBar->setPercent(CurTime * 100.0f / StageTime);
	std::string s_CurTime = std::to_string(CurTime);
	StageTimeLeft->setString(s_CurTime);
}

void StageController::UpdateTimer(float dt)
{
	if (CurTime == 0)
	{
		NextStage();
		return;
	}
	CurTime--;
	StageBar->setPercent(CurTime * 100.0f / StageTime);
	std::string s_CurTime = std::to_string(CurTime);
	StageTimeLeft->setString(s_CurTime);
}


void StageController::StartNewRound()
{
	if (gscene->st->NextRefresh)
	{
		gscene->st->ShuffleItem();
		if (gscene->st->is_open())
		{
			gscene->st->SelectId = -1;
			gscene->st->UpdateDisplay();
			gscene->st->CheckRefresh();
			gscene->st->CheckPurchase();
			gscene->st->ToggleDetail(false);
		}
	}
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	interest = static_cast<int>(std::min(gscene->st->CurCoin * InterestRate, MaxInterest));
	gscene->st->CoinUpdate(interest);
	CurStage = PREPARE;
}

const int StageController::getStage()
{
	return CurStage;
}