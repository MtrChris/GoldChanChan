#pragma once

#ifndef __SETTINGSCENE_H__
#define __SETTINGSCENE_H__

#include "GoldChan.h"

class SettingScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	cocos2d::Vector<cocos2d::MenuItem*> ButtonList;
	cocos2d::Vector<cocos2d::Label*> ButtonTextList;

	virtual bool init();
	void BackButtonCallback(Ref* pSender); // ���ذ�ť�Ļص�����
	void MusicButtonCallBack(Ref* pSender);

	CREATE_FUNC(SettingScene)

	/* ����Ϊ��ѡ�����һЩͼ�β����Ķ��� */
	const char* TextFont = "����";								 // ����
	const float TitleY = 10;								     // �����λ���붥���ľ���
	const float TitleSize = 20;								     // ��������Ĵ�С
	const cocos2d::Color3B TitleColor = cocos2d::Color3B::BLACK; // ������ɫ
	const cocos2d::Vec2 BackButtonPos = cocos2d::Vec2(20, 20);   // ���ذ�ť��λ��
	const cocos2d::Size BackButtonSize = cocos2d::Size(50, 20);  // ���ذ�ť�Ĵ�С
	const float BackTextSize = 10;                               // ��������Ĵ�С
	const float StartY = 20; // ��ťλ��
	const float TextX = 100; // ����˵����ť��λ��
	const float ButtonX = 100; // ��ť��λ�ã�����ұ߽磩
	const float RowGap = 5; // �о�
	const cocos2d::Size ButtonSize = cocos2d::Size(50, 20);
	const float ButtonTextSize = 10; // ��ť���ֵĴ�С
	const char* ButtonTextFont = "����";
	const cocos2d::Color3B ButtonTextColor = cocos2d::Color3B::BLACK;
	const float SettingInfoSize = 10;
	const char* SettingInfoFont = "����";
	const cocos2d::Color3B SettingInfoColor = cocos2d::Color3B::YELLOW;
};

#endif // !__SETTINGSCENE_H__