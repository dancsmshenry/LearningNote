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