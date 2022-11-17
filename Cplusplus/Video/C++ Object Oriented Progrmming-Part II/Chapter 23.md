# 重载new()，delete()示例

- 重载class member operator new()时
  - 第一参数必须是size_t，其余的参数以new所指定的placement arguments为初值
  - 前提是每一个版本声明都必须有独特的参数列
- 重载class member operator delete()时
  - 可以重载多个版本，但是都不会被delete给调用
  - 只有当new所调用的ctor抛出exception时，才会调用这些版本的operator delete()，它只可能这样被调用，主要用来归还未能完全创建成功的object所占用的memory