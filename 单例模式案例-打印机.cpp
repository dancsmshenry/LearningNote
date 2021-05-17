#include <iostream>

using namespace std;

class Printer{
    private:
        Printer(){};
        Printer(const Printer& p){};
    
    public:
        static Printer* getInstance(){
            return singlePrinter;
        }

        void printText(string str){
            m_Count ++ ;
            cout << str << endl;
            cout << "��ӡ��ʹ����"<< m_Count << "����" << endl;
        }

        int m_Count = 0;

    private:
        static Printer* singlePrinter;//�����˳��������Ⱥ���Ϊstatic�Ǳ�������˳��ִ��
};

Printer* Printer::singlePrinter = new Printer;

void test01(){
    //�õ���ӡ��
    Printer * printer = Printer::getInstance();
    printer->printText("��ְ����");
    printer->printText("��ְ����");
    printer->printText("��н����");
}

int main(){
    test01();
}