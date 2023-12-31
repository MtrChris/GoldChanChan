#include "GoldChan.h"
#include "GameScene.h"
#include "Store.h"
#include "HeroHandler.h"
#include "StageController.h"

USING_NS_CC;

bool Store::init()
{
	if (!Node::init())
	{
		return false;
	}
	return true;
}

void Store::initWithScene(GameScene* m_gscene)
{
	gscene = m_gscene;
	ItemList = new Hero * [HeroBatch];
	ShuffleItem();
	gscene->addChild(this, 1);
	StoreOpen = false;
	CurCoin = StartCoin;
	CoinDisplay();
	SelectId = -1;
	NextRefresh = true;
}

void Store::ShuffleItem()
{
	for(int i = 0; i < HeroBatch; i++)
	{
		ItemList[i] = gscene->hh->HeroLibrary[rand() % gscene->hh->HeroNum];
		//ItemList[i] = gscene->hh->HeroLibrary[0];
		if (ItemBgList.size() == HeroBatch)
		{
			ItemBgList.at(i)->setEnabled(true);
		}
	}
}

void Store::ToggleStore(const bool state)
{
	if (state)
	{
		SetLabelText(gscene->StoreText, "返回");
		initMenu();
		gscene->hh->SetSlotState(false);
		gscene->hh->SetBoardState(false);
	}
	else
	{
		for (Vector<Node*>::iterator it = StoreElem.begin(); it < StoreElem.end(); it++)
		{
			this->removeChild(*it);
		}
		StoreElem.clear();
		SetLabelText(gscene->StoreText, "商店");
		gscene->hh->CheckButtonState();
	}
}

void Store::initMenu()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 创建角色位的背景和人物
	ItemBgMenu = Menu::create();
	UpdateDisplay();
	//ItemBgMenu = Menu::createWithArray(ItemBgList);
	ItemBgMenu->setPosition(Vec2::ZERO);
	StoreElem.pushBack(ItemBgMenu);
	this->addChild(ItemBgMenu, 2);
	SelectId = -1;

	// 创建商店按钮
	Vector<MenuItem*> ButtonImage;
	// 1. 角色详情按钮
	DetailNode = Node::create();
	this->addChild(DetailNode, 3);
	StoreElem.pushBack(DetailNode);
	Vec2 ButtonPos = origin + Vec2(ItemPosLeft.x + ButtonSize.width / 2,
		visibleSize.height - ItemPosLeft.y - ItemBgSize.height - ButtonDy - ButtonSize.height / 2);
	DetailButton = CreateButton(ButtonPos, ButtonSize, "ButtonUnclick.png", "ButtonClick.png", 
		"ButtonDisable.png");
	DetailText = CreateLabel("详情", ButtonTextFont, ButtonPos, ButtonTextSize, ButtonTextColor);
	DetailButton->setCallback([&](Ref* pSender) {
		ToggleDetail(true);
		});
	ButtonImage.pushBack(DetailButton);
	StoreElem.pushBack(DetailText);
	this->addChild(DetailText, 3);

	// 2. 购买按钮
	ButtonPos.x += HeroBatch / 2.0f * ItemBgSize.width - ButtonSize.width / 2;
	PurchaseButton = CreateButton(ButtonPos, ButtonSize, 
		"ButtonUnclick.png", "ButtonClick.png", "ButtonDisable.png");
	PurchaseButton->setCallback([&](Ref* pSender) {
		PurchaseItem();
	});
	PurchaseText = CreateLabel("购买", ButtonTextFont, ButtonPos, ButtonTextSize, ButtonTextColor);
	ButtonImage.pushBack(PurchaseButton);
	StoreElem.pushBack(PurchaseText);
	this->addChild(PurchaseText, 3);
	CheckPurchase();

	// 3. 刷新按钮
	ButtonPos.x += HeroBatch / 2.0f * ItemBgSize.width - ButtonSize.width / 2;
	RefreshButton = CreateButton(ButtonPos, ButtonSize, "ButtonUnclick.png", "ButtonClick.png", "ButtonDisable.png");
	RefreshText = CreateLabel("刷新", ButtonTextFont, ButtonPos, ButtonTextSize, ButtonTextColor);
	ButtonImage.pushBack(RefreshButton);
	StoreElem.pushBack(RefreshText);
	this->addChild(RefreshText, 3);
	CheckRefresh();
	RefreshButton->setCallback([&](Ref* pSender) {
		SelectId = -1;
		CoinUpdate(-RefreshPrice);
		ShuffleItem();
		UpdateDisplay();
		CheckRefresh();
		CheckPurchase();
		ToggleDetail(false);
	});
	
	// 4. 锁定按钮
	ButtonPos.y += ItemBgSize.height + 2 * ButtonDy + ButtonSize.height;
	MenuItemImage* LockButton = CreateButton(ButtonPos, ButtonSize, "ButtonUnclick.png", "ButtonClick.png", "ButtonDisable.png");
	Label* LockText = CreateLabel("锁定", ButtonTextFont, ButtonPos, ButtonTextSize, ButtonTextColor);
	ButtonImage.pushBack(LockButton);
	this->addChild(LockText, 3);
	StoreElem.pushBack(LockText);
	LockButton->setCallback([this, LockButton](Ref* pSender) {
		NextRefresh = !NextRefresh;
		if (NextRefresh)
		{
			LockButton->unselected();
		}
		else
		{
			LockButton->selected();
		}
		});

	Menu* ButtonMenu = Menu::createWithArray(ButtonImage);
	ButtonMenu->setPosition(Vec2::ZERO);
	StoreElem.pushBack(ButtonMenu);
	this->addChild(ButtonMenu, 2);
}

