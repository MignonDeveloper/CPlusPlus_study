# 4. 복사 생성자와 임시 객체



## [0] Basic

1. `int a(10);`  → a는 생성되는 대상체(인스턴스) , 10은 초기값(상수)
   `int b(a);`   → b는 **사본**(인스턴스), a는 **원본** 초기값(인스턴스)

2. 생성자 & 소멸자 는, Caller가 call 해서 호출되는 것이 아니라, 호출되는 시점이 문법적으로 특정되어 있다.

   - **생성자** : instance 생성 시 (동적할당 new / 인스턴스 선언)
   - **소멸자** : instance 소멸 시 (동적할당 해제 delete / Scope에서 벗어날 때 / 전역 instance의 경우 프로그램이 끝날 때)

3. 객체의 생성

   - `int a(10);` → 일반적인 인스턴스 생성

   - `int b(a);`  → 복사 생성

   - 객체의 복사 생성: 복사 생성자를 호출한다.

     ```c++
     CMyString strData;
     CMyString strNew;             //  기본적인 객체 instance 생성(=Default 생성자)
     CMyString strCopy(strData);   //  복사 생성(=복사 생성자 호출)
     ```

4. 생성자의 종류

   | Constructor                           | Description                                                  |
   | ------------------------------------- | ------------------------------------------------------------ |
   | 기본 생성자(Default Constructor)      | 매개변수가 없는 경우                                         |
   | 다중 정의(Overriding)된 생성자        | 매개변수가 존재하는 경우                                     |
   | → 변환 생성자(Conversion Constructor) | 매개변수가 1개인 경우                                        |
   | 복사 생성자(Copy Constructor)         | 이름 없는 임시 객체와 연관                                   |
   | 이동 생성자(Move Constructor)         | 복사생성자 + R-Value 참조<br />(Move Semantics 지원을 위해 C++11부터 등장) |



## [1] 복사 생성자

> **객체의 복사본을 생성할 때 호출되는 생성자**를 의미한다.

클래스를 작성할 때 복사 생성자를 생략하면 디폴트 생성자 처럼, Shallow Copy하는 복사 생성자를 컴파일러가 알아서 만들어 넣어둔다. **즉, 꼭 필요한 경우가 아니라면 굳이 정의할 필요는 없다.** 하지만 반대로 **복사 생성자를 적용하지 않으면 심각한 문제가 발생**하는 경우가 있다.

- **클래스 내부에서 메모리를 동적할당 및 해제하고, 이를 멤버 포인터 변수로 관리하는 경우**

```c++
class CMyData {
public:
	CMyData() { cout << "CMyData( )" << endl; }
	CMyData (const CMyData &rhs) {      // → 복사 생성자 선언 및 정의
		this -> m_nData = rhs.m_nData;  // → m_nData의 소속을 명확하게 표현하기 위해 사용    
        cout << "CMyData (const CMyData & rhs)" << endl;
	}

	int GetData(void) const {return m_nData;}
	void SetData(int nParam) {this -> m_nData = nParam;}
    
private:
	int m_nData = 0;
};

int _tmain ( int argc, _TCHAR * argv[]) {
	CMyData a;                           // → 디폴트 생성자가 호출되는 경우
	a.SetData(10);
	CMyData b(a);                        // → 복사 생성자가 호출되는 경우
	cout << b.GetData() << endl;
	return 0;
}
```



#### 복사 생성자가 꼭 필요한가요?

**Deep Copy & Shallow Copy**

- Shallow Copy는, **대상체에 접근할 수 있는 방법(수단, Pointer)이 추가**되는 것을 의미
- Deep Copy는 **원본(대상체) 자체가 하나 추가**되는 것을 의미

new 연산자로 동적할당을 통해 메모리를 관리하는 클래스의 사본을 만들 때, “Shallow Copy”를 통해서 대상체를 가리키는 포인터(수단)만 추가되면, 클래스를 해제할 때 내부에 있는 같은 동적할당된 메모리를 2번 delete 하는 경우가 발생한다. 이렇게 동적할당된 메모리를 Shallow Copy하게 되는 경우는 디폴트 복사 생성자를 이용할 때이다. 멤버가 가지고 있는 값만 복사하기 때문에, 원본 클래스의 멤버 포인터가 가지고 있던 똑같은 주소를 사본 클래스의 멤버 포인터변수가 가지게 된다. 

