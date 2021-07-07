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
	MyString operator+(const MyString& rhs);
	MyString& operator+=(const MyString& rhs);
	bool operator==(const MyString& rhs) const;
	bool operator!=(const MyString& rhs) const;
	char operator[](int index) const;
	char& operator[](int index);
	operator const char*(void) const;

private:
	// ����� ���ڿ��� ����
	int m_nLength;
	// ���ڿ��� �����ϱ� ���� ���� �Ҵ��� �޸𸮸� ����Ű�� ������
	char* m_pszData;

public:
	int SetString(const char* pszParam);
	int GetLength() const;
	const char* GetString () const;
	int Append(const char* pszParam);
	void Release();
};

