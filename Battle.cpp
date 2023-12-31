//#include"Battle.h"
//USING_NS_CC;
//
//bool Player::init()
//{
//	if (!Sprite::init())
//	{
//		return false;
//	}
//	return true;
//}
//
//Player* Player::NormalCreate(GameScene* m_gscene, string name, string picname, int hp)
//{
//	Player* ret = Player::create();
//	ret->NormalCreate(m_gscene, name, picname, hp);
//	return ret;
//}
//
//void Player::NormalInit(GameScene* m_gscene, string name, string picname, int hp)
//{
//	gscene = m_gscene;
//	Name = name;
//	HP = hp;
//	gscene->addChild(this);
//}
//
//bool Player::get_condition() {
//	return HP == 0 ? 0 : 1;
//}
//void Player::get_attack(int leftHeroes) {
//	int damage = 4 + 2 * leftHeroes;
//	if (damage > HP) HP = 0;
//	else HP -= damage;
//}
//
////myHero* myHero::findNearestTarget(Player player) {
////	myHero* target;
////	vector<myHero*> heroesList = player.getHeroesList;
////	float minDis = 10000000.0f, dis;
////	float myPosX = this->getPositionX(), myPosY = this->getPositionY();
////	for (vector<myHero*> ::iterator i = heroesList.begin(); i != heroesList.end(); ++i) {
////		int tPosX = (*i)->getPositionX();
////		int tPosY = (*i)->getPositionY();
////		dis = (myPosX - tPosX) * (myPosX - tPosX) + (myPosY - tPosY) * (myPosY - tPosY);
////		if (dis < minDis) target = *i;
////	}
////	return target;
////}