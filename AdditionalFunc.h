#pragma once

// 该头文件定义了一些项目中常用的函数

#ifndef __ADDITIONALFUNC_H__
#define __ADDITIONALFUNC_H__

#include <string>
#include "cocos2d.h"
#include "ui\CocosGUI.h"

/* 中文显示处理函数 */
char* FontToUTF8(const char* font);
int GBKToUTF8(std::string& gbkstr, const char* toCode, const char* formCode);

/* 快速创建对象函数 */
// 创建一个图片并设置为整个窗口背景
cocos2d::Sprite* CreateBackground(cocos2d::Scene* curscene, const char* picname, 
	const cocos2d::Size& visibleSize, const cocos2d::Vec2& origin, const int z = 0);
// 对结点的图片大小重新调整
void ResizePic(cocos2d::Node* node, float newWidth, float newHeight);
// 创建一个菜单按钮
cocos2d::MenuItemImage* CreateButton(const cocos2d::Vec2& pos, const cocos2d::Size& size,
	const char* picname1 = "ButtonUnclick.png", const char* picname2 = "ButtonClick.png", 
	const char* picname3 = "");
// 创建一个精灵
cocos2d::Sprite* CreateSprite(cocos2d::Node* curscene, const cocos2d::Vec2& pos, 
	const cocos2d::Size& size, const char* picname, const int z = 0);
// 创建一个标签文本
cocos2d::Label* CreateLabel(const char* display, const char* font, const cocos2d::Vec2& pos,
	const float size, const cocos2d::Color3B& color = cocos2d::Color3B::BLACK);
// 重置标签文本内容
void SetLabelText(cocos2d::Label* target, const char* newtext);
// 创建一个进度条
cocos2d::ui::LoadingBar* CreateLoadingBar(const char* picname, const cocos2d::Vec2& pos,
	const cocos2d::Size& size, const float percent = 0);

#endif // !__ADDITIONALFUNC_H__