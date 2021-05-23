#include <iostream>

using namespace std;

template<class T>
void mySwap(T &a, T &b){
    T temp = a;
    a = b;
    b = temp;
}

template<class T>
void MySort(T arr[], int len){
    for (int i = 0; i < len; i++){
        int max = i;
        for (int j = i + 1; j < len; j++){
            if (arr[max] < arr[j]){
                max = j;//交换下标
            }
        }
        if (max != i){
            mySwap(arr[max], arr[i]);//交换数据
        }
    }
}

template<class T>//这个要紧跟着下面的函数
void printArray(T arr[], int len){
    for (int i = 0; i < len; i++){
        cout << arr[i] << ' '; 
    }
    cout << endl;
}

void test01(){
    char charArr[] = "helloworld";
    int len = sizeof(charArr)/sizeof(char);
    MySort(charArr, len);

    printArray(charArr, len);
}

void test02(){
    int intArr[] = {1,4,9,3,2,5,6,7,19};
    int len = sizeof(intArr)/sizeof(int);
    MySort(intArr, len);

    printArray(intArr, len);
}

int main(){
    //test01();

    test02();
}