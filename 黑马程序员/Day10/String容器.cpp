#include <iostream>
#include <string>//�ַ�����ͷ�ļ�
#include <stdexcept>//�쳣��ͷ�ļ�

using namespace std;

/**
 * char*��һ��ָ�룬��string��һ���࣬��װ��char*����������ַ���
 **/ 

//�ַ����Ĺ���
void test01(){
    //Ĭ�Ϲ��죨�Զ����죨�ࣩ��˼�������string�Ĺ��죩
    string str;
    
    //ʹ��һ��string�����ʼ����һ��stirng���󣬿�������
    string str1(str);

    //ʹ����֪�ַ�����ʼ��������Ϊ�ǿ�������
    string str2 = str;
    string str3 = "abc";
    
    //ʹ��n���ַ���c��ʼ������
    string str4(10, 'n');
    
    cout << str3 << endl;
    cout << str4 << endl;

    //������ֵ
    str = "Hello";
    str1 = str3;

    //string& assign(const char *s, int n);�����ַ���s��ǰn���ַ�������ǰ���ַ���
    str2.assign("abcdef", 3);
    cout << str2 << endl;

    //string& assign(const string &s, int start, int n);����s��start��ʼn���ַ���ֵ���ַ���
    string str6;
    str6.assign("abcdefg", 1, 3);//bcd
    cout << str6 << endl;

    //string& assign(int n, char c);����n���ַ�c������ǰ�ַ���
    string str7;
    str7.assign(10, 'a');
    cout << str7 << endl;

    //string& assign(const string &s);�����ַ���s������ǰ�ַ���
    //string& assign(const char *s);�����ַ�s������ǰ�ַ���
    string str8;
    str8.assign(str7);
    cout << str8 << endl;
}


/**
 * string�����ַ�����
 * char& operator[](int n){};//ͨ��[]����ȡ�ַ�
 * char& at(int n)//ͨ��at������ȡ�ַ�
 **/ 
void test02(){
    string s = "Hello world!";
    
    for (int i = 0; i < s.size(); i ++){
        // cout << s[i] << endl;
        // cout << s.at(i) << endl;
        /**
         * []���ʵ�Խ��ĵط���ֱ�ӹҵ�
         * at���ʵ�Խ��ĵط����׳��쳣
         **/ 
    }

    try{
        //cout << s[1000] << endl;
        cout << s.at(1000) << endl;
    }catch(out_of_range &e){
        cout << e.what() << endl;//ʹ�ñ�׼����쳣�����׳��쳣
        cout << "throw exception" << endl;
    }catch(...){
        cout << "catch other exception" << endl;
    }
}

//string��ƴ�ӡ����Һ��滻
void test03(){
    //ƴ��
    string s1 = "I";
    string s2 = " love you!";

    //string+string
    s1 += s2;

    //string+char
    s1 += '!';

    //string+char
    const char *a = "!!!";
    //ע�⣺�����"!!!"��ָconst char����һ�����������������һ��charָ��ָ��const char���������ͻᱨ���Ż�
    //���ԣ���Ҫ��Ϊconst
    s1 += a;

    s1.append("!!!!");

    cout << s1 << endl;


    //����
    
    //����Ҳ����Ļ��ͷ���-1
    //int find(const string& s, int pos = 0) const;//����str��һ�γ��ֵ�λ�ã���pos��ʼ����
    //int find(const char* s, int pos = 0) const;//����s��һ�γ��ֵ�λ�ã���pos��ʼ����
    //int find(char c, int pos = 0) const;//����c��һ�γ��ֵ�λ�ã���pos��ʼ����
    //int find(const char* s, int pos = 0, int n) const;//��posλ�ò���s��ǰn���ַ���һ��λ��

    //rfind�ǴӺ���ǰ�ҵ�
    //int rfind(const stirng& str, int pos = npos) const;//����str���һ�γ��ֵ�λ�ã���pos��ʼ����
    //int rfind(const char* s, int pos = npos) const;//����s���һ�γ��ֵ�λ�ã���pos��ʼ����
    //int rfind(const stirng& str, int pos, int n) const;//��pos����s��ǰn���ַ����һ��λ��
    //int rfind(const char c, int pos = 0) const;//�����ַ�c���һ�γ��ֵ�λ��


    string s11 = "abcdef";
    int pos = s11.find("dc");
    cout << pos << endl;

    //�滻
    //string& replace(int pos, int n, const string& str);//�滻��pos��ʼn���ַ�Ϊ�ַ���str
    //string& replace(int pos, int n, const char* str);//�滻��pos��ʼ��n���ַ�Ϊ�ַ�str

    string s111 = "hello";
    s111.replace(1, 3, "1111111");
    //��Ȿ�ʣ��ǰ�s111�������ַ���λ����Ҫ���ɵ��ַ�
    cout << s111 << endl;
}

