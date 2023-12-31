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

class Hero : public cocos2d::Sprite  //英雄类
{
protected:
	int heroID = -1;              //英雄编号
	std::string Name = "名称";    //英雄名称
	std::string PicName = "图片"; //英雄立绘
	std::string Type = "职业";    //英雄职业
	int HPmax = -1;               //英雄生命上限
	int MPmax = -1;               //英雄能量上限
	int ATK = -1;                 //英雄攻击力
	int DEF = -1;                 //英雄防御力
	int Range = -1;               //英雄攻击范围
	int Price = -1;               //英雄价格

public:
	/*
	* ！！！！！！
	* 使用方式：Hero* hero = Hero::create_with_attribute(...);
	* ！！！！！！
	*/
	static Hero* create_with_attribute(int id, std::string name, std::string type, int HP, int MP, int atk, int def, int range, int price,
		std::string image_name);  //创建英雄精灵
	void init_with_attribute(int id, std::string name, std::string type, int HP, int MP, int atk, int def, int range, int price,
		std::string image_name);  //初始化英雄
	void get_attribute(std::string& type, int& HP, int& MP, int& ATK, int& DEF, int& range);  //获取角色信息
	std::string getPicName();     //获取角色图片名称
	std::string getHeroName();    //获取角色名称
	const int getID();            //获取角色ID
	const int get_price();        //获取英雄价格
	virtual bool init();
	CREATE_FUNC(Hero)
};

class myHero : public Hero  //我的英雄
{
protected:
	int HP;                            //英雄当前血量
	int MP;                            //英雄当前能量
	int level;                         //英雄等级
	int condition;                     //英雄状态（1为存活，0为死亡）
	int Camp;                          //英雄阵营（1为我方，0为敌方）
	const float moveSpeed = 100.0f;    //英雄移动速度
	const float moveInterval = 0.2f;   //英雄移动间隔
	const float attackInterval = 0.3f; //角色攻击间隔
	int hero_x = 0;                    //英雄在场上的初始横坐标
	int hero_y = 0;                    //英雄在场上的初始纵坐标
	GameScene* scene_pointer = NULL;   //指向场景的指针


	cocos2d::ui::LoadingBar* HPBar;
	cocos2d::ui::LoadingBar* MPBar;
public:
	myHero* target_hero = NULL;        //英雄当前锁定的目标英雄
	Player* player = NULL;             //指向玩家的指针！！！！！！！！！！！！！！！！！！！！！！！！！！！
	/*
	* ！！！！！！
	* 使用方式：myHero* myhero = myHero::create_with_hero(hero);
	* ！！！！！！
	*/
	virtual bool init();
	CREATE_FUNC(myHero)
		static myHero* create_with_hero(Hero* hero, int m_camp, GameScene* pointer);  //创建我的英雄精灵
	void init_with_hero(Hero* hero, int m_camp, GameScene* pointer);              //初始化我的英雄

	//英雄属性相关函数
	void level_up();                          //英雄升级
	const int getLevel();                     //获取英雄等级
	bool get_condition();                     //获取英雄状态
	void hero_init();                         //一局结束后英雄状态刷新

	//英雄放置相关函数
	void move_to_board(int x, int y);          //英雄移动到场上
	void remove_from_board();                  //英雄从场上移除
	myHero* findNearestTarget(Player* player);
	myHero* myHero::findHurtTarget(Player* player);

	//英雄行动相关函数
	void start_battle();
	void end_battle();
	void change_target(myHero* hero);       //切换锁定目标
	void moveAction(float dt);              //角色移动
	void relativeMove(float x, float y);    //相对英雄坐标移动
	void absoluteMove(float x, float y);    //绝对坐标移动
	void hero_action();                     //英雄一轮锁定移动+攻击
	void attack();                          //英雄攻击
	void attacked();                        //角色被攻击
	void heal();                            //英雄治疗
	void healed();                          //英雄被治疗
	void dead();                            //英雄死亡
	/*
	调用方法
	myhero->change_target(myhero2);
	myhero->hero_action();
	*/
	const cocos2d::Size OnBoardSize = cocos2d::Size(22, 22);
	const float BarHeight = 2;
};
/* 调用方法
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
