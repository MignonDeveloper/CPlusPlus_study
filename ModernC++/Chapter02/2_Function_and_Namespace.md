# C++ 함수와 네임스페이스



## [1] 디폴트 매개변수

> 참조자, 함수 다중정의, 디폴트 매개변수 등으로 인해 호출자의 코드만 봐서는 함수의 원형을 알 수 없다. 따라서 **C++에서는 절대로 호출자의 코드만 보고 함수의 원형을 확정해서는 안된다.**

C에서는 함수를 호출하려면 반드시 매개변수의 실인수를 기술해야 하지만, C++에서는 경우에 따라 생략 가능

- 매개변수의 디폴트 값은 반드시 **함수 원형의 선언 부분**에 기술해야한다. → 클래스 메소드를 .cpp 파일에 따로 정의할 때 주의가 필요함
- 정의 부분에 기술할 경우 컴파일 오류가 발생하며, 선언 및 정의를 동시에 하는 경우에는 바로 적는다.

```c++
int TestFunc ( int = 10 );  // C/C++의 함수 원형 선언에서는 매개변수의 이름 생략 가능

//--------------------------------------------------------------------------

int TestFunc ( int nParam = 10 ) { return nParam; }
  // nParam 매개변수의 Default 값은 10이다.
  // 이와 같이 함수의 원형에 매개변수의 초기값을 설정할 수 있다. [함수의 다형성을 지원하는 또 다른 방법]

int _tmain ( int argc, _TCHAR *argv[] ){
	cout << TestFunc( ) << endl;   // 호출자가 실인수를 기술 안했으므로, 디폴트
	cout << TestFunc(20) << endl;  // 호출자가 디폴트값을 확정, 디폴트 값 무시
	return 0;
}

```



### Default Parameter 기술 시, 주의사항 3가지

1. **피호출자 함수 매개변수의 디폴트 값은 반드시 오른쪽 매개변수부터 기술**해야 한다. (절대로 중간이 비어서는 안된다.)
2. 매개변수가 여러 개일 때 왼쪽 첫번째 매개변수의 디폴트 값을 기술하려면, 나머지 오른쪽 ‘모든' 매개변수에 대한 디폴트 값을 기술해야 한다.
3. **호출자가 설정하는 실인수는 피호출자 함수 매개변수의 왼쪽부터 짝을 이룬다.** 짝이 맞지 않는 매개변수는 디폴트 값을 적용한다.



### Default Parameter 어떤 경우에 사용해야할까?

호출자의 코드만 보고서는 함수의 원형을 정확히 알아낼 수 없다. 그렇기에 디폴트 매개변수는 자칫 **모호성**을 만들 수 있고 이는 사용자가 코드를 이해하는데 매우 심각한 방해요소로 작용할 수 있다. 따라서 `가급적이면 디폴트 매개변수를 사용하는 일을 자제하는 것이 좋다.`



>  단, 함수를 만든 사람과 사용자가 서로 다른 경우에 대해서는 다른 측면에서의 생각이 필요하다.

프로그래밍의 특성상 작성이 끝난 코드를 수정해야 하는 경우가 종종 발생하는데, 아래와 같은 경우를 생각해보자.

```c++
# 2013년 철수가 만든 함수
int CalcLayout(int nWidth, int nHeight){
    return nWidth * nHeight;
}

# 2013년 사용자 코드
int _tmain( ){
    CalcLayout(10,5);
    return 0;
}
```



```c++
# 2013년 철수의 코드를 2016년 영희가 변경
#define MyType_A 100
#define MyType_B 200
int CalcLayout(int nWidth, int nHeight, int nType){
    return nWidth * nHeight + nType;
}

# 2016년 사용자 코드
int _tmain( ){
    CalcLayout(10,5,MyType_A);
    return 0;
}
```

이런 경우 영희가 변경한 코드로 인해 2013년 사용자가 사용하던 코드는 사용이 불가능하다. 세번째 인자의 값을 전달하지 않기 때문이다. 따라서 이 때 영희가 `int nType = MyType_A`로 디폴트 매개변수를 선언해줄 수 있다면 초기 사용자의 코드와 현재 사용자의 코드 모두 포괄적으로 사용가능한 코드를 만들어줄 수 있다. 이러한 경우를 제외하고는 디폴트 매개변수를 사용하는 일은 매우 신중해야 한다.



실력있는 개발자라면, `"미래의 유지보수 문제에 대응할 수 있도록 현재코드를 작성해야 한다."`

- C++ 같은 객체지향 언어는 ‘객체'라는 대상에 대한 제작자와 사용자가 다른 경우가 많으므로, 실제 함수를 사용하는 사람을 고려해서 코드를 작성하는 습관을 갖는 것이 중요하다.





