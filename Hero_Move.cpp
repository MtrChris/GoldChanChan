#include"Player_and_Heroes.h"
#include"GameScene.h"
#include "HeroHandler.h"
#include"StageController.h"

USING_NS_CC;
using namespace std;

//����ƶ�
void myHero::relativeMove(float x, float y)
{
	auto moveToward = MoveBy::create(10.0f, Vec2(x, y));
	auto seq = Sequence::create(moveToward, nullptr);
	runAction(seq);
}

//�����ƶ�
void myHero::absoluteMove(float x, float y)
{
	auto moveToward = MoveTo::create(10.0f, Vec2(x, y));
	auto seq = Sequence::create(moveToward, nullptr);
	runAction(seq);
}

// һ��ս���ж�
void myHero::moveAction(float dt) {
	static float num = 0;  //��¼ʱ��
	if (!get_condition())  //�ҷ�����
	{
		unschedule(CC_SCHEDULE_SELECTOR(myHero::moveAction));
		dead();
		scheduleOnce(CC_SCHEDULE_SELECTOR(myHero::remove), 1.0f);
		//if (Camp == 1)
		//	scene_pointer->me->HeroesOnBoard.eraseObject(this);
		//else
		//	scene_pointer->enemy->HeroesOnBoard.eraseObject(this);

		//scene_pointer->hh->Board[hero_x][hero_y] = nullptr;
		//scene_pointer->removeChild(this);
		return;
	}
	if (Type != "ҽ��" && target_hero == nullptr)  //�Ҳ����з�Ŀ��
	{
		unschedule(CC_SCHEDULE_SELECTOR(myHero::moveAction));
		//scheduleOnce(CC_SCHEDULE_SELECTOR(myHero::no_hero_left), 1.1f);
		return;
	}
	if (Type == "ҽ��" && (target_hero == nullptr || !target_hero->get_condition() ||
		target_hero->HP == HPmax))  //��ǰ���ƽ�ɫ����Ѫ��δ��������ѪĿ��
	{
		change_target(findHurtTarget(player));
	}
	else if ((Type != "ҽ��" && !target_hero->get_condition()))  //�з�����
	{
		change_target(findNearestTarget(player));
	}
	else
	{
		float t_x = target_hero->getPositionX();
		float t_y = target_hero->getPositionY();
		float x = getPositionX();
		float y = getPositionY();
		float moveDistance = moveInterval * moveSpeed;
		float distance = sqrt((t_x - x) * (t_x - x) + (t_y - y) * (t_y - y));
		if (distance > Range)  //Ŀ��δ���빥����Χ���ƶ�
		{
			float proportion = moveDistance / distance;
			auto moveToward = MoveBy::create(moveInterval, Vec2((t_x - x) * proportion, (t_y - y) * proportion));
			runAction(moveToward);
		}
		else  //Ŀ���ڷ�Χ�ڣ�ִ�в���
		{
			if (Type != "ҽ��" && num >= attackInterval) {
				attack();
				num = 0;
			}
			else if (Type == "ҽ��" && num >= attackInterval) {
				heal();
				num = 0;
			}
			else
				num += moveInterval;
		}
	}
}

//��ɫһ�������ƶ�+����
void myHero::hero_action() {
	schedule(CC_SCHEDULE_SELECTOR(myHero::moveAction), moveInterval);
}

void Player::JudgeStageEnd(float dt)
{
	bool HasMyHero = false;
	bool HasEnemyHero = false;
	for (int row = 0; !HasMyHero && row < gscene->hh->BoardRow; row++)
	{
		for (int col = 0; !HasMyHero && col < gscene->hh->BoardCol; col++)
		{
			if (gscene->hh->Board[row][col] != nullptr && gscene->hh->Board[row][col]->get_condition())
			{
				HasMyHero = true;
			}
		}
	}
	for (int row = gscene->hh->BoardRow; !HasEnemyHero && row < gscene->hh->FullRow; row++)
	{
		for (int col = 0; !HasEnemyHero && col < gscene->hh->BoardCol; col++)
		{
			if (gscene->hh->Board[row][col] != nullptr && gscene->hh->Board[row][col]->get_condition())
			{
				HasEnemyHero = true;
			}
		}
	}
	if (!(HasMyHero && HasEnemyHero) && gscene->sc->getCurTime() > 1)
	{
		unschedule(CC_SCHEDULE_SELECTOR(Player::JudgeStageEnd));
		scheduleOnce(CC_SCHEDULE_SELECTOR(Player::StageEnd), 1.5f);
	}
}

void Player::StageEnd(float dt)
{
	gscene->sc->NextStage();
}
