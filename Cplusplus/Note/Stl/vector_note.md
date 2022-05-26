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