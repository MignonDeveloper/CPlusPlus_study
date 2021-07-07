#include <iostream>
#include "MyString.h"
using namespace std;

MyString TestFunc(void)
{
	MyString strTest("TestFunc() return");
	cout << strTest << endl;

	return strTest;
}

int main(void)
{
	TestFunc();

	return 0;
}