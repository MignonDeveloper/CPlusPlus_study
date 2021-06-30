# Lecture 1. C와는 다른 C++

## C와 C++ 언어의 특징
- **C언어** = **절차지향 언어**
    - 보이는 구문을 순차적으로 진행 & 자주 쓰인 절차적 흐름을 함수로 만들어 사용
    - but, 대규모 프로젝트를 진행할 때 소속&개인(객체) 사이의 관계를 담아내기 어려움

- **C++ 언어** = **객체지향 언어**
    - Class (객체)를 설계하는 것에 중점
    - 객체지향 프로그래밍은 모든 것이 객체로 이루어짐
    - **개념,추상**과 **구현,실체**를 따로 완성(분리)시키는 것이 중요함

<br>

## Hello, World! 출력하기
```cpp
// HelloCpp.cpp: 콘솔 응용프로그램에 대한 진입점
#include "stdafx.h"
#include <iostream>
int main(int argc,char *argv[]){
    std::cout << “Hello, World!” << std::endl;
    return 0;
}
```

- **Standard Application Frameworks** 
    - 표준 어플리케이션 프레임워크 = 미리 컴파일된 헤더
    - 프로젝트 전체 파일에 적용하고 싶은 선언을 해당 파일에 쓴다.
    - cpp 파일 추가시 기본으로 추가 → 기능을 켜고 끌 수 있다.

<br>

- C++에서 User Defined Header가 아닌 <표쥰 헤더파일>은 확장자 생략
    - C언어의 표준 헤더파일은 앞에 C를 붙이고 확장자 생략

<br>

- 주요 개념들
    - **`std`**: **네임스페이스(Namespace)** 를 의미 = 소속의 개념
    - **`::`**: 스코프 설정 연산자(Scope Resolution Operator)
    - **`cout`** : **콘솔 출력을 담당하는 객체**
        - `std::cout` → ‘std’ namespace에 속하는 cout 객체를 의미
    - **`<<`**: **연산자 함수**

<br>

## 객체지향의 지향성
> 특정일을 전문적으로 하는 객체에 일을 맡긴다.
- **특정일** : 필요하면, 특정일을 하는 객체(하나의 프로그램의 기능 중 일부)를 직접만든다.
- **전문적** : 보안문제가 낮고 대부분의 경우에 잘 대비되어 있으며, 처리능력이 높다.
- **맡긴다**: Interface와 API를 통해서 전달하면 해당 객체가 알아서 처리해서 편의성이 높다

<br>

## Instance
> 특정 추상형식(자료형, 사용자 정의 자료형, 객체 … )에 대한 하나의 예시, 구현 (Variable보다 Instance라는 표현에 더 익숙해져야 한다.)

- 객체지향에서는 모든 것을 객체로 표현하고, **객체의 형식을 갖는 변수를 Instance**라 한다.
- **객체(추상, 형식)** → **인스턴스(구현, 예시)**
    - `string strData;` : strData는 string 자료형에 대한 instance

<br>

## std::cout, cin
> ‘std’ namespace에 속한 iostream 클래스의 객체

**cout = Console Output**
- C처럼 출력해야 하는 결과에 맞춰서 **자료형(형식 문자)를 지정하지 않아도 된다**.
- 물론, cout 객체의 메소드를 통해 해당 기능을 접목시킬 수 있다.

**cin = Console Input** 
- 콘솔 입력 방법(Protocol)을 제공하는 객체, cout과 마찬가지로 **자료형을 맞출 필요 없다**.

**실수의 출력**
- cout은 기본적으로 필요한 소수점까지 알아서 잘 출력해준다.
- 근데, 만약 소수점 3자리만 출력하고 싶다면 cout 객체에 설정을 해줘야 한다.
    - `cout.setf(ios::fixed);`
    - `cout.setf(ios::showpoint);`
    - `cout.precision(3);`

(+) **String**

```cpp
string strName;
cin >> strName;
getline(cin, strName)
```

기본 문자배열을 이용할 시, 선언해둔 길이를 넘어가면 오류가 발생하지만,

String 객체를 선언 및 정의할 때는 문자열의 최대길이를 신경쓰지 않아도 된다.

<br>

### 자료형

일정 크기의 메모리에 저장된 정보를 해석하는 방법

C++에서 변수의 선언 및 정의 → **Constructor Initialization**

1. ***int a(10); / int b(a);***
    - 변수 a를 원본으로 이를 복사해서 b 인스턴스를 만들어 낸다.
    - 하나의 **Clone**을 생성(복사 생성자의 개념과 연결 )
2. ***int (10);***
    - **이름 없는 인스턴스** 선언 및 정의

C++11 표준에서 새롭게 선보인 자료형 → **auto**, **decltype(expr)**

1. `auto`: 초기값의 형식에 맞춰서 선언하는 인스턴스의 자료형식이 자동으로 결정된다.
    - 활용 예시
        - `int a=10;`
        - `auto b(a);`
        - `auto pfTest = TestFunction;` → 함수형 포인터로 자동 인식
    - Template, Parallel Programming과 같은 고급 문법에서 매우 중요하게 활용된다
    - 범위 기반 for문에서 활용가능
        - 읽기 기능만 필요할 때 : `for(auto n : array)`
        - 읽기 및 쓰기 기능이 필요할 때: `for(auto &n : array)`

