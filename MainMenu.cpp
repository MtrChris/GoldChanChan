/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "GoldChan.h"
#include "MainMenu.h"
#include "ModeSelectScene.h"
#include "SettingScene.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
    return MainMenu::create();
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
    TEST_INIT
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 3. add your codes below...

    // 标题文字
    Label* label = CreateLabel("金铲铲之战", TextFont, Vec2::ZERO, TitleSize, TitleColor);
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height - label->getContentSize().height / 2 - TitleY));

    // add the label as a child to this layer
    this->addChild(label, 1);
    // 使用main_menu.png作为背景
    auto menuScreen = CreateBackground(this, "main_menu.jpg", visibleSize, origin);

    // 创建开始按钮、设置按钮和退出按钮
    float CenterX = origin.x + visibleSize.width / 2;
    float CenterY = origin.y + visibleSize.height / 2;

    MenuItemImage* startImage = CreateButton(Vec2(CenterX, CenterY), ButtonSize);
    MenuItemImage* settingImage = CreateButton(Vec2(CenterX, CenterY - ButtonGap), ButtonSize);
    MenuItemImage* quitImage = CreateButton(Vec2(CenterX, CenterY - 2 * ButtonGap), ButtonSize);
    startImage->initWithCallback(CC_CALLBACK_1(MainMenu::StartGameCallback, this));
    settingImage->initWithCallback(CC_CALLBACK_1(MainMenu::SettingCallback, this));
    quitImage->initWithCallback(CC_CALLBACK_1(MainMenu::QuitCallback, this));
    ButtonList.pushBack(startImage);
    ButtonList.pushBack(settingImage);
    ButtonList.pushBack(quitImage);
    Label* startText = CreateLabel("开始游戏", TextFont, Vec2(CenterX, CenterY), ButtonTextSize, ButtonTextColor);
    Label* settingText = CreateLabel("设置", TextFont, Vec2(CenterX, CenterY - ButtonGap), ButtonTextSize, ButtonTextColor);
    Label* quitText = CreateLabel("退出", TextFont, Vec2(CenterX, CenterY - 2 * ButtonGap), ButtonTextSize, ButtonTextColor);
    
    // 将上述元素添加到主界面中
    this->addChild(startText, 1);
    this->addChild(settingText, 1);
    this->addChild(quitText, 1);
    auto menu = Menu::create(startImage, settingImage, quitImage, NULL);
    menu->setPosition(Vec2::ZERO);
    menu->setName("MenuButton");
    this->addChild(menu, 0);
    SetButtonState(true);
    CATCH_INIT
    return true;
}


void MainMenu::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void MainMenu::StartGameCallback(Ref* pSender)
{
    Director::getInstance()->replaceScene(ModeSelectScene::createScene());
}

void MainMenu::SettingCallback(cocos2d::Ref* pSender)
{
    Director::getInstance()->replaceScene(SettingScene::createScene());
}

void MainMenu::QuitCallback(cocos2d::Ref* pSender)
{
    // 弹出确认对话框
    Sprite* QuitBox = Sprite::create("QuitBox.png");
    if (QuitBox == nullptr)
    {
        throw LoadFailure("QuitBox.png", "picture");
    }
    ResizePic(QuitBox, QuitBoxSize.width, QuitBoxSize.height);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    float CenterX = origin.x + visibleSize.width / 2;
    float CenterY = origin.y + visibleSize.height / 2;
    QuitBox->setPosition(Vec2(CenterX, CenterY));
    QuitBox->setName("QuitBox");

    // 创建确认和取消按钮
    Label* QuitMessage = CreateLabel("确定退出游戏？", TextFont, Vec2(CenterX, CenterY + 50), QuitMessageSize, ButtonTextColor);
    QuitMessage->setName("QuitMessage");
    float buttonX = CenterX - QuitBox->getContentSize().width / 2 + ButtonSize.width;
    float buttonY = CenterY - QuitBox->getContentSize().height / 2 + ButtonSize.height * 2;
    MenuItemImage* CancelImage = CreateButton(Vec2(buttonX, buttonY), ButtonSize);
    Label* CancelText = CreateLabel("取消", TextFont, Vec2(buttonX, buttonY), ButtonTextSize, ButtonTextColor);
    CancelText->setName("CancelButton");
    buttonX = CenterX + QuitBox->getContentSize().width / 2 - ButtonSize.width;
    MenuItemImage* ConfirmImage = CreateButton(Vec2(buttonX, buttonY), ButtonSize);
    Label* ConfirmText = CreateLabel("确定", TextFont, Vec2(buttonX, buttonY), ButtonTextSize, ButtonTextColor);
    ConfirmText->setName("ConfirmButton");
    CancelImage->setCallback(CC_CALLBACK_1(MainMenu::QuitCancelCallback, this));
    ConfirmImage->setCallback(CC_CALLBACK_1(MainMenu::menuCloseCallback, this));

    Menu* menu = Menu::create(CancelImage, ConfirmImage, NULL);
    menu->setPosition(Vec2::ZERO);
    menu->setName("QuitMenu");
    this->addChild(menu, 3);
    this->addChild(CancelText, 3);
    this->addChild(ConfirmText, 3);
    this->addChild(QuitBox, 2);
    this->addChild(QuitMessage, 3);

    // 屏蔽之前的按钮
    SetButtonState(false);
}

void MainMenu::QuitCancelCallback(Ref* pSender)
{
    this->removeChildByName("QuitBox");
    this->removeChildByName("QuitMenu");
    this->removeChildByName("QuitMessage");
    this->removeChildByName("CancelButton");
    this->removeChildByName("ConfirmButton");
    SetButtonState(true);
}

void MainMenu::SetButtonState(const bool state)
{
    for (Vector<MenuItemImage*>::iterator it = ButtonList.begin(); it < ButtonList.end(); it++)
    {
        (*it)->setEnabled(state);
    }
}
