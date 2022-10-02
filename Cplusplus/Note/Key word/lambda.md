# lambda的用法

- ```cpp
  auto func = []() {
      cout << "" << endl;
  };
  
  auto func1 = []() -> int {
      return 1;
  };
  
  []() { std::cout << "test in nameless function" << std::endl;}(); // 匿名函数
  ```







# lambda参数

## []

| 格式    | 作用                                                         |
| ------- | ------------------------------------------------------------ |
| []      | 不进行捕获                                                   |
| [=]     | 使用拷贝捕获上下文变量（需要改变的话，要在小括号的后面加上mutable；这样就等价于&了） |
| [&]     | 使用引用捕获上下文变量                                       |
| [x]     | 拷贝x（值传递，将外面作用域的x值作为左值拷贝到lambda的作用域内；注意，此时的x是一个只读值；要修改的话就得加上mutable） |
| [&x]    | 引用x                                                        |
| [x]     | 拷贝x                                                        |
| [&, x]  | 拷贝x，其余的使用引用                                        |
| [=, &x] | 引用x，其余的使用拷贝                                        |

- ```cpp
      int x = 4;
      auto y = [&r = x, x = x + 1]() -> int
      // 对x的理解：是外面x的一个拷贝，因此此时外面的x不变（依然是4），而里面的x为一个新建的数字，其值为5
      // 但是这里的x是一个只读值
      // 如果想要改变它的话，就需要在后面加上mutable
      {
          r += 2;
          return x + 2;
      }(); // Updates ::x to 6, and initializes y to 7.
  ```

- lambda在使用拷贝捕获后修改外部变量时，需要添加mutable来修饰

  - 默认情况下,lambda函数总是一个const函数，mutable可以取消其常量性，使得捕捉到的变量内容可以更改使用该修饰符时，参数列表不可省略（即使参数为空）

- 捕捉列表不允许变量重复传递,否则就会导致编译错误

  - 比如:[=,a]："=" 已经以值传递的方式捕捉了所有变量,捕捉a重复



## ()

- 存放的是传入函数的参数



## {}

- 函数本体



## ->

- 箭头后面存放的是指定的返回类型

- ```cpp
  auto func1 = []() -> int {
      return 1;
  };//这里的箭头表示返回的类型
  ```







# details

- 在lambda函数定义中，参数列表和返回值类型都是可选部分，而捕捉列表和函数体可以为空。因此C++11中最简单的lambda函数为：[]{}; 该lambda函数不能做任何事情



## lambda之间不能互相赋值，但是可以赋给函数指针

- ```cpp
  void (*PF)();
  int main()
  {
      auto f1 = []
      { cout << "hello world" << endl; };
      auto f2 = []
      { cout << "hello world" << endl; };
      // f1 = f2; // 编译失败--->提示找不到operator=()
      // 允许使用一个lambda表达式拷贝构造一个新的副本
      auto f3(f2);
      f3();
      // 可以将lambda表达式赋值给相同类型的函数指针
      PF = f2;
      PF();
      return 0;
  }
  
  //	可以当作 函数指针参数 传入 函数
  void enumerateDict(void (*func) (Key&, Val&)) const;
  
  enumerateDict([](string& k, string& v) -> void {
  	//do something
  });
  ```



## 对于外部变量引用的捕获，由于引用捕获不会延长变量的生命周期，所以很有可能被悬挂



## 从效率上说，最好不要使用[=]，[&]来一次性大量捕获变量



## lambda在成员函数内，调用其他成员函数或变量时，对象可能已经销毁

- ```cpp
  //	std::thread使用lambda做回调，有没有什么注意事项
  #include <thread>
  #include <chrono>
  #include <iostream>
  
  class Test {
  public:
  	Test()  = default;
  	~Test() = default;
  	std::thread TestProblem() const {
  		std::thread thd(
  			[this] {
  				std::this_thread::sleep_for(std::chrono::seconds(1));
  				std::cout << data << std::endl;
  			}
  		);
  		return thd;
  	}
  private:
  	int data = 1;
  };
  
  int main(int argc, char* argv[]) {
  
  	Test* test = new Test;
  	std::thread thd = test->TestProblem();
  	thd.detach();
  
  	delete test;
  	std::this_thread::sleep_for(std::chrono::seconds(2));
  
  	return 0;
  }
  ```



## Lambda在满足要求的情况下会隐式转换为constexpr



- 我发现，lambda带来的问题就是变量的生命周期，可能会造成空悬挂的情况







# 底层实现

- 实际在底层编译器对于lambda表达式的处理方式，完全就是按照函数对象的方式处理的
- 即如果定义了一个lambda表达式，编译器会自动生成一个类，在该类中重载了operator()
