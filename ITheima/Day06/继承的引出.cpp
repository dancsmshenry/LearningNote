#include <iostream>

using namespace std;

// class News{
//     public:
//         void header(){
//             cout << "����ͷ��" << endl;
//         }
    
//         void footer(){
//             cout << "�����ײ�" << endl;
//         }

//         void left(){
//             cout << "����б�" << endl;
//         }

//         void content(){
//             cout << "���Ų���" << endl;
//         }
// };

// class YuLe{
//     public:
//         void header(){
//             cout << "����ͷ��" << endl;
//         }
    
//         void footer(){
//             cout << "�����ײ�" << endl;
//         }

//         void left(){
//             cout << "����б�" << endl;
//         }

//         void content(){
//             cout << "�װٺ�.." << endl;
//         }
// };

//�̳�д��������һ���������վ �ظ��Ĵ��붼д�������ҳ��
class BasePage{
    public:
        void header(){
            cout << "����ͷ��" << endl;
        }
    
        void footer(){
            cout << "�����ײ�" << endl;
        }

        void left(){
            cout << "����б�" << endl;
        }
};


//�̳м��ٴ�������
//BasePage ���ࣨ���ࣩ News �����ࣨ���ࣩ
//������Ա���������֣�һ���Ǵӻ���̳й����ģ�һ�����Լ����ӵĳ�Ա
//�ӻ���̳й����ı���Ϊ���ԣ������ĳ�Ա����Ϊ����
class News :public BasePage{//�̳У�News��̳���BasePage��
    public:
        void content(){
            cout << "���Ų���" << endl;
        }
};

class YuLe :public BasePage{
    public:
        void content(){
            cout << "�װٺ�.." << endl;
        }
};

class Game :public BasePage{
    public:
        void content(){
            cout << "KPLֱ��" << endl;
        }
};

void test01(){
    News news;
    news.header();
    news.footer();
    news.left();
    news.content();

    //����ҳ
    YuLe yule;
    yule.header();
    yule.footer();
    yule.left();
    yule.content();
}

int main(){
    test01();
}