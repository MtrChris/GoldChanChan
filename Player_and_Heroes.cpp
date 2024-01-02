#include"Player_and_Heroes.h"
#include"GameScene.h"
#include "HeroHandler.h"
#include "Store.h"

USING_NS_CC;
using namespace std;

//������Ӣ�����Եľ���
Hero* Hero::create_with_attribute(int id, string name, string type, int HP, int MP, int atk, int def,
	int range, int price, string image_name)
{
	Hero* hero = Hero::create();
	hero->init_with_attribute(id, name, type, HP, MP, atk, def, range, price, image_name);
	return hero;
}

//��ȡӢ������
void Hero::get_attribute(string& type, int& HP, int& MP, int& atk, int& def, int& range)
{
	type = Type;
	HP = HPmax;
	MP = MPmax;
	atk = ATK;
	def = DEF;
	range = Range;
}

//�޲γ�ʼ��Ӣ��
bool Hero::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	Name = "����";
	PicName = "image.png";
	Type = "ְҵ";
	HPmax = -1;
	MPmax = -1;
	int Price = -1;
	int ATK = -1;
	int DEF = -1;
	int Range = -1;
	// �������鲢�󶨵���ɫ
	initWithFile("HelloWorld.png");
	setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
	return true;
}

//��ʼ��������Ӣ��
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
	// �������鲢�󶨵���ɫ
	initWithFile(image_name);
	setAnchorPoint(Vec2(0.5, 0.5));
	scheduleUpdate();
}

//��ȡͼƬ����
string Hero::getPicName()
{
	return PicName;
}
//��ȡӢ������
string Hero::getHeroName()
{
	return Name;
}

const int Hero::getID()
{
	return heroID;
}

//��ȡӢ�ۼ۸�
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

//�����ҵĳ�ʼ��ɫ
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
	if ((camp == MY && Type != "ҽ��") || (camp == ENEMY && Type == "ҽ��"))
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

//��ɫ����
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

//һ�ֽ�����Ӣ��״̬ˢ��
void myHero::hero_init()
{
	HP = HPmax;    //����Ѫ
	HPBar->setPercent(100.0f * HP / HPmax);
	MP = 0;        //��������
	MPBar->setPercent(100.0f * MP / MPmax);
	condition = 1; //���Ϊ���
	target_hero = NULL;  //�������з�
	setPosition(scene_pointer->hh->GetBoardPos(hero_x, hero_y) - Vec2(0, BarHeight));
}

//�л�����Ŀ��
void myHero::change_target(myHero* hero)
{
	target_hero = hero;
}

//Ӣ�۹���
void myHero::attack()
{
	int damage = ATK - target_hero->DEF;
	if (MP == MPmax) {
		damage *= 2;
		MP = 0;
		MPBar->setPercent(100.0f * MP / MPmax);
	}
	if (damage < 50) damage = 50; //�����˺�
	if (target_hero->HP <= damage) {  //��ɳ���Ѫ�����˺�����ɫ����
		target_hero->HP = 0;
		target_hero->condition = 0;   //��ɫ����
	}
	else
		target_hero->HP -= damage;

	MP += 5;
	MPBar->setPercent(100.0f * MP / MPmax);
	target_hero->attacked();
}
//Ӣ�۱�����
void myHero::attacked()
{
	HPBar->setPercent(100.0f * HP / HPmax);
	auto tintTo = TintTo::create(0.05f, 255, 0, 0);
	auto tintBack = TintTo::create(0.05f, 255, 255, 255);
	auto seq = Sequence::create(tintTo, tintBack, nullptr);
	runAction(seq);
}

//Ӣ������
void myHero::heal()
{
	int therapeutic_dose = ATK;  //��ɫ������
	if (MP == MPmax) {  //��ɫ�ͷż���
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

//Ӣ�۱�����
void myHero::healed()
{
	HPBar->setPercent(100.0f * HP / HPmax);
	auto tintTo = TintTo::create(0.05f, 0, 255, 0);
	auto tintBack = TintTo::create(0.05f, 255, 255, 255);
	auto seq = Sequence::create(tintTo, tintBack, nullptr);
	runAction(seq);
}

//Ӣ������
void myHero::dead()
{
	if (Camp)
	{
		scene_pointer->st->CoinUpdate(Price);
	}
	auto fadeOut = FadeOut::create(1.0f);
	runAction(fadeOut);
}

//��ɫ����Ϊ���ɼ�
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