그러므로 new 연산자를 통해 동적할당 하는 class라면 같은 메모리가 2번 해제되는 경우를 방지하기 위해서 꼭 별도의 복사 생성자를 추가해줘야 하고, 해당 생성자 내에서 Deep Copy를 하는 과정이 포함되어야 한다.



#### 복사 생성자가 호출되는 경우 - (1) 함수 호출과 (2) 복사 생성

1. 명시적으로 객체의 복사본을 생성하는 방식으로 선언하는 경우: `CTest a(b);`
2. 함수 형태로 호출되는 경우
   - 클래스가 `매개변수`로 사용되는 경우
   - 클래스가 반환형식으로 사용되는 경우 → 이름없는 임시 객체를 만들어내는 문제가 있다.

```c++
class CTestData {
public:
   CTestData(int nParam) : m_nData(nParam) {cout<<“CTestData(int)”<<endl;}
   CTestData(const CTestData &rhs) : m_nData(rhs.m_nData) {
      cout << “CTestData(const CTestData&)” << endl;
   }
   int GetData() const {return m_nData;}
   void SetData(int nParam) {m_nData = nParam;}

private:
   int m_nData = 0;
};

void TestFunc(CTestData param) { // →  매개변수가 CTestData 클래스 형식이므로 복사 생성자 호출
                                 // →  CTestData param(a); 를 한 것과 같은 의미
   cout << “TestFunc()” << endl;
   param.SetData(20);            // 함수가 종료되면서 지역변수인 param instance는 소멸
}
int _tmain(int argc, _TCHAR * argv[]){
   cout << "*****Begin*****" << endl;
   CTestData a(10);
   TestFunc(a);
   cout << "a : " << a.GetData() << endl;
   cout << "*****End*****" << endl;
   return 0;
}

// ------------------------------- output --------------------------------------
*****Begin*****
CTestData(int)   → 인스턴스 a에 대해서 선언해서 변환 생성자 호출
CTestData(const CTestData &)  →  즉, 제작자가 코드를 잘 못 작성해서 의미없는 객체가 하나 
                                                     추가되어 성능 저하를 가져온다.
TestFunc()           
a : 10                 →  인스턴스 a에 대해서 SetData가 적용된 것이 아니므로, 값 그대로 유지
*****End*****
```

해당 코드에서 의미없는 객체가 하나 추가되는 것을 막기 위한 해결책 2가지

1. `CTestData(const CTestData &rhs) = delete;`
   delete를 통해서 **함수가 삭제되었다는 것을 명시적으로 표현. 오류를 발생**시킨다.
2. `TestFunc(const CTestData &param) `
   함수의 매개변수를 받을 때 **참조형식으로 받아서 객체가 새로 생성되는 것을 방지**한다.



#### 함수에서 매개변수로 class 형식을 받을 때, 주의할 point

```c++
void TestFunc(CTest Param)
void TestFunc(const CTest &Param)
```

1. 상수화된 instance의 경우, **(1) 매개변수에 대해 쓰기가 안되고**, **(2) const 멤버 메소드만 호출 가능**하다.
2. **const**: 매개변수로 받은 객체 instance의 값이 바뀌면 안되는 경우. (함수 내에서 바뀌는 경우 제외)
3. **&Param**: 의미없는 객체가 추가 생성되어, **성능의 저하 및 함수 Overhead**가 발생하는 것을 방지하기 위해 **참조형식 이용**



#### 복사 생성자와 Deep Copy

> Deep Copy: 복사에 의해서 실제로 2개의 값이 생성되는 것

클래스 멤버 中 포인터 변수가 존재하고, 클래스 내부에서 메모리 동적 할당 및 해제 한다면 Deep Copy !

