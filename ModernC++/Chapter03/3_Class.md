# 3. Class



## [0] Basic

1. C언어 : `절차지향` 언어 → 넘어가는 흐름을 이해
   C++ 언어 : `객체지향` 언어 → Class로 구현, 클래스 설계의 목표 중요 

2. **추상 자료구조** (제작자가 설계) ← **사용 코드** (사용자가 활용)
   둘 사이에 `“의존성”` (= 관계)이 존재한다.
    → **제작자 쪽에서 변화가 생기면, 불가피하게 사용자 코드에도 변화**가 생길 수 밖에 없다.

3. 대상(자료구조)을 만드는 **제작자**는, 대상을 잘 알고 + 사용방법에 대한 이해도가 높다.
   대상을 사용하는 **사용자**는, 대상을 상대적으로 잘 모르고 + 실수할 가능성이 있다.

4. 그래서, **제작자가 배려를 해줘야 한다!**
   배려 : **사용자의 실수 및 오류를 발생시킬 가능성을 최대한 줄여주는 설계가 필요**하다.

   ex) 특정 자료구조에 출력을 하는 기능을 구현한다고 가정하면,
      사용자가 직접 출력 할 시, 대상에 대해서 잘 알아야 한다. (실수할 가능성이 높음)
      해당 방식 보다, 따로 함수를 만들어서 사용자를 배려하는 코드를 만드는게 바람직하다.





## [1] 객체지향 프로그래밍 개요

#### 객체와 클래스의 사전적인 정의

> 클래스를 설계하고, 클래스라는 틀을 이용해서 실제로 구현한 것이 객체

- **객체** : 변수들과 그와 관련된 메소드들이 모여서 이룬 하나의 꾸러미
  (변수, 메소드가 모여서 어떤 동작이나 상태를 나타내는 단위)
- **클래스** : C의 구조체에서 확정된 변수, 객체, 함수를 포함한 하나의 틀
  (이러한 객체를 모아서 사용하는 틀)



C의 구조체와 다른 **C++ Class Style** → `user.Print()`

- 인스턴스의 주소를 안 넘기는 것 같지만, stack frame을 확인하면 `user(&instance)`로 주소를 보낸다.

- `&instance` : **Hidden Parameter**, 해당 파라미터를 담고 있는 pointer가 **함수 내부에 있는 this parameter**
- instance 주소를 hidden parameter가 담아보내고, 함수 내부에서는 this pointer에 담겨진다.