void Store::StoreButtonCallback(Ref* pSender)
{
	StoreOpen = !StoreOpen;
	ToggleStore(StoreOpen);
}

void Store::CheckPurchase()
{
	if (SelectId < 0)
	{
		PurchaseButton->setEnabled(false);
		PurchaseText->setColor(GrayText);
		DetailButton->setEnabled(false);
		DetailText->setColor(GrayText);
	}
	else if (CurCoin < ItemList[SelectId]->get_price())
	{
		PurchaseButton->setEnabled(false);
		PurchaseText->setColor(GrayText);
		DetailButton->setEnabled(true);
		DetailText->setColor(ButtonTextColor);
	}
	else
	{
		PurchaseButton->setEnabled(true);
		PurchaseText->setColor(ButtonTextColor);
		DetailButton->setEnabled(true);
		DetailText->setColor(ButtonTextColor);
	}
}

void Store::CheckRefresh()
{
	if (CurCoin < RefreshPrice)
	{
		RefreshButton->setEnabled(false);
		RefreshText->setColor(GrayText);
	}
	else
	{
		RefreshButton->setEnabled(true);
		RefreshText->setColor(ButtonTextColor);
	}
}

void Store::CoinUpdate(const int dif)
{
	if (dif == 0)
	{
		return;
	}
	CurCoin += dif;
	CoinDisplay();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	std::string DisplayMsg = (dif > 0 ? "+" : "") + std::to_string(dif);
	float CoinMsgPosX = origin.x + gscene->CoinBgPos.x + gscene->CoinBgSize.width - CoinMsgDx;
	float CoinMsgPosY = origin.y + visibleSize.height - gscene->CoinBgPos.y - gscene->CoinBgSize.height / 2;
	FadingText* CoinMsg = FadingText::FastCreate(this, DisplayMsg.data(), CoinMsgFont, Vec2(CoinMsgPosX, CoinMsgPosY),
		CoinMsgSize, dif > 0 ? CoinMsgColorA : CoinMsgColorB, 0.01f);
	gscene->addChild(CoinMsg, 2);
}

void Store::ItemBgCallback(Ref* pSender)
{
	for (int i = 0; i < HeroBatch; i++)
	{
		MenuItem* CurItem = ItemBgList.at(i);
		if (pSender == CurItem && SelectId != i)
		{
			SelectId = i;
			CurItem->selected();
		}
		else
		{
			CurItem->unselected();
			if (SelectId == i)
			{
				SelectId = -1;
			}
		}
	}
	ToggleDetail(false);
	CheckPurchase();
}

