#include <iostream>
#include <string>

using namespace std;

class Printer{
    private:
        Printer();
        Printer(const Printer& p);
    
    public:
        static Printer* getInstance(){
            return singlePrinter;
        }

        void printText(string str){
            cout << str << endl;
        }

    private:
        static Printer* singlePrinter;//这里的顺序必须有先后，因为static是编译器按顺序执行
};

Printer* Printer::singlePrinter = new Printer;

void test01(){
    //拿到打印机
    Printer * printer = Printer::getInstance();
    printer->printText("离职报告");
}

int main(){
    test01();
}