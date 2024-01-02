#pragma once

#ifndef __EXCEPTIONCLASSES_H__
#define __EXCEPTIONCLASSES_H__

// ��Ÿ����쳣����
#include <exception>
#include <string>
#include "cocos2d.h"

#define TEST_INIT  try {
#define CATCH_INIT } catch (std::exception& exp) { \
  this->removeAllChildren();\
  this->addChild(ErrorScene::CreateWithException(exp), 10); \
}

// ����ͼƬ�������ʧ�ܵ��쳣
class LoadFailure : public std::exception
{
public:
	LoadFailure(); // ���캯��
	//LoadFailure();
	LoadFailure(std::string& fname, std::string& ftype);
	LoadFailure(const char* fname, const char* ftype);
	const char* what() const;
	~LoadFailure(); // ��������
private:
	std::string filename;
	std::string filetype;
	std::string error_content;
};

// �������
class ErrorScene : public cocos2d::Sprite
{
public:
	static ErrorScene* CreateWithException(std::exception& exp = std::exception::exception("Runtime exception"));
	void ErrorScene::initScene(std::exception& exp);
	virtual bool init();
	CREATE_FUNC(ErrorScene)

	char const * TextFont = "����";
	const float TextSize = 10;
	const float TextGap = 20;
	const cocos2d::Vec2 TextStart = cocos2d::Vec2(50, 50);
	const cocos2d::Color3B TextColor1 = cocos2d::Color3B::WHITE;
	const cocos2d::Color3B TextColor2 = cocos2d::Color3B::YELLOW;
	const cocos2d::Color3B TextColor3 = cocos2d::Color3B::RED;
};


#endif // !__EXCEPTIONCLASSES_H__
