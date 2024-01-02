#include "GameScene.h"
#include "Store.h"
#include "StageController.h"
#include "HeroHandler.h"
#include "MainMenu.h"

USING_NS_CC;

Scene* GameScene::CreateScene(bool multi)
{
	GameScene* ret = GameScene::create();
	if (multi)
	{
		ret->sv = Sever::create();
		ret->addChild(ret->sv);
		ret->initSever();
	}
	else
	{
		ret->sv = nullptr;
		ret->enemy->AIAction();
	}
	return ret;
}

bool GameScene::init()
{
	TEST_INIT
	if (!Scene::init())
	{
		return false;
	}
	initGraph(); // ����ͼ�ν���
	// ����Store
	hh = HeroHandler::create();
	hh->initWithScene(this);
	st = Store::create();
	st->initWithScene(this);
	sc = StageController::create();
	sc->initWithScene(this);
	me = enemy = nullptr;
	me = Player::NormalCreate(this, "player", "Player.png", PlayerHP);
	enemy = Player::NormalCreate(this, "AI", "Player.png", PlayerHP);
	isQuitBoxOpen = false;
	SetButtonState(true); // �������а�ť�Ĺ���
	//enemy->AIAction();

	CATCH_INIT

	return true;
}

void GameScene::initGraph()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// ��Ϸ����
	auto GameScreen = CreateBackground(this, "GameBg.png", visibleSize, origin);

	Vector<MenuItem*> menuitems;

	// ����������
	//Vec2 ExpVec = origin + Vec2(ButtonSize.width / 2, ButtonSize.height / 2) + ExpPos;
	//MenuItemImage* BuyExpButton = CreateButton(ExpVec, ButtonSize, "ExpButtonUnselect.png", "ExpButtonSelect.png");
	//Label* BuyExpText = CreateLabel("������", TextFont, ExpVec, ButtonTextSize, ButtonTextColor);
	//auto ExpBar = CreateLoadingBar("ExpBar.png", ExpVec + Vec2(0, ButtonSize.height / 2 + ExpGap),
	//	ExpBarSize, 100);
	//float OutlineScale = (BarOutlineScale - 1) * ExpBarSize.height;
	//Sprite* ExpBarOutline = CreateSprite(this, ExpVec + Vec2(0, ButtonSize.height / 2 + ExpGap),
	//	Size(OutlineScale, OutlineScale) + ExpBarSize, "BarOutline.png");

	//menuitems.pushBack(BuyExpButton);
	//ButtonList.pushBack(BuyExpButton);
	//this->addChild(BuyExpText, 1);
	//this->addChild(ExpBar, 2);

	// �����̵갴ť
	Vec2 ShopVec = Vec2(origin.x + visibleSize.width - ButtonSize.width / 2,
		origin.y + ButtonSize.height / 2) + ShopPos;
	StoreButton = CreateButton(ShopVec, ButtonSize, "ShopButtonUnselect.png", "ShopButtonSelect.png");
	StoreText = CreateLabel("�̵�", TextFont, ShopVec, ButtonTextSize, ButtonTextColor);
	StoreButton->setCallback([&](Ref* pSender)
		{
			st->StoreOpen = !st->StoreOpen;
			st->ToggleStore(st->StoreOpen);
		});
	menuitems.pushBack(StoreButton);
	ButtonList.pushBack(StoreButton);
	this->addChild(StoreText, 1);


	// �������Ͻǰ�ť
	Vec2 ExitVec = Vec2(origin.x + visibleSize.width - ExitButtonSize.width / 2,
		origin.y + visibleSize.height - ExitButtonSize.height / 2) + ExitPos;
	MenuItemImage* ExitButton = CreateButton(ExitVec, ExitButtonSize, "ExitUnclick.png", "ExitClick.png");
	ButtonList.pushBack(ExitButton);
	ExitButton->setCallback(CC_CALLBACK_1(GameScene::ExitButtonCallback, this));

	// �������Ͻ���Ϣ
	float CoinBgPosX = origin.x + CoinBgPos.x + CoinBgSize.width / 2;
	float CoinBgPosY = origin.y + visibleSize.height - CoinBgPos.y - CoinBgSize.height / 2;
	Sprite* CoinBg = CreateSprite(this, Vec2(CoinBgPosX, CoinBgPosY), CoinBgSize, "InfoBg.png", 1);
	// �������ͼ��
	Sprite* CoinImg = CreateSprite(this, Vec2(CoinBgPosX - CoinBgSize.width / 2 + CoinImgX, CoinBgPosY),
		CoinSize, "Coin.png", 2);
	// ��������ı�
	CoinNum = CreateLabel("", TextFont, Vec2(CoinBgPosX - CoinBgSize.width / 2 + CoinImgX + CoinSize.width
		+ CoinNumX, CoinBgPosY), CoinNumSize, InfoTextColor);
	this->addChild(CoinNum, 2);

	menuitems.pushBack(ExitButton);
	Menu* menu = Menu::createWithArray(menuitems);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
}