```c++
class CTest {
public:
	CTest(int nParam) { m_pData = new int(nParam); }
	CTest(const CTest &rhs) {
          // → 별도의 복사 생성자를 선언 및 정의 하는 이유는 Deep Copy를 구현하기 위해서
          //   (1) 새로운 메모리를 동적할당 받고, (2) 별도의 대상체를 생성해서 값만 복사
		  this -> m_pData = new int(*rhs.m_pData );                          
        
		  // this -> m_pData = rhs.m_pData;
          //  → Default 복사 생성자의 역할과 동일 = Shallow Copy
          //    주소값 자체가 복사되어 대상체를 가리키는 수단이 하나 더 늘어난다.
          //    이렇게 되면, 같은 대상체에 대해서 delete를 2번 하게 되므로 오류가 발생한다.
	}
	~CTest() {delete nParam;}
    
private:
	int *m_pData = nullptr;
};

int _tmain(int argc, _TCHAR *argv[]) {
	CTest a;
	CTest b(a);
	return 0;
}
```



#### 대입 연산자

> **단순 대입 연산자가 구조체나 클래스에도 기본적으로 적용**된다. (단, 객체 선언 할 때 단순 대입 연산자는 복사 생성자를 호출한다.)

단순 대입 연산자의 동작방식 수정 → **연산자 다중정의 (Operator Overloading)**

- 연산자 자체를 C++에서는 함수로 만들어, Overloading(대체) 시킨다. → (+,-,/,*,%,=,++,+=, … )
- 연산자 자체를 함수로 생각할 수 있다. (단, 기본형식에는 안되고 **Class에 대해서 재정의 가능**)
- 대입 연산자는 Shallow Copy & Deep Copy와 연관이 되기 때문에 중요하다.

```c++
// 연산자 재정의가 없을 시, Shallow Copy → 모든 멤버의 값을 그대로 복사한다.
// 이런 경우에는 Class 내부에서 동적할당 시, delete를 중복하게 되는 문제가 발생한다.
CTest a;
CTest b;
a.SetData(5);
b = a;
b.operator=(a);

// Deep Copy가 되므로 오류없이 정상 작동!
// Overloading시, 객체 자신에 대한 참조를 반환시킨다! 연속되는 연산이나 Chaining에 활용 하도록 설계.
CTest& operator=(const Test & rhs) {
	*(this -> m_pData) = *rhs.m_pData;
	return *this;
}
```



## [2] 묵시적 변환

#### 변환 생성자(Conversion Constructor)

> 매개변수가 한 개인 생성자 → **클래스와 매개변수 형식 사이에 호환성**이 생긴다.

그러나 문제는, **변환 생성자가 은근슬쩍 호출되는 경우가 존재해서, 불필요한 임시객체를 만들어냄으로써 프로그램의 효율을 갉아먹는 원인이 된다.**

```c++
class CTestData {
public:
    CTestData(int nParam) : m_nData(nParam) {
    // → 매개변수가 하나뿐인 생성자는 형 변환이 가능하다.(호환성의 의미)
	    cout << "CTestData(int)" << endl;
	}
};

void TestFunc(CTestData param) { // → 원래 형식이 달라서 호출되면 안되는데 객체가 추가된다.
	cout << "TestFunc():" << param.GetData() << endl;
}
int _tmain(int argc, _TCHAR * argv[]){
    TestFunc(5);         // → CTestData param(5) 와 같은 형태로 인스턴스가 선언된다!
    return 0;            //   (호환성이 높은 변환 생성자가 호출된다.)   
}                           

// -------------------- output -----------------------
CTestData(int)
TestFunc() : 5
```



```c++
class CTestData {
public:
    CTestData(int nParam) : m_nData(nParam) {cout << "CTestData(int)" << endl;}
    ~CTestData() {cout << "~CTestData()" << endl;}
};

void TestFunc(const CTestData &param) {
	cout << "TestFunc():" << param.GetData() << endl;
}

int _tmain(int argc, _TCHAR * argv[]){
	cout << "*****Begin*****" << endl;
	TestFunc(5);
	// const CTestData &param = 5;가 되므로 문법적으로 오류인데,
	// 컴파일러가 ‘알아서' 임시 객체를 생성한 후 이 임시 객체에 대한
	// 참조가 TestFunc() 함수로 전달되도록 했다.
    //    → const CTestData &param = CTestData(5);
	// 제작자의 의도와 관계없이 + 허락없이 컴파일러가 알아서 객체를 생성 & 소멸 
    
	cout << "*****End*****" << endl;
	return 0;
}
```

따라서, 클래스 형식을 매개변수로 사용할 때

1. **const + 참조형식**으로 클래스 형식에 대한 매개변수 받아오기
2. **묵시적 변환 생성자를 지원하는 클래스인지 확인** 필요

