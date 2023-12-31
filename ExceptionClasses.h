#pragma once

// 存放各类异常的类

#include <exception>
#include <string>

#ifndef __EXCEPTIONCLASSES_H__
#define __EXCEPTIONCLASSES_H__

// 加载图片、字体等失败的异常
class LoadFailure : public std::exception
{
public:
	LoadFailure(); // 构造函数
	//LoadFailure();
	LoadFailure(std::string& fname, std::string& ftype);
	LoadFailure(const char* fname, const char* ftype);
	const char* what() const;
	~LoadFailure(); // 析构函数
private:
	std::string filename;
	std::string filetype;
	std::string error_content;
};


#endif // !__EXCEPTIONCLASSES_H__