## [2] 함수의 다중정의

> C++에서 **‘다중정의(Overloading)’**는 하나(함수 이름, 변수 이름 등)가 여러 의미를 동시에 갖는 것을 의미
>
>   = C++은 **'함수의 다형성'**을 지원한다.

C에서는 이름이 같은 함수가 존재할 수 없다. 즉, 함수의 '다형성'을 지원하지 않는다. 하지만 C++에서는 *매개변수의 구성이 달라지는 등 함수의 원형이 달라지면* 이름이 같더라도 다른 함수로 취급한다. 이로인해 코드와 구조가 유연해지는 장점을 가지고 있지만, 이를 사용하는 사용자의 입장에서는 주의가 필요하다. (의도하지 않은 함수를 호출할 가능성 주의)

```c++
int Add ( int a, int b, int c ) {return a+b+c;}
int Add ( int a, int b ) {return a+b;}
double Add ( double a, double b ) {return a+b;}

cout << Add(3,4) << endl;
cout << Add(3,4,5) << endl;
cout << Add(3.3,4.4) << endl;
```



C++에서 다형성이 가능한 이유는 **Name Mangling**을 통해서 예명을 본명으로 바꿔서 저장하기 때문이다.

- 함수의 본명인 Mangled Name은 서로 절대로 중복이 불가능하기 때문에 C++에서는 다중정의(Overloading), 재정의(Overriding)이 가능하다. `int __cdecl Add(int, int)  →  (?Add@@YAHHH@Z)`



### 다중정의와 모호성

> **디폴트 매개변수 & 다중정의**가 조합되면 매우 **강력한 모호성**이 발생할 수 있으니 주의

```c++
void TestFunc(int a) { cout << “TestFunc(int)” << endl; }
void TestFunc(int a, int b = 10) { cout << “TestFunc(int,int)” << endl; }

int _tmain( int argc, _TCHAR *argv[] ){
	TestFunc(5);
}
```



### 함수 템플릿

"다중정의"를 사용하는 이유는 사용자의 편의성, 확장성이다. 하지만 이는 `유지보수`의 측면에서 문제점을 가진다.

1. 사용자를 편하게 해주기 위해 제작자는 같은 일을 여러 번 반복해야 한다.
2. 하나에서 논리적 결함이 발견되면, 정의된 모든 것에 수정을 해줘야 한다.
3. 특정 다중 정의된 함수를 사용하지 않음에 따라, 불필요한 코드로 남을 수 있다.



따라서 가급적이면 함수의 다중 정의 보다는 `함수 템플릿(Template)` 사용을 권장한다.

> 템플릿이란, 함수/클래스를 찍어내는 틀과 같은 역할을 한다.

- 형식을 기술해야할 자리에 매개변수처리를 하듯이 뚫어놓고, 여기에 해당하는 형식을 Caller가 결정
- 같은 일을 하는 코드가 여러번 등장할 필요가 없기 때문에 안정적이고 유지보수에도 좋다.

```c++
template <typename T>   // 일종의 틀로서, typename은 자료형을 의미, T는 자료형의 이름
반환형식   함수이름   ( 매개변수 … ) {
     … 
}

```



ex1)

```c++
template <typename T>
T TestFunc(T a){
	cout << “매개변수 a: “ << a << endl;
	return a;
}

int _tmain(int argc, _TCHAR *argv[]){
	cout << “int\t” << TestFunc(3) << endl;
	cout << “double\t” << TestFunc(4.4) << endl;
	cout << “char\t” << TestFunc(‘B’) << endl;
	cout << “char*\t” << TestFunc(“Hello”) << endl;
	return 0;
}
```



ex2)

```c++
template <typename T>
T TestFunc(T a, T b) { return a+b; }

int _tmain( int argc, _TCHAR * argv[] ){
	cout << Add(3,4) << endl;  // 호출스택을 확인해보면, Add<int>(int a,int b) 로 확정!
	cout << Add(3.3, 4.4) << endl;
	cout << Add<int>(3,4) << endl; // <typename T>와 짝을 이룬다.
	return 0;
}
```





## [3] 인라인 함수

> For Optimization,
>
> 컴파일러가 고급어를 기계어로 번역하는 과정에서 **CPU나 메모리 사용의 효율을 높이도록 코드를 변경**

함수를 호출하면, 아래와 같은 **Overhead**가 발생한다.

1. Stack Memory 사용량이 증가하고,
2. 매개변수 활용을 위한 복사가 필요하며,
3. 제어의 흐름이 바뀐다.



