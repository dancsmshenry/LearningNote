# non-explicit one argument ctor

- ```cpp
  class Fraction{
    public:
      Fraction(int num, int den = 1):m_numerator(num), m_denominator(den){}
      
      Fraction operator+(const Fraction& f){
          return Fraction(...);
      }
      
     private:
      int m_numerator;//分子
      int m_denominator;//分母
  };
  
  Fration f(3, 5);
  Fraction d2 = f + 4;//会首先调用Fraction的重载，,发现目标不是Ftaction，所以会首先调用non-explict-one-argument-ctor将4转换为Fraction，然后再调用Fraction的重载+
  ```

- 但是会出现一种情况，即对于编译器来说有多条路径需要走，此时会出现二义性

  - ```cpp
    class Fraction{
      public:
        explict Fraction(int num, int den = 1):m_numerator(num), m_denominator(den){}
        
        operator double() const{
            return (double)(m_numerator / m_denominator);
        }
        
        Fraction operator+(const Fraction& f){
            return Fraction(...);
        }
        
       private:
        int m_numerator;//分子
        int m_denominator;//分母
    };
    
    Fration f(3, 5);
    Fraction d2 = f + 4;//编译器到底是要把4变为Fraction来操作，还是说要把f变为double来操作（两条路都走得通）
    //所以为了规范使用，就在构造函数前面加上explict，表示这个函数必须显式调用，不能隐式调用
    //这样，代码就会直接报错，说不能把double隐式的转换为Fraction
    ```

- 关键字explicit：被该词修饰的函数只能被显式的调用，不能被隐式调用（大部分用在构造函数上面）