묵시적 변환 생성자가 사용자 모르게 호출되는 가능성을 차단하는게 바람직 하므로, 변환 생성자 앞에 explicit 예약어를 붙여서, 묵시적으로 변환이 일어나지 않게 해서 임시객체가 생성되지 못하게 방지한다.

- `explicit CTestData(int nParam) : m_nData (nParam) { … }`



#### 허용되는 변환

클래스가 변환 생성자를 제공하면 두 형식사이에 호환성이 생긴다. 그러나, 이는 반쪽짜리 변환이다. (int → CTest 로 할 수 있지만, CTest → int로 할 수 없기 때문)이런 경우, **형변환 연산자 (혹은 형변환자)**를 만들어 놓으면 불가능한 변환이 가능해진다.

- 클래스의 형변환 연산자에도 변환 생성자처럼 **explicit 예약어를 적용**할 수 있다.
- 단, 묵시적 형변환을 이용하면 **사용자의 입장에서는 매우 편리하게 사용할 수 있다. → 제작자의 판단

```c++
class CTestData {
public :
    explicit CTestData(int nParam) : m_nData(nParam) { }
    operator int(void) { return m_nData; }
…
};

int _tmain(int argc, _TCHAR * argv[]){
    CTestData a(10);
    …
    cout << a << endl;
    // 본래 cout 객체를 통해 클래스 인스턴스를 화면에 출력할 수 없다. 
    // 하지만 형변환 연산자를 클래스 내부에 만들어 둬서, int 자료형으로 변환되어 인식
    
    cout << (int)a << endl;
    // 무조건 형 변환 시켜버리는 C언어 스타일
    
    cout << static_cast<int>(a) << endl;
    // C++ 에서 사용해야 하는 형변환 연산
    // 적절한 형변환 연산자를 제공하지 않으면 강제로 형식을 변환해주지 않는다.
    
    return 0;
}
```



## [3] 임시 객체

변환 생성자가 묵시적으로 호출되는 것을 **explicit** 예약어로 막으려는 이유는 사용자 코드에서 **보이지 않는 객체가 생성되고 소멸하는 것을 막기 위한 것**. 그런데, 이름도 없으며 생성직후 대부분 소멸하여 막을 수도 없는 은밀한 임시객체도 존재한다.



#### 이름없는 임시 객체

> 이름 없는 임시객체라는 것은 말 그대로 존재하는 인스턴스지만, **‘식별자'가 부여되지 않은 객체**

```c++
// 제작자 코드
class CTestData {
public:
    CTestData(int nParam, char* pszName): m_nData(nParam), m_pszName(pszName) {
        cout << "CTestData(int) :" << m_pszName << endl;
    }
    ~CTestData() { cout << "~CTestData() :" << m_pszName << endl; }
    CTestData(const CTestData &rhs): m_nData(rhs.m_nData), m_pszName(rhs.m_pszName) {
        cout << "CTestData(const CTestData &) :" << m_pszName << endl;
    }
    CTestData& operator= (const CTestData &rhs){
        cout << "operator =" << endl;
        m_nData = rhs.m_nData;
        return *this;
    }

    int GetData() const { return m_nData; }
    void SetData (int nParam) { m_nData = nParam; }

private:
    int m_nData = 0;
    char *m_pszName = nullptr;
};
```

```c++
// 사용자 코드
CTestData TestFunc(int nParam){
    CTestData a(nParam, “a”);
    return a;
}
int _tmain( int argc, _TCHAR *argv[] ){
    CTestData b(5, “b”);
    cout << “*****Before*****” << endl;
    b = TestFunc(10);
    cout << “*****After*****” << endl;
    cout << b.GetData() << endl;
    return 0;
}

// -------------------------- output ------------------------------
CTestData(int) : b
*****Before*****
CTestData(int) : a
(1) CTestData(const CTestData &) : a
(2) ~CTestData() : a
(3) operator = 
(4) ~CTestData() : a
*****After*****
10
~CTestData() : b
```

(1) 함수 반환값 자료형에 맞춘 Class형을 반환할 때, return 값으로 임시객체 생성

(2) 함수 내의 지역변수 모두 소멸

(3) return 값으로 반환된 임시객체와 관련된 작업 시행

