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
	void initLibrary(); // ��ʼ��ȫ��ɫ�б�
	void initSlot(); // ��ʼ����Ʒ��
	void initBoard(); // ��ʼ������
	CREATE_FUNC(HeroHandler)

	static const int HeroNum = 10; // ��ɫ����
	Hero* HeroLibrary[HeroNum]; // Ӣ��ͼ������Ҫ���ӵ�Node�ϣ�����const��
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

	const int SlotNum = 8; // ��ɫλ������
	const float SlotY = 10;  // ��ɫλ��λ��
	const float SlotX = 20;  // ��ɫλ�뾭�����ľ���
	const float SlotGap = 10; // ������ɫλ֮��ľ���
	const cocos2d::Size SlotSize = cocos2d::Size(30, 40); // ��ɫλͼƬ�Ĵ�С
	const cocos2d::Size SlotHeroSize = cocos2d::Size(25, 25); // ��ɫͼƬ�Ĵ�С
	const float SlotHeroDy = 5; // ���������
	const float SlotLevelDy = 3; // ����ڵײ��·�
	const float SlotLevelSize = 6;
	const char* LevelFont = "����";
	const cocos2d::Color3B LevelColor[3] = { cocos2d::Color3B::GRAY, cocos2d::Color3B::GREEN,
	cocos2d::Color3B::BLUE };
	const cocos2d::Size BoardBgSize = cocos2d::Size(34, 40);
	const float BoardDy = 5;
	const cocos2d::Size ButtonSize = cocos2d::Size(40, 15);
	const float ButtonTextSize = 10;
	const cocos2d::Color3B ButtonTextColor = cocos2d::Color3B::BLACK;
	const cocos2d::Color3B GrayTextColor = cocos2d::Color3B::GRAY;
	const float ButtonDy = 5; // ������̵갴ť
	const float ButtonDx = 10;
	const char* ButtonTextFont = "����";
	const float InfoTextSize = 8;
	const char* InfoTextFont = "����";
	const cocos2d::Color3B InfoTextColor = cocos2d::Color3B::RED;
	const float InfoTextDy = 5;
};

#endif // !__HEROHANDLER_H__