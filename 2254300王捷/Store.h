#pragma once

#ifndef __STORE_H__
#define __STORE_H__

#include "GoldChan.h"
#include "GameScene.h"
#include "Player_and_Heroes.h"


class Store : public cocos2d::Node
{
	friend class GameScene;
	friend class StageController;
private:
	Hero** ItemList;
	cocos2d::Vector<cocos2d::Node*> StoreElem; // �̵������Ԫ��
	GameScene* gscene; // �����̵���ĳ���
	bool StoreOpen; // ��¼�̵�Ĵ�״̬
	cocos2d::Vector<cocos2d::MenuItem*> ItemBgList;
	cocos2d::Menu* ItemBgMenu;
	cocos2d::Vector<Node*> ItemDisplayNode; // չʾ��Ʒ�Ľ��
	cocos2d::MenuItemImage* DetailButton; // ���鰴ť
	cocos2d::Label* DetailText; // �����ı�
	cocos2d::MenuItemImage* PurchaseButton; // ����ť
	cocos2d::Label* PurchaseText; // �����ı�
	cocos2d::MenuItemImage* RefreshButton;  // ˢ�°�ť
	cocos2d::Label* RefreshText;  // ˢ���ı�
	cocos2d::Node* DetailNode; // ��ʾ����Ľ��
	int SelectId; // ��ǰѡ�е��̵�λ
	int CurCoin;

	void CheckPurchase(); // ȷ�Ϲ���ť�Ƿ����
	void CheckRefresh();  // ȷ��ˢ�°�ť�Ƿ����
public:
	virtual bool init();
	void initWithScene(GameScene* m_gscene);
	CREATE_FUNC(Store)
	void ShuffleItem(); // �����ȡ��ɫ
	void PurchaseItem(); // �����ɫ
	void ToggleStore(const bool state); // ��/�ر��̵� 
	void initMenu(); // ��ʼ���̵�˵�
	void CoinDisplay(); // ���²���ʾ��ǰ��������
	void UpdateDisplay(); // ���¼���ɫ
	void CoinUpdate(const int dif);    // ���»�������

	void StoreButtonCallback(cocos2d::Ref* pSender); // �̵갴ť�Ļص�����
	void ItemBgCallback(cocos2d::Ref* pSender);      // �̵��ɫλ�Ļص�����
	void ToggleDetail(bool mode); // �ı��ɫ�������ʾ״̬
	void Store::DisplayInfo(const char* Atb, const char* DisplayStr, cocos2d::Vec2& pos); // ��ʾ��ɫ��Ϣ
	bool is_open(); // �̵��Ƿ��

	const int HeroBatch = 5; // ÿһ��ˢ�µĽ�ɫ����
	bool NextRefresh; // ��һ���Ƿ�ˢ��
	/* ---- ����ΪһЩͼ�β����Ķ��� ---- */
	const cocos2d::Size ItemBgSize = cocos2d::Size(80, 100); // ��Ʒ�����Ĵ�С
	const cocos2d::Vec2 ItemPosLeft = cocos2d::Vec2(30, 30); // �������Ʒ��λ�ã���������Ͻǣ�
	const float ButtonDy = 5;                               // ��ť���ɫλ�����������
	const cocos2d::Size ButtonSize = cocos2d::Size(40, 15);   // ��ť�Ĵ�С
	const char* ButtonTextFont = "����"; // ��ť�ı�������
	const float ButtonTextSize = 10; // ��ť�ı��Ĵ�С
	const cocos2d::Color3B ButtonTextColor = cocos2d::Color3B::BLACK; // ��ť�ı�����ɫ
	const cocos2d::Color3B GrayText = cocos2d::Color3B::GRAY;         // �Ҷ��ı�����ɫ
	const int StartCoin = 20; // ��ʼ���
	const int RefreshPrice = 2; // ˢ��������
	const char* InfoTextFont = "����"; // ��ɫ��Ϣ������
	const float InfoTextSize = 8;
	const cocos2d::Size HeroImgSize = cocos2d::Size(70, 70); // Ӣ��ͼ��Ĵ�С
	const cocos2d::Vec2 HeroImgPos = cocos2d::Vec2(5, 5);   // Ӣ��ͼ���λ�ã�����ڽ�ɫλ���Ͻǣ�
	const cocos2d::Vec2 HeroNamePos = cocos2d::Vec2(15, 5); // ��ɫ���Ƶ�λ�ã�����ڽ�ɫλ�ײ��м䣩
	const cocos2d::Vec2 HeroPricePos = cocos2d::Vec2(15, 5); // ��ɫ�۸��λ�ã�����ڽ�ɫλ�ײ��м䣩
	const cocos2d::Color3B HeroNameColor = cocos2d::Color3B::BLACK; // ��ɫ���Ƶ���ɫ
	const cocos2d::Color3B HeroPriceColor = cocos2d::Color3B::BLACK; // ��ɫ�۸����ɫ
	const cocos2d::Color3B PriceRedColor = cocos2d::Color3B::RED;
	const float HeroNameSize = 8;
	const float HeroPriceGap = 10;
	const float HeroPriceSize = 8;
	const cocos2d::Size CoinSize = cocos2d::Size(8, 8);
	const float DetailPosDy = 5; // ��ɫ��������ڰ�ť��λ��
	const cocos2d::Size DetailBgSize = cocos2d::Size(300, 70);
	const float TextRowGap = 5; // �о�
	const float TextColGap = 100; // �о�
	const float TextEdgeX = 10;
	const cocos2d::Color3B TextAtbColor = cocos2d::Color3B::YELLOW; // ��ɫ����������ɫ
	const cocos2d::Color3B TextInfoColor = cocos2d::Color3B::WHITE;
	const float DetailTextSize = 8;
	const char* DetailFont = "����";
	const cocos2d::Vec2 ProfilePos = cocos2d::Vec2(5, 5); // ��ɫͼƬλ�ã���������Ͻǣ�
	const cocos2d::Size ProfileSize = cocos2d::Size(60, 60);
	const cocos2d::Color3B CoinMsgColorA = cocos2d::Color3B(200, 155, 0);
	const cocos2d::Color3B CoinMsgColorB = cocos2d::Color3B(255, 10, 0);
	const float CoinMsgSize = 8; // ���������Ϣ�Ĵ�С
	const float CoinMsgDx = 8; // ���������Ϣ����ʾλ��
	const char* CoinMsgFont = "����";
};

#endif  // !__STORE_H__