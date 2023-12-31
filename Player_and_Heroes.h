#pragma once

#ifndef __PLAYER_AND_HEROES_H__
#define __PLAYER_AND_HEROES_H__

#include"GoldChan.h"

class Player;
class GameScene;

enum CAMP
{
	MY, ENEMY
};

enum IMAGE
{
	DISPLAY, BATTLE
};

class Hero : public cocos2d::Sprite  //Ӣ����
{
protected:
	int heroID = -1;              //Ӣ�۱��
	std::string Name = "����";    //Ӣ������
	std::string PicName = "ͼƬ"; //Ӣ������
	std::string Type = "ְҵ";    //Ӣ��ְҵ
	int HPmax = -1;               //Ӣ����������
	int MPmax = -1;               //Ӣ����������
	int ATK = -1;                 //Ӣ�۹�����
	int DEF = -1;                 //Ӣ�۷�����
	int Range = -1;               //Ӣ�۹�����Χ
	int Price = -1;               //Ӣ�ۼ۸�

public:
	/*
	* ������������
	* ʹ�÷�ʽ��Hero* hero = Hero::create_with_attribute(...);
	* ������������
	*/
	static Hero* create_with_attribute(int id, std::string name, std::string type, int HP, int MP, int atk, int def, int range, int price,
		std::string image_name);  //����Ӣ�۾���
	void init_with_attribute(int id, std::string name, std::string type, int HP, int MP, int atk, int def, int range, int price,
		std::string image_name);  //��ʼ��Ӣ��
	void get_attribute(std::string& type, int& HP, int& MP, int& ATK, int& DEF, int& range);  //��ȡ��ɫ��Ϣ
	std::string getPicName();     //��ȡ��ɫͼƬ����
	std::string getHeroName();    //��ȡ��ɫ����
	const int getID();            //��ȡ��ɫID
	const int get_price();        //��ȡӢ�ۼ۸�
	virtual bool init();
	CREATE_FUNC(Hero)
};

class myHero : public Hero  //�ҵ�Ӣ��
{
protected:
	int HP;                            //Ӣ�۵�ǰѪ��
	int MP;                            //Ӣ�۵�ǰ����
	int level;                         //Ӣ�۵ȼ�
	int condition;                     //Ӣ��״̬��1Ϊ��0Ϊ������
	int Camp;                          //Ӣ����Ӫ��1Ϊ�ҷ���0Ϊ�з���
	const float moveSpeed = 100.0f;    //Ӣ���ƶ��ٶ�
	const float moveInterval = 0.2f;   //Ӣ���ƶ����
	const float attackInterval = 0.3f; //��ɫ�������
	int hero_x = 0;                    //Ӣ���ڳ��ϵĳ�ʼ������
	int hero_y = 0;                    //Ӣ���ڳ��ϵĳ�ʼ������
	GameScene* scene_pointer = NULL;   //ָ�򳡾���ָ��


	cocos2d::ui::LoadingBar* HPBar;
	cocos2d::ui::LoadingBar* MPBar;
public:
	myHero* target_hero = NULL;        //Ӣ�۵�ǰ������Ŀ��Ӣ��
	Player* player = NULL;             //ָ����ҵ�ָ�룡����������������������������������������������������
	/*
	* ������������
	* ʹ�÷�ʽ��myHero* myhero = myHero::create_with_hero(hero);
	* ������������
	*/
	virtual bool init();
	CREATE_FUNC(myHero)
		static myHero* create_with_hero(Hero* hero, int m_camp, GameScene* pointer);  //�����ҵ�Ӣ�۾���
	void init_with_hero(Hero* hero, int m_camp, GameScene* pointer);              //��ʼ���ҵ�Ӣ��

	//Ӣ��������غ���
	void level_up();                          //Ӣ������
	const int getLevel();                     //��ȡӢ�۵ȼ�
	bool get_condition();                     //��ȡӢ��״̬
	void hero_init();                         //һ�ֽ�����Ӣ��״̬ˢ��

	//Ӣ�۷�����غ���
	void move_to_board(int x, int y);          //Ӣ���ƶ�������
	void remove_from_board();                  //Ӣ�۴ӳ����Ƴ�
	myHero* findNearestTarget(Player* player);
	myHero* myHero::findHurtTarget(Player* player);

	//Ӣ���ж���غ���
	void start_battle();
	void end_battle();
	void change_target(myHero* hero);       //�л�����Ŀ��
	void moveAction(float dt);              //��ɫ�ƶ�
	void relativeMove(float x, float y);    //���Ӣ�������ƶ�
	void absoluteMove(float x, float y);    //���������ƶ�
	void hero_action();                     //Ӣ��һ�������ƶ�+����
	void attack();                          //Ӣ�۹���
	void attacked();                        //��ɫ������
	void heal();                            //Ӣ������
	void healed();                          //Ӣ�۱�����
	void dead();                            //Ӣ������
	/*
	���÷���
	myhero->change_target(myhero2);
	myhero->hero_action();
	*/
	const cocos2d::Size OnBoardSize = cocos2d::Size(22, 22);
	const float BarHeight = 2;
};
/* ���÷���
	auto hero = myHero::create();
	this->addChild(hero);
	hero->moveHero(10, 10);
*/

class Player : public cocos2d::Sprite
{
protected:
	GameScene* gscene;
	std::string Name;
	std::string PicName;
	int HP;
	cocos2d::ui::LoadingBar* HPBar;
public:
	virtual bool init();
	void init_graph();
	cocos2d::Vector<myHero*> HeroesOnBoard;
	static Player* NormalCreate(GameScene* m_gscene, std::string name, std::string picname, int hp);
	void NormalInit(GameScene* m_gscene, std::string name, std::string picname, int hp);
	bool get_condition();
	void get_attack(int leftHeroes);
	void Player::AIAction();

	CREATE_FUNC(Player)

	const cocos2d::Vec2 PlayerPos = cocos2d::Vec2(10, 10);
	const cocos2d::Size PlayerSize = cocos2d::Size(40, 40);
	const float BarHeight = 5;
};
#endif  // !__PLAYER_AND_HEROES_H__