(4) 임시객체와 관련된 작업이 끝나자마자, 임시객체 소멸 

**이름 없는 임시객체의 원본은, 임시객체의 복사 생성이 끝난 후, 임시객체가 할일을 다한 즉시 소멸**한다. 임시객체에 대해서 아무일도 안하는 코드(ex. `TestFunc(10);` ) 일지라도 임시객체는 생성되고 소멸된다. 성능만 저하될 뿐 얻는 소득은 아무것도 없다! 이런 불합리함을 없애고 싶다면, Release 모드로 컴파일하면 최적화를 시킨다.



하지만 이름없는 **임시객체에 “별명"을 부여**하면 상황이 또 달라진다.  → 임시객체가 할일이 남은 것과 똑같은 것!

```c++
int _tmain( int argc, _TCHAR *argv[] ){
    cout << “*****Before*****” << endl;
    CTestData &rData = TestFunc(10);
    cout << “*****After*****” << endl;
    return 0;
}

// -------------------------- output ------------------------------
*****Before*****
CTestData(int) : a
CTestData(const CTestData &) : a
~CTestData() : a
*****After*****
~CTestData() : a    // 임시객체가 _tmain() 함수의 실행이 끝난 후에 소멸
                    // rData 변수의 유효범위 안으로 임시객체의 생명주기가 맞춰진 것
```

임시객체의 이러한 일련의 과정은 **완전히 숨겨져 있어서 눈에 명시적으로 보이지 않는다. **그래서, 이러한 부분을 생각하지 않고 놓치기 쉽다. **(기본 자료형은 알아서 처리되니까 신경 X)**. 연산이 끝나면 바로 소멸하기 때문에 눈에 보이지 않지만, 이는 성능과 직결된다. 그래서 생긴 것이 **이동 시맨틱(C++11)**



## [4] 이동 시맨틱

> C++11에 새로 추가된 **이동 시맨틱(Move Semantics)**은 **이동 생성자 & 이동 대입 연산자**로 구현된다.

이동 시맨틱은 ‘이름없는 임시객체'의 문제를 해결하기 위해서 생겼다. 임시객체가 생기는 것은 막을 수 없다. 그래서 임시 객체가 생성되더라도 부하가 최소화 될 수 있도록 구조를 변경한다.

즉, 복사생성자와 대입연산자에 R-Value 참조를 조합해서, **새로운 이동 생성자 & 이동 대입 연산자를 만들어낸 것**

- `이동 생성자`: 함수 반환값으로 클래스가 있을 때! 
- `이동 대입 연산자` : 대입하는 연산의 값이 R-Value 일 때!
- 깊은 복사 대신, 얕은 복사를 통해서 부하가 튀는 것을 방지. **이렇게 하기 위해서는 임시객체가 생성될 때 기존의 pointer 변수에 null을 넣는다.**
- 얕은 복사를 통해서 대상체가 가리키는 것을 가져오고, 원래 임시 객체가 대상체를 가리키던 pointer 변수의 값을 nullptr 로 만들면서, 임시객체가 소멸될 때 원본 대상체의 값을 delete 하지 않도록 방지

```c++
class CTestData{
public:
  CTestData() { cout << "CTestData()" << endl; }
  ~CTestData() { cout << "~CTestData()" << endl; }
  CTestData(const CTestData &rhs) : m_nData(rhs.m_nData) {
    cout << "CTestData(const CTestData &rhs)" << endl;
  }
  CTestData(const CTestData &&rhs) : m_nData(rhs.m_nData) {
    // 임시객체의 생성은 막을 수 없지만, 최대한 메모리를 적게 사용해보자
    cout << "CTestData(const CTestData &&rhs)" << endl;
  }

  CTestData& operator = (const CTestData &) = default;

  int GetData() const { return m_nData; }
  void SetData(int nParam) { m_nData = nParam; }

private:
  int m_nData = 0;
};

CTestData TestFunc(int nParam) {
  cout << "**TestFunc() : Begin**" << endl;

  CTestData a;
  a.SetData(nParam);
  cout << "**TestFunc() : End**" << endl;
  
  return a;
}

int _tmain(void){
  CTestData b;
  cout << "*****Before*****" << endl;
  b = TestFunc(20);
  cout << "*****After*****" << endl;
  CTestData c(b);
  return 0;
}
```

