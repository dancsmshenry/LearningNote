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







- 栈上是不能动态扩容的

- 原因：栈上的元素的析构时脱离了作用域才会析构的，而我们如果需要实现动态扩容的话就需要

- int a[4]是在栈上分配内存的

- vector越界访问其实是不会报错的（但是访问到啥变量就不清楚了）（因为每次判断是否越界的分支if语句其实是非常损耗性能的）

- vector的at会检查是否越界（at的参数时size_t，放入负数的话会被转为整数）

- vector<int> a(4);// 保证了初始化得到的元素为0

- resize的扩容，会把新扩容得到的元素设为0（原来的部分比较大的话，就会把多出来的部分给删除掉）

- 弱引用的存在周期一定要比主对象的存在周期要短（否则容易存在空悬指针的情况）

- ```cpp
  #include <iostream>
  #include <vector>
  
  using namespace std;
  
  int main() {
      int *p;
      std::vector<int> holder;
      {
          vector<int> a{1,2,3,4,5};
          p = a.data();
          holder = std::move(a);
      }
      cout << p[0] << endl;
  }
  ```

- clear只是改变容器的大小（last/end指针的位置），不会改变capacity

- shrink_to_fit将容器的容量变小，所以会重新分配内存

- 为什么end要在最后一个元素的后面一个位置：因为当没有元素的时候，begin和end指向一起

- 迭代器也可以用[]运算符进行访问：b[i]等价于*(b + i)

- erasre也不会改变容器的容量的



为什么会出现int8_t等类型？

- 因为对于c语言的标准，不同的平台都有自己的实现（windows上32位和64位的long都是32位的，但是在unix中32位的是16位，64位的是32位）
- 所以为了方便跨平台，使用stdint库，统一标准