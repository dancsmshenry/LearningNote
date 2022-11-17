# 演进、环境与资源

- 测试cpp所支持的版本

  - ```cpp
    #include <iostream>
    
    using namespace std;
    
    int main(){
        cout << __cplusplus << endl;//201402，查看当前编辑器是否支持cpp14的版本
    }
    ```

- 新式c header file不带.h名称，而变为`#include<cstdio>`

  - 引入标准库的文件也不需要带.h了，而变为`#include<vector>`

- 在早期版本std::tr1里面的代码现在也被放到了std namespace里面了

- 推荐几个比较好的网站和书籍

  - cplusplue.com
  - gcc.gnu.org
  - zh.cppreference.con
