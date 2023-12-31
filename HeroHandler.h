#pragma once
#ifndef __HEROHANDLER_H__
#define __HEROHANDLER_H__

#include "GoldChan.h"

class GameScene;
class Hero;
class myHero;

class HeroHandler : public cocos2d::Node
{
	friend class Player;
	friend class myHero;
public:
	static const int BoardRow = 3;
	static const int FullRow = 2 * BoardRow;
	static const int BoardCol = 10;

private:
	GameScene* gscene;
	cocos2d::Node* HeroLibraryNode;
	cocos2d::Vector<myHero*> Inventory;
	cocos2d::Vector<cocos2d::MenuItem*> SlotBgList;
	cocos2d::Vector<myHero*> HeroOnBoard;
	cocos2d::Vector<cocos2d::Node*> HeroInventoryNode;
	cocos2d::Vector<cocos2d::MenuItem*> BoardBgList;
	myHero* Board[FullRow][BoardCol];
	cocos2d::Vector<cocos2d::MenuItem*> ButtonImgList;
	cocos2d::Vector<cocos2d::Label*> ButtonTextList;
	int SlotId;
	int SelectRow;
	int SelectCol;
public:
	virtual bool init();
	void initWithScene(GameScene* m_gscene);
	void initLibrary(); // 初始化全角色列表
	void initSlot(); // 初始化物品栏
	void initBoard(); // 初始化棋盘
	CREATE_FUNC(HeroHandler)

	static const int HeroNum = 10; // 角色数量
	Hero* HeroLibrary[HeroNum]; // 英雄图鉴（需要链接到Node上，不加const）
	const int MaxLevel = 3;
	bool CheckInventoryFull();
	void HeroToInventory(myHero* target);
	void HeroToInventory(Hero* base);
	void UpgradeHero();
	void DisplayInventory();
	void SlotBgCallback(Ref* pSender);
	void SetSlotState(bool state);
	void SetBoardState(bool state, bool SelectEmpty = true);
	void BoardBgCallback(Ref* pSender);
	cocos2d::Vec2 GetBoardPos(int row, int col);
	void HeroToBoard();
	void BoardHeroToInv();
	void DestroyHero();
	void CheckButtonState();

	const int SlotNum = 8; // 角色位的数量
	const float SlotY = 10;  // 角色位的位置
	const float SlotX = 20;  // 角色位与经验区的距离
	const float SlotGap = 10; // 两个角色位之间的距离
	const cocos2d::Size SlotSize = cocos2d::Size(30, 40); // 角色位图片的大小
	const cocos2d::Size SlotHeroSize = cocos2d::Size(25, 25); // 角色图片的大小
	const float SlotHeroDy = 5; // 相对于中心
	const float SlotLevelDy = 3; // 相对于底部下方
	const float SlotLevelSize = 6;
	const char* LevelFont = "宋体";
	const cocos2d::Color3B LevelColor[3] = { cocos2d::Color3B::GRAY, cocos2d::Color3B::GREEN,
	cocos2d::Color3B::BLUE };
	const cocos2d::Size BoardBgSize = cocos2d::Size(34, 40);
	const float BoardDy = 5;
	const cocos2d::Size ButtonSize = cocos2d::Size(40, 15);
	const float ButtonTextSize = 10;
	const cocos2d::Color3B ButtonTextColor = cocos2d::Color3B::BLACK;
	const cocos2d::Color3B GrayTextColor = cocos2d::Color3B::GRAY;
	const float ButtonDy = 5; // 相对于商店按钮
	const float ButtonDx = 10;
	const char* ButtonTextFont = "宋体";
	const float InfoTextSize = 8;
	const char* InfoTextFont = "宋体";
	const cocos2d::Color3B InfoTextColor = cocos2d::Color3B::RED;
	const float InfoTextDy = 5;
};

#endif // !__HEROHANDLER_H__