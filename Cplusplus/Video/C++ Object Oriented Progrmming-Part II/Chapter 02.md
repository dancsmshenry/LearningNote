# conversion function

- ```cpp
  class Fraction{
    public:
      Fraction(int num, int den = 1):m_numerator(num), m_denominator(den){}
      
      operator double() const{
          return (double)(m_numerator / m_denominator);
      }//转换函数，conversion function，把Fraction类型转换为double类型
      
     private:
      int m_numerator;//分子
      int m_denominator;//分母
  };
  
  Fration f(3, 5);
  double d = 4 + f;//调用operator double()将f转换为0.5
  ```
