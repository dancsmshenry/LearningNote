#include <iostream>

using namespace std;

/**
 * 单例模式的核心结构只有一个被称为单例的特殊类，
 * 通过单例模式可以保证系统中有一个类只有一个实例而且该实例易于外界访问
 * 从而方便对实例个数的控制并且节约系统资源（参考任务管理器）
 **/


//创建主席类
//需求：单例模式，为了创建类中的对象，并且保证只有一个对象实例
/**
 * 对这一过程的解释：一方面，首先是用static静态初始化对象（因为用static就可以在编译器初始化变量）
 * 而另一方面，初始化对象时会调用构造函数
 * 但是单例模式是只有一个对象，如果构造函数是在public，按照正常的做法就会无限的创建这个对象
 * ps：正常构造对象时调用的构造函数都是调用public中的
 * 所以必须把构造函数放到private中（放到这里的话因为已经有了这个类，所以就可以调用private中的构造函数）好像说错了
 **/ 
class ChairMan{
    //构造函数并将其私有化，如果不私有化，那就会导致可以不断重复的创建这个对象，就不是单例模式了
    private:
        //这里：因为是单例模式，只能创建一个类对象，但如果要将构造函数放在public中，会导致说可以构造很多的类对象
        //所以首先把构造函数放到private中，不被创建那么多的类对象
        //问题又来了：私有化以后怎么生成这个类对象啊？？？
        ChairMan(){
            cout << "创建国家主席" << endl;
        }

        //所以就在这里，会先写一个static（维护一个静态的指向chairman的一个指针）
        //而静态的又是在编译期就执行的（ok）
        //注意，这里是在类内声明，即要在类外初始化
        //而这里是静态的变量，是可以在其他地方访问得到的，就有可能被篡改为NULL
        //所以为了保证不被删改，改为private:
        //而私有化以后不能访问得到这个数据，所以就要向外面提供接口
        static ChairMan *singleMan;

        

    public:
        ChairMan (const ChairMan &cm){
            //为了防止单例模式中唯一的对象被拷贝，这里将拷贝构造函数也私有化（最后私有化吧）
        }

        //对外提供接口，来访问主席
        static ChairMan* getInstance(){
            return singleMan;
        }
};

//这里就是之前的静态指针的初始化（去掉static，加上作用域ChairMan）
//这里加上了作用域，所以还是在类内里面做的操作，就可以访问private的ChairMan
ChairMan* ChairMan::singleMan = new ChairMan;

void test01(){
    /**
     * ChairMan c1;
     * ChairMan *c2 = new ChairMan;
     * ChairMan *c3 = new ChairMan;
     **/ 
    
    //这样做的好处是，封装的ChairMan类只能是singleMan，别的方法无法new出这个类
    // ChairMan::singleMan;

    //ChairMan c1;//很明显这段代码是错误的
}

void test02(){
    // ChairMan *cm1 = ChairMan::singleMan;
    // ChairMan *cm2 = ChairMan::singleMan;
    // cout << (cm1 == cm2 ? "Yes" : "No");//Yes
    //即二者是指向同一个类对象，是共享数据
}

void test03(){
    ChairMan* cm1 = ChairMan::getInstance();//这样就不能修改对象的指针了，不能改为nulll了
    ChairMan* cm2 = ChairMan::getInstance();
    cout << (cm1 == cm2 ? "Yes" : "No") << endl;//Yes,即指向的是同一个对象

    ChairMan* cm3 = new ChairMan(* cm2);
    cout << (cm3 == cm2 ? "Yes" : "No") << endl;//No，这里被拷贝了一个新的和singleman一模一样的对象
    //解决办法：拷贝函数私有化
}

int main(){
    cout << "调用main函数" << endl;
    //test01();
    /**
     * 这里是先输出“创建国家主席”（因为这里是静态创建对象，是在编译期就执行的）
     **/ 
    //ChairMan p1;//这里出现报错，因为其构造函数为私有的，无法被类外的语句访问
    //即平常的类对象的构建，是由类外的语句调用类内的构造函数，所以一般的构造函数放在类的公共部分

    //test02();
    test03();
}
/**
 * 单例模式：
 * 目的：为了让类中只有一个实例，实例不需要自己释放
 * 将默认构造和拷贝构造都私有化（默认不私有化会导致能够构造无限个对象，拷贝不私有化会导致拷贝出无数个相同的对象）
 * 内部维护一个对象指针，并且这个对象指针也是要私有化的（由这个指针指向唯一的单例对象，指针私有化是防止类外修改指针）
 * 对外提供函数接口访问指针（指针都私有化了，肯定要有找到它的入口吗，即公开入口）
 * 保证类中只能实例化唯一一个对象
 **/