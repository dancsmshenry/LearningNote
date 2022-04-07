- ```cpp
  //a) string转const char*
  string s = “abc”; 
  const char* c_s = s.c_str(); 
  
  //b) const char* 转string，直接赋值即可
  const char* c_s = “abc”; 
  string s(c_s); 
  
  //c) string 转char*
  string s = “abc”; 
  char* c; 
  const int len = s.length(); 
  c = new char[len+1]; 
  strcpy(c,s.c_str()); 
  
  //d) char* 转string
  char* c = “abc”; 
  string s(c); 
  
  //e) const char* 转char*
  const char* cpc = “abc”; 
  char* pc = new char[strlen(cpc)+1]; 
  strcpy(pc,cpc);
  
  //f) char* 转const char*，直接赋值即可
  char* pc = “abc”; 
  const char* cpc = pc;
  ```

- string的底部就是封装了const char*

- 实际操作过程我们可以用const char*给 string类初始化

- string继承自basic_string,其实是对char * 进行了封装，封装的string包含了char*数组，容量，长度等等属性

- string可以进行动态扩展，在每次扩展的时候另外申请一块原空间大小两倍的空间（2^n），然后将原字 符串拷贝过去，并加上新增的内容