void GameScene::ExitButtonCallback(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	float CenterX = origin.x + visibleSize.width / 2;
	float CenterY = origin.y + visibleSize.height / 2;
	// ����ȷ�϶Ի���
	Sprite* QuitBox = CreateSprite(this, Vec2(CenterX, CenterY), QuitBoxSize, "QuitBox.png", 5);
	QuitBox->setName("QuitBox");

	// ����ȷ�Ϻ�ȡ����ť
	Label* QuitMessage = CreateLabel("ȷ���˳���ǰ�Ծ֣�", "����", Vec2(CenterX, CenterY + QuitMessageY), 
		QuitMessageSize, ButtonTextColor);
	QuitMessage->setName("QuitMessage");
	float buttonX = CenterX - QuitBoxSize.width / 2 + QuitButtonSize.width;
	float buttonY = CenterY - QuitBoxSize.height / 2 + QuitButtonSize.height;
	MenuItemImage* CancelImage = CreateButton(Vec2(buttonX, buttonY), QuitButtonSize);
	Label* CancelText = CreateLabel("ȡ��", "����", Vec2(buttonX, buttonY), QuitTextSize, ButtonTextColor);
	CancelText->setName("CancelButton");
	CancelImage->setCallback(CC_CALLBACK_1(GameScene::QuitCancelCallback, this));

	buttonX = CenterX + QuitBoxSize.width / 2 - QuitButtonSize.width;
	MenuItemImage* ConfirmImage = CreateButton(Vec2(buttonX, buttonY), QuitButtonSize);
	Label* ConfirmText = CreateLabel("ȷ��", "����", Vec2(buttonX, buttonY), QuitTextSize, ButtonTextColor);
	ConfirmText->setName("ConfirmButton");
	ConfirmImage->setCallback([&](Ref* pSender) {
		Director::getInstance()->replaceScene(MainMenu::createScene());
		});

	MenuItemImage* RetryImage = CreateButton(Vec2(CenterX, buttonY), QuitButtonSize);
	Label* RetryText = CreateLabel("����", "����", Vec2(CenterX, buttonY), QuitTextSize, ButtonTextColor);
	RetryText->setName("RetryButton");
	RetryImage->setCallback(CC_CALLBACK_1(GameScene::RetryCallback, this));

	Menu* menu = Menu::create(CancelImage, ConfirmImage, RetryImage, NULL);
	menu->setPosition(Vec2::ZERO);
	menu->setName("QuitMenu");
	this->addChild(menu, 6);
	this->addChild(CancelText, 6);
	this->addChild(ConfirmText, 6);
	this->addChild(RetryText, 6);
	this->addChild(QuitMessage, 6);
	SetButtonState(false); // ������Ϸ�ڰ�ť�Ĺ���
	isQuitBoxOpen = true;
	hh->CheckButtonState();
}

void GameScene::QuitCancelCallback(Ref* pSender)
{
	this->removeChildByName("QuitBox");
	this->removeChildByName("QuitMenu");
	this->removeChildByName("QuitMessage");
	this->removeChildByName("CancelButton");
	this->removeChildByName("ConfirmButton");
	this->removeChildByName("RetryButton");
	SetButtonState(true); // �ָ���Ϸ�ڰ�ť�Ĺ���
	isQuitBoxOpen = false;
	hh->CheckButtonState();
}

void GameScene::SetButtonState(const bool state)
{
	for (Vector<MenuItemImage*>::iterator it = ButtonList.begin(); it < ButtonList.end(); it++)
	{
		(*it)->setEnabled(state);
	}
}

/* FadingText���ʵ�� */
FadingText* FadingText::FastCreate(Node* m_parent, const char* display, const char* font, const Vec2& pos,
	const float size, const Color3B& color, float dt)
{
	FadingText* Text = FadingText::create();
	Text->FastInit(m_parent, display, font, pos, size, color, dt);
	return Text;
}

