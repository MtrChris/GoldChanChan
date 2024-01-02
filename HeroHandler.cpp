#include "HeroHandler.h"
#include "GameScene.h"
#include "Store.h"
#include "StageController.h"
#include "Player_and_Heroes.h"
#include <algorithm>

USING_NS_CC;

bool HeroHandler::init()
{
	if (!Node::init())
	{
		return false;
	}
	return true;
}

void HeroHandler::initWithScene(GameScene* m_gscene)
{
	gscene = m_gscene;
	gscene->addChild(this);
	HeroLibraryNode = Node::create();
	this->addChild(HeroLibraryNode);
	HeroLibraryNode->setVisible(false);
	initLibrary();
	initSlot();
	initBoard();
}

void HeroHandler::initLibrary()
{
	/*----------------------------------------------名称------职业---生命-能量-攻击-防御-范围-价格------------------------*/
/*----------------------------------------------名称---------职业---生命-能量--攻击-防御-范围-价格------------------------*/
	HeroLibrary[0] = Hero::create_with_attribute(0, "神里凌华", "近卫", 800, 80, 150, 100, 35, 1, "Akaya.png");
	HeroLibrary[1] = Hero::create_with_attribute(1, "恐怖奶奶", "近卫", 1000, 80, 200, 50, 35, 2, "42.png");
	HeroLibrary[2] = Hero::create_with_attribute(2, "玛恩纳", "近卫", 1500, 80, 250, 80, 35, 3, "Ma.png");
	HeroLibrary[3] = Hero::create_with_attribute(3, "钟离", "重装", 2000, 50, 150, 200, 35, 3, "Zhongli.png");
	HeroLibrary[4] = Hero::create_with_attribute(4, "符玄", "重装", 1500, 50, 150, 130, 35, 2, "Fu.png");
	HeroLibrary[5] = Hero::create_with_attribute(5, "批脸陈", "射手", 500, 100, 300, 100, 100, 2, "Chen.png");
	HeroLibrary[6] = Hero::create_with_attribute(6, "甘雨", "射手", 500, 100, 500, 0, 100, 5, "Ganyu.png");
	HeroLibrary[7] = Hero::create_with_attribute(7, "黑芙", "射手", 500, 100, 200, 50, 100, 2, "Furina.png");
	HeroLibrary[8] = Hero::create_with_attribute(8, "心海", "医疗", 1500, 60, 150, 50, 70, 2, "Kokomi.png");
	HeroLibrary[9] = Hero::create_with_attribute(9, "白芙", "医疗", 1000, 60, 100, 50, 70, 1, "Fulina.png");
	
	for (int i = 0; i < HeroNum; i++)
	{
		HeroLibraryNode->addChild(HeroLibrary[i]);
	}
}


///*----------------------------------------------名称------职业---生命-能量-攻击-防御-范围-价格------------------------*/
//HeroLibrary[0] = Hero::create_with_attribute("神里凌华", "近卫", 1500, 100, 150, 100, 1, 2, /*修改图片*/"HelloWorld.png");
//HeroLibrary[1] = Hero::create_with_attribute("恐怖奶奶", "近卫", 1500, 100, 150, 100, 1, 2, /*修改图片*/"HelloWorld.png");
//HeroLibrary[2] = Hero::create_with_attribute("玛恩纳", "近卫", 1500, 100, 150, 100, 1, 2, /*修改图片*/"HelloWorld.png");
//HeroLibrary[3] = Hero::create_with_attribute("钟离", "重装", 1500, 100, 150, 100, 1, 2, /*修改图片*/"HelloWorld.png");
//HeroLibrary[4] = Hero::create_with_attribute("符玄", "重装", 1500, 100, 150, 100, 1, 2, /*修改图片*/"HelloWorld.png");
//HeroLibrary[5] = Hero::create_with_attribute("批脸陈", "射手", 1500, 100, 150, 100, 1, 2, /*修改图片*/"HelloWorld.png");
//HeroLibrary[6] = Hero::create_with_attribute("甘雨", "射手", 9999, 60, 999, 999, 9, 9, /*修改图片*/"HelloWorld.png");
//HeroLibrary[7] = Hero::create_with_attribute("黑芙", "射手", 1500, 100, 150, 100, 1, 2, /*修改图片*/"HelloWorld.png");
//HeroLibrary[8] = Hero::create_with_attribute("心海", "医疗", 1500, 100, 150, 100, 1, 2, /*修改图片*/"HelloWorld.png");
//HeroLibrary[9] = Hero::create_with_attribute("白芙", "医疗", 1500, 100, 150, 100, 1, 2, /*修改图片*/"HelloWorld.png");

