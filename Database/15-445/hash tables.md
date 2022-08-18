# 引擎的两种结构

- 哈希表
- 二叉树







# 用途

- 数据库的元数据存储
- 一些数据库的核心数据结构（例如redis）
- 临时表（比如join语句中使用的就是hash表）
- 索引







# design decision of datestruct

- 数据结构的考虑
  - 如何在内存中布局数据结构、存储什么样的信息，才能支持高效的数据访问
- 并发性
  - 如何使多个线程同时访问数据结构而不会出问题







# hash table

- 将键映射到值的无序关联数组
- 使用哈希函数计算给定键到数组中的偏移量，从中可以找到所需的值
- 空间复杂度：O(n)
- 查询的时间复杂度：平均为O（1），最差为O（n）







# static hash table

- 分配一个巨大的数组，每个槽位指向或者存储具体的数据
- 要查找一个数据，按元素的数量对键进行hash运算，查找其在数组中的偏移量
- 这里的大前提就是：
  - 要知道所有元素的数量
  - 要有一个完美的哈希函数（使得如果key1不等于key2，那么hash(key1)!=hash(key2)）







# design decision

- 设计hash需要考虑的因素

- 首先是哈希函数，如何将一个较大的数值域映射到一个较小的域，同时要权衡计算速度和元素的碰撞率（减少哈希冲突）
- 其次是哈希方案，如何处理散列后的键冲突，即如何处理hash冲突
  - 在分配一个较大的哈希表和额外的查找插入键指令中进行权衡
- 对于任何输入键，返回该键的整数表示形式
- 我们不希望对DBMS哈希表使用加密哈希函数
- 我们想要的是速度快且碰撞率低的hash函数







# hash function

- ![](image/hash functions_01.png)
- ![](image\hash functions_02.png)
- ![](image\hash functions_03.png)







# static hash schemes

- hash表的容量是固定的

## linear probe hashing

- 又名线性探测法
- insert:如果hash到的slot是空的，就把数据放入；否则就往下挪一位，然后继续探测是否可以放数据
- find:如果hash到的slot中数据不是要找的数据，就往下挪一位去找
- delete:如果hash到的slot中的数据不是要删除的数据，就往下删除
- 不过有些问题，你比如说如果find后的slot为空的（可能delete把它删掉了..），那是不是就代表数据没有放到hashmap中呢？（所以后续有方法来解决）
- ![](image\linear probe hashing_01.png)
- ![](image\linear probe hashing_02.png)





如果其中一个元素被删除了，那怎么做才不影响后续的查询

- 方法一：墓碑标记法：占着被删除元素的位置，但是不存放数据，如有查询就往后传递（这样的话，find的时候看到墓碑，就会继续往下找，而不是返回fail了）
- ![](image\linear probe hashing delete_01.png)
- ![](image\linear probe hashing delete_02.png)
- 方法二：移动数据（把后面的数据往前移动，即删除数据后，对hash中的数据重新调整一遍）
- ![](image/movement_01.png)
- ![](image/movement_02.png)



## non-unique keys

如果每一个key可以对应多个value的话，该怎么处理

- ![](image\non-unique keys.png)
- 方法一：键值key不变，存储一个指针指向一个value lists，用这个list存储数据
- 方法二：将键值和value组成给一个新的数据，放入到hash map中



## robin hood hashing

- 属于是线性探测的变体
- 每个槽不仅要存value，还要存取一个它距离正确位置的一个偏移量
- 元素的插入过程：
  - 一开始先找到对应的slot，如果slot为空就把元素放进去
  - 否则就往下挪一位放置
  - 但如果下一位里面还有元素，就要比较它们的偏移量（即此时这个位置数据的偏移量和如果当前元素位于这个位置时的偏移量）
  - 如果小于等于后面位置的计数，就继续往后移动
  - 否则就把数据安插在这里，让原来这个位置的数据往后移动

- ![](image\robin hood hashing_01.png)
- ![](image\robin hood hashing_02.png)
- ![](image\robin hood hashing_03.png)



## cuckoo hashing

- 杜鹃鸟的特点：把蛋下到别的窝里面，用得非常少（因为如果出现了循环碰撞的情况，程序就挂了...；讲真，这种做法有点贱了）

- 使用多个hash表和不同的hash函数
- 具体国臣
  - 比如说用两个hash表和两个hash函数
  - 对于一个数据，如果可以放在第一个hash表，就放在第一个hash中；如果第一个hash表放不了，而第二个hash能放，就放到第二个hash表中
  - 如果两个都不能放，就把其中一个拿出来，先放入当前的数据
  - 然后用另一个hash把拿出来的这个数据再hash一遍，放到另一个hash表
  - 一直这样来回hash
