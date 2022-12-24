# Why do we need to join

因为数据在关系型数据库中的存储，是按照数据模型间的连接关系分开的

所以，如果想要获取一连串相关联的数据，就需要用join连表查询

本节主要研究的是**内连接**，用**相等**谓词连接的算法

<br/>

<br/>

<br/>

# Join operators

首先就要研究**算子的输出**，向上级输出的数据是什么类型的

接着就要研究**不同算法的花费**，并根据开销决定用选取算法

<br/>

<br/>

## Operator output

### Data

early materialization（提前物化）

向上输出的是两个表连接后得到的数据，即把整条数据记录都往上传

优点：算子得到的结果不需要回表查询

缺点：传输整条数据的开销过大

<br/>

<br/>

### Record ids

late materialization（延迟物化）

向上输出的是数据记录的id号

优点：数据在算子间的传输开销较小

缺点：如果想要获取完整的数据记录，就需要回表查询

<br/>

<br/>

## Cost analysis criteria

对算法的开销进行分析

以**磁盘的IO次数**衡量算法的开销

<br/>

笛卡尔积

笛卡尔积是解决join最朴素的方法，但它是非常低效的

因此，为了降低连表查询时开销，提出了以下算法：
- nested loop join（simple，stupid，block，index）
- sort-merge join
- hash join

<br/>

<br/>

<br/>


# Nested loop join

<br/>

## Simple nested loop join

嵌套循环，分为外层循环和内层循环（可以理解为`O(n^2)`的循环）

外层循环时遍历R表的每一行，针对R表的每一行

再在内层循环中遍历S表中的每一行，进行匹配

PS：这里假设R表的数据能够全部都放入到磁盘中（因此会有一些trick说，将小表放到左边）

<img src="image/stupid nested loop join.png" style="zoom:150%;" />

<br/>

缺点：没有充分利用到缓存池的特点

- 比如说对于R表的第一条记录进行join的时候，会轮流将S表的数据都读到buffer中
- 而在用完S表的数据后又会将它放回磁盘，并在对R表的第二条记录进行join的时候重新读入
- 此时就会发现buffer失效了，这种做法并没有利用缓冲池能提高内存页的利用率的优点

<br/>

<br/>

**算法开销**

要读取整个R表，所以是`M`（总共有M个数据页）

对于R表中的每一条记录，都需要一一和S表中的数据匹配，所以是`m * N`（R表中有m条记录，每条记录都需要读取S表的N个数据页）

<img src="image/stupid nested loop join_01.png" style="zoom:150%;" />

<br/>

<br/>

## Block nested loop join

一个优化思路，此前都是按照一条条数据记录进行join，可以改进为按照数据页进行遍历

<br/>

先读取R数据表的数据页A

然后再依次的遍历S中的数据页，从而将数据页A中的数据一一对上

接着再读取R表的下一个数据页B，一次类推

PS：此时内存最少能够存放三个数据页即可（R、S表的数据页，以及匹配结果的数据页）

<img src="image/block nested loop join_01.png" style="zoom:150%;" />

<br/>

<br/>

**算法开销**

要读取整个R表，所以是`M`（R表中有M个页）

而此时是以数据页进行匹配的，即每个数据页都匹配一遍S表，所以是`M * N`（R表中有M个页，S表有N个页）

<img src="image/block nested loop join_02.png" style="zoom:150%;" />

<br/>

<br/>

**基于缓冲池的优化**

假设内存缓冲池中有B个缓存页

选取其中一个页作为输出缓存，一个页作为内表（S表）的缓存

剩下的B-2个页作为外表（R表）的缓存

<img src="image/block nested loop join_03.png" style="zoom:150%;" />

<br/>

<br/>

**算法开销**

`M + (M / (B - 2) * N)`

