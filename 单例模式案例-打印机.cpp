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
            cout << "打印机使用了"<< m_Count << "次了" << endl;
        }

        int m_Count = 0;

    private:
        static Printer* singlePrinter;//这里的顺序必须有先后，因为static是编译器按顺序执行
};

Printer* Printer::singlePrinter = new Printer;

void test01(){
    //拿到打印机
    Printer * printer = Printer::getInstance();
    printer->printText("离职报告");
    printer->printText("入职报告");
    printer->printText("加薪申请");
}

int main(){
    test01();
}