void HeroHandler::HeroToInventory(Hero* base)
{
	myHero* target = myHero::create_with_hero(base, MY, gscene);
	gscene->addChild(target, 4);
	HeroToInventory(target);
}

void HeroHandler::HeroToInventory(myHero* target)
{
	Inventory.pushBack(target);
	sort(Inventory.begin(), Inventory.end(), [&](myHero* h1, myHero* h2)
		{
			return h1->getID() < h2->getID() || h1->getID() == h2->getID() && h1->getLevel() > h2->getLevel();
		});
	UpgradeHero();
	DisplayInventory();
}

void HeroHandler::UpgradeHero()
{
	for (int i = 2; i < Inventory.size(); i++)
	{
		if(Inventory.at(i)->getID() == Inventory.at(i - 1)->getID() && 
			Inventory.at(i - 1)->getID() == Inventory.at(i - 2)->getID() &&
			Inventory.at(i)->getLevel() < MaxLevel &&
			Inventory.at(i)->getLevel() == Inventory.at(i - 1)->getLevel() &&
			Inventory.at(i - 1)->getLevel() == Inventory.at(i - 2)->getLevel())
		{
			Inventory.erase(Inventory.begin() + i - 1, Inventory.begin() + i + 1);
			Inventory.at(i - 2)->level_up();
			if (i >= 4)
			{
				i -= 3;
			}
		}
	}
}

bool HeroHandler::CheckInventoryFull()
{
	if (Inventory.size() >= SlotNum)
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		//Vec2 TextPos = origin + Vec2(ItemPosLeft.x + ButtonSize.width / 2 + HeroBatch / 2.5f * ItemBgSize.width - ButtonSize.width / 2,
		//	visibleSize.height - ItemPosLeft.y - ItemBgSize.height - ButtonDy - ButtonSize.height / 2);
		float SlotPosY = origin.y + SlotY + SlotSize.height / 2 + InfoTextDy + InfoTextSize / 2;
		Vec2 TextPos = origin + Vec2(visibleSize.width / 2, SlotPosY);
		FadingText* FullInv = FadingText::FastCreate(this, "角色栏满！", InfoTextFont,
			TextPos, InfoTextSize, InfoTextColor);
		this->addChild(FullInv, 3);
		return true;
	}
	return false;
}

void HeroHandler::initSlot()
{
	// 创建角色位
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	float SlotPosX = origin.x + gscene->ButtonSize.width + SlotX + SlotSize.width / 2;
	float SlotPosY = origin.y + SlotY + SlotSize.height / 2;
	for (int i = 0; i < SlotNum; i++)
	{
		//Sprite* HeroSlot = CreateSprite(this, Vec2(SlotPosX, SlotPosY), SlotSize, "HeroSlot.png", 1);
		MenuItemImage* HeroSlot = CreateButton(Vec2(SlotPosX, SlotPosY), SlotSize, "HeroSlotUnselect.png",
			"HeroSlotSelect.png");
		HeroSlot->setEnabled(false);
		SlotBgList.pushBack(HeroSlot);
		HeroSlot->setCallback(CC_CALLBACK_1(HeroHandler::SlotBgCallback, this));
		SlotPosX += SlotSize.width + SlotGap;
	}
	Menu* SlotMenu = Menu::createWithArray(SlotBgList);
	SlotMenu->setPosition(Vec2::ZERO);
	this->addChild(SlotMenu, 0);
	SetSlotState(true);
}

