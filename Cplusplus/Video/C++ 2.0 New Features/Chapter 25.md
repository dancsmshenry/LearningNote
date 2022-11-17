# 写一个Move-aware class

- ```cpp
  class MyString{
    static size_t DCtor;
    static size_t CTor;
    static size_t CCtor;
    static size_t MCtor;
    static size_t MAsgn;
    static size_t Dtor;
    private:
      char* _data;
      size_t _len;
      void _init_data(const char *s){
          _data = new char[_len + 1];
          memcpy(_data, s, _len);
          _data[_len] = '\0';
      }
    public:
      //default constructor
      MyString():_data(NULL), _len(0){++DCtor;}
      
      //constructor
      MyString(const char* p):_len(strlen(p)){
          ++CTor;
          _init_data(p);
      }
      
      //copy constructor
      MyString(const MyString& str): _len(str._len){
          ++CTor;
          _init_data(str._data);
      }
      
      //move constructor
      MyString(MyString&& str) noexcept:_data(str._data), len(str._len){
          ++MCtor;
          str.len = 0;//新的指针指向了传进来的对象后，原来的那个对象的指针的len属性就要设为0，_data就要指向空（如果没指向空，就会造成多个指针指向同一个对象，而如果这里直接是删除了这个指针，那么在后面的析构函数的位置，就会变为delete一个不存在的东西，就会报错；同时，因为传进来的大多是临时对象，在作用域结束后会消失的，如果指针没有指向null，那么就会使得本对象一起和他消失）
          str._data = NULL;//重要
      }
      
      //copy assignment
      MyString& operator=(const MyString& str){
          ++CAsgn;
          if (this != &str){
              if (_data) delete _data;
              _len = str._len;
              _inity_data(str._data);
          }else{}
          
          return *this;
      }
      
      //move assignment
      MyString& operator=(MyString&& str) noexcept{
          ++MAsgn;
          if (this 1= &str){
              if (_data) delete _data;//如果原来有指向的，先把它删除
              _len = str._len;
              _data = str._data;
              str.len = 0;
              str._data = NULL;
          }
          return *this;
      }
      
      //dtor
      virtual ~MyString(){
          ++Dtor;
          if (_data){//需要先判断是不是null，如果不是才delete
              delete _data;
          }
      }
  };
  ```
