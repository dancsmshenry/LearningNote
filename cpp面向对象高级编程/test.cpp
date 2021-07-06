#include <iostream>

using namespace std;

class Complex{
    public:
        Complex(int r, int i):re(r), im(i) {}

        inline Complex& __doapl(Complex* ths, const Complex& r){
            ths->re += r.re;
            ths->im += r.im;
            return *ths;
            /**
             * 这里return返回的是一个指针指向的对象，是一个value值
             * 但是上面接受端是一个引用
             * 看似不合理，实际上用引用接受远比用值接受要快得多（即这里也可以改为不用&直接用值接收）
             * 规定定律：传递者无需知道接收者是以引用的方式接收的
             * 即我反正接收的是一个对值得引用，你只要给我一个值即可（无论是通过什么方式获取的值）
             **/ 
        }

        inline Complex& operator+= (const Complex& r){
            return __doapl(this, r);
        }

        int getRe() const{
            return re;
        }

        int getIm() const{
            return im;
        }

    private:
        int re;
        int im;
};

inline Complex operator +(Complex& x, Complex& y){
    return Complex(x.getRe() + y.getRe(), x.getIm() + y.getIm());
    //这里是临时对象，所以不能用引用来接收
    //这里的+是一个二元操作符，所以参数是一左一右的
    //如果在类里面的话，那第一个参数默认就是类的this
}

int real(Complex x){
    return x.getRe();
}

int imag(Complex x){
    return x.getIm();
}

ostream& operator<<(ostream& os, const Complex& r){
    return os << '(' << r.getRe() << ',' << r.getIm() << ')';
    //这里的r用了const以后，是不可以访问其内置函数(那些没有const的内置函数)的，也就是确保不会改变类对象原来的数据
    // return os << '(' << real(r) << ',' << imag(r) << ')';
}

int main(){
    Complex c1(1, 0);
    Complex c2(2, 3);
    c2 += c1;
    c2 = c2 + c1;

    // cout << c2.getRe() << " " << c2.getIm() << endl;

    cout << c2;
}
/**
 * 书写类对象的时候，一定要自己手写类对象的拷贝（即重载=）
 * 因为如果不自己重载，假如类对象内部维护的是一个指针，指针指向的是一个char
 * 不重载，导致在拷贝的时候直接是把新的对象的指针指向原来的那个对象，就会出现偏差错误
 * 即只拷贝指针就是浅拷贝，把内容具体的复制过去就是深拷贝
 * 然后因为原来的指针也有一个指向的char，现在没有指向了，就叫做内存泄漏
 * 
 * 栈：在作用域结束后就会清空所有的内容
 * 堆：需要自己手动释放内存
 * 
 * 静态函数的区别在于里面是没有this指针的
 * 
 * 是说在类里面的静态变量，是在编译的时候就分配了空间了的
 * 在函数里的静态变量，是要在开始的时候（进入其作用域）才分配空间，但是作用域结束后改变量也不会消失的
 * 而类里面的静态函数是没有this指针的
 * 
 * 构造是由内而外的
 * 析构是由外而内的
 * 
 * 子类继承父类后的函数：
 * non-virtual函数：不希望子类重新定义它，即这个函数所有的子类和父类都要一样
 * virtual函数：希望子类重新定义它（一定要重新定义它），并且已经有了默认的定义
 * pure virtual函数：希望子类一定要重新定义它，而父类没有对其的默认定义
 **/ 