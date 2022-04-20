# vecotr a； a在堆上还是栈上？





# vecotr a； a中数据在堆上还是栈上？





# vector的clear()的时间复杂度是多少？

- 参考:https://www.zhihu.com/question/355171938/answer/2173582004





# 怎么在vector变量的有效期内，释放其中元素所占的内存

- `vector<int>().swap(a);`
- 但为什么不能用`a.swap(vector<Data>());`
  - 因为swap的参数是T&，不能传递匿名对象





# push_back和emplace_back

- 这两者都是将对象放到vector当中

- ```cpp
  #include <iostream>
  #include <vector>
  
  class Test {
  public:
      Test() {std::cout << "Test" << std::endl;}
      ~Test() {std::cout << "~Test" << std::endl;}
      Test(const Test &p) {std::cout << "Test copy" << std::endl;}
      Test(const Test &&p) {std::cout << "Test move" << std::endl;}
      Test(int age) {std::cout << "Test age" << std::endl;}
  };
  
  int main(int argc, const char *argv[]) {
      std::vector<Test> v;
      v.emplace_back(Test(12));
      /*
      Test age
  	Test move
  	~Test
  	~Test//程序结束的析构
  	传右值：这里调用了一次构造函数（先在外面构造一个临时对象，执行完这句话后析构），一次移动构造函数（在emplace_back里面），所以有两次析构
      */
      
      v.push_back(Test(12));
      /*
      Test age
  	Test move
  	~Test
  	~Test//程序结束的析构
  	传右值：这里调用了一次构造函数（先在外面构造一个临时对象，执行完这句话后析构），一次移动构造函数（在push_back里面），所以有两次析构 
      */
      
      v.emplace_back(12);
      /*
      Test age
  	~Test//程序结束的析构
  	传右值：这里调用了一次含参的构造函数
      */
      
      v.push_back(12);
      /*
      Test age
  	Test move
  	~Test
  	~Test//程序结束的析构
  	传右值：这里调用了一次构造函数（先在外面构造一个临时对象，执行完这句话后析构），一次移动构造函数（在push_back里面），所以有两次析构
      */
      
      //传左值的话，两者都是一样的：调用一次构造函数，再调用一次拷贝构造函数（在push_back或emplace_back里面）
  }
  
  ```

- 所以，从语义上来说，如果你传入的是一个左值，就表明你是还需要这个值的，所以两个push都是一样的效果

- 但，如果你传入的是一个右值的话，那么系统就会认为你是不需要这个值的，所以就会调用移动构造函数然后再push

- 而至此，好像两者都是一样的，没啥不同，但是接下来就会有问题了：

  - 如果传入的不是该类对象，而是一个数字（但是可以隐性的转换为该类对象）
  - 那对于push_back来说，和传入一般的右值是一样的
  - 可是，对于emplace_back来说，只会调用一次构造函数哦......
  - 可能这就是emplace_back的意义吧....







# vector的扩容

- https://blog.csdn.net/fl2011sx/article/details/119452341
- 讲的很好，瞬间就理解为什么之前说一定要在不会expect的地方写上expect了...