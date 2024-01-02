#include"Player_and_Heroes.h"
#include"GameScene.h"
#include "HeroHandler.h"
#include "Store.h"

USING_NS_CC;
using namespace std;

//创建带英雄属性的精灵
Hero* Hero::create_with_attribute(int id, string name, string type, int HP, int MP, int atk, int def,
	int range, int price, string image_name)
{
	Hero* hero = Hero::create();
	hero->init_with_attribute(id, name, type, HP, MP, atk, def, range, price, image_name);
	return hero;
}

//获取英雄属性
void Hero::get_attribute(string& type, int& HP, int& MP, int& atk, int& def, int& range)
{
	type = Type;
	HP = HPmax;
	MP = MPmax;
	atk = ATK;
	def = DEF;
	range = Range;
}

//无参初始化英雄
bool Hero::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	Name = "姓名";
	PicName = "image.png";
	Type = "职业";
	HPmax = -1;
	MPmax = -1;
	int Price = -1;
	int ATK = -1;
	int DEF = -1;
	int Range = -1;
	// 创建精灵并绑定到角色
	initWithFile("HelloWorld.png");
	setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
	return true;
}

//初始化带属性英雄
void Hero::init_with_attribute(int id, string name, string type, int hp, int mp, int atk, int def,
	int range, int price, string image_name)
{
	heroID = id;
	Name = name;
	PicName = image_name;
	Type = type;
	HPmax = hp;
	MPmax = mp;
	ATK = atk;
	DEF = def;
	Range = range;
	Price = price;
	// 创建精灵并绑定到角色
	initWithFile(image_name);
	setAnchorPoint(Vec2(0.5, 0.5));
	scheduleUpdate();
}

//获取图片名称
string Hero::getPicName()
{
	return PicName;
}
//获取英雄名称
string Hero::getHeroName()
{
	return Name;
}

const int Hero::getID()
{
	return heroID;
}

//获取英雄价格
const int Hero::get_price()
{
	return Price;
}

/* ---- Hero /\ ---- myHero \/ ----- */

bool myHero::init()
{
	if (!Sprite::init() || !Hero::init())
	{
		return false;
	}
	return true;
}

//创建我的初始角色
void myHero::init_with_hero(Hero* hero, int camp, GameScene* pointer)
{
	std::string type;
	int hp, mp, atk, def, range;
	hero->get_attribute(type, hp, mp, atk, def, range);
	scene_pointer = pointer;
	heroID = hero->getID();
	Name = hero->getHeroName();
	PicName = hero->getPicName();
	Type = type;
	HPmax = hp;
	HP = HPmax;
	MPmax = mp;
	MP = 0;
	ATK = atk;
	DEF = def;
	Range = range;
	Price = hero->get_price();
	level = 1;
	condition = 1;
	Camp = camp;
	if ((camp == MY && Type != "医疗") || (camp == ENEMY && Type == "医疗"))
		player = scene_pointer->enemy;
	else
		player = scene_pointer->me;
	Sprite::initWithFile(PicName);
	ResizePic(this, OnBoardSize.width, OnBoardSize.height);
	this->setVisible(false);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 BarPos = Vec2(1.0f / getScaleX() * OnBoardSize.width / 2, BarHeight / 2 +
		1.0f / getScaleY() * OnBoardSize.height);
	Size BarSize = Size(1.0f / getScaleX() * OnBoardSize.width, 1.0f / getScaleY() * BarHeight);
	//HPBar = CreateLoadingBar("HPBar.png", Vec2(OnBoardSize.width / 2, BarHeight / 2 + OnBoardSize.height),
	//	Size(visibleSize.width, BarHeight), 100);
	if(Camp)
	{
		HPBar = CreateLoadingBar("EnemyHPBar.png", BarPos, BarSize, 100);
	}
	else
	{
		HPBar = CreateLoadingBar("MyHPBar.png", BarPos, BarSize, 100);
	}
	this->addChild(HPBar);
	BarPos.y += 1.0f / getScaleY() * BarHeight;
	//MPBar = CreateLoadingBar("MPBar.png", Vec2(OnBoardSize.width / 2, -3 * OnBoardSize.height / 2),
	//	Size(OnBoardSize.width, BarHeight), 100);
	MPBar = CreateLoadingBar("MPBar.png", BarPos, BarSize);
	this->addChild(MPBar);
}

