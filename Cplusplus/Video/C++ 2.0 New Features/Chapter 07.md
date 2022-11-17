# Explicit for ctors taking more than one argument

- 对于含有一个或多个参数（有默认值的）的构造函数，不希望在程序中隐式的调用，就加上explicit

- ```cpp
  class Complex{
    public:
      explicit Complex(int re, int im = 0):real(re), imag(im){}
      
      Complex operator+(const Complex& x){
          return Complex((real + x.real), (imag) + x.imag);
      }
  };
  
  Complex c1(12, 5);
  Complex c2 = c1 + 5;//error,因为这里不能隐式的把5转换为complex
  ```

- 大概率只会用在类的构造函数上

- ```cpp
  class P{
      public:
      P(int a, int b){
        //  
      }
      
      P(initializer_list<int>){
          //
      }
      
      explicit P(int a, int b, int c){
          //
      }
  };
  
  P p5 = {1,2,32};//error,不能隐式的调用P(int a, int b, int c)函数
  ```

