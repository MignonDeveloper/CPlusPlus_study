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
	// ����� ���ڿ��� ����
	int m_nLength;
	// ���ڿ��� �����ϱ� ���� ���� �Ҵ��� �޸𸮸� ����Ű�� ������
	char* m_pszData;

public:
	int SetString(const char* pszParam);
	const char* GetString () const;
	void Release();
};

