# tuple

- ```cpp
  tuple<string, int, int, complex<double>> t;
  cout << "sizeof = " << sizeof(t) << endl;//32,为什么不是（4+4+4+16）呢？
  
  cout << get<0>(t) << get<1>(t) << endl;//get是获取tuple中的第n个元素
  
  auto t2 = make_tuple(22,49,"77");//make_tuple制造出一个tuple
  
  get<1>(t1) = get<1>(t2);//get其中的元素并赋值
  
  t1 < t2;//把tuple中的每个元素都拿出来进行比较，最后返回结果
  
  tuple<int, float, string> t3(77, 1.1, "more light");
  int i1;
  float f1;
  string s1;
  tie(i1, f1, s1) = t3;//把i1,f1,s1三个值放到t3里面
  
  typedef tuple<int, float, string> TupleType;
  cout << tuple_size<TupleType>::value << endl;//输出tuple的元素个数
  tuple_element<1, TupleType>::type f1 = 1.0;//拿出tuple的第一个值的类型来定义参数
  ```

- 在cpp11之前，实现tuple这种数据类型都是逐个逐个去定义的
