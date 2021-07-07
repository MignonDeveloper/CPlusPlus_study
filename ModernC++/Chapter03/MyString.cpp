#include "MyString.h"
#include <string>
MyString::MyString(): m_pszData(nullptr), m_nLength(0)
{

}


MyString::~MyString()
{
	Release();
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