void HeroHandler::DisplayInventory()
{
	for (Vector<Node*>::iterator it = HeroInventoryNode.begin(); it < HeroInventoryNode.end(); it++)
	{
		this->removeChild(*it);
	}
	HeroInventoryNode.clear();
	// 角色信息
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	float SlotPosX = origin.x + gscene->ButtonSize.width + SlotX + SlotSize.width / 2;
	float SlotPosY = origin.y + SlotY + SlotSize.height / 2 ;
	for (int i = 0; i < Inventory.size(); i++)
	{
		std::string PicName = Inventory.at(i)->getPicName();
		Sprite* HeroImg = CreateSprite(this, Vec2(SlotPosX, SlotPosY + SlotHeroDy), SlotHeroSize, PicName.data(), 2);
		HeroInventoryNode.pushBack(HeroImg);
		std::string DisplayLevel = "Lv." + std::to_string(Inventory.at(i)->getLevel());
		Label* HeroLevel = CreateLabel(DisplayLevel.data(), LevelFont, Vec2(SlotPosX,
			SlotPosY - SlotSize.height / 2 + SlotLevelDy + SlotLevelSize / 2), SlotLevelSize,
			LevelColor[Inventory.at(i)->getLevel() - 1]);
		this->addChild(HeroLevel, 2);
		HeroInventoryNode.pushBack(HeroLevel);
		SlotPosX += SlotSize.width + SlotGap;
		if(!gscene->st->is_open() && gscene->sc->getStage() != FIGHT)
		{
			SlotBgList.at(i)->setEnabled(true);
		}
		else
		{
			SlotBgList.at(i)->setEnabled(false);
		}
	}
	for (int i = Inventory.size(); i < SlotNum; i++)
	{
		SlotBgList.at(i)->setEnabled(false);
	}
}

void HeroHandler::SlotBgCallback(Ref* pSender)
{
	for (int i = 0; i < SlotNum; i++)
	{
		MenuItem* CurSlot = SlotBgList.at(i);
		if (pSender == CurSlot && SlotId != i)
		{
			SlotId = i;
			CurSlot->selected();
			SetBoardState(true, true);
			ButtonImgList.at(1)->setEnabled(true);
			ButtonTextList.at(1)->setColor(ButtonTextColor);
		}
		else
		{
			CurSlot->unselected();
			if (SlotId == i)
			{
				SlotId = -1;
				SetBoardState(true, false);
				ButtonImgList.at(0)->setEnabled(false);
				ButtonTextList.at(0)->setColor(GrayTextColor);
				ButtonImgList.at(1)->setEnabled(false);
				ButtonTextList.at(1)->setColor(GrayTextColor);
				ButtonImgList.at(2)->setEnabled(false);
				ButtonTextList.at(2)->setColor(GrayTextColor);
			}
		}
	}
}

void HeroHandler::SetSlotState(bool state)
{
	for (int i = 0; i < SlotNum; i++)
	{
		if (i < Inventory.size())
		{
			SlotBgList.at(i)->setEnabled(state);
		}
		else
		{
			SlotBgList.at(i)->setEnabled(false);
		}
	}
	if (!state)
	{
		ButtonImgList.at(1)->setEnabled(false);
		ButtonTextList.at(1)->setColor(GrayTextColor);
		SlotId = -1;
	}
}