myHero* myHero::create_with_hero(Hero* hero, int flag, GameScene* pointer)
{
	myHero* myhero = myHero::create();
	myhero->init_with_hero(hero, flag, pointer);
	return myhero;
}

const int myHero::getLevel()
{
	return level;
}

//角色升级
void myHero::level_up()
{
	level++;
	HPmax *= 2;
	MPmax *= 2;
	ATK *= 2;
	DEF *= 2;
	Price *= 3;
}

bool myHero::get_condition()
{
	return condition;
}

//一局结束后英雄状态刷新
void myHero::hero_init()
{
	HP = HPmax;    //回满血
	HPBar->setPercent(100.0f * HP / HPmax);
	MP = 0;        //回满能量
	MPBar->setPercent(100.0f * MP / MPmax);
	condition = 1; //标记为存活
	target_hero = NULL;  //不锁定敌方
	setPosition(scene_pointer->hh->GetBoardPos(hero_x, hero_y) - Vec2(0, BarHeight));
}

//切换锁定目标
void myHero::change_target(myHero* hero)
{
	target_hero = hero;
}

//英雄攻击
void myHero::attack()
{
	int damage = ATK - target_hero->DEF;
	if (MP == MPmax) {
		damage *= 2;
		MP = 0;
		MPBar->setPercent(100.0f * MP / MPmax);
	}
	if (damage < 50) damage = 50; //保底伤害
	if (target_hero->HP <= damage) {  //造成超过血量的伤害，角色死亡
		target_hero->HP = 0;
		target_hero->condition = 0;   //角色死亡
	}
	else
		target_hero->HP -= damage;

	MP += 5;
	MPBar->setPercent(100.0f * MP / MPmax);
	target_hero->attacked();
}
//英雄被攻击
void myHero::attacked()
{
	HPBar->setPercent(100.0f * HP / HPmax);
	auto tintTo = TintTo::create(0.05f, 255, 0, 0);
	auto tintBack = TintTo::create(0.05f, 255, 255, 255);
	auto seq = Sequence::create(tintTo, tintBack, nullptr);
	runAction(seq);
}

//英雄治疗
void myHero::heal()
{
	int therapeutic_dose = ATK;  //角色治疗量
	if (MP == MPmax) {  //角色释放技能
		therapeutic_dose *= 2;
		MP = 0;
		MPBar->setPercent(100.0f * MP / MPmax);
	}
	if (target_hero->HP + therapeutic_dose >= target_hero->HPmax) {
		target_hero->HP = target_hero->HPmax;
	}
	else
		target_hero->HP += therapeutic_dose;
	MP += 5;
	MPBar->setPercent(100.0f * MP / MPmax);
	target_hero->healed();
}

//英雄被治疗
void myHero::healed()
{
	HPBar->setPercent(100.0f * HP / HPmax);
	auto tintTo = TintTo::create(0.05f, 0, 255, 0);
	auto tintBack = TintTo::create(0.05f, 255, 255, 255);
	auto seq = Sequence::create(tintTo, tintBack, nullptr);
	runAction(seq);
}

//英雄死亡
void myHero::dead()
{
	if (Camp)
	{
		scene_pointer->st->CoinUpdate(Price);
	}
	auto fadeOut = FadeOut::create(1.0f);
	runAction(fadeOut);
}

//角色设置为不可见
void myHero::remove(float dlt) {
	this->setVisible(false);
}

void myHero::start_battle()
{
	condition = 1;
	change_target(findNearestTarget(player));
	schedule(CC_SCHEDULE_SELECTOR(myHero::moveAction), moveInterval);
}

void myHero::end_battle()
{
	if (get_condition())
	{
		if(isScheduled(CC_SCHEDULE_SELECTOR(myHero::moveAction)))
		{
			unschedule(CC_SCHEDULE_SELECTOR(myHero::moveAction));
		}
		hero_init();
	}
}