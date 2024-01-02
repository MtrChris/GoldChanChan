#include"Player_and_Heroes.h"
#include "GameScene.h"
#include "HeroHandler.h"
#include "StageController.h"

USING_NS_CC;
using namespace std;

void myHero::move_to_board(int x, int y)
{
	hero_x = x;
	hero_y = y;
	this->setVisible(true);
}
void myHero::remove_from_board()
{
	hero_x = 0;
	hero_y = 0;
	this->setVisible(false);
}

bool Player::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	return true;
}

Player* Player::NormalCreate(GameScene* m_gscene, string name, string picname, int hp)
{
	Player* ret = Player::create();
	ret->NormalInit(m_gscene, name, picname, hp);
	return ret;
}

void Player::NormalInit(GameScene* m_gscene, string name, string picname, int hp)
{
	gscene = m_gscene;
	Name = name;
	HP = hp;
	PicName = picname;
	gscene->addChild(this, 0);
	init_graph();
}

bool Player::lose() {
	return HP <= 0;
}

void Player::get_attack(int leftHeroes) {
	int damage = 6 + 4 * leftHeroes;
	if (damage > HP) HP = 0;
	else HP -= damage;
	HPBar->setPercent(HP * 100.0f / gscene->PlayerHP);
}

myHero* myHero::findNearestTarget(Player* player) {
	myHero* target = nullptr;
	Vector<myHero*> heroesList = player->HeroesOnBoard;
	float minDis = 10000000.0f, dis;
	float myPosX = this->getPositionX(), myPosY = this->getPositionY();
	for (vector<myHero*> ::iterator i = heroesList.begin(); i != heroesList.end(); ++i) {
		if (!(*i)->get_condition()) continue;
		float tPosX = (*i)->getPositionX();
		float tPosY = (*i)->getPositionY();
		dis = (myPosX - tPosX) * (myPosX - tPosX) + (myPosY - tPosY) * (myPosY - tPosY);
		if (dis < minDis) {
			target = *i;
			minDis = dis;
		}
	}
	return target;
}

myHero* myHero::findHurtTarget(Player* player) {
	myHero* target = nullptr;
	Vector<myHero*> heroesList = player->HeroesOnBoard;
	float minDis = 10000000.0f, dis;
	float myPosX = this->getPositionX(), myPosY = this->getPositionY();
	for (vector<myHero*> ::iterator i = heroesList.begin(); i != heroesList.end(); ++i) {
		if (!(*i)->get_condition() || (*i)->HP == (*i)->HPmax) continue;
		float tPosX = (*i)->getPositionX();
		float tPosY = (*i)->getPositionY();
		dis = (myPosX - tPosX) * (myPosX - tPosX) + (myPosY - tPosY) * (myPosY - tPosY);
		if (dis < minDis) {
			target = *i;
			minDis = dis;
		}
	}
	return target;
}

void myHero::erase_hero()
{
	if(Camp)
	{
		scene_pointer->enemy->HeroesOnBoard.eraseObject(this);
	}
	else
	{
		scene_pointer->me->HeroesOnBoard.eraseObject(this);
	}
	scene_pointer->hh->Board[hero_x][hero_y] = nullptr;
	scene_pointer->removeChild(this);
}

void Player::init_graph()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	initWithFile(PicName);
	Vec2 PlayerVec;
	if (gscene->me == nullptr)
	{
		PlayerVec = origin + PlayerPos + Vec2(PlayerSize / 2) + Vec2(0, BarHeight / 2);
		HPBar = CreateLoadingBar("MyHPBar.png", PlayerVec + Vec2(0, PlayerSize.height / 2 + BarHeight / 2),
			Size(PlayerSize.width, BarHeight), 100);
	}
	else
	{
		PlayerVec = origin + Vec2(PlayerPos.x, -PlayerPos.y) + Vec2(0, visibleSize.height - gscene->CoinBgSize.height)
			+ Vec2(PlayerSize.width / 2, -PlayerSize.height / 2 - BarHeight);
		HPBar = CreateLoadingBar("EnemyHPBar.png", PlayerVec + Vec2(0, PlayerSize.height / 2 + BarHeight / 2),
			Size(PlayerSize.width, BarHeight), 100);
	}
	ResizePic(this, PlayerSize.width, PlayerSize.height);
	setPosition(PlayerVec);
	gscene->addChild(HPBar, 1);
}

//void Player::AIAction() {
//	int maxHero = 3, maxCoin = 10, nowCoin = 0;
//	for (int i = 1; i <= maxHero; ++i) {
//		Hero* selectedHero = gscene->hh->HeroLibrary[rand() % 10];
//		myHero* newHero = myHero::create_with_hero(selectedHero, ENEMY, gscene);
//		nowCoin += selectedHero->get_price();
//		if (nowCoin > maxCoin) break;
//		int row = (rand() % gscene->hh->BoardRow) + gscene->hh->BoardRow, col = rand() % gscene->hh->BoardCol;
//		while (gscene->hh->Board[row][col] != nullptr)
//			row = (rand() % gscene->hh->BoardRow) + gscene->hh->BoardRow, col = rand() % gscene->hh->BoardCol;
//		gscene->enemy->HeroesOnBoard.pushBack(newHero);
//		gscene->addChild(newHero, 4);
//		gscene->hh->Board[row][col] = newHero;
//		newHero->move_to_board(row, col);
//		newHero->setPosition(gscene->hh->GetBoardPos(row, col)
//			- Vec2(0, newHero->BarHeight));
//	}
//}

void Player::AIAction() {
	HeroHandler* HH = gscene->hh;
	int rnd = gscene->sc->getRound();
	int maxHero = rnd / 2 + 6, maxCoin = rnd * 10 + 10, nowCoin = 0;
	for (int i = 1; i <= maxHero; ++i) {
		Hero* selectedHero = HH->HeroLibrary[rand() % 10];
		myHero* newHero = myHero::create_with_hero(selectedHero, ENEMY, gscene);
		if ((rand() % 20) <= rnd) {
			newHero->level_up();
			if ((rand() % 50) <= rnd) newHero->level_up();
		}
		nowCoin += selectedHero->get_price();
		if (nowCoin > maxCoin || (gscene->enemy->HeroesOnBoard.size() >= maxHero)) break;
		int row = (rand() % HH->BoardRow) + HH->BoardRow, col = rand() % HH->BoardCol;
		while (HH->Board[row][col] != nullptr)
			row = (rand() % HH->BoardRow) + HH->BoardRow, col = rand() % HH->BoardCol;
		gscene->enemy->HeroesOnBoard.pushBack(newHero);
		gscene->addChild(newHero, 0);
		HH->Board[row][col] = newHero;
		newHero->move_to_board(row, col);
		newHero->setPosition(HH->GetBoardPos(row, col)
			- Vec2(0, newHero->BarHeight));
	}
}


