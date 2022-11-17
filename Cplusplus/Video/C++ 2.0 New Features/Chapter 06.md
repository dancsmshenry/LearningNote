# Initializer_list II

- ```cpp
  void print(std::initializer_list<int> vals){
      for (auto p = vals.begin(); p != vals.end(); ++ p){
          cout << *p << endl;
      }
  }//和之前的variadic templates相比，前者可以接收任意数量任意类型的，而这个只能接收任意数量指定类型的
  
  print({1,2,3,4,5,6});
  
  class P{
    P(int a, int b){
        //
    }
    
    P(initializer_list<int> initlist){
        //
    }
  };
  
  P p(11, 5);//调用的是第一个构造函数
  P p{11, 5};//调用的是第二个函数（如果没有了第二个函数，会自动调用第一个函数）
  P p{11, 22, 33};//调用的是第二个函数
  P s={11, 5};//调用的也是第二个函数（如果没有了第二个函数，会自动调用第一个函数）
  //但是如果是complex之类的话，就会调用到int a，int b的那个函数
  ```

- initializer_list的底层实现

  - 包含一个指向array的一个指针和其长度
  - 所以如果copy一个相同的initializer_list，那么，这两个list其中的指针都是指向同一个内存地址的（浅拷贝）

- 被广泛的用于stl中（用list，接受任意个数的对象作为初值）

- 也可以用于比较大小的max和min上，使其可以比较多个对象的大小

  - ```cpp
    int maxn(initializer_list<int> __l){
        int result = INT_MIN;
        for (auto p = __l.begin(); p != __l.end(); p ++ ){
            result = max(*p, result);
        }
        return result;
    }
    
    int main(){
        cout << maxn({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19}) << endl;
    }
    ```

