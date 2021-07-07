#include "MyString.h"
#include <cstring>
#include <iostream>
using namespace std;
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


MyString MyString::operator+(const MyString& rhs)
{
	MyString strResult(this->GetString());
	strResult.Append(rhs.GetString());
	return strResult;
}


MyString& MyString::operator+=(const MyString& rhs)
{
	this->Append(rhs.GetString());
	return *this;
}


bool MyString::operator==(const MyString& rhs) const
{
	if (this->m_pszData == nullptr || rhs.m_pszData == nullptr) return false;
	bool result = strncmp(this->m_pszData, rhs.m_pszData, this->m_nLength) == 0 ? true : false;
	return result;
}


bool MyString::operator!=(const MyString& rhs) const
{
	return !(this->operator==(rhs));
}


char MyString::operator[](int index) const
{
	return m_pszData[index];
}


char& MyString::operator[](int index)
{
	return m_pszData[index];
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
	m_nLength = strlen(pszParam);
	m_pszData = new char[m_nLength + 1];
	strcpy_s(m_pszData, m_nLength + 1, pszParam);

	return m_nLength;
}

int MyString::GetLength() const
{
	return m_nLength;
}


const char* MyString::GetString() const
{
	return m_pszData;
}


int MyString::Append(const char* pszParam)
{
	if (strlen(pszParam) == 0 || pszParam == nullptr) return 0;
	if (this->m_nLength == 0) {
		this->SetString(pszParam);
		return this->m_nLength;
	}

	int nLenCur = m_nLength;
	int nLenParam = strlen(pszParam);
	char* pszResult = new char[nLenCur + nLenParam + 1];

	strcpy_s(pszResult, sizeof(char) * (nLenCur + 1), m_pszData);
	strcpy_s(pszResult + sizeof(char) * nLenCur, sizeof(char) * (nLenParam + 1), pszParam);

	Release();
	m_pszData = pszResult;
	m_nLength = nLenCur + nLenParam;

	return m_nLength;
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