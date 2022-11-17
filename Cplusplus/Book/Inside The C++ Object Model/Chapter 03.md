# 第三章 Data 语意学

- 影响对象大小的三个因素
  - 语言本身所造成的额外负担（如virtual带来的虚指针）
  - 编辑器对代码的优化（有些编译器会优化对象的模型和大小）
  - Alignment的限制（结构对齐，将数值调整到某个数的整数倍，padding，就是将数值调整到某数的整数倍，在32位计算机上，通常alignment为4 bytes）
- 编译器的优化
  - 对于一个空类，一般的编译器会认为它的大小为1，里面只有一个char大小的类型
  - 而一些编译器则对其进行了优化，认为它的大小为0
  - 编译器之间的差异说明cpp对象模型的演化
- 影响每个class object的大小的原因：
  - 由编译器自动加上的额外data members，用以支持某些语言特性（主要是各种virtual特性）
  - alignment（边界调整）需要



## 3.1 Data Member 的绑定

- 早期cpp的两种防御性程序设计风格

  - ```cpp
    /*把所有的data members放在class声明起头处，以确保正确的绑定*/
    class Point3d{
        float x, y, z;
        public:
        	float X() const {return x;}
    };
    ```

  - ```cpp
    /*把所有的inline functions，不管大小都放在class声明之外*/
    class Point3d{
        public:
        	Point3d();
        	float X() const;
        	void X(float) const;
    };
    
    inline float Point3d::X() const{
        return x;
    }
    ```

  - 背景：书上有写







## 3.2 Data Member 的布局

- 在class object中的排列中，nonstatic data members的排列顺序和声明顺序一致（不受static等member的影响）

- 注：static member不属于class object的

- 编译器还可能会合成一些内部使用的data members以支持整个对象模型，如vptr（有些编译器会放到最前面，有些会放到最后面）

- ```cpp
  class Point3d{
      public:
      //...
      private:
      	float x;
      private:
      	float y;
  };
  
  /*对于该class的布局，各家编译器是把一个以上的access sections连锁在一起，依照声明的顺序称为一个连续区块*/
  ```





## 3.3 Data Member 的存取

### Static Data Members

- 可以视为一个global变量（但只在class生命范围内可见）
- 每个static data member只有一个实例，存放在程序的data segment
- 无论多复杂的继承结构，static member只有一个实例
- 如果取一个static data member的地址，会得到一个指向其数据类型的指针，而不是指向其class member的指针
- 对于不同对象的同名static值，编译器会对每一个static data member编码（name-mangling）



### Nonstatic Data Members

- nonstatic data members直接存放在每一个class object中

- ```cpp
  Point3d Point3d::translate(const Point3d &pt) {
      x += pt.x;
      y += pt.y;
  }
  
  /*实际上的内部转化*/
  Point3d Point3d::translate(Point3d* const this, const Point3d &pt) {
      this -> x += pt.x;
      this -> y += pt.y;
  }
  ```

- 对于以下两个存取数据的方法

  - origin.x = 0.0;和pt->x = 0.0;
  - 一般是没有区别的，但是如果是虚拟继承的话，pt->x = 0.0;就要到执行期才能够执行

- 注意：获取object中的data member的时候，地址会比平常的时候要少一位（即要-1，3.6节会说的）

  - 获取data member的偏移量在编译时期可知





## 3.4 ”继承“与Data Member

### 只要继承不要多态

- 出现的问题：
  - 会重复设计一些相同操作的函数
  - 把一个class分解为两层或多层，可能为了“表现class体系之抽象化”而膨胀所需的空间（alignment）
- 因为继承是把整个对象都继承下来



### 加上多态

- 虚指针vptr在cpp2.0以后都房子啊最前面
- 负担：
  - virtual table
  - vptr
  - constructor，构造的时候需要设立初值
  - destructor，析构的时候需要指向空



### 多重继承

- 对一个多重派生对象，将其地址指定给最左端base class的指针（布局从左往右依次，即从上往下）



### 虚拟继承

- 2种虚拟多重继承的模型（每一个对象都带有一个指针）
- 对于object中的变量，求它的地址得到的是他的偏移量
- 区分int和object中的int：地址的会+1，平常的不会





## 3.5 对象成员的效率







## 3.6 指向 Data Members 的指针