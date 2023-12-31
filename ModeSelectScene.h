#pragma once

/*
*  ѡ����ģʽ/����ģʽ�Ľ���
*/

#ifndef __MODESELECTSCENE_H__
#define __MODESELECTSCENE_H__

#include "GoldChan.h"

class ModeSelectScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void SingleStartCallback(Ref* pSender);
	void MultiPlayerStartCallback(Ref* pSender);
	void BackButtonCallback(Ref* pSender); // ���ذ�ť�Ļص�����

	CREATE_FUNC(ModeSelectScene)

	/* ����Ϊ��ѡ�����һЩͼ�β����Ķ��� */
	const float BoxYDif = 20;                               // ѡ����������������
	const cocos2d::Size BoxSize = cocos2d::Size(200, 200);
	const float BoxTextSize = 20;                           // ѡ�������Ĵ�С
	cocos2d::Color3B TextColor = cocos2d::Color3B::BLACK;   // ������ɫ
	const cocos2d::Size ButtonSize = cocos2d::Size(50, 20); // ���ذ�ť�Ĵ�С
	const cocos2d::Vec2 ButtonPos = cocos2d::Vec2(20, 20);  // ���ذ�ť������·���λ��
	const char* TextFont = "����";                          // ���ֵ�����
	const float ButtonTextSize = 10;                        // ���ذ�ť����Ĵ�С
};

#endif // !__MODESELECTSCENE_H__