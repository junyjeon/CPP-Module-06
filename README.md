<div align="center">
  <h1>💻 CPP Module 06</h1>
  <p>C++ 타입 캐스팅 | 형변환 연산자</p>

  <img src="assets/18_cpp_module_06_review.jpg" alt="C++ Type Casting" width="800"/>
  
  <div>
    <img src="https://img.shields.io/badge/Score-100%2F100-success?style=flat-square&logo=42" alt="42 Score"/>
    <img src="https://img.shields.io/badge/Language-C++98-00599C?style=flat-square&logo=c%2B%2B" alt="Language"/>
  </div>

  ### 학습 내용
  - static_cast 변환
  - dynamic_cast와 RTTI
  - reinterpret_cast 활용
  - const_cast의 사용과 주의점
  - 스칼라 타입 변환과 직렬화
</div>

## 🚀 Quick Start
```bash
make && ./convert
```

## 📋 목차
1. [개요](#-개요)
2. [구현 요구사항](#-구현-요구사항)
3. [타입 변환](#-타입-변환)
4. [테스트 방법](#-테스트-방법)
5. [Tips](#-tips)
6. [평가 준비](#-평가-준비)
7. [참고자료](#-참고자료)

## 🎯 개요
> C++의 다양한 타입 캐스팅을 학습하는 프로젝트입니다.

### 프로젝트 구조
```
📦 CPP-Module-06
 ├── 📜 ex00/
 │   ├── ScalarConverter.{hpp,cpp}  # 스칼라 타입 변환
 │   └── main.cpp
 ├── 📜 ex01/
 │   ├── Serializer.{hpp,cpp}       # 데이터 직렬화
 │   └── main.cpp
 └── 📜 ex02/
     ├── Base.{hpp,cpp}             # 동적 타입 식별
     └── main.cpp
```

### Key Features
- 스칼라 타입 변환 (char, int, float, double)
- 데이터 직렬화/역직렬화
- RTTI를 이용한 동적 타입 식별
- 4가지 C++ 캐스팅 연산자 활용

## 💡 구현 요구사항
> C++의 타입 캐스팅 연산자들을 올바르게 사용해야 합니다.

### 필수 구현
- [x] static_cast
- [x] dynamic_cast
- [x] reinterpret_cast
- [x] const_cast

## 🔄 타입 변환
> C++의 4가지 캐스팅 연산자의 특징과 사용법을 이해합니다.

### 1. static_cast
```cpp
// 기본 타입 간의 변환
double d = 3.14;
int i = static_cast<int>(d);  // 3

// 포인터 타입의 상향/하향 변환
Base* base = static_cast<Base*>(derived);      // 상향 변환 (안전)
Derived* derived = static_cast<Derived*>(base); // 하향 변환 (주의 필요)
```

### 2. dynamic_cast
```cpp
class Base { virtual void dummy() {} };  // 다형성 필요
class Derived : public Base {};

Base* base = new Derived;
// RTTI를 이용한 안전한 하향 변환
Derived* derived = dynamic_cast<Derived*>(base);
if (derived == nullptr) {
    // 변환 실패 처리
}
```

### 3. reinterpret_cast
```cpp
// 포인터를 정수로 변환
uintptr_t serialized = reinterpret_cast<uintptr_t>(ptr);

// 정수를 포인터로 변환
void* deserialized = reinterpret_cast<void*>(serialized);
```

### 4. const_cast
```cpp
const int constant = 42;
int* modifiable = const_cast<int*>(&constant);  // const 제거 (위험!)
```

## 🔍 테스트 방법
> 각 exercise별 테스트를 수행합니다.

### ex00: ScalarConverter
```bash
./convert 0
./convert nan
./convert 42.0f
./convert "Hello World"
```

#### 실행 결과 예시
```
# ./convert 42
char: '*'
int: 42
float: 42.0f
double: 42.0

# ./convert nan
char: impossible
int: impossible
float: nanf
double: nan
```

### ex01: Serializer
```bash
./serialize
```

#### 실행 결과 예시
```
Original address: 0x7fff5fbff7e0
Serialized: 140732920764384
Deserialized address: 0x7fff5fbff7e0
Values match: true
```

### ex02: Base
```bash
./identify
```

#### 실행 결과 예시
```
Generated type: C
Pointer identifies as: C
Reference identifies as: C
```

### 자주 발생하는 오류와 해결책
1. 컴파일 오류
```bash
error: 'dynamic_cast' not permitted with -fno-rtti
# 해결: RTTI 활성화
CXXFLAGS += -frtti
```

2. 런타임 오류
```cpp
// 문제: segmentation fault in dynamic_cast
Base* ptr = nullptr;
Derived& ref = dynamic_cast<Derived&>(*ptr);  // crash!

// 해결: nullptr 체크 추가
if (ptr) {
    try {
        Derived& ref = dynamic_cast<Derived&>(*ptr);
    } catch (std::bad_cast&) {
        // 처리
    }
}
```

3. 변환 오류
```cpp
// 문제: 부동소수점 정밀도 손실
float f = 42.42f;
std::cout << std::fixed << std::setprecision(1);  // 추가

// 문제: 문자 출력 형식
char c = 42;
std::cout << "char: '" << c << "'" << std::endl;  // 따옴표 추가
```

## ⚠️ 주의사항
> 구현 시 반드시 확인해야 할 사항들입니다.

### 1. 타입 변환 시
- 범위 검사 필수
  ```cpp
  // 잘못된 예
  int i = 1000;
  char c = static_cast<char>(i);  // 데이터 손실!

  // 올바른 예
  if (i >= 0 && i <= 127) {
      char c = static_cast<char>(i);
  } else {
      std::cout << "char: impossible" << std::endl;
  }
  ```

- 특수값 처리
  ```cpp
  // nan, inf 등의 특수값 처리
  if (std::isnan(d)) {
      std::cout << "char: impossible" << std::endl;
      std::cout << "int: impossible" << std::endl;
  }
  ```

### 2. 메모리 관리
- RTTI 사용 시 메모리 누수 주의
  ```cpp
  Base* ptr = generate();
  // 반드시 삭제 필요
  delete ptr;
  ```

## 💡 Tips
### 1. 디버깅
```bash
# 컴파일 시 디버그 심볼 추가
clang++ -g *.cpp

# gdb로 디버깅
gdb ./convert
(gdb) break ScalarConverter::convert
(gdb) run "42.42"
```

### 2. 구현 전략
- 문자열 파싱은 단계별로 구현
  1. 특수값 확인 (nan, inf)
  2. 문자 리터럴 확인 ('c')
  3. 숫자 파싱 (정수/실수)

- RTTI 활용
  ```cpp
  try {
      A& a = dynamic_cast<A&>(base);
      std::cout << "A" << std::endl;
  } catch (std::bad_cast&) {
      // 변환 실패
  }
  ```

## ✅ 평가 준비
> 평가 시 확인하는 핵심 사항들입니다.

### 1. 기본 요구사항
| 항목 | 설명 | 확인 |
|-----|------|------|
| 컴파일 | C++ 98 표준 준수 | ⬜ |
| 캐스팅 | 적절한 캐스팅 연산자 사용 | ⬜ |
| 예외 처리 | 범위 검사 및 에러 처리 | ⬜ |
| 메모리 | 누수 없음 | ⬜ |

### 2. Exercise별 체크리스트

#### ex00: ScalarConverter
- [ ] char 변환 및 출력
  - 출력 가능 문자인 경우 `'` 로 감싸기
  - non-displayable 처리
- [ ] 숫자 변환 정확도
  - 소수점 처리
  - 과학적 표기법 지원
- [ ] 특수값 처리
  - nan, +inf, -inf
  - nanf, +inff, -inff

#### ex01: Serializer
- [ ] reinterpret_cast 올바른 사용
- [ ] 데이터 손실 없는 변환
- [ ] 포인터-정수 간 변환 정확성

#### ex02: Base
- [ ] dynamic_cast 올바른 사용
- [ ] RTTI 활용
- [ ] 랜덤 생성 구현
- [ ] 포인터/참조 버전 구분

### 3. 평가 대비 질문
```cpp
// Q: static_cast와 dynamic_cast의 차이점은?
A: static_cast는 컴파일 시점, dynamic_cast는 실행 시점에 타입 검사.
   dynamic_cast는 RTTI를 사용하여 더 안전하지만 성능 저하가 있음.

// Q: reinterpret_cast는 언제 사용하나요?
A: 포인터와 정수 간의 변환 등 로우레벨 타입 재해석이 필요할 때.
   직렬화/역직렬화 구현에 활용.

// Q: const_cast 사용 시 주의점은?
A: const 객체 수정은 정의되지 않은 동작을 유발할 수 있음.
   레거시 코드 통합 등 불가피한 경우에만 제한적으로 사용.
```

## 📚 참고자료
> 과제 구현에 도움이 되는 자료들입니다.

### C++ 타입 캐스팅
- [C++ Reference - Type Casting](https://en.cppreference.com/w/cpp/language/expressions#Conversions)
  - [static_cast](https://en.cppreference.com/w/cpp/language/static_cast)
  - [dynamic_cast](https://en.cppreference.com/w/cpp/language/dynamic_cast)
  - [reinterpret_cast](https://en.cppreference.com/w/cpp/language/reinterpret_cast)
  - [const_cast](https://en.cppreference.com/w/cpp/language/const_cast)

### RTTI (Run-time Type Information)
```cpp
// typeid 연산자 사용
#include <typeinfo>

Base* ptr = new Derived();
std::cout << typeid(*ptr).name() << std::endl;

// dynamic_cast와 RTTI
if (dynamic_cast<Derived*>(ptr) != nullptr) {
    std::cout << "ptr is pointing to Derived" << std::endl;
}
```

### 문자열 처리
- [std::string](https://en.cppreference.com/w/cpp/string/basic_string)
- [std::stringstream](https://en.cppreference.com/w/cpp/io/basic_stringstream)
```cpp
#include <sstream>

std::stringstream ss;
ss << "42.42";
double d;
ss >> d;  // 문자열을 double로 변환
```

### 부동소수점
- [IEEE 754](https://en.wikipedia.org/wiki/IEEE_754)
- [std::numeric_limits](https://en.cppreference.com/w/cpp/types/numeric_limits)
```cpp
#include <limits>
#include <cmath>

// 특수값 처리
bool isNaN = std::isnan(value);
bool isInf = std::isinf(value);

// epsilon 비교
bool isEqual = std::fabs(a - b) < std::numeric_limits<double>::epsilon();
```

### 도구
- [C++ Shell](http://cpp.sh/)
    - 온라인 C++ 컴파일러
- [Compiler Explorer](https://godbolt.org/)
    - 어셈블리 확인
- [C++ Insights](https://cppinsights.io/)
    - 코드 동작 분석