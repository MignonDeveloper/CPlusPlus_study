#include <iostream>
#include "MyString.h"
using namespace std;

void TestFunc(const MyString& param) {
	cout << param.GetString() << endl;
}

int main() {
	MyString strData;
	strData.SetString("Hello");
	TestFunc(strData);
}