void Store::CoinDisplay()
{
	std::string s_CurCoin = std::to_string(CurCoin);
	gscene->CoinNum->setString(s_CurCoin);
}

void Store::PurchaseItem()
{
	if(SelectId >= 0)
	{
		if (gscene->hh->CheckInventoryFull())
		{
			return;
		}
		CoinUpdate(-ItemList[SelectId]->get_price());
		gscene->hh->HeroToInventory(ItemList[SelectId]);
		ItemList[SelectId] = nullptr;
		SelectId = -1;
		ToggleDetail(false);
		UpdateDisplay();
		CheckPurchase();
		CheckRefresh();
	}
}

void Store::UpdateDisplay()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	for (Vector<Node*>::iterator it = ItemDisplayNode.begin(); it < ItemDisplayNode.end(); it++)
	{
		this->removeChild(*it);
	}
	for (Vector<MenuItem*>::iterator it = ItemBgList.begin(); it < ItemBgList.end(); it++)
	{
		this->removeChild(*it);
	}

	ItemBgList.clear();
	ItemDisplayNode.clear();
	ItemBgMenu->removeAllChildren();
	float ItemPosX = origin.x + ItemPosLeft.x + ItemBgSize.width / 2;
	float ItemPosY = origin.y + visibleSize.height - ItemPosLeft.y - ItemBgSize.height / 2;

	for (int i = 0; i < HeroBatch; i++)
	{
		MenuItemImage* ItemBg = CreateButton(Vec2(ItemPosX, ItemPosY), ItemBgSize, "ItemBgUnselect.png",
			"ItemBgSelect.png", "ItemBgDisable.png");
		ItemBg->setCallback(CC_CALLBACK_1(Store::ItemBgCallback, this));
		ItemBgList.pushBack(ItemBg);
		Node* DisplayNode = Node::create();
		this->addChild(DisplayNode, 3);
		StoreElem.pushBack(DisplayNode);
		ItemDisplayNode.pushBack(DisplayNode);
		if (ItemList[i] == nullptr)
		{
			ItemBg->setEnabled(false);
		}
		else
		{
			Vec2 HeroImgDisplayPos = Vec2(ItemPosX + HeroImgPos.x - ItemBgSize.width / 2, ItemPosY - HeroImgPos.y + ItemBgSize.height / 2)
				+ Vec2(HeroImgSize.width / 2, -HeroImgSize.height / 2);
			Sprite* HeroImg = CreateSprite(DisplayNode, HeroImgDisplayPos, HeroImgSize, ItemList[i]->getPicName().data());
			std::string HeroName = ItemList[i]->getHeroName();
			float ElemPosX = ItemPosX - HeroNamePos.x;
			float ElemPosY = ItemPosY - ItemBgSize.height / 2 + HeroNamePos.y + HeroNameSize / 2;
			Label* HeroNameDisplay = CreateLabel(HeroName.data(), InfoTextFont, Vec2(ElemPosX, ElemPosY),
				HeroNameSize, HeroNameColor);
			DisplayNode->addChild(HeroNameDisplay);
			ElemPosX += HeroNamePos.x + HeroPricePos.x + CoinSize.width / 2;
			ElemPosY += HeroPricePos.y - HeroNamePos.y - HeroNameSize / 2 + CoinSize.height / 2;
			Sprite* CoinImg = CreateSprite(DisplayNode, Vec2(ElemPosX, ElemPosY), CoinSize, "Coin.png");
			ElemPosX += CoinSize.width / 2 + HeroPriceGap;
			ElemPosY += HeroPriceSize / 2 - CoinSize.height / 2;
			std::string HeroPrice = std::to_string(ItemList[i]->get_price());
			Label* HeroPriceDisplay = CreateLabel(HeroPrice.data(), InfoTextFont, Vec2(ElemPosX, ElemPosY),
				HeroPriceSize, HeroPriceColor);
			if (CurCoin < ItemList[i]->get_price())
			{
				HeroPriceDisplay->setColor(PriceRedColor);
			}
			DisplayNode->addChild(HeroPriceDisplay);
		}
		ItemPosX += ItemBgSize.width;
		ItemBgMenu->addChild(ItemBg);
	}
}

