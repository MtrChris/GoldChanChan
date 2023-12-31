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

// һ���ƶ�����
void myHero::moveAction(float dt) {
	static float num = 0;  //��¼ʱ��
	if (!get_condition())  //�ҷ�����
	{
		if (Camp == 1)
			scene_pointer->me->HeroesOnBoard.eraseObject(this);
		else
			scene_pointer->enemy->HeroesOnBoard.eraseObject(this);
		unschedule(CC_SCHEDULE_SELECTOR(myHero::moveAction));
		scene_pointer->hh->Board[hero_x][hero_y] = nullptr;
		scene_pointer->removeChild(this);
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
	if (Type != "ҽ��" && target_hero == nullptr)  //�Ҳ����з�Ŀ��
	{
		scene_pointer->sc->NextStage();
		return;
	}
}

//��ɫһ�������ƶ�+����
void myHero::hero_action() {
	schedule(CC_SCHEDULE_SELECTOR(myHero::moveAction), moveInterval);
}

myHero* myHero::findHurtTarget(Player* player) {
	myHero* target = nullptr;
	Vector<myHero*> heroesList = player->HeroesOnBoard;
	float minDis = 10000000.0f, dis;
	float myPosX = this->getPositionX(), myPosY = this->getPositionY();
	for (vector<myHero*> ::iterator i = heroesList.begin(); i != heroesList.end(); ++i) {
		if ((*i)->HP == (*i)->HPmax) continue;
		int tPosX = (*i)->getPositionX();
		int tPosY = (*i)->getPositionY();
		dis = (myPosX - tPosX) * (myPosX - tPosX) + (myPosY - tPosY) * (myPosY - tPosY);
		if (dis < minDis) {
			target = *i;
			minDis = dis;
		}
	}
	return target;
}