#pragma once

// ��Ÿ����쳣����

#include <exception>
#include <string>

#ifndef __EXCEPTIONCLASSES_H__
#define __EXCEPTIONCLASSES_H__

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


#endif // !__EXCEPTIONCLASSES_H__