void HeroHandler::initBoard()
{
	for (int row = 0; row < FullRow; row++)
	{
		for (int col = 0; col < BoardCol; col++)
		{
			Board[row][col] = nullptr;
		}
	}
	SelectRow = -1;
	SelectCol = -1;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	// 绘制棋盘
	for (int row = 0; row < BoardRow; row++)
	{
		for (int col = 0; col < BoardCol; col++)
		{
			MenuItemImage* BoardBg = CreateButton(GetBoardPos(row, col), BoardBgSize, 
				"BoardBgUnselect.png", "BoardBgSelect.png", "BoardBgDisable.png");
			BoardBg->setCallback(CC_CALLBACK_1(HeroHandler::BoardBgCallback, this));
			BoardBgList.pushBack(BoardBg);
		}
	}
	Menu* BoardMenu = Menu::createWithArray(BoardBgList);
	BoardMenu->setPosition(Vec2::ZERO);
	this->addChild(BoardMenu, 2);

	float ButtonPosX = origin.x + ButtonDx + ButtonSize.width / 2;
	float ButtonPosY = origin.y + gscene->ShopPos.y + gscene->ButtonSize.height + ButtonDy +
		ButtonSize.height / 2;
	MenuItemImage* PlaceImg = CreateButton(Vec2(ButtonPosX, ButtonPosY),
		ButtonSize, "ButtonUnclick.png", "ButtonClick.png", "ButtonDisable.png");
	ButtonImgList.pushBack(PlaceImg);
	Label* PlaceText = CreateLabel("放置", ButtonTextFont, Vec2(ButtonPosX, ButtonPosY), 
		ButtonTextSize, GrayTextColor);
	ButtonTextList.pushBack(PlaceText);
	this->addChild(PlaceText, 2);
	PlaceImg->setCallback([&](Ref* pSender){
			HeroToBoard();
		});
	PlaceImg->setEnabled(false);

	ButtonPosX = origin.x + visibleSize.width - ButtonDx - ButtonSize.width / 2;
	MenuItemImage* DestroyImg = CreateButton(Vec2(ButtonPosX, ButtonPosY),
		ButtonSize, "ButtonUnclick.png", "ButtonClick.png", "ButtonDisable.png");
	ButtonImgList.pushBack(DestroyImg);
	Label* DestroyText = CreateLabel("回收", ButtonTextFont, Vec2(ButtonPosX, ButtonPosY), 
		ButtonTextSize, GrayTextColor);
	ButtonTextList.pushBack(DestroyText);
	this->addChild(DestroyText, 2);
	DestroyImg->setCallback([&](Ref* pSender) {
		DestroyHero();
		});
	DestroyImg->setEnabled(false);

	ButtonPosX = origin.x + ButtonDx + ButtonSize.width / 2;
	ButtonPosY += ButtonSize.height + ButtonDy;
	MenuItemImage* RemoveImg = CreateButton(Vec2(ButtonPosX, ButtonPosY),
		ButtonSize, "ButtonUnclick.png", "ButtonClick.png", "ButtonDisable.png");
	ButtonImgList.pushBack(RemoveImg);
	Label* RemoveText = CreateLabel("召回", ButtonTextFont, Vec2(ButtonPosX, ButtonPosY),
		ButtonTextSize, GrayTextColor);
	ButtonTextList.pushBack(RemoveText);
	this->addChild(RemoveText, 2);
	RemoveImg->setCallback([&](Ref* pSender) {
		BoardHeroToInv();
		});
	RemoveImg->setEnabled(false);

	Menu* ButtonMenu = Menu::createWithArray(ButtonImgList);
	ButtonMenu->setPosition(Vec2::ZERO);
	this->addChild(ButtonMenu, 1);

	SetBoardState(false);
}

void HeroHandler::BoardBgCallback(Ref* pSender)
{
	for (int row = 0; row < BoardRow; row++)
	{
		for (int col = 0; col < BoardCol; col++)
		{
			if (BoardBgList.at(row * BoardCol + col) == pSender)
			{
				if (SelectRow == row && SelectCol == col)
				{
					SelectRow = -1;
					SelectCol = -1;
					BoardBgList.at(row * BoardCol + col)->unselected();
					ButtonImgList.at(0)->setEnabled(false);
					ButtonTextList.at(0)->setColor(GrayTextColor);
					ButtonImgList.at(2)->setEnabled(false);
					ButtonTextList.at(2)->setColor(GrayTextColor);
				}
				else
				{
					SelectRow = row;
					SelectCol = col;
					BoardBgList.at(row * BoardCol + col)->selected();
					if(Board[row][col] == nullptr)
					{
						ButtonImgList.at(0)->setEnabled(true);
						ButtonTextList.at(0)->setColor(ButtonTextColor);
						ButtonImgList.at(2)->setEnabled(false);
						ButtonTextList.at(2)->setColor(GrayTextColor);
					}
					else
					{
						ButtonImgList.at(0)->setEnabled(false);
						ButtonTextList.at(0)->setColor(GrayTextColor);
						ButtonImgList.at(2)->setEnabled(true);
						ButtonTextList.at(2)->setColor(ButtonTextColor);
					}
				}
			}
			else
			{
				BoardBgList.at(row * BoardCol + col)->unselected();
			}
		}
	}
}

