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
	// �����׶���Ϣ
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
		gscene->me->schedule(CC_SCHEDULE_SELECTOR(Player::JudgeStageEnd));
	}
	else if (CurStage == FIGHT || CurStage == CREEP)
	{
		if(gscene->me->isScheduled(CC_SCHEDULE_SELECTOR(Player::JudgeStageEnd)))
		{
			gscene->me->unschedule(CC_SCHEDULE_SELECTOR(Player::JudgeStageEnd));
		}
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
		for (int row = 0; row < gscene->hh->FullRow; row++)
		{
			for (int col = 0; col < gscene->hh->BoardCol; col++)
			{
				myHero* CurHero = gscene->hh->Board[row][col];
				if (CurHero != nullptr && !CurHero->isVisible())
				{
					CurHero->erase_hero();
				}
			}
		}
		int myHeroLeft = gscene->me->HeroesOnBoard.size();
		int EnemyHeroLeft = gscene->enemy->HeroesOnBoard.size();
		if (myHeroLeft > EnemyHeroLeft)
		{
			gscene->enemy->get_attack(myHeroLeft - EnemyHeroLeft);
		}
		else if(myHeroLeft < EnemyHeroLeft)
		{
			gscene->me->get_attack(EnemyHeroLeft - myHeroLeft);
		}
		if (gscene->me->lose())
		{
			unscheduleAllCallbacks();
			gscene->DisplayResult(false);
		}
		else if (gscene->enemy->lose())
		{
			unscheduleAllCallbacks();
			gscene->DisplayResult(true);
		}
		if(gscene->sv == nullptr)
		{
			gscene->enemy->AIAction();
		}
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
	Round++;
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

const int StageController::getCurTime()
{
	return CurTime;
}

const int StageController::getRound()
{
	return Round;
}