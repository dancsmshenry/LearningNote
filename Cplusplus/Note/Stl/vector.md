# vecotr a； a在堆上还是栈上？





# vecotr a； a中数据在堆上还是栈上？





# vector的clear()的时间复杂度是多少？

- 参考:https://www.zhihu.com/question/355171938/answer/2173582004





# 怎么在vector变量的有效期内，释放其中元素所占的内存

- `vector<int>().swap(a);`
- 但为什么不能用`a.swap(vector<Data>());`
  - 因为swap的参数是T&，不能传递匿名对象