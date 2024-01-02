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
	cocos2d::Vector<cocos2d::Node*> StoreElem; // 商店的所有元素
	GameScene* gscene; // 调用商店类的场景
	bool StoreOpen; // 记录商店的打开状态
	cocos2d::Vector<cocos2d::MenuItem*> ItemBgList;
	cocos2d::Menu* ItemBgMenu;
	cocos2d::Vector<Node*> ItemDisplayNode; // 展示商品的结点
	cocos2d::MenuItemImage* DetailButton; // 详情按钮
	cocos2d::Label* DetailText; // 详情文本
	cocos2d::MenuItemImage* PurchaseButton; // 购买按钮
	cocos2d::Label* PurchaseText; // 购买文本
	cocos2d::MenuItemImage* RefreshButton;  // 刷新按钮
	cocos2d::Label* RefreshText;  // 刷新文本
	cocos2d::Node* DetailNode; // 显示详情的结点
	int SelectId; // 当前选中的商店位
	int CurCoin;

	void CheckPurchase(); // 确认购买按钮是否可用
	void CheckRefresh();  // 确认刷新按钮是否可用
public:
	virtual bool init();
	void initWithScene(GameScene* m_gscene);
	CREATE_FUNC(Store)
	void ShuffleItem(); // 随机抽取角色
	void PurchaseItem(); // 购买角色
	void ToggleStore(const bool state); // 打开/关闭商店 
	void initMenu(); // 初始化商店菜单
	void CoinDisplay(); // 更新并显示当前货币数量
	void UpdateDisplay(); // 重新检查角色
	void CoinUpdate(const int dif);    // 更新货币数量

	void StoreButtonCallback(cocos2d::Ref* pSender); // 商店按钮的回调函数
	void ItemBgCallback(cocos2d::Ref* pSender);      // 商店角色位的回调函数
	void ToggleDetail(bool mode); // 改变角色详情的显示状态
	void Store::DisplayInfo(const char* Atb, const char* DisplayStr, cocos2d::Vec2& pos); // 显示角色信息
	bool is_open(); // 商店是否打开

	const int HeroBatch = 5; // 每一轮刷新的角色数量
	bool NextRefresh; // 下一轮是否刷新
	/* ---- 以下为一些图形参数的定义 ---- */
	const cocos2d::Size ItemBgSize = cocos2d::Size(80, 100); // 物品背景的大小
	const cocos2d::Vec2 ItemPosLeft = cocos2d::Vec2(30, 30); // 最左端物品的位置（相对于左上角）
	const float ButtonDy = 5;                               // 按钮与角色位的纵坐标距离
	const cocos2d::Size ButtonSize = cocos2d::Size(40, 15);   // 按钮的大小
	const char* ButtonTextFont = "宋体"; // 按钮文本的字体
	const float ButtonTextSize = 10; // 按钮文本的大小
	const cocos2d::Color3B ButtonTextColor = cocos2d::Color3B::BLACK; // 按钮文本的颜色
	const cocos2d::Color3B GrayText = cocos2d::Color3B::GRAY;         // 灰度文本的颜色
	const int StartCoin = 20; // 初始金币
	const int RefreshPrice = 2; // 刷新所需金币
	const char* InfoTextFont = "宋体"; // 角色信息的字体
	const float InfoTextSize = 8;
	const cocos2d::Size HeroImgSize = cocos2d::Size(70, 70); // 英雄图标的大小
	const cocos2d::Vec2 HeroImgPos = cocos2d::Vec2(5, 5);   // 英雄图标的位置（相对于角色位左上角）
	const cocos2d::Vec2 HeroNamePos = cocos2d::Vec2(15, 5); // 角色名称的位置（相对于角色位底部中间）
	const cocos2d::Vec2 HeroPricePos = cocos2d::Vec2(15, 5); // 角色价格的位置（相对于角色位底部中间）
	const cocos2d::Color3B HeroNameColor = cocos2d::Color3B::BLACK; // 角色名称的颜色
	const cocos2d::Color3B HeroPriceColor = cocos2d::Color3B::BLACK; // 角色价格的颜色
	const cocos2d::Color3B PriceRedColor = cocos2d::Color3B::RED;
	const float HeroNameSize = 8;
	const float HeroPriceGap = 10;
	const float HeroPriceSize = 8;
	const cocos2d::Size CoinSize = cocos2d::Size(8, 8);
	const float DetailPosDy = 5; // 角色界面相对于按钮的位置
	const cocos2d::Size DetailBgSize = cocos2d::Size(300, 70);
	const float TextRowGap = 5; // 行距
	const float TextColGap = 100; // 列距
	const float TextEdgeX = 10;
	const cocos2d::Color3B TextAtbColor = cocos2d::Color3B::YELLOW; // 角色属性名的颜色
	const cocos2d::Color3B TextInfoColor = cocos2d::Color3B::WHITE;
	const float DetailTextSize = 8;
	const char* DetailFont = "宋体";
	const cocos2d::Vec2 ProfilePos = cocos2d::Vec2(5, 5); // 角色图片位置（相对于左上角）
	const cocos2d::Size ProfileSize = cocos2d::Size(60, 60);
	const cocos2d::Color3B CoinMsgColorA = cocos2d::Color3B(200, 155, 0);
	const cocos2d::Color3B CoinMsgColorB = cocos2d::Color3B(255, 10, 0);
	const float CoinMsgSize = 8; // 金币数量信息的大小
	const float CoinMsgDx = 8; // 金币数量信息的显示位置
	const char* CoinMsgFont = "宋体";
};

#endif  // !__STORE_H__