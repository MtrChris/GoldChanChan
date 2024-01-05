#pragma once

/*
*  ������
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

    // �밴ť�Ͳ˵���صĺ���
    void menuCloseCallback(cocos2d::Ref* pSender);
    void StartGameCallback(cocos2d::Ref* pSender);
    void SettingCallback(cocos2d::Ref* pSender);
    void QuitCallback(cocos2d::Ref* pSender);
    void QuitCancelCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(MainMenu)

    /* ����Ϊ�������һЩͼ�β����Ķ��� */
    const char* TextFont = "����";                                      // ���ֵ�����
    const float TitleY = 10;                                            // ���������λ��
    const float TitleSize = 48;                                         // ����Ĵ�С
    const cocos2d::Color3B TitleColor = cocos2d::Color3B(255, 215, 10); // ������ɫ
    const float ButtonGap = 50;                                         // ������ť֮��ļ��
    const cocos2d::Size ButtonSize = cocos2d::Size(100, 40);            // ��ť�Ĵ�С
    const float ButtonTextSize = 15;                                    // ��ť���ֵĴ�С 
    const cocos2d::Size QuitButtonSize = cocos2d::Size(100, 40);        // �˳�ȷ�ϰ�ť�Ĵ�С
    const float QuitTextSize = 15;                                      // ��ť���ֵĴ�С
    cocos2d::Color3B ButtonTextColor = cocos2d::Color3B::BLACK;         // ��ť���ֵ���ɫ
    const cocos2d::Size QuitBoxSize = cocos2d::Size(300, 150);          // �˳������Ĵ�С
    const float QuitMessageSize = 20;                                   // �˳���ʾ��Ϣ�Ĵ�С
};

#endif // __MAINMENU_H__
