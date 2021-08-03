vector<T>和vector<T*>的区别

对二叉树还不是很了解，类以及指针访问和对象访问（.和->）不是很了解

string用数组的方式为什么不行？

对于string最好用+或者push_back()来进行字符串的增删改查

不要用s[i]之类的，报错严重

```c++
while ((a -- ) > 0)//可以理解为先比较（a > 0）是否成立，如果成立的话就先a--，在进行下面的操作
    //所以a--的本质是先对a进行比较或是运算，接着再--
```

int 的数据范围-2147483648， 2147483647

```c++
if ((t | A[j]) == A[j]) break;
if (t | A[j] == A[j]) break;//这里必须要加上括号
```

a.size()和n = a.size()是不一样的，会增加时间

`unordered_set`基于哈希表，数据插入和查找的时间复杂度很低，几乎是常数时间，而代价是消耗比较多的内存，**无自动排序功能**。底层实现上，使用一个下标范围比较大的数组来存储元素，形成很多的桶，利用`hash`函数对`key`进行映射到不同区域进行保存。

define是一个函数，const比define快(以及二者的区别)

大小写转换，大写 + 32 = 小写（ascall码）

字符串中，要用单引号来表示字母，不能用双引号？？？？？（字符串的单引号和双引号）

##### C++库函数

```c++
stoi(要转的字符串， 起始位置， 多少进制)//将字符串转换为n进制
to_string (要转变的数字) //将数字转化为字符串
substr函数(截取字符串中的某一段)
pow(x, y)x的y次方
fabs()绝对值
memcpy(f1, f2, n)//把f2中的n个字符复制到f1中
```

##### 二维数组初始化长度

```c++
vector<vector<int>> P(m + 1, vector<int>(n + 1, 0));
```

##### 数组初始化

```c++
memset(数组名，数组值，要初始化的数组的大小)
```

事实上，C 标准只是规定 int 型不能低于 16 位，long 型不能低于 32 位。所以有的平台的编译器可能将 int 和 long 实现为同样的长度。比如在 64 位平台下的 Windows 用的 LLP64 数据模型中 int 和 long 都是 32 位的。

## Vector

```c++
向量
vector<int> a(10)//初始化10个元素为0
vector<int> a(10, 1)//初始化10个元素，都为1
vector<int> b(a)//把向量a复制到向量b
vectot<int> b(a.begin(), a.begin + 3)//把向量a复制到向量b(但只复制前三个)
vector<int> b(c, c + 7)//把数组c的前七个复制到b中

a.back();//返回a的最后一个元素
a.front();//返回a的第一个元素
a.size();//返回a的大小
a.empty();//判断a是否为空
a.push_back();//把元素放到向量的最后一个位置
a.pop_back();//把最后一个元素删除
a.swap(b);//a和b中的元素交换
a.begin();//是指指针，用于指向向量开始的地方，所以要回到原值需要*
a.end();//同理，是指向向量最后的位置
a[i];//返回a的第i元素,当且仅当a存在
```



```c++
vector<int> a(10)//初始化10个元素为0
vector<int> a(10, 1)//初始化10个元素，都为1
vector<int> b(a)//把向量a复制到向量b
vectot<int> b(a.begin(), a.begin + 3)//把向量a复制到向量b(但只复制前三个)
vector<int> b(c, c + 7)//把数组c的前七个复制到b中

a.back();//返回a的最后一个元素
a.front();//返回a的第一个元素
a.size();//返回a的大小
a.empty();//判断a是否为空
a.push_back();//把元素放到向量的最后一个位置
a.pop_back();//把最后一个元素删除
a.swap(b);//a和b中的元素交换
a.begin();//是指指针，用于指向向量开始的地方，所以要回到原值需要*
a.end();//同理，是指向向量最后的位置
a[i];//返回a的第i元素,当且仅当a存在
```





## Pair

```c++
对
pair<int, int> p1;//初始化对
pair<int, int> p1（2147483646， 2147483645）;//初始化对并赋值
pair<int, int> p2(p1)//用p1初始化p2
//pair类型之间可以互比大小，按照字典序比较
p1.first//返回第一个值
p1.second//返回第二个值
```



## String

```c++
字符串
string a = “asehf”;//初始化
string b(a);//以a来初始化b
a.size();//返回a的长度
a.length();//同上
string b = a.substr(初始位置（包括）, 末位置（不包括）);//截取a的字符串的部分
a.empty();//判断是否为空
a.clear();//清空字符串
a.c_str();//返回字符串所在字符数组的起始地址
```



## Queue

```c++
队列
queue<int> q1;//初始化
q1.push();//将元素接到队列末
q1.pop();//将第一个元素弹出队列，但是不会返回元素值
q1.front();//队列第一个元素
q1.back();//队列最后一个元素
q1.size();//队列大小
q1.empty();//判断是否为空
```



## Priority queue

```c++
优先队列
//就大的优先出列，小的最后出列，所以元素放入后会自动排序，把大的先放在上面
size()
empty()
push()  插入一个元素
top()  返回堆顶元素
pop()  弹出堆顶元素
```



## Stack

```c++
栈
size();
empty();
push();  向栈顶插入一个元素
top();  返回栈顶元素
pop();  弹出栈顶元素
```



## Deque

```c++
双向队列
size()
empty()
clear()
front()/back()
push_back()/pop_back()
push_front()/pop_front()
begin()/end()
```



## Set

```c++
集合
begin()     　　 ,返回set容器的第一个元素

end() 　　　　 ,返回set容器的最后一个元素

clear()   　　     ,删除set容器中的所有的元素

empty() 　　　,判断set容器是否为空

max_size() 　 ,返回set容器可能包含的元素最大个数

size() 　　　　 ,返回当前set容器中的元素个数

rbegin　　　　 ,返回的值和end()相同

rend()　　　　 ,返回的值和rbegin()相同
    
count();//查找set中某个某个键值出现的次数。这个函数在set并不是很实用，因为一个键值在set只可能出现0或1次，这样就变成了判断某一键值是否在set出现过了。
```

