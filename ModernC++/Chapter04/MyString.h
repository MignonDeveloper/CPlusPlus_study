#pragma once
class MyString
{
public:
	MyString();
	MyString(const MyString& rhs);
	MyString(MyString&& rhs);
	explicit MyString(const char* pszParam);
	~MyString();

	MyString& operator=(const MyString& rhs);
	MyString& operator=(MyString&& rhs);
	operator const char*(void) const;

private:
	// 저장된 무자열의 길이
	int m_nLength;
	// 문자열을 저장하기 위해 동적 할당한 메모리를 가리키는 포인터
	char* m_pszData;

public:
	int SetString(const char* pszParam);
	const char* GetString () const;
	void Release();
};

