#include <iostream>

using namespace std;

/**
 * 单例模式的实现：
 * 在单例类的内部，实现只生成一个实例，同时它提供一个静态的getInstance()工厂方法
 * 让客户可以访问它的唯一实例
 * 为了防止外部对其实例化，将其默认构造函数和拷贝构造函数设计为私有
 * 在单例类内部定义了一个singleman类型的静态对象，作为外部共享的唯一实例
 * 
 * 单例模式的介绍：
 * 单例模式的核心结构只有一个被称为单例的特殊类，
 * 通过单例模式可以保证系统中有一个类只有一个实例而且该实例易于外界访问
 * 从而方便对实例个数的控制并且节约系统资源（参考任务管理器）
 **/ 


//创建主席类
//需求：单例模式，为了创建类中的对象，并且保证只有一个对象实例
class ChairMan{
    private:
        //1、将构造函数私有化
        ChairMan(){
            cout << "Creat a single chairman" << endl;
        }

        //5、拷贝构造私有化(防止拷贝出新的对象)
        ChairMan(const ChairMan& cm){

        }

        //2、创建一个指向对象的指针，并设为静态变量
        //注意：这里如果是设为public的话，在外面写一个ChairMan::singleMan = NULL;,对象就无了

        //3、所以将该实例对象设为私有化
        static ChairMan *singleMan;

    public:
        //4、对外提供访问单例对象的接口
        //如果不是static，那外界还需要通过对象来访问，不符合逻辑；
        //故使用static，用作用域来使用接口
        static ChairMan *getInstance(){
            return singleMan;
        }
};

//类外初始化，类内声明（注意，这里的初始化还是相当于是在类内实现的，所以new还是会用到构造函数）
ChairMan* ChairMan::singleMan = new ChairMan;

void test01(){
    ChairMan* cm1 = ChairMan::getInstance();
    ChairMan* cm2 = ChairMan::getInstance();//这两者都指的是同一个实例对象

    if (cm1 == cm2){
        cout << "cm1 == cm2" << endl;
    }
}

int main(){
    cout <<"int main()" << endl;//证明该实例对象在编译阶段就已经创建了
    test01();
}

/**
 * 总结：
 * 目的：为了让类中只有一个实例，实例不需要自己释放
 * 将默认构造和拷贝构造都私有化（默认不私有化会导致能够构造无限个对象，拷贝不私有化会导致拷贝出无数个相同的对象）
 * 内部维护一个对象指针，并且这个对象指针也是要私有化的（由这个指针指向唯一的单例对象，指针私有化是防止类外修改指针）
 * 私有化唯一指针
 * 对外提供函数接口访问指针（指针都私有化了，肯定要有找到它的入口吗，即公开入口）
 * 保证类中只能实例化唯一一个对象
 **/ 