보통 이런문제를 극복하기 위해서 예전에는 **Macro**를 사용했다. 특히 길이가 짧고 단순한 것임에도 불구하고 관리 상의 목적 때문에 함수로 만들어진 코드를 매크로로 변환할 경우 무시할 수 없는 수준의 성능향상을 기대할 수 있다. 하지만, 매크로는 함수가 아니어서 **다양한 논리적 오류**를 발생시킨다. 또한 **매개변수에 형식을 지정할 수 없는 치명적인 단점**을 가지고 있다.

이를 보완하고자 탄생한 것이 바로 **인라인 함수(Inline Function)**이다.

> **매크로의 장점**(함수 호출 안해도 되는 것) + **함수의 장점**(자료형식 지정 가능 및 논리적인 흐름을 부여할 수 있는 것)을 두루 갖춘 함수로서, **함수의 원형 앞에 inline 이라는 예약어만 작성**하면 바로 사용가능하다.





## [4] 네임 스페이스(Namespace)

> C++가 지원하는 각종 요소들(변수, 함수, 클래스 등)을 한 범주로 묶어주기 위한 문법 = 소속
>
> → 여러 사람이 프로그램을 만들다보면, 이름이 중복될 가능성이 매우 높다. 이를 해결하기 위해 **[소속 / 분류]**를 의미하는 namespace가 등장

```c++
namespace 이름 {
      …    → 네임스페이스의 블록 내부에서 선언하는 변수나 함수들은 모두 명시한 ‘이름’속에 속하게 된다.
}

// ---------------------------------------------------------------------------
ex)
namespace TEST {
	int g_nData = 100;
	void TestFunc(void) { cout << “Test::TestFunc()” << endl; }
}

int _tmain( int argc, _TCHAR *argv[] ){
	TEST::TestFunc();
	cout << TEST::g_nData << endl; // 식별자 앞에 범위 지정 연산자(::)를 사용
	return 0;
}
```



### using 선언

> > 프로그램 내부에서 앞으로 자주 사용해야 하는 네임스페이스가 있다면, 모든 식별자 앞에 이를 기술할 것이 아니라 **using 예약어**를 선언한 후 **네임스페이스를 생략하는 것도 좋은 방법**이다. 
> >
> > 단, 모호성이 발생가능한 경우는 네임스페이스를 구체적으로 명시함으로써 모호성을 제거해야한다.

```c++
using namespace 네임스페이스_이름;

using namespace std;
cout << g_nData << endl;
```



### namespace 중첩

> > 네임스페이스 안에 또 다른 네임스페이스가 속할 수 있다.

```c++
ex)
namespace TEST {
	int g_nData = 100;
	namespace DEV {
		int g_nData = 200;
		namespace WIN {
			int g_nData = 300;
		}
	}
}

TEST::g_nData 
TEST::DEV::g_nDATA
TEST::DEV::WIN::g_nDATA
```



### C와 C++의 식별자 차이

<table>
    <tr colspan="4" align="center">
        <td colspan="2">C 함수 원형</td>
        <td colspan="2">C++ 함수 원형</td>
    </tr>
    <tr align="center">
        <td>반환 형식</td>
        <td>int</td>
        <td>반환 형식</td>
        <td>int</td>
    </tr>
    <tr align="center">
        <td>호출 규약</td>
        <td>__cdecl</td>
        <td>호출 규약</td>
        <td>__cdecl</td>
    </tr>
    <tr align="center">
        <td>이름</td>
        <td>TestFunc</td>
        <td>소속::이름</td>
        <td>::TestFunc(명시적 전역)</td>
    </tr>
    <tr align="center">
        <td>매개변수 리스트</td>
        <td>(int, int)</td>
        <td>매개변수 리스트</td>
        <td>(int, int)</td>
    </tr>
    <tr align="center">
        <td>-</td>
        <td>-</td>
        <td>const</td>
        <td>const</td>
    </tr>
</table>





## [5] 식별자 검색 순서

> C++에서 "식별자가 선언된 위치를 검색하는 순서"

**전역 함수인 경우**

1. 현재 블록 범위
2. 현재 블록 범위를 포함하고 있는 상위 블록 범위 (최대 적용 범위는 함수 몸체까지)
3. 가장 최근에 선언된 전역 변수와 함수
4. using 선언된 네임스페이스 혹은 전역 네임스페이스. 단, 동일한 식별자가 존재할 경우 컴파일 오류 발생



**클래스 메서드인 경우**

1. 현재 블록 범위
2. 현재 블록 범위를 포함하고 있는 상위 블록 범위 (최대 적용 범위는 함수 몸체까지)
3. 클래스의 멤버
4. 부모 클래스의 멤버
5. 가장 최근에 선언된 전역변수와 함수
6. 호출자 코드가 속한 네임스페이스의 상위 네임스페이스
7. using 선언 된 네임스페이스 혹은 전역 네임스페이스. 단, 동일한 식별자가 존재할 경우 컴파일 오류 발생