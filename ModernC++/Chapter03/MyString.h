#pragma once
class MyString
{
public:
	MyString();
	~MyString();
	// ���ڿ��� �����ϱ� ���� ���� �Ҵ��� �޸𸮸� ����Ű�� ������
	char* m_pszData;

private:
	// ����� ���ڿ��� ����
	int m_nLength;

public:
	int SetString(const char* pszParam);
	const char* GetString () const;
	void Release();
};

