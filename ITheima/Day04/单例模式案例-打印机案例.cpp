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
            cout << "Printer using in :"<< m_Count << endl;
        }

        int m_Count = 0;

    private:
        static Printer* singlePrinter;
};

Printer* Printer::singlePrinter = new Printer;

void test01(){
    //拿到打印机
    Printer * printer = Printer::getInstance();
    printer->printText("lizhi baogao");
    printer->printText("ruzhi baogao");
    printer->printText("lizhi baogao");
}

int main(){
    test01();
}