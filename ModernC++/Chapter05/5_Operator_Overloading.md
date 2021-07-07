# 5. 연산자 다중정의

<br>

## [0] Basic

1. C++ 언어는 **연산자 재정의** **및** **연산자 다중정의**를 지원. 즉, 연산자가 함수화 될 수 있다. (단, Class에 대해서만)
2. **제작자**는 **대상(Class, 추상자료형)에 대해서 설계**를 한다.
    → 대상에 대해서 잘 알고 있기 때문에, **사용자의 입장에서 생각하며, 실수/오남용을 안하게 노력이 필요**
3. **사용자**는 제작자에 비해 **상대적으로 대상에 대해 무지**하다.
    → 따라서, 굳이 사용자가 깊이 복잡하게 공부하지 않아도 **“보편적 직관"**에 따라 **사용하는데 불편함이 없도록 제작자가 설계를 해줘야 한다.**
4. `CMyData a;`
   `a+=3;` / `a.append(3);` 사용자의 입장에서 무엇이 더 나은가?
    → `a+=3;` 표현이 **추상성이 더 높으며, 더 직관적이다. = 사용자가 실수할 가능성이 낮다.**
5. **추상성이 높다. = 복잡도가 낮다.**
    → 단순한 논리를 통해 추상적으로 구현이 가능하다. 유지보수 비용이 적게 든다.
6. **추상성이 낮다. = 복잡도가 높다.**
    → 많은 것을 신경써야 해서 Bug(오류)가 일어날 확률이 높다. 유지보수 비용이 많이 든다.
7. 결론
   (1) Class 객체에 제작자가 **연산자 재정의** **및** **연산자 다중정의**를 잘 설계하면,
      사용자의 입장에서 **직관성&편리성이 높아져서 S/W의 완성도가 증가한다.**
   (2) 근데, 만약 제작자가 잘 못만들면, 그 피해는 온전히 사용자가 덤탱이를 쓰게 된다.
   (3) 기본 연산자는 실패하면 안되기 때문에, "예외처리"를 통해 해결

<br>

## [1] 연산자 함수

- 연산자를 이용하듯 호출할 수 있는 메서드를 의미한다.
  - 제작자가 클래스를 만들 때, 지원가능한 연산자들을 만들어서 넣어주면 사용자는 훨씬 더 간결한 방법으로 코드를 작성할 수 있다.
- 연산자 함수는 절대 오류가 발생해서는 안된다! (**예외처리가 필수적**)
  - 사용자 코드를 간결하게 작성할 수 있도록 해준 덕분에 사용자 코드쪽의 문제점을 찾기가 어렵다. 이런 단점이 있음에도 불구하고, 유용한 장점 때문에 널리 사용된다!
- **단, 절대로 논리 연산자들을 다중 정의해서는 안된다.** 심각한 논리적 오류를 사용자에게 떠넘길 수 있다.

<br>

## [2] 산술 연산자

> ‘더한다'는 의미를 어떻게 정의하는가에 따라서 결과는 천차만별 이다. 즉, 무엇이든간에 제작자가 원하는 형태로 덧셈을 할 수 있다.

```c++
class CMyData {
public:
    CMyData(int nData): m_nData(nParam) {cout << “CMyData(int)” << endl;}  // 변환 생성자
    CMyData(const CMyData &rhs): m_nData(rhs.m_nData) {                    // 복사 생성자
	    cout << "CMyData(const CMyData&)" << endl;
    }
    CMyData(CMyData &&rhs) : m_nData(rhs.m_nData) {                        // 이동 생성자
	    // → const 생략 이유 = 포인터 멤버 변수가 있다면, 초기화 해줘야 하므로!
    	cout << "CMyData(const CMyData&&)" << endl;
    }

    operator int(void) {return m_nData;}               // 형변환 연산자
    CMyData operator+ (const CMyData &rhs) {           // 산술(+) 연산자
        cout << "operator +" << endl;
        CMyData result(0);
        result.m_nData = this -> m_nData + rhs.m_nData;
        return result;
    }
    CMyData& operator = (const CMyData &rhs) {         // 대입 연산자
        cout << "operator =" << endl;
        m_nData = rhs.m_nData;
        return *this;
    }

private:
	int m_nData = 0;
};

int _tmain(int argc, _TCHAR * argv[]){
    cout << "*****Begin*****" << endl;
    CMyData a(0), b(3), c(4);

    a = b + c;
    cout << a << endl;
    cout << "*****End*****" << endl;
    return 0;       
}                       

// ------------------------ output -----------------------------
*****Begin*****
CMyData(int)
CMyData(int)
CMyData(int)
operator +
CMyData(int)
CMyData(CMyData&&)
operator =
7
*****End*****
```

- **함수의 매개변수**가 클래스인 경우에는 무조건 참조로 받는 것이 맞습니다.
- 모든 연산자의 **함수의 반환형식**을 참조로 반환하면 좋겠지만, 함수의 반환형식은 대입연산자 같은 몇몇을 제외하고는 임시객체를 의도적으로 이용할 수 밖에 없습니다.
  - 예를들어 x+y 라는 연산을 하면 x와 y는 절대로 달라지지 않으므로 새로운 instance를 반환해서 임시객체로 이용해야 한다.