- M表示要将R表中所有的数据都读取一遍
- `M/(B - 2)`表示将R表中的数据全数放入大小为`B - 2`内存中，需要多少次
- 因此如果``B - 2 > M`，那就相当于只需要`M + N`

<img src="image/block nested loop join_04.png" style="zoom:150%;" />

<br/>

<br/>

## Index nested loop join

思考：为什么simple/block nested loop join那么慢？换言之，为什么一定要完全遍历S表的所有数据？

主要是因为内表（S表）没有加索引，导致每次数据的查询必须全遍历，由此引申出基于索引的查询

<br/>

算法的开销：`M + (m * C)`（C是指每次查询所有需要的页数）

<img src="image/index nested loop join.png" style="zoom:150%;" />

<br/>

<br/>

## Summary

如果选取nested loop join作为join的算法，那么：

- 尽量把小一点的表作为外表

- 尽量缓存多一点外表的数据，这样可以减少内表的遍历次数
  - 因为我们是以外表为核心遍历的，所以内表的数据缓存下来是没有意义的，每次都还是得从头遍历
- 每次查找都会一直遍历循环内表，因此提出利用索引进行查询，提高效率

<br/>

<br/>

<br/>

# Sort-merge join

将需要进行join的数据列，先进行sort，然后再merge

<img src="image/sort merge join的伪代码.png" style="zoom: 150%;" />

<br/>

merge时的一些细节：

- 对于双指针中二者值相等的时候，一般的做法是输出值后同时下移指针
- 但这里内表（S表）中可能会出现多个数据相同的情况，如果同时下移指针可能会略过一些数据
- 所以不能同时移动两边的指针，而只能移动内表的指针（即移动S表的指针）

<br/>

<br/>

**算法开销**

<img src="image/sort merage join的cost_01.png" style="zoom:150%;" />

<br/>

<br/>

缺点：如果两边的数据全都一样，或者说重复的数据太多，在最严重的时候会导致退化为simple nested loop join

那什么时候该算法才是最高效的？

- 当数据本身就排好序了，就减少了sort的过程，直接merge（比如说下一级算子给的数据是有序的，或者是从index读取的数据）
- 或者说需要的数据本身要求是有序的，那么sort就必不可少

<br/>

<br/>

<br/>

# Hash join

思考：发现B+树的查询有点随机性（和树的结点数和层数有关），并且我们的需求其实是点查询，不需要B+树范围扫描的特性

因此引入了hash查询

<br/>

## Basic hash join algoritham

Phase I：build，扫描外表数据，构建hash表

Phase II：probe，扫描内表的数据，放入hash表中查询

<br/>

<br/>

hash表中的key是语句用于join的那一列数据

而value有以下几种表示方法：
- 提前物化（full tuple，将整个元组作为数据存储）
- 推迟物化（tuple identifier，即是数据的行id之类的，后续回表取数据）
- <img src="image/hash table values.png" style="zoom:150%;" />

<br/>

<br/>

**bloom filter加速**

背景：发现如果使用hash匹配数据，没匹配上很浪费时间精力，因此想要用bloom filter进行优化

<br/>

即用外表做一个hash，同时维护一个bloom filter，然后内表查数据的时候，就先查bloom filter，如果没有就不继续查了

<br/>

为什么bloom filter可以提高性能，因为内表查询数据首先会去filter中查找，如果没找到，就会跳过当前数据

而如果没有bloom filter的话，就会加载hash表的page，然后去寻找（这种磁盘的IO无疑是浪费资源的）

所以bloom filter就可以提早知道数据不存在，就不会去读取内存，从而提高效率

PS：bloom filter会出现假阳性

<br/>

<br/>

**算法开销**

<img src="image/hash join cost_01.png" style="zoom:150%;" />

<br/>

<br/>

## Grace hash join

背景：上述算法的主要问题是：内存不够，会导致hash难以构建，那该怎么办？因此需要把一些hash表的数据放到硬盘中

- 所以有了grace hash join

<br/>

解决在basic hash join的过程中，hash表无法全部放到内存的问题

Phase I：用同一个hash函数，把R表和S表分别做一个hash表1和hash表2

phase II：把R表的hash表1和S表的hash表2，各取一个分区的数据，进行nested loop join
- 这里的原理就是，都是用的同一种hash算法，能够join的元素必然是在同一个分区当中的

<br/>

<br/>

### Recursive partitioning

背景：如果一个分区的元素都非常多，都放不到内存中，该怎么办

解决办法：对这个非常大的分区，对两边的数据表，再用一个新的hash函数进行hash，直到能够分到足够小的块

<img src="image/recursive partitioning.png" style="zoom: 150%;" />

<br/>

<br/>

**算法的开销**

partitioning phase：`2（M + N）`

- 无论是内表还是外表，一次是要把数据从硬盘读到内存中，另一次是要把数据写入到hash表中
- 这里假设hash表的页数也是和原来的数据表同页

<br/>

probing phase：`M + N`

- 两边分别把hash表的数据都读入到内存，所以就是M + N
- 读到内存的数据再进行nested loop join

<br/>

因此总共的开销是`3 * (M + N)`

<img src="image/grace hash join cost.png" style="zoom:150%;" />

如果提前知道外表的大小，就可以用静态的hash表对数据操作，而不是使用动态扩容的hash表

<br/>

<br/>

<br/>

# Conclusion

<img src="image/join algorithms summary.png" style="zoom: 150%;" />

如果是两个大表做join的话，最好就是做hash join

但，如果需要数据是倾斜的，即发生hash冲突的概率较大（会导致算法退化），那么最好还是选择sort-merge

或者，输出结果需要被排序的时候，会选择sort-merge

一般，比较好的DBMS会选择hash join和sort-merge join