void Store::ToggleDetail(bool mode)
{
	if (DetailNode->getChildrenCount() > 0)
	{
		DetailNode->removeAllChildren();
	}
	else if (mode)
	{
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		auto visibleSize = Director::getInstance()->getVisibleSize();
		float DetailPosX = origin.x + ItemPosLeft.x + 2.5f * ItemBgSize.width;
		float DetailPosY = origin.y + visibleSize.height - ItemPosLeft.y - ItemBgSize.height
			- ButtonDy - ButtonSize.height - DetailPosDy - DetailBgSize.height / 2;
		Sprite* DetailBg = CreateSprite(DetailNode, Vec2(DetailPosX, DetailPosY), DetailBgSize, "DetailBg.png");
		std::string PicName = ItemList[SelectId]->getPicName();
		Vec2 ProfileDisplayPos = Vec2(DetailPosX - DetailBgSize.width / 2, DetailPosY + DetailBgSize.height / 2) 
			+ Vec2(ProfilePos.x, -ProfilePos.y) + Vec2(ProfileSize.width / 2, -ProfileSize.height / 2);
		Sprite* HeroProfile = CreateSprite(DetailNode, ProfileDisplayPos, ProfileSize, PicName.data());
		float TextStartX = DetailPosX - DetailBgSize.width / 2 + ProfilePos.x + ProfileSize.width + TextEdgeX;
		float TextStartY = DetailPosY + DetailBgSize.height / 2 - TextRowGap;

		// 1. 角色名称
		std::string name, type;
		int HP, MP, ATK, DEF, range;
		name = ItemList[SelectId]->getHeroName();
		ItemList[SelectId]->get_attribute(type, HP, MP, ATK, DEF, range);

		Vec2 TextPos = Vec2(TextStartX, TextStartY - DetailTextSize / 2);
		DisplayInfo("名称：", name.data(), TextPos);

		TextPos.y -= TextRowGap + DetailTextSize;
		DisplayInfo("职业：", type.data(), TextPos);

		/* ---- 第二列 ---- */
		TextPos.x += TextColGap;
		TextPos.y = TextStartY - DetailTextSize / 2;
		DisplayInfo("生命值：", std::to_string(HP).data(), TextPos);

		TextPos.y -= TextRowGap + DetailTextSize;
		DisplayInfo("能量：", std::to_string(MP).data(), TextPos);

		TextPos.y -= TextRowGap + DetailTextSize;
		DisplayInfo("攻击力：", std::to_string(ATK).data(), TextPos);

		TextPos.y -= TextRowGap + DetailTextSize;
		DisplayInfo("防御力：", std::to_string(DEF).data(), TextPos);

		TextPos.y -= TextRowGap + DetailTextSize;
		DisplayInfo("攻击范围：", std::to_string(range).data(), TextPos);
	}
}

void Store::DisplayInfo(const char* Atb, const char* DisplayStr, Vec2& pos)
{
	float TextPosX = pos.x;
	float TextPosY = pos.y;
	Label* AtbName = CreateLabel(Atb, DetailFont, Vec2::ZERO, DetailTextSize, TextInfoColor);
	AtbName->setPosition(Vec2(TextPosX + AtbName->getContentSize().width / 2, TextPosY));
	TextPosX += AtbName->getContentSize().width;
	DetailNode->addChild(AtbName);
	Label* InfoStr = CreateLabel(DisplayStr, DetailFont, Vec2::ZERO, DetailTextSize, TextAtbColor);
	InfoStr->setPosition(Vec2(TextPosX + InfoStr->getContentSize().width / 2, TextPosY));
	DetailNode->addChild(InfoStr);
}

bool Store::is_open()
{
	return StoreOpen;
}
