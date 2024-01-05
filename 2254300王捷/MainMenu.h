#pragma once

/*
*  主界面
*/

#ifndef __MAINMENU_H__
#define __MAINMENU_H__

#include "cocos2d.h"

class MainMenu : public cocos2d::Scene
{
private:
    cocos2d::Vector<cocos2d::MenuItemImage*> ButtonList;

    void SetButtonState(const bool state);
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // 与按钮和菜单相关的函数
    void menuCloseCallback(cocos2d::Ref* pSender);
    void StartGameCallback(cocos2d::Ref* pSender);
    void SettingCallback(cocos2d::Ref* pSender);
    void QuitCallback(cocos2d::Ref* pSender);
    void QuitCancelCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(MainMenu)

    /* 以下为标题界面一些图形参数的定义 */
    const char* TextFont = "宋体";                                      // 文字的字体
    const float TitleY = 10;                                            // 标题的纵向位置
    const float TitleSize = 48;                                         // 标题的大小
    const cocos2d::Color3B TitleColor = cocos2d::Color3B(255, 215, 10); // 标题颜色
    const float ButtonGap = 50;                                         // 两个按钮之间的间隔
    const cocos2d::Size ButtonSize = cocos2d::Size(100, 40);            // 按钮的大小
    const float ButtonTextSize = 15;                                    // 按钮文字的大小 
    const cocos2d::Size QuitButtonSize = cocos2d::Size(100, 40);        // 退出确认按钮的大小
    const float QuitTextSize = 15;                                      // 按钮文字的大小
    cocos2d::Color3B ButtonTextColor = cocos2d::Color3B::BLACK;         // 按钮文字的颜色
    const cocos2d::Size QuitBoxSize = cocos2d::Size(300, 150);          // 退出弹窗的大小
    const float QuitMessageSize = 20;                                   // 退出提示信息的大小
};

#endif // __MAINMENU_H__
