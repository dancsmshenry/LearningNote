#include <iostream>
#include <string>
#include <stdexcept>//�쳣��ͷ�ļ�

using namespace std;

void test01(){
    string str;//Ĭ�Ϲ��죨�Զ����죨�ࣩ��˼�������string�Ĺ��죩
    //����һ���յ��ַ���
    
    string str1(str);//��������
    //ʹ��һ��string�����ʼ����һ��stirng����

    string str2 = str;//Ҳ�ǿ�������
    string str3 = "abc";
    //ʹ����֪�ַ�����ʼ������
    
    string str4(10, 'n');
    //ʹ��n���ַ���c��ʼ������

    cout << str3 << endl;
    cout << str4 << endl;

    //������ֵ
    str = "Hello";
    str1 = str3;

    //string& assign(const char *s, int n);�����ַ���������ǰn���ַ�������ǰ���ַ���
    str2.assign("abcdef", 6);
    cout << str2 << endl;

    //string& assign(const string &s, int start, int n);����s��start��ʼn���ַ���ֵ���ַ���
    string str6;
    str6.assign(str2, 0, 3);//ע���Ǵ�start��ʼ��nλ
    cout << str6 << endl;

}

/**
 * string����ַ�����
 * char& operator[](int n){};//ͨ��[]����ȡ�ַ�
 * char& at(int n)//ͨ��at������ȡ�ַ�
 **/ 
void test02(){
    string s = "Hello world!";
    
    for (int i = 0; i < s.size(); i ++){
        // cout << s[i] << endl;
        //cout << s.at(i) << endl;//������ͬ
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
    }
    catch(...){
        cout << "�׳�Խ���쳣"  << endl;
    }
}

int main(){
    // test01();
    test02();
}
//��Ϊ���¶��ǹ���strign��api��ʹ�ã����Ծ��ݲ��˽���