- **연산자 함수도 다중정의** 할 수 있습니다.
  - 우리가 항상 쓰던 cout 객체는 ostream 클래스의 인스턴스입니다. 전역변수 형태로 존재하며, std 네임스페이스 소속입니다. ostream 클래스는 C++의 다양한 기본자료형에 대해서 <<, >> 라는 연산자 함수를 제공하고, 이는 기본자료형 각각에 대해서 다중정의 되어있습니다.

<br>

## [3] 대입 연산자

#### 대입 연산자 사용 시, 2가지 주의해야하는 경우

1. 본인 스스로를 대입하는 경우 (`a=a`)

   - 보편적이거나 적절한 코드는 아니지만, 분명 문법적으로 틀리지 않았고, 뒤쪽에 인스턴스가 매개변수로 받아서 이러한 경우가 실제로 발생할 수 있다.

   - ```c++
     void operator = (const CMyData &rhs) {
     	if ( this == &rhs ) return; // → R-Value가 자기 자신이면 대입을 수행하지 않는다.
     	…
     }
     ```

2. 대입 연산이 연속으로 이어지는 경우 ( a = b = c )

   - 클래스 인스턴스안에 void를 대입하는 것은 불가능! 따라서 자기 자신을 반환한다.

   - ```c++
     CMyData& operator = (const CMyData &rsh) {
     	if( this == &rhs ) return *this;
     	… 
     	return *this;
     } 
     ```



#### 복합 대입 연산자

> +=, *=, /=, -=, … 에 대해서 3가지 과정이 공통적으로 포함된다.

```c++
CMyData& operator += (const CMyData &rhs) {
    // 1. 현재 값 처리
    int *pnNewData = new int(*m_pnData);

    // 2. 누적할 값 처리
    *pnNewData += *rhs.m_pnData;

    // 3. 기존 데이터를 삭제하고 새 메모리로 대체
    delete m_pnData;
    m_pnData = pnNewData;

    return *this;
}
```



#### 이동 대입 연산자

1. 연산에 의한 것 = 이동 대입 연산자
   - 임시객체를 R-Value 삼아서 곧바로 단순대입연산을 실시할 때, 이동대입연산자 호출
2. 함수 호출의 반환자료 = 이동 생성자
   - 임시객체를 이용해서 연산을 하거나, 호출자 함수에서 처리할 때 임시객체를 만들어주는 방법

```c++
CMyData& operator = (CMyData &&rhs) {
	cout << “operator=(Move)” << endl;

	m_pnData = rhs.m_pnData;
	rhs.m_pnData = nullptr;
    
    // → 얕은 복사를 수행하고, 원본은 nullptr로 초기화해서 delete가 2번 되는 것을 방지한다.
	return *this;
}
```

<br>

## [4] 배열 연산자

> 포인터 및 메모리 동적할당을 수행하면서도, 사용자에게 배열을 다루는 것처럼 편리함을 제공! → 성능 향상 및 기능의 확장을 기대할 수 있다.

#### 2가지 경우를 고려해줘야 한다!

1.  L-Value로 사용하는 경우: `int& operator [] (int nIndex);`
2. R-Value로 사용하는 경우:  `int operator [] (int nIndex) const;`

```c++
// 제작자 코드
class CIntArray {
public:
	CIntArray(int nSize) : m_nSize(nSize) {
		m_pnData = new int[nSize]; // 전달된 개수 만큼 int 자료를 담을 수 있는 메모리를 확보한다.
		memset(m_pnData, 0, sizeof(int) * nSize);
	}
	~CIntArray { delete [] m_pnData; }

	int operator [] (int nIndex) const {
		cout << "operator [] const" << endl;
		return m_pnData[nIndex];
	}
	int& operator [] (int nIndex) {
		cout << "operator []" << endl;
		return m_pnData[nIndex];
	}

private:
	int *m_pnData;
	int m_nSize;
};

//사용자 코드
void TestFunc (const CIntArray &arParam){
	cout << “TestFunc()” << endl;
	cout << arParam[3] << endl;
}
int _tmain(int argc, _TCHAR *argv[]){
	CIntArray arr(5);
	for( int i = 0; i < 5; ++i ){
		arr[i] = i*10;
	}
	TestFunc(arr);
	return 0;
}
```

<br>

## [5] 관계 연산자

> 상등 / 부등 / 비교 연산자를 의미

- `int 클래스_이름::operator == (const 클래스_이름 &);`

- `int 클래스_이름::operator != (const 클래스_이름 &);`

<br>

## [6] 단항 증감 연산자

> ++ / -- 연산자를 의미

- 전위식 : (매개변수 없이) `int operator ++ ()`

- 후위식 : `int operator ++ (int)`



우선순위에 따라 계산 결과가 달라지므로 주의

```c++
int operator ++ () {
    cout << “operator++()” << endl;
    return ++m_nData;
}

int operator ++ (int) {
    cout << “operator++(int)” << endl;
    int nData = m_nData;
    m_nData++;
    return nData;
}
```