2. `decltype(expr)`: expression(상수, 변수, ...)의 자료형을 인스턴스의 자료형으로 결정
    - `int foo = 0; decltpye(foo) bar;`

<br>

### 메모리 동적 할당

Run Time 동안 사용할 메모리 공간을 할당하는 것

**가상 메모리 체계**
- 없는 것이 생기는게 아니라, 이미 존재하는 것에서 **사용허가를 받고 다시 반환**하는 구조
- **OS가 메모리를 통제**하여, 할당에 실패할 가능성이 줄어든다. (실패 시, 예외처리 발생)
- **포인터**와 메모리 관리는 항상 같이 쓰이는 개념으로, **할당 & 해제의 관리문제가 존재**한다.

<br>

**new / delete 연산자**
- 기존 malloc()과 free()함수의 문제 해결
    - (1) 어떤 자료형을 **몇 개 담은 것**인지에 대한 정보가 부족한 문제
    - (2) 객체가 생성 또는 소멸 되면서 **꼭 해야하는 작업**을 하지 못하는 문제
    - (3) **예외 발생이 아닌 null값을 return**하는 문제

`new`: 메모리 동적 할당 + 객체의 생성자 호출

`delete`: 동적할당 받은 메모리 해제 + 객체의 소멸자 호출

```cpp
int *pData = new int;
int *pNewData = new int(10);

*pData = 5;
std::cout << *pData << std::endl;
std::cout << *pNewData << std::endl;
delete pData;
delete pNewData;
```

- 인스턴스만 동적으로 생성할 수도 있고,
초기값을 기술해서 인스턴스를 동적으로 생성할 수 있다.
- 포인터에 간접지정 연산자를 이용해서 접근 → 변수처럼 행동하게 만든다.

<br>

### Reference

**참조형 변수 선언과 정의**

1. 처음 어떤 변수와 짝(선언과 동시에 반드시 초기화)을 이루게 되면, 그 짝이 절대로 달라지지 않는다. (강제화)
2. 단, 짝을 이루고 있는 원본 변수의 내부 값이 달라지는 것을 감지해주지는 않는다.

```cpp
int nData(10);
std::cout << nData << std::endl;
int &rData = nData; // 참조자가 가리키는 대상을 바꿀 수 없지만, 그 내부에 있는 값은 바꿀 수 있다.

rData = 5;
// pointer 처럼 간접지정연산자가 필요없다.
// 참조자의 값을 바꾸면 원본의 값도 변경된다.
std::cout << nData << std::endl;
```

**R-Value 참조**

- 이름이 없는 임시객체는 성능저하 & 오류를 발생시키는 원인을 제공한다.이를 해결하기 위해서 필요한 것이 R-Value 참조
- `&&` : &가 두 번 연속 등장
    - `int &&rData = nInput + 5;` → **산술연산으로 만들어진 임시결과(임시객체)**에 대한 R-Value 참조
    - `int &&rResult = TestFunc(10)`; → **함수반환으로 만들어진 임시결과(임시객체)**에 대한 R-Value 참조
- **임시결과** = 이어지는 연산에 활용된 직후 소멸하는 R-Value. 따라서, R-Value 참조는 곧 사라질 대상에 대한 참조자를 부여하는 것

<br>

### 참조를 사용하는 이유

포인터의 문제점인 <**변절**>을 해결한다. (포인터는 변수여서, 가리키는 주소 값이 달라질 수 있다.)

포인터를 이용했을 때, 변절이 일어나는 경우

```cpp
int nData = 10;
int nNewData = 20;
int *pnData = &nData;

*pnData = 5;             // nData ← 5
pnData = &nNewData;      // 변절
*pnData = 10;            // nNewData ← 10
```

참조자는 가리키는 대상이 변하지 않는다!!

```cpp
int &rData = nData;
rData = 5;
```

`int *const rData = &nData;`

- 변하지 않는 포인터와 같은데 구조적으로 제한해둔 것

▷ **덩치 큰 자료는 Value가 아닌 Reference로 전달하는 것이 효율적**

     **덩치가 큰 자료는 참조자로 전달하면 편리하고, 크기도 적게 차지한다.**

    (포인터는 꼭 필요한 경우, 어쩔 수 없는 경우에만 사용)

```cpp
void TestFunc (int &rData) { rParam = 100; }           // 원본의 값이 100으로 바뀐다.
int _tmain (int argc, _TCHAR * argv[]){
	int nData = 0;
	TestFunc(nData);                                       // int &rData = nData; 와 같은 효과
	std::cout << nData << std::endl;
	return 0;
}
```

한 가지 주의해야할 사항으로
>  → 함수의 매개변수가 참조자인 경우, 호출자 코드만 봐서는 매개변수가 참조형식인지 알 수 없다! **따라서 꼭 함수의 원형을 확인할 것!**

<br>