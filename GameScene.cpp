#include "GameScene.h"
#include "Store.h"
#include "StageController.h"
#include "HeroHandler.h"
#include "MainMenu.h"

USING_NS_CC;

Scene* GameScene::CreateScene()
{
	return GameScene::create();
}

bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	initGraph(); // 绘制图形界面
	// 创建Store
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
	SetButtonState(true); // 开启所有按钮的功能
	enemy->AIAction();
	//DisplayResult(false);
	
	return true;
}

void GameScene::initGraph()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 游戏背景
	auto GameScreen = CreateBackground(this, "GameBg.png", visibleSize, origin);

	Vector<MenuItem*> menuitems;

	// 创建经验区
	//Vec2 ExpVec = origin + Vec2(ButtonSize.width / 2, ButtonSize.height / 2) + ExpPos;
	//MenuItemImage* BuyExpButton = CreateButton(ExpVec, ButtonSize, "ExpButtonUnselect.png", "ExpButtonSelect.png");
	//Label* BuyExpText = CreateLabel("购买经验", TextFont, ExpVec, ButtonTextSize, ButtonTextColor);
	//auto ExpBar = CreateLoadingBar("ExpBar.png", ExpVec + Vec2(0, ButtonSize.height / 2 + ExpGap),
	//	ExpBarSize, 100);
	//float OutlineScale = (BarOutlineScale - 1) * ExpBarSize.height;
	//Sprite* ExpBarOutline = CreateSprite(this, ExpVec + Vec2(0, ButtonSize.height / 2 + ExpGap),
	//	Size(OutlineScale, OutlineScale) + ExpBarSize, "BarOutline.png");

	//menuitems.pushBack(BuyExpButton);
	//ButtonList.pushBack(BuyExpButton);
	//this->addChild(BuyExpText, 1);
	//this->addChild(ExpBar, 2);

	// 创建商店按钮
	Vec2 ShopVec = Vec2(origin.x + visibleSize.width - ButtonSize.width / 2,
		origin.y + ButtonSize.height / 2) + ShopPos;
	StoreButton = CreateButton(ShopVec, ButtonSize, "ShopButtonUnselect.png", "ShopButtonSelect.png");
	StoreText = CreateLabel("商店", TextFont, ShopVec, ButtonTextSize, ButtonTextColor);
	StoreButton->setCallback([&](Ref* pSender)
		{
			st->StoreOpen = !st->StoreOpen;
			st->ToggleStore(st->StoreOpen);
		});
	menuitems.pushBack(StoreButton);
	ButtonList.pushBack(StoreButton);
	this->addChild(StoreText, 1);


	// 创建右上角按钮
	Vec2 ExitVec = Vec2(origin.x + visibleSize.width - ExitButtonSize.width / 2,
		origin.y + visibleSize.height - ExitButtonSize.height / 2) + ExitPos;
	MenuItemImage* ExitButton = CreateButton(ExitVec, ExitButtonSize, "ExitUnclick.png", "ExitClick.png");
	ButtonList.pushBack(ExitButton);
	ExitButton->setCallback(CC_CALLBACK_1(GameScene::ExitButtonCallback, this));

	// 创建左上角信息
	float CoinBgPosX = origin.x + CoinBgPos.x + CoinBgSize.width / 2;
	float CoinBgPosY = origin.y + visibleSize.height - CoinBgPos.y - CoinBgSize.height / 2;
	Sprite* CoinBg = CreateSprite(this, Vec2(CoinBgPosX, CoinBgPosY), CoinBgSize, "InfoBg.png", 1);
	// 创建金币图像
	Sprite* CoinImg = CreateSprite(this, Vec2(CoinBgPosX - CoinBgSize.width / 2 + CoinImgX, CoinBgPosY),
		CoinSize, "Coin.png", 2);
	// 创建金币文本
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
	// 弹出确认对话框
	Sprite* QuitBox = Sprite::create("QuitBox.png");
	if (QuitBox == nullptr)
	{
		throw LoadFailure("QuitBox.png", "picture");
	}
	ResizePic(QuitBox, QuitBoxSize.width, QuitBoxSize.height);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	float CenterX = origin.x + visibleSize.width / 2;
	float CenterY = origin.y + visibleSize.height / 2;
	QuitBox->setPosition(Vec2(CenterX, CenterY));
	QuitBox->setName("QuitBox");

	// 创建确认和取消按钮
	Label* QuitMessage = CreateLabel("确定退出当前对局？", "宋体", Vec2(CenterX, CenterY + 50), QuitMessageSize, ButtonTextColor);
	QuitMessage->setName("QuitMessage");
	float buttonX = CenterX - QuitBox->getContentSize().width / 2 + QuitButtonSize.width;
	float buttonY = CenterY - QuitBox->getContentSize().height / 2 + QuitButtonSize.height * 2;
	MenuItemImage* CancelImage = CreateButton(Vec2(buttonX, buttonY), QuitButtonSize);
	Label* CancelText = CreateLabel("取消", "宋体", Vec2(buttonX, buttonY), QuitTextSize, ButtonTextColor);
	CancelText->setName("CancelButton");
	buttonX = CenterX + QuitBox->getContentSize().width / 2 - QuitButtonSize.width;
	MenuItemImage* ConfirmImage = CreateButton(Vec2(buttonX, buttonY), QuitButtonSize);
	Label* ConfirmText = CreateLabel("确定", "宋体", Vec2(buttonX, buttonY), QuitTextSize, ButtonTextColor);
	ConfirmText->setName("ConfirmButton");
	CancelImage->setCallback(CC_CALLBACK_1(GameScene::QuitCancelCallback, this));
	ConfirmImage->setCallback([&](Ref* pSender) {
		Director::getInstance()->replaceScene(MainMenu::createScene());
		});

	Menu* menu = Menu::create(CancelImage, ConfirmImage, NULL);
	menu->setPosition(Vec2::ZERO);
	menu->setName("QuitMenu");
	this->addChild(menu, 3);
	this->addChild(CancelText, 3);
	this->addChild(ConfirmText, 3);
	this->addChild(QuitBox, 2);
	this->addChild(QuitMessage, 3);
	SetButtonState(false); // 屏蔽游戏内按钮的功能
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
	SetButtonState(true); // 恢复游戏内按钮的功能
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

/* FadingText类的实现 */
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
	SetButtonState(false); // 屏蔽游戏内按钮的功能
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

	Label* RetryText = CreateLabel("重试", ResTextFont, ButtonPos, ResTextSize, ResTextColor);
	this->addChild(RetryText, 6);

	ButtonPos.x += ResButtonSize.width + 2 * ResButtonX;
	MenuItemImage* ExitImg = CreateButton(ButtonPos, ResButtonSize);
	ExitImg->setCallback(CC_CALLBACK_1(GameScene::MainMenuCallback, this));

	Label* ExitText = CreateLabel("主菜单", ResTextFont, ButtonPos, ResTextSize, ResTextColor);
	this->addChild(ExitText, 6);

	Menu* ResMenu = Menu::create(RetryImg, ExitImg, NULL);
	ResMenu->setPosition(Vec2::ZERO);
	this->addChild(ResMenu, 5);
}

void GameScene::RetryCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(GameScene::create());
}

void GameScene::MainMenuCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(MainMenu::create());
}