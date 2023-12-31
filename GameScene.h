#pragma once

#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "GoldChan.h"
#include "Player_and_Heroes.h"

class Store;
class StageController;
class HeroHandler;
class Player;

class GameScene : public cocos2d::Scene
{
	friend class Store;
	friend class StageController;
	friend class HeroHandler;
	friend class myHero;
	friend class Player;
private:
	Store* st;
	StageController* sc;
	HeroHandler* hh;
	Player* me;
	Player* enemy;
	bool isQuitBoxOpen;

	cocos2d::Vector<cocos2d::MenuItemImage*> ButtonList;
	cocos2d::Label* StoreText; // �̵갴ť������
	cocos2d::MenuItemImage* StoreButton; // �̵갴ť
	cocos2d::Label* CoinNum;   // ��ʾ���н�������ı�
	void SetButtonState(const bool state);

public:
	static cocos2d::Scene* CreateScene();
	virtual bool init(); 
	CREATE_FUNC(GameScene)

	void initGraph(); // ��ʼ��ͼ�ν���
	void ExitButtonCallback(cocos2d::Ref* pSender); // �˳���ť�ĺ���
	void QuitCancelCallback(cocos2d::Ref* pSender); // �˳�ȡ����ť�ĺ���
	void DisplayResult(bool state); // �������
	void RetryCallback(Ref* pSender); // ���԰�ť
	void MainMenuCallback(Ref* pSender); // ���˵���ť

	/* ����Ϊ��ͼ�ν����йصĺ궨�� */
	const cocos2d::Size ButtonSize = cocos2d::Size(50, 50); // �̵�;��鰴ť�Ĵ�С
	const cocos2d::Size ExpBarSize = cocos2d::Size(50, 5);  // �������Ĵ�С 
	const cocos2d::Size ExitButtonSize = cocos2d::Size(15, 15); // �˳���ť�Ĵ�С
	const cocos2d::Vec2 ExpPos = cocos2d::Vec2(10, 10);   // ���鰴ť��λ�ã�������½ǣ�
	const cocos2d::Vec2 ShopPos = cocos2d::Vec2(-10, 10); // �̵갴ť��λ�ã�������½ǣ�
	const cocos2d::Vec2 ExitPos = cocos2d::Vec2(-10, -10);  // �˳���ť��λ�ã�������Ͻǣ�
	const float ExpGap = 20; // �������뾭�鰴ť֮���λ��
	const float ButtonTextSize = 8; // ��ť�����ֵĴ�С
	const cocos2d::Color3B ButtonTextColor = cocos2d::Color3B::BLACK; // ��ť���ֵ���ɫ
	const char* TextFont = "����";
	const cocos2d::Size QuitBoxSize = cocos2d::Size(300, 150);        // �˳������Ĵ�С
	const cocos2d::Size QuitButtonSize = cocos2d::Size(100, 40);      // �˳�ȷ�ϰ�ť�Ĵ�С
	const float QuitTextSize = 15;                                    // ��ť���ֵĴ�С
	const float QuitMessageSize = 20;                                 // �˳���ʾ��Ϣ�Ĵ�С
	const cocos2d::Size CoinBgSize = cocos2d::Size(50, 15);           // ��ʾ������������Ĵ�С
	const cocos2d::Vec2 CoinBgPos = cocos2d::Vec2(10, 10);            // ��ʾ�������������λ�ã���������Ͻǣ�
	const float CoinImgX = 10; // ���ͼ������ڱ�Ե��λ��
	const float CoinNumX = 10; // �����������ڱ�Ե��λ��
	const float CoinNumSize = 10; // ����������ı���С
	const cocos2d::Size CoinSize = cocos2d::Size(10, 10); // ���ͼ��Ĵ�С
	const cocos2d::Color3B InfoTextColor = cocos2d::Color3B::BLACK; // ��Ϣ���ֵ���ɫ
	const float BarOutlineScale = 1.2f; // ������������ڿ�������
	const int PlayerHP = 100;
	const cocos2d::Size ResSize = cocos2d::Size(300, 180);
	const float ResButtonY = 40;
	const float ResButtonX = 50;
	const cocos2d::Size ResButtonSize = cocos2d::Size(50, 20);
	const char* ResTextFont = "����";
	const float ResTextSize = 10;
	const cocos2d::Color3B ResTextColor = cocos2d::Color3B::BLACK;
};

class FadingText : public cocos2d::Label
{
private:
	cocos2d::Node* parent;
	float deltaTime;
	int alpha;
public:
	static FadingText* FastCreate(cocos2d::Node* m_parent, const char* display, const char* font, const cocos2d::Vec2& pos,
		const float size, const cocos2d::Color3B& color = cocos2d::Color3B::BLACK, float dt = 0.01f);
	virtual bool init();
	void FastInit(cocos2d::Node* m_parent, const char* display, const char* font, const cocos2d::Vec2& pos,
		const float size, const cocos2d::Color3B& color = cocos2d::Color3B::BLACK, float dt = 0.01f);
	CREATE_FUNC(FadingText)
	
	void FadeFunc(float dt); // ���غ���
};

#endif // !__GAMESCENE_H__