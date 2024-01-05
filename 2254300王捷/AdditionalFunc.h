#pragma once

// ��ͷ�ļ�������һЩ��Ŀ�г��õĺ���

#ifndef __ADDITIONALFUNC_H__
#define __ADDITIONALFUNC_H__

#include <string>
#include "cocos2d.h"
#include "ui\CocosGUI.h"

/* ������ʾ������ */
char* FontToUTF8(const char* font);
int GBKToUTF8(std::string& gbkstr, const char* toCode, const char* formCode);

/* ���ٴ��������� */
// ����һ��ͼƬ������Ϊ�������ڱ���
cocos2d::Sprite* CreateBackground(cocos2d::Scene* curscene, const char* picname, 
	const cocos2d::Size& visibleSize, const cocos2d::Vec2& origin, const int z = 0);
// �Խ���ͼƬ��С���µ���
void ResizePic(cocos2d::Node* node, float newWidth, float newHeight);
// ����һ���˵���ť
cocos2d::MenuItemImage* CreateButton(const cocos2d::Vec2& pos, const cocos2d::Size& size,
	const char* picname1 = "ButtonUnclick.png", const char* picname2 = "ButtonClick.png", 
	const char* picname3 = "");
// ����һ������
cocos2d::Sprite* CreateSprite(cocos2d::Node* curscene, const cocos2d::Vec2& pos, 
	const cocos2d::Size& size, const char* picname, const int z = 0);
// ����һ����ǩ�ı�
cocos2d::Label* CreateLabel(const char* display, const char* font, const cocos2d::Vec2& pos,
	const float size, const cocos2d::Color3B& color = cocos2d::Color3B::BLACK);
// ���ñ�ǩ�ı�����
void SetLabelText(cocos2d::Label* target, const char* newtext);
// ����һ��������
cocos2d::ui::LoadingBar* CreateLoadingBar(const char* picname, const cocos2d::Vec2& pos,
	const cocos2d::Size& size, const float percent = 0);

#endif // !__ADDITIONALFUNC_H__