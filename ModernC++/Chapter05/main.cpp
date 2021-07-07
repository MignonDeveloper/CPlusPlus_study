#include <iostream>
#include "MyString.h"
using namespace std;

int main(void)
{
	MyString strLeft("Test"), strRight("String");

	if (strLeft == strRight) cout << "Same" << endl;
	else cout << "Different" << endl;

	strLeft = MyString("String");
	if (strLeft != strRight) cout << "Different" << endl;
	else cout << "Same" << endl;

	return 0;
}