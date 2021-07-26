#include <iostream>

using namespace std;

// class News{
//     public:
//         void header(){
//             cout << "公共头部" << endl;
//         }
    
//         void footer(){
//             cout << "公共底部" << endl;
//         }

//         void left(){
//             cout << "左侧列表" << endl;
//         }

//         void content(){
//             cout << "新闻播放" << endl;
//         }
// };

// class YuLe{
//     public:
//         void header(){
//             cout << "公共头部" << endl;
//         }
    
//         void footer(){
//             cout << "公共底部" << endl;
//         }

//         void left(){
//             cout << "左侧列表" << endl;
//         }

//         void content(){
//             cout << "白百合.." << endl;
//         }
// };

//继承写法，抽象一个基类的网站 重复的代码都写到这个网页上
class BasePage{
    public:
        void header(){
            cout << "公共头部" << endl;
        }
    
        void footer(){
            cout << "公共底部" << endl;
        }

        void left(){
            cout << "左侧列表" << endl;
        }
};


//继承减少代码内容
//BasePage 基类（父类） News 派生类（子类）
//派生成员包含两部分：一类是从基类继承过来的，一类是自己增加的成员
//从基类继承过来的表现为共性，新增的成员体现为个性
class News :public BasePage{//继承，News类继承于BasePage类
    public:
        void content(){
            cout << "新闻播放" << endl;
        }
};

class YuLe :public BasePage{
    public:
        void content(){
            cout << "白百合.." << endl;
        }
};

class Game :public BasePage{
    public:
        void content(){
            cout << "KPL直播" << endl;
        }
};

void test01(){
    News news;
    news.header();
    news.footer();
    news.left();
    news.content();

    //娱乐页
    YuLe yule;
    yule.header();
    yule.footer();
    yule.left();
    yule.content();
}

int main(){
    test01();
}