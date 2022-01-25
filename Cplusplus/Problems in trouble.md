- A继承自父类B和C，如果使用B的指针ptr1和C的指针ptr2同时指向一个A对象，则ptr1和ptr2的地址是否一致？

- B是父类，派生出A，B中有虚函数f并被A重写，使用B的指针指向A对象，则： 若B的构造函数中调用f则调用A的f还是B的f以及为什么； 如果B中有成员函数g，g中调用了f，而B的构造函数调用了g，则是调用了谁的f以及为什么

- 如何解释下列代码

  - ```cpp
    class A{
        public:
            A(){}
            A(A &a){cout << "A &a" << endl;}
            A(const A &a){cout << "const A &a" << endl;}
    };
    
    int main(){
        const A a;
        A a1(a);//调用A(const A &a){cout << "const A &a" << endl;}
        
        A a;
        A a2(a);//调用A(A &a){cout << "A &a" << endl;}
    }
    ```

  - 是否可以参照侯捷之前说的，如果两个函数const版本和非const版本同时存在，const只能调用const的版本，非const版本只能调用非const的版本呢？

- static和const可不可以同时修饰成员函数？（代码测试，不行的！）

- 多态只能适用于虚函数

  - 即如果有一个父类的指针指向子类，然后调用两个类都有的那个同名的虚函数，那么这就叫做多态，就会发生调用子类函数的情况
  - 但是，如果是调用两个类都有的同名的一个函数（非虚函数），那么会直接调用到父类的那个函数那里

- 对于一个多态的小bug

  - 如果父类的virtual函数设为了private的话，那就无法使用多态了（代码测验过）

- 能说一下虚继承的底层实现吗？或者多态（虚函数表）的底层实现也可以

- `int (&b)[10] = a;`是什么？`int a[10];`又是什么？（mark:https://blog.csdn.net/qq_34988341/article/details/106452518）

- 为什么构造函数不能作为虚函数

- 在群里面看到的代码：

  - ```cpp
    static char_type* copy(char_type* dst, const char_type* src, size_t n){//拷贝的过程要注意内存重叠的问题
        assert(src + n <= dst || dst + n <= src);
        char_type* r = dst;
        for (; n != 0; -- n, ++ dst, ++ src){
            *dst = *src;
        }
        
        return r;
    }
    ```

  - 内存拷贝的四种情况：

  - 第一种：dst  空格空格  src

  - 第二种：src 空格空格 dst

  - 第三种：dst src（src的有一部分是和dst重合的），那么，此时从前往后复制的时候，也不会影响

  - 第四种：src dst（dst的有一部分是和src重合的），那么，此时从前往后复制，就会把src后面的一部分给覆盖掉，导致两个内存的内容不同

  - 参考c的库函数memmove()