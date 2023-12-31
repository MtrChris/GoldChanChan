#include "AdditionalFunc.h"

#include "ExceptionClasses.h"
#include <windows.h>
#include "iconv.h"

USING_NS_CC;

char* FontToUTF8(const char* font)
{
	int len = MultiByteToWideChar(CP_ACP, 0, font, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_ACP, 0, font, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr)
	{
		delete[] wstr;
	}
	return str;
}

int GBKToUTF8(std::string& gbkstr, const char* toCode, const char* formCode)
{
	iconv_t iconvH;
	iconvH = iconv_open(formCode, toCode);
	if (iconvH == 0)
	{
		return -1;
	}
	const char* strChar = gbkstr.c_str();
	const char** pin = &strChar;
	size_t len = gbkstr.length();
	size_t outlen = 4 * len;
	char* outbuf = new char[outlen];
	char* pBuff = outbuf;
	memset(outbuf, 0, outlen);
	if (iconv(iconvH, pin, &len, &outbuf, &outlen))
	{
		iconv_close(iconvH);
	}
	gbkstr = pBuff;
	iconv_close(iconvH);
	delete[] pBuff;
	return 0;
}

Sprite* CreateBackground(Scene* curscene, const char* picname, const Size& visibleSize, 
	const Vec2& origin, const int z)
{
	auto Background = Sprite::create(picname);
	if (Background == nullptr)
	{
		throw LoadFailure(picname, "picture(sprite)");
	}
	Background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	// 调整图片大小至整个背景
	Background->setContentSize(visibleSize);
	curscene->addChild(Background, z);
	return Background;
}

Sprite* CreateSprite(Node* curscene, const Vec2& pos, const Size& size, const char* picname, 
	const int z)
{
	Sprite* RetSprite = Sprite::create(picname);
	if (RetSprite == nullptr)
	{
		throw LoadFailure(picname, "sprite");
	}
	RetSprite->setPosition(pos);
	ResizePic(RetSprite, size.width, size.height);
	curscene->addChild(RetSprite, z);
	return RetSprite;
}

void ResizePic(Node* node, float newWidth, float newHeight)
{
	Size cursize = node->getContentSize();
	float scaleX = newWidth / cursize.width * node->getScaleX();
	float scaleY = newHeight / cursize.height * node->getScaleY();
	node->setScaleX(scaleX);
	node->setScaleY(scaleY);
	//node->setContentSize(Size(newWidth, newHeight));
}

MenuItemImage* CreateButton(const Vec2& pos, const Size& size, const char* picname1, 
	const char* picname2, const char* picname3)
{
	MenuItemImage* buttonImage = MenuItemImage::create(picname1, picname2, picname3);
	if (buttonImage == nullptr)
	{
		throw LoadFailure(picname1, "button");
	}
	buttonImage->setPosition(pos);
	ResizePic(buttonImage, size.width, size.height);
	return buttonImage;
}

Label* CreateLabel(const char* display, const char* font, const Vec2& pos, const float size, 
	const Color3B& color)
{
	std::string displayName = display;
	GBKToUTF8(displayName, "gb2312", "utf-8");
	Label* Text = Label::createWithSystemFont(displayName, font, size);
	if (Text == nullptr)
	{
		throw LoadFailure(font, "font");
	}
	Text->setPosition(pos);
	Text->setColor(color);
	return Text;
}

void SetLabelText(Label* target, const char* newtext)
{
	std::string display = newtext;
	GBKToUTF8(display, "gb2312", "utf-8");
	target->setString(display);
}

ui::LoadingBar* CreateLoadingBar(const char* picname, const Vec2& pos, const Size& size, const float percent)
{
	ui::LoadingBar* BarImage = ui::LoadingBar::create(picname);
	if (BarImage == nullptr)
	{
		throw LoadFailure(picname, "LoadingBar");
	}
	BarImage->setPosition(pos);
	ResizePic(BarImage, size.width, size.height);
	BarImage->setDirection(ui::LoadingBar::Direction::LEFT);
	BarImage->setPercent(percent);
	return BarImage;
}