- ![](image/cuckoo hashing_01.png)
- ![](image/cuckoo hashing_02.png)
- ![](image/cuckoo hashing_03.png)
- ![](image/cuckoo hashing_04.png)

## 思考

- 主要问题就是设计hash表的时候就要知道未来最多能够存储多少数据（少了不够空间，多了浪费空间）
- 不能动态的扩容伸缩，即需要根据需求对hash进行动态伸缩
- 而现实是很多时候我们都不知道具体的数据量有多少的...







# dynamic hash schemes

## chained Hashing

- 即拉链法

- 为哈希表中的每个槽维护一个桶链表，通过将具有相同散列键的所有元素放入同一个bucket中来解决冲突
- 为了确定一个元素是否存在，哈希到它所在的桶中并扫描它
- 插入和删除是查找的一般化
- 这里的桶bucket可能是一个链表，也可能是一个数组
- 如果一个bucket不够的话，就会继续再接一个bucket
- 类比java的hashmap，它的第一个bucket就只有一个值，当第二个值来的时候，就会让第一个值的bucket指向第二个值得bucket，就是一个纯链表，即单链表（如果数据非常多的话，就会变为红黑树，即把后面的链表压缩为了红黑树）
  - 就1.7包括1.7之前，hashmap都是用数组+链表实现的，并且使用的是头插法
  - 而1.8开始，当链表的长度大于8且数组大小大于等于64的时候，就会将外接的链表变为红黑树；当红黑树节点小于6的时候，又会退化成链表
  - 因为红黑树能够提高查询的时间复杂度

- 而go的map，好像是第一个bucket是8个单位，多的元素就放到溢出的桶里面
- ![](image\chained hashing.png)



## extendible hashing

- 可拓展hash

- 多个槽位的指针指向同一个桶链
- https://blog.csdn.net/qq12323qweeqwe/article/details/124576114
- 我理解的
  - 对于每个数据用hash算法算出一个数，然后转换为二进制，放到对应的桶里面
  - 如果桶里面满了的话，就分裂（比如说现在只比较前两位，分裂以后就会比较前三位）
- 这里的槽（bucket）上面的数字是说，本bucket只看前面的x位数，比如说下图的第一个槽就看第一位数，第一位数是0的就放到这里
- 注意，这里如果global变了的话（即一开始是看前两位，后面要看前三位，换为十进制就是一开始容量扩大到十倍），那么对所有的数据，可就要进行一次rehash了
- ![](image/extendible hashing_01.png)
- ![](image/extendible hashing_02.png)



## linear hashing

- 线性hash

- 哈希表维护一个指针，用于跟踪下一个要分割的桶
- 当任何一个桶溢出时，将桶在指针所在位置进行分割
- 使用多个哈希值为给定的键找到正确的桶
- 可以使用不同的溢出标准
  - 空间利用率
  - 溢出链的平均长度
- 我的一个理解
  - split point一开始是指向0号bucket
  - 然后我们放入数据到bucket中，如果对于任意一个放入数据的过程，我们发现出现了要追加数据页的情况，就要将split pointer指向的页面进行分页，即用一个新的hash函数，将其中的数据分隔开，即用新的hash函数将数据重新分配到当前的slot和新的slot里面
  - 你比如说hash1 = key % 4，那么新的hash2 = key % 8，比如原来的slot里面有5，9，那么原来的slot就是1，新的slot就是5，那么5就会被分到slot5，9就不变
  - 接着指针往后移一位
  - 同时，指针前面的数据都用hash2进行查找，指针后面的bucket用hash1来查找
  - 比如说一开始20是放在0号slot的位置的，但是分页过后，20就放到了4号的位置，那么此时find 20的时候（这个过程肯定是先用hash1的），发现映射到了slot0，而slot0位于split pointer的上方，那么此时明白了，就要用hash2进行查找

- ![](image/linear hashing_01.png)
- ![](image/linear hashing_02.png)



- 在拆分指针的基础上，拆分每个桶，能够到达每个溢出的存储桶
- 这个pointer会一直遍历到所有的原有的slot上面（对应到上图就是0-3之间）
  - 而此时就表明，当前的扩容已经结束了，就要把指针重新移回0的位置


- 删除

  - 找到对应的slot，然后删除元素

  - 如果桶里面没有元素，就把桶给删除了

- 感觉很少人用



# conclusion

- hash是一个快速的数据结构，能够支持O(1)的快速查找
- 不管数据再多，查询时间都是一个常数
- 在很多地方都有用：join语句，索引，元数据处理，redis
- 权衡：速度和灵活性（拓展性），二者不可兼得
- 建议表的索引不要用hash table（缺点，不能范围查找）