void HeroHandler::SetBoardState(bool state, bool SelectEmpty)
{
	for (int row = 0; row < BoardRow; row++)
	{
		for (int col = 0; col < BoardCol; col++)
		{
			if (Board[row][col] == nullptr)
			{
				BoardBgList.at(row * BoardCol + col)->setEnabled(state && SelectEmpty);
			}
			else
			{
				BoardBgList.at(row * BoardCol + col)->setEnabled(state && !SelectEmpty);
			}
		}
	}
	if (!state)
	{
		ButtonImgList.at(0)->setEnabled(false);
		ButtonTextList.at(0)->setColor(GrayTextColor);
		ButtonImgList.at(2)->setEnabled(false);
		ButtonTextList.at(2)->setColor(GrayTextColor);
		SelectRow = -1;
		SelectCol = -1;
	}
	for (Vector<MenuItem*>::iterator it = BoardBgList.begin(); it < BoardBgList.end(); it++)
	{
		(*it)->setVisible(state);
	}
}

Vec2 HeroHandler::GetBoardPos(int row, int col)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Vec2 BoardStartPos = origin + Vec2(visibleSize.width / 2, SlotY + SlotSize.height + BoardDy)
		- Vec2((BoardCol + 0.5f) * BoardBgSize.width / 2, 0) + Vec2(BoardBgSize / 2);
	Vec2 ret = BoardStartPos + Vec2((col + 0.5f * (row % 2)) * BoardBgSize.width,
		row * 0.75f * BoardBgSize.height);
	return ret;
}

void HeroHandler::HeroToBoard()
{
	SlotBgList.at(SlotId)->unselected();
	BoardBgList.at(SelectRow * BoardCol + SelectCol)->unselected();
	gscene->me->HeroesOnBoard.pushBack(Inventory.at(SlotId));
	ButtonImgList.at(0)->setEnabled(false);
	ButtonTextList.at(0)->setColor(GrayTextColor);
	ButtonImgList.at(1)->setEnabled(false);
	ButtonTextList.at(1)->setColor(GrayTextColor);
	ButtonImgList.at(2)->setEnabled(false);
	ButtonTextList.at(2)->setColor(GrayTextColor);
	if (gscene->sv != nullptr)
	{
		gscene->sv->SendMsg(1, Inventory.at(SlotId)->getID(), SelectRow, SelectCol);
	}
	Board[SelectRow][SelectCol] = Inventory.at(SlotId);
	Inventory.at(SlotId)->move_to_board(SelectRow, SelectCol);
	Inventory.at(SlotId)->setPosition(GetBoardPos(SelectRow, SelectCol)
	- Vec2(0, Inventory.at(SlotId)->BarHeight));
	Inventory.erase(SlotId);
	SlotId = -1;
	SelectRow = -1;
	SelectCol = -1;
	DisplayInventory();
	SetBoardState(true, false);
}

void HeroHandler::DestroyHero()
{
	SlotBgList.at(SlotId)->unselected();
	SetBoardState(false);
	gscene->st->CoinUpdate(Inventory.at(SlotId)->get_price());
	Inventory.erase(SlotId);
	SlotId = -1;
	DisplayInventory();
}

void HeroHandler::BoardHeroToInv()
{
	if (CheckInventoryFull())
	{
		return;
	}
	Board[SelectRow][SelectCol]->remove_from_board();
	gscene->me->HeroesOnBoard.eraseObject(Board[SelectRow][SelectCol]);
	BoardBgList.at(SelectRow * BoardCol + SelectCol)->unselected();
	BoardBgList.at(SelectRow * BoardCol + SelectCol)->setEnabled(false);
	ButtonImgList.at(0)->setEnabled(false);
	ButtonTextList.at(0)->setColor(GrayTextColor);
	ButtonImgList.at(1)->setEnabled(false);
	ButtonTextList.at(1)->setColor(GrayTextColor);
	ButtonImgList.at(2)->setEnabled(false);
	ButtonTextList.at(2)->setColor(GrayTextColor);
	HeroToInventory(Board[SelectRow][SelectCol]);
	Board[SelectRow][SelectCol] = nullptr;
	SelectRow = -1;
	SelectCol = -1;
}

void HeroHandler::CheckButtonState()
{
	if (gscene->sc->getStage() != FIGHT && gscene->sc->getStage() != CREEP
		&& !gscene->st->is_open() && !gscene->isQuitBoxOpen)
	{
		gscene->hh->SetSlotState(true);
		gscene->hh->SetBoardState(true, false);
	}
	else
	{
		gscene->hh->SetSlotState(false);
		gscene->hh->SetBoardState(false);
	}
}