> **나를** **‘손님’( = ‘사용자' )** **으로 생각!** **내가 만든 클래스에 대해서 객관화**

단, 이제는 인식의 전환이 필요하다. 내가 만든 클래스를 가져다 사용하지만 상대적으로 잘 모르는 다수의 '사용자'를 배려해야 한다.

- **사용자의 편의성을 극대화**
- 사용자의 **실수 가능성을 제작자가 차단**



#### 인터페이스 함수

> 사용자(외부)의 접근을 허용 및 차단하는 통제가 필요하다

[![interface](https://lh5.googleusercontent.com/vW92NlKxSxE-XvXSClAbQiTBr4V2iYEYS7XVwISnZLBIp3AbP9LCwA3JtbOzAnYT7BgDAzSk_hWSonY-brN6KDzuiUTLh7ICfBS7q_nXhC8FGAz8pFHHCqJjqKlmpdW5mnzLqTRT)](https://www.draw.io/?page-id=prtHgNgQTEPvFCAcTncT&scale=auto#G1UTbbimQSBVGxXaI0VyzWrBx2JHXoXyQ8)



왜 접근을 통제해야 할까?

- 제작자는 대상체를 잘 알고, 사용자는 상대적으로 대상체에 대해 무지하다.
- 따라서, **제작자는 사용자의 실수/오남용으로 인해 대상을 사용하는데 있어서 고장나는 일이 없도록 근본적으로 차단 해야하는 의무**가 있고, 이를 위해 통제를 한다.





## [2] 클래스 기본 문법

#### 클래스 기본 문법

```c++
class 클래스_이름 {
접근제어지시자:
	멤버 변수 선언;

	멤버 함수 선언 및 정의;
};
```

```c++
// Example
class USERDATA {
public :
  int nAge;
  char szName[32];
	
  void Print(void){
    printf(“%d, %s\n”, nAge, szName);
  }
};
```



#### 멤버 선언 및 정의

> C++에서는 **생성자(Constructor)**를 이용해 초기화

생성자의 특징

1. 반환 자료형이 없다.
2. 호출하는 함수가 아니라, 적절한 시기에 내부에서 자동으로 호출되는 함수

```c++
// 제작자 코드
class CTest {
public:
	CTest() {    // ‘생성자 함수' 선언 및 정의 (멤버 변수 초기화), 인스턴스를 생성할 때 자동으로 호출
		m_nData = 10; // 인스턴스가 생성되면 멤버 데이터를 ‘자동으로’ 초기화한다.
	}
	int m_nData;
	void PrintData(void) { cout << m_nData << endl; }
};

// 사용자 코드
CTest test;             // 클래스에 대한 인스턴스 선언
test.PrintData();       // 10
```



#### 멤버 함수 선언과 정의 분리하기

> 클래스 선언 내부에는 함수의 원형만 두고, 나머지(정의 부분)는 클래스 선언 외부에 별도로 정의한다.
>
> 모든 클래스의 멤버함수는 **지역변수 → 멤버변수 → 전역변수** 순으로 검색한다.

```c++
class CTest {
public:
	…
	void PrintData(void);
};

// 외부에 분리된 멤버함수 정의
void CTest::PrintData(void) {
	cout << m_nData << endl;
}
```



#### 멤버 변수를 초기화 하는 방법 2가지 추가

1. **생성자 초기화 목록** 

   ```c++
   CTest( )
   : m_nData1(10), m_nData2(20)  // 함수 원형과 몸체(block) 사이에 위치
   { … }
   ```

2. (C++11) **선언과 동시에 초기화**

   ```c++
   int m_nData1 = 10;
   int m_nData2 = 20;
   ```

   

#### 접근제어 지시자

> 제작자가 **사용자가 이용할 수 있는 코드를 제한하는 용도**로 활용

 제작자와 사용자를 구분하는 매우 중요한 문법으로, 제작자 자신이 만든 클래스의 특정요소에 사용자가 접근할 수 없게 하려면 접근 제어 지시자를 활용해야 한다



접근 제어 지시자 종류 3가지

1. `public`: 멤버에 관한 모든 외부 접근이 허용된다.
2. `protected`: 멤버에 관한 모든 외부 접근이 차단한다. 단, **상속관계에 있는 파생클래스**의 접근은 허용한다.
3. `private`: 외부접근 뿐만 아니라 파생 클래스로부터의 접근까지 모두 차단한다. (지시자를 따로 명시하지 않으면, private으로 간주)

클래스 내부 멤버함수는 private 멤버에 접근하는 것이 자유롭다. 단, protected, private은 외부에서 접근할 때 **멤버접근 연산자를 통한 접근이 불가능**하다. 따라서, **인터페이스 함수를 이용해서 제작자가 값의 변화를 통제할 수 있다.** (생성자 또한 접근제어 지시자의 영향을 받으니 주의할 것)





## [3] 생성자와 소멸자

#### 생성자(Constructor)와 소멸자(Destructor)의 특징

1. 생성자와 소멸자는 **클래스 객체(인스턴스)가 생성 및 소멸될 때 ‘자동으로’ 호출되는 함수**다.
2. **반환 형식이 없으며, 메서드의 이름이 함수의 이름과 같다. **(단, 소멸자의 이름 앞에는 `~`이 붙는다.)
3. **생성자는 다중정의(Overriding) 할 수 있지만, 소멸자는 유일**하다.



#### 디폴트 생성자(Default Constructor)

> **매개변수가 하나도 없는 생성자**로, 클래스 제작자가 디폴트 생성자와 소멸자를 기술하지 않아도, 컴파일러가 알아서 넣는다. = **생성자와 소멸자가 없는 클래스는 없다.**

- 생성자는 다중정의 할 수 있다. 하지만, 객체가 소멸할 때는 다양성이 있을 수 없기 때문에 소멸자는 다중정의가 불가능하다.
- 새로운 생성자를 만들면서 디폴트 생성자를 생략할 수 있다. 단, 해당 경우에 매개변수 없이 인스턴스를 선언하면 컴파일 오류가 발생한다. 즉 Default Constructor를 delete한 것과 같은 효과가 나타난다.

Example)

```c++
class CTest {
public:
	CTest() { cout << "CTest::CTest()" << endl; }
	~CTest() { cout << "CTest::~CTest()" << endl; }
};
```

```c++
int main(){
  cout << “Begin” << endl;
  CTest a;
  cout << “End” << endl;
  return 0;
}

// output
Begin
CTest::CTest() // 인스턴스(자동변수) 생성 순간
End
CTest::~CTest() // main함수의 자동변수인 a가 사라지는 시점 = 함수가 반환될 때!!
```

```c++
CTest a;
int main( ){
  cout << “Begin” << endl;
  cout << “End” << endl;
  return 0;
}

// output
CTest::CTest() // 전역 인스턴스 = 생성자는 프로그램이 실행될 때
Begin
End
CTest::~CTest() // 전역 인스턴스 = 소멸자는 프로그램이 종료될 때
```



#### 동적 객체의 생성과 소멸

1. 클래스의 인스턴스는 **선언을 통해 생성**이 가능

2. **new 연산**으로 동적 생성가능 → **delete 연산**으로 삭제 (배열로 생성한 객체 → delete [] 로 삭제)

   → new 연산자는 생성자 호출 & delete 연산자는 소멸자 호출!



#### 참조 형식 멤버 초기화

> 클래스의 멤버 변수는 참조 형식으로 선언할 수 있다. 그런데, 참조자는 반드시 선언과 동시에 초기화가 필요!
>
> 따라서, 반드시 **"생성자 초기화 목록"**으로 초기화가 필요하다.

```c++
class CRefTest {
public:
  CRefTest(int &rParam) : m_nData(rParam) { }
  int GetData(void) { return m_nData; }

private:
  int &m_nData;
};

int main(void){
  int a=10;
  CRefTest t(a);
  cout << t.GetData() << endl; // 10
  a=20;
  cout << t.GetData() << endl; // 20
  return 0;
}
```



#### 생성자 다중 정의

> **생성자도 함수이므로** **다중정의(Overriding)**이 가능하다. 생성자 다중정의 시, 제작자가 해야 할 일은 많아지지만 그 만큼 **사용자의 코드는 더 간편해지고 편리**해진다.

```c++
class CMyData {
public:
  // 둘 중 어떤 생성자를 호출할지는 컴파일러가 매개변수를 보고 알아서 결정한다.
  CMyData(int nParam): m_nData(nParam) { … } // 디폴트 생성자가 없으므로, delete와 같은 효과
  CMyData(int x, int y): m_nData(x+y) { … }
  
  int GetData(void) {return m_nData;}
    
private:
  int m_nData;
};
```



#### 생성자 위임

> 생성자가 다중정의 될 경우, 사용자는 편리하지만 제작자는 같은 코드를 반복해야 하는 번거로움이 있고, 심지어는 버그가 발생할 수 도 있다. → **(C++11) 에서 ‘생성자 위임**' 지원

```c++
class CMyPoint {
public:
  CMyPoint(int x){
    cout << "CMyPoint::CMyPoint(int x);" << endl;
    if(x > 100) m_x = 100;
    else m_x = x;
  }

  CMyPoint(int x, int y): CMyPoint(x)
  {
    cout << "CMyPoint::CMyPoint(int x, int y);" << endl;
    if(y > 200) m_y = 200;
    else m_y = y;
  }

  void Print(void){
      cout << "X : " << m_x << endl;
      cout << "Y : " << m_y << endl;
  }
    
private:
    int m_x = 0, m_y = 0;
};

int main(){
    CMyPoint ptEnd(50, 20);
    ptEnd.Print();
}

// output
CMyPoint::CMyPoint(int x);
CMyPoint::CMyPoint(int x, int y);
X:50
Y:20
```



#### 명시적 디폴트 생성자

> 클래스 멤버 함수의 선언과 정의를 별도로 분리할 수 있다. **default 예약어**를 사용하면, **별도로 정의하지 않더라도 선언과 정의를 한 번에 끝낼 수 있다.**

```c++
class CTest {
public:
  CTest(void);
  … 
};
CTest::CTest(void) { }

// 위와 같이 할 필요없이 클래스 선언 내부에서 아래와 같이 선언하면
// 별도로 정의를 기술하지 않고도 선언과 정의가 완벽하게 분리된다. -> 템플릿 프로그래밍할 때 필요
CTest(void) = default;
```

생성자 다중 정의를 통해서, 새로운 생성자를 기술하고 디폴트 생성자를 기술하지 않는다면 디폴트 생성자는 사라진 것이라고 할 수 있다. 그런데, 그것이 드러내놓고 사라졌다고 표현을 안하다보니 혼란스러운 경우가 있다.이럴 때는 **delete 예약어**를 사용해서 **디폴트 생성자가 사라졌다는 것을 명시적으로 보여준다.**

- `CTest(void) = delete;`





## [4] 메서드

> 클래스의 멤버하무를 Method라 부른다.

#### 

#### 멤버함수(메서드)의 원형

`(virtual / static)`  `반환_자료형`  `클래스이름::함수이름(매개변수)`  `(const)`

- **virtual**: 가상 멤버 함수
- **static**: 정적 멤버 함수 (this pointer로 접근이 불가능하다.)
- **const**: 상수화된 멤버 함수 (일반 및 정적 멤버에 대해 쓰기가 불가능)



#### this pointer

> 제작자가 작성 중인 **클래스의 실제 인스턴스에 대한 주소를 가리키는 포인터**

- 이는 Class를 작성중인 현재가 아니라, **미래(사용자의 실제 인스턴스)에 결정**된다.
- 제작자의 입장에서, 현재 결정되지 않은 “인스턴스의 주소”를 이용해서 프로그램을 작성해야 할 수도 있다.

```c++
class CMyData {
public:
 CMyData(int nParam): m_nData(nParam) { … }
 void PrintData(void) {
   cout<< m_nData << endl; // m_nData, 실제로는 this->m_nData로 컴파일
   cout<< CMyData::m_nData << endl; // CMyData 클래스의 멤버 m_nData
   cout<< this->m_nData << endl; // 메소드를 호출한 인스턴스의 m_nData
   cout<< this->CMyData::m_nData << endl; // 인스턴스의 CMyData 클래스 멤버 m_nData
 }
 // 상속을 고려한다면 (4)번째 표현이 가장 명시적
    
private:
 int m_nData;
};

CMyData a(5), b(10); // &a와 &b는 보이지는 않지만 실제로는 Hidden Parameter로 전달된다.
a.PrintData();
b.PrintData();
```



#### 상수형 메서드 (const 예약어)

> (1) 멤버 변수에 **읽기 접근은 가능하지만, 쓰기는 허용되지 않는 메서드**를 의미

```c++
class CTest {
public:
	CTest(int nParam) : m_nData(nParam) { }
	~CTest( ) { }

	int GetData(void) const { return this -> m_nData; }  // 상수형 메서드로 선언 및 정의
	int SetData(int nParam) { this -> m_nData = nParam; }

private:
	int m_nData = 0;
};
```



> (2) **상수화된 메서드가 아니라면 멤버 함수라도 호출할 수 없다.**

상수형 메서드를 상수화 하는 방법은 **this 포인터를 상수형 포인터로 변경하는 것**이다. 

1. 절대로(혹은 문법적으로) 멤버 변수의 값을 쓸 수 없다.
2. 상수형 메서드가 아닌 멤버는 상수형 메서드를 호출할 수 없다. = 상수화된 메서드에서는 상수화된 메서드만 호출할 수 있다.
3. 상수화된 instance의 경우에도 상수화된 메서드만 호출할 수 있다.
4. 할 수 있다면, 최선을 다해 Const를 사용하세요! 정말 실력 있는 C++ 프로그래머는 const를 제대로 사용할 줄 알아야합니다.



> (3) 상수형 메서드의 예외사항, 미래의 어느 시점(ex. 상속) const 기능을 잠시 제거해야할 필요가 있다.

- **mutable 예약어** / C++ 전용 형변환 연산자 **const_cast< >**

```c++
class CTest {
public:
	CTest(int nParam) : m_nData(nParam) { }
	~CTest() { }

	int GetData(void) const {
		// 상수형 메서드라도 mutable 멤버 변수에는 값을 쓸 수 있다.
		m_nData = 20;
		return m_nData;
	}
	int SetData(int nParam) { m_nData = nParam; }

private:
	mutable int m_nData = 0 ;
};

void TestFunc( const int &nParam ) {
	int &nNewParam = const_cast<int&>(nParam);
	nNewParam = 20;
}
int _tmain(int argc, _TCHAR * argv[]){
	int nData = 10;
	TestFunc(nData);
	cout << nData << endl;  // 20
	return 0;
}
```



#### 멤버 함수 다중 정의

> 메서드도 다중정의 될 수 있다. 단, 클래스에서 생각해봐야할 문제에 대해서 하나 짚고 넘어가자.

```c++
class CMyData {
public:
	CMyData() : m_nData(0) {}
	
	int GetData(void) const { return m_nData; }
	void SetData(int nParam) { m_nData = nParam; }
	void SetData(double dParam) { m_nData = 0; }
    
private:
	int m_nData;
};

// 사용자 코드
CMyData a,b;
a.SetData(5);
b.SetData(3.3);
```

메서드를 **다중정의 해서 오류를 발생시키지 않는 것도 좋은 방법**이지만,사용자로 하여금 **명백히 컴파일 오류를 발생시켜주는 것이 더 나은 선택일 수 있다!**(모호성을 줄이고 명백하게 만들기 위해서) 따라서,

- `void SetData (double dParam) = delete;`
- 실수로 double 형 자료가 넘어오는 것을 차단한다. (컴파일 오류를 발생시켜서 사용자에게 전달 및 예외처리)





## [5] 정적 멤버

> 사용자의 코드에서 특정 클래스의 메서드를 호출하고 싶다면 좋든, 싫든 **무조건 인스턴스를 선언하거나 new 연산으로 동적 인스턴스를 생성** 하고 멤버 접근 연산자를 통해 호출해야한다. **가끔은 이럴 필요가 전혀 없는 함수를 만들어야 할 때가 있는데,** 이 경우 많은 사람들이 전역함수를 만들어서 해결하려는 경향이 있지만 객체지향 프로그래밍에서 소속 객체 없이 스스로 존재하는 전역함수들은 좋은 설계를 역행하거나 불필요한 의존관계를 만드는 원인이 된다. 이에 대한 대안으로 나온 것이 바로 “**정적 멤버**” 이다.

- ‘정적 멤버'는 사실상 전역 변수나 함수와 같은데, **단지 클래스의 멤버로 들어온 것 뿐**이다.
- `static` 예약어를 작성하면 된다.
- 정적 멤버 함수는 접근 할 수 있는 멤버 변수가, static 멤버 변수로 제한된다. 반대로 일반 메서드에서는 static 멤버 변수 접근 가능



Static Member의 특징

1. 인스턴스(Object)를 선언하지 않고 직접 호출이 가능하되,
2. this 포인터를 사용할 수 없으며,
3. `정적변수`는 반드시 선언과 정의를 분리해야한다.



```c++
class CTest {
public :
	CTest(int nParam) : m_nData(nParam) { m_nCount++; }
	int GetData(void) { return m_nData; }
	
	static void ResetCount { m_nCount = 0; }
	static int GetCount { return m_nCout; }
    
private:
	static int m_nCount;
};
int CTest::m_nCount = 0;

// 사용자 코드
CTest a(5), b(10);
cout << a.GetCount() << endl;                     // 2         
CTest::ResetCount();
cout << CTest::GetCount << endl;                  // 0
```