bool FadingText::init()
{
	return true;
}

void FadingText::FastInit(Node* m_parent, const char* display, const char* font, const Vec2& pos,
	const float size, const Color3B& color, float dt)
{
	std::string displayName = display;
	GBKToUTF8(displayName, "gb2312", "utf-8");
	setSystemFontName(font);
	setSystemFontSize(size);
	setDimensions(Size::ZERO.width, Size::ZERO.height);
	setAlignment(TextHAlignment::LEFT, TextVAlignment::TOP);
	setString(displayName.data());
	//if (Text == nullptr)
	//{
	//	throw LoadFailure(font, "font");
	//}
	setPosition(pos);
	setColor(color);
	deltaTime = dt;
	alpha = 255;
	parent = m_parent;
	this->schedule(CC_SCHEDULE_SELECTOR(FadingText::FadeFunc), dt);
}

void FadingText::FadeFunc(float dt)
{
	this->setOpacity(alpha);
	alpha--;
	if (alpha == 0)
	{
		this->unschedule(CC_SCHEDULE_SELECTOR(FadingText::FadeFunc));
		parent->removeChild(this);
	}
}

void GameScene::DisplayResult(bool state)
{
	SetButtonState(false); // ������Ϸ�ڰ�ť�Ĺ���
	isQuitBoxOpen = true;
	hh->CheckButtonState();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	const char* picname;
	if (state)
	{
		picname = "Win.png";
	}
	else
	{
		picname = "Lose.png";
	}
	Sprite* ResBg = CreateSprite(this, origin + Vec2(visibleSize / 2), ResSize, picname, 5);
	Vec2 ButtonPos = origin + Vec2(visibleSize / 2) + Vec2(-ResButtonX, -ResButtonY) - Vec2(ButtonSize / 2);
	MenuItemImage* RetryImg = CreateButton(ButtonPos, ResButtonSize);
	RetryImg->setCallback(CC_CALLBACK_1(GameScene::RetryCallback, this));

	Label* RetryText = CreateLabel("����", ResTextFont, ButtonPos, ResTextSize, ResTextColor);
	this->addChild(RetryText, 6);

	ButtonPos.x += ResButtonSize.width + 2 * ResButtonX;
	MenuItemImage* ExitImg = CreateButton(ButtonPos, ResButtonSize);
	ExitImg->setCallback(CC_CALLBACK_1(GameScene::MainMenuCallback, this));

	Label* ExitText = CreateLabel("���˵�", ResTextFont, ButtonPos, ResTextSize, ResTextColor);
	this->addChild(ExitText, 6);

	Menu* ResMenu = Menu::create(RetryImg, ExitImg, NULL);
	ResMenu->setPosition(Vec2::ZERO);
	this->addChild(ResMenu, 5);
}

void GameScene::RetryCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(GameScene::CreateScene(sv != nullptr));
}

void GameScene::MainMenuCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(MainMenu::create());
}

void GameScene::initSever()
{
	SetButtonState(false);
	schedule(CC_SCHEDULE_SELECTOR(GameScene::SeverConnect));
}

void GameScene::SeverConnect(float dt)
{
	if (sv->connect())
	{
		unschedule(CC_SCHEDULE_SELECTOR(GameScene::SeverConnect));
		SetButtonState(true);
		schedule(CC_SCHEDULE_SELECTOR(GameScene::SeverMsgRead));
	}
}

void GameScene::SeverMsgRead(float dt)
{
	int op, id, row, col;
	if (sv->GetMsg(op, id, row, col))
	{
		if (op == 1)
		{
			myHero* newHero = myHero::create_with_hero(hh->HeroLibrary[id], ENEMY, this);
			enemy->HeroesOnBoard.pushBack(newHero);
			addChild(newHero, 0);
			hh->Board[row][col] = newHero;
			newHero->move_to_board(row, col);
			newHero->setPosition(hh->GetBoardPos(row, col)
				- Vec2(0, newHero->BarHeight));
		}
		else if(op == 2)
		{
			hh->Board[row][col]->remove_from_board();
			enemy->HeroesOnBoard.eraseObject(hh->Board[row][col]);
			hh->Board[row][col]->erase_hero();
			hh->Board[row][col] = nullptr;
		}
	}
}