#include "MyString.h"
#include <string>
#include <iostream>
MyString::MyString() : m_pszData(nullptr), m_nLength(0)
{

}


MyString::MyString(const MyString& rhs): MyString::MyString()
{
	this->SetString(rhs.GetString());
}


MyString::MyString(MyString&& rhs) : MyString::MyString() // what is noexcept?
{
	// std::cout << "이동생성자" << std::endl;
	this->m_pszData = rhs.m_pszData;
	this->m_nLength = rhs.m_nLength;

	rhs.m_pszData = nullptr;
	rhs.m_nLength = 0;
}


MyString::MyString(const char* pszParam): MyString::MyString()
{
	this->SetString(pszParam);
}


MyString::~MyString()
{
	Release();
}


MyString& MyString::operator=(const MyString& rhs)
{
	if (rhs.GetString() == nullptr || this == &rhs) {
		return *this;
	}
	this->Release();
	this->SetString(rhs.GetString());
	return *this;
}


MyString& MyString::operator=(MyString&& rhs)
{
	if (rhs.GetString() == nullptr || this == &rhs) {
		return *this;
	}
	this->Release();
	this->m_pszData = rhs.m_pszData;
	this->m_nLength = rhs.m_nLength;

	rhs.m_pszData = nullptr;
	rhs.m_nLength = 0;
	return *this;
}


MyString::operator const char*(void) const
{
	return GetString();
}


int MyString::SetString(const char* pszParam)
{
	if (strlen(pszParam) == 0 || pszParam == nullptr) {
		return 0;
	}

	Release();
	int m_nLength = strlen(pszParam);
	m_pszData = new char[m_nLength + 1];
	strcpy_s(m_pszData, m_nLength + 1, pszParam);

	return m_nLength;
}


const char* MyString::GetString() const
{
	return m_pszData;
}


void MyString::Release()
{
	if (m_nLength == 0) {
		return;
	}

	delete[] m_pszData;
	m_pszData = nullptr;
	m_nLength = 0;
}