//string�ıȽϲ���
void test04(){
    //int compare(const string& s) const;//���ַ���s���бȽ�
    //int compare(const char* s) const;//���ַ���s���бȽ�
    /**
     * compare������>ʱ����1��<ʱ����-1��==ʱ����0
     * �Ƚ����ִ�Сд���Ƚ�ʱ�ο��ֵ�˳����Խǰ���ԽС
     * ��д��AС��Сд��a
     * �ȴ�С�볤��û�й�ϵ�����ǵ����ıȽ���ĸ���ֵ���
     **/ 

    string s1 = "hell";
    string s2 = "hello";

    if (s1.compare(s2) == 0){
        cout << "s1 == s2" << endl;
    }else if (s1.compare(s2) == -1){
        cout << "s1 < s2" << endl;
    }else{
        cout << "s1 > s2" << endl;
    }
}

//string�Ӵ�
//string substr(int pos = 0, int n = npos) const;//������pos��ʼ��n���ַ���ɵ��ַ���
void test05(){
    string s1 = "hello world!!";
    string s2;
    s2 = s1.substr(0, 5);
    cout << s2 << endl;

    //���󣬲���һ���Ҽ����û���
    string email = "zhangtao@sina.com";

    int pos = email.find("@");
    cout << "pos = " << pos << endl;

    cout << "username:" << email.substr(0, pos) << endl;
}

//string�Ĳ����ɾ��
/**
 * string& insert(int pos, const char* s&)//�����ַ���
 * string& insert(int pos, const string& str)//�����ַ���
 * string& insert(int pos, int n, char c)//��ָ��λ�ò���n���ַ�c
 * 
 * string& erase(int pos, int n = npos)//ɾ����pos��ʼ��n���ַ�
 **/ 
void test06(){
    string s1 = "hello";
    s1.insert(1, "111");
    cout << "s1 = " << s1 << endl;

    //ɾ��111
    s1.erase(1, 3);
    cout << "s1 = " << s1 << endl;
}

void func(string s){
    cout << s << endl;
}

void func2(char *s){
    cout << s << endl;
}

void test07(){
    string s = "abc";

    //string ת char
    const char *p = s.c_str();

    func(p);//��ʽת����const char��ʽת��Ϊstring

    //char ת stirng
    string s2(p);

    // func2(s2);//���ﲻ�ܹ���string��ʽת��Ϊchar
}

void test08(){
    //��סһ�������ַ��������¸�ֵ���·����ڴ��ʱ�򣬵�ַ�ͻᷢ���ı�
    //��ô�ı�֮ǰԭ���ĵ�ַ�Ͳ���ı�����s��ֵ��
    //��������������ĵ�ַû�з����ı䰡��������(�ı��ˣ�������ԭ���Ĵ�С������û�����·���ռ�)
    string s = "abcdef";
    char& a = s[1];
    char& b = s[2];
    a = '2';
    b = '1';
    cout << s << endl;//a21def
    cout << (int*)s.c_str() << endl;

    s = "sdflkjaslkdsfslkfdsdf";
    a = '2';
    b = '1';
    cout << s << endl;
    cout << (int*)s.c_str() << endl;
}

//дһ�������������ڲ���string�ַ����е�����Сд��ĸ����Ϊ��д��ĸ
void test09(string &s){
    for (int i = 0; i < s.size(); i ++){
        //ȫ��Ϊ��д
        s[i] = toupper(s[i]);

        //ȫ��ΪСд
        // s[i] = tolower(s[i]);
    }

    cout << s << endl;
}

int main(){
    // test01();

    // test02();

    // test03();

    // test04();

    // test05();

    // test06();

    // test07();

    // test08();

    string s1 = "lskdfjslkfjslkdf";
    test09(s1);
}