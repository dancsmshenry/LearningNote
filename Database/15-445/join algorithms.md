# background

- 为什么需要join连表算法：因为关系型数据库本身就是按照数据模型的连接关系给分开的
- 所以如果想要取用数据的话，就应该join连表去取数据
- 研究的是**内连接**，用**相等**谓词连接的算法
- 最好把小一点的表放到左侧



# join operators

- 首先就要研究算子的输出是什么，向上级输出的data是什么
- 其次，要研究一下不同的算法的cost，根据cost决定用什么去实现



## operator output

### data

- early materialization：提前物化
- 向上输出两个表连接后得到的数据
- 即把全部的数据记录都往上传
- 好处：最后算子得到的就是result，不需要回表



### record ids

- late materialization：延迟物化
- 向上输出的数据，不是记录本身，而是记录id
- 上级要获得数据就需要用记录id进行回表



# cost analysis criteria

- 算法开销的分析
- 以磁盘IO的数量对算法的开销进行估计



笛卡尔积

- 笛卡尔积是解决join最基础的办法，但它是非常的低效的
- 为了降低连表开销，想到了以下算法
  - nested loop join（鸟巢，嵌套循环）（simple，stupid，block，index）
  - sort-merge join
  - hash join





# nested loop join



## stupid nested loop join

- 嵌套循环
- 外层循环是遍历R表的每一行，对于R表的每一行，再开一个内层循环，用来遍历S表的每一行
- 相当于O(N^2)的算法循环



- PS：对于磁盘来说的小表，应该是对于磁盘页来说的，即数据总共占用的空间的大小，而不能仅仅依靠记录的行数去决定
- 所以前面说的要把小表放到前面就是指这样的表
- 因为这样遍历R表的磁盘IO次数就少
- PS：这种说把小表放到左边的办法，我是有点存疑的，因为实际上IO的数量取决于表的记录和表的页数的，即是由两个变量决定的...
- 虽然ppt中的第17页证明了说小表放到左边好像可以减少IO，但是这建立的一个基础却是表的页数越大，记录越多
- 可是依然存在页数越大，但是记录会变小（因为单条数据会很大）



缺点

- 没有充分利用到缓存池的特点
- 比如说对于第一行记录在另一个表中进行遍历，那么就会把另一个表中的数据都读入到buffer中
- 但是当读到第二行记录的时候，上面的缓存就一点用都没有了..，即又得从头开始遍历



cost

- ![](image/stupid nested loop join_01.png)



## block nested loop join

- 一种优化的思路：按照数据页进行遍历
- 先读入R数据的数据页A，然后再依次的读取S数据的数据页B，依次的寻找是否有数据页A的数据
- 这样的cost就是 M + M * N，即数据页的读取次数相对上面就减少了（注意这里的cost是根据IO的次数来决定的）

- ![](image/block nested loop join_01.png)
- ![](image/block nested loop join_02.png)



继续优化一下

- 给一个页作为输出缓存，给一个页作为内表缓存（及上图的S表），其他的页全部给R表的数据缓存
- 假设内存池中有B个缓存页
- 这里是将一个页作为输出缓存，一个页作为内表缓存，剩下的B-2个页作为外表数据的缓存
- 所以这里的cost就是M + （M / (B-2)  * N），这里是M / (B-2)是因为要分这么多次把M张页放入到内存中
- 其实，这里很难理解的一个原因就是，我们要减少的应该是**磁盘的IO次数**，但总是和数据的比较次数搞混淆
- 所以就相当于利用了缓存，提高性能
- PS：如果B > M + 2，那就相当于只需要M + N次，非常的高效
- ![](image/block nested loop join_03.png)
- ![](image/block nested loop join_04.png)



- 为什么basic nested loop join那么慢，即为什么一定要遍历一遍S表的所有数据
- 因为没有加索引，内表没有索引，导致必须每次都要遍历一遍内表...



## index nested loop join

- 走索引查询内表的数据
- 所以cost：M + (m * C)，其中C是指每次查询所有需要的页数（不好估计，因为树的层数和结点不清楚）



## summary

- 尽量让小表放左边，因为这样就可以让左边的大表遍历的次数减少
- 尽量缓存多一点外表的数据，这样可以减少内表的遍历次数
  - 如果是缓存内表的话，你的缓存池再大，还是面临着缓存池冲刷的问题，即每次都会重新刷新的数据，导致缓存失效
- 会一直遍历循环内表（当然如果有索引的话就用索引就ok了）
- 几种nested的做法：simple / stupid，block，index





# sort merage sort

- 先按照要join的列对数据进行sort，然后再进行merge
- <img src="image/sort merge join的伪代码.png" style="zoom:200%;" />
- 其实这里有一个细节，就是双指针吧，一般遇到二者相同的，就会输出结果然后把两边的指针都往下移
- 但是可能会出现R表，即左边的表当前行的下一行还有列的值和他相等，即会因此略过一些数据
- 所以不能同时移动两边的指针，而只能移动右表的指针



- <img src="image/sort merage join的cost_01.png" style="zoom:150%;" />
- <img src="image/sort merage join的cost_02.png" style="zoom:150%;" />
- 这种方法的缺点就是，如果两边的数据全都一样，或者说重复的数据太多，在最严重的时候会导致退化为stupid nested loop join



- 什么时候最好用（when is sort-merge join useful?）
  - 当数据本身就排好序了，就减少了sort的过程，直接merge，就很快（可能是下一级算子给的数据是有序的，或者是从index读取的数据）
  - 还有一种情况是给定的需求是要有序的数据，那么sort部分就是必不可少的



思考

- 发现B+树的查询有点随机性（和树的结点数和层数有关），并且我们需要的其实是点查询，即不需要B+树扫描的特性，即需要的是够快
- 因此引入了hash查询



# hash join



## basic hash join algoritham

- 阶段一：build
  - 扫描外表从而构建hash表
- 阶段二：probe
  - 然后去内表一行行的去查询
- 即拿外表作为hash表，然后拿内表一行一行的去检查
- hash表的kv是什么，k是语句用于join的那一列数据
- 而v是什么，又有几种方法
  - 提前物化（full tuple，将整个元组作为数据存储）和推迟物化（tuple identifier，即是数据的行id之类的，后续回表取数据）
- 可以用bloom filter加速
  - 背景：发现如果使用hash匹配数据，没匹配上很浪费时间精力，因此想要用bloom filter进行优化
  - 即用外表做一个hash的同时，还要做一个bloom filter，然后内表查数据的时候，就先查bloom filter，如果没有就不继续查了
  - 为什么bloom filter可以优化，因为filter只是用一个小的数据就可以看数据是否存在，而hash的匹配，是存在IO的情况的（比如说hash的值是1，那么就要把对应的页读取，可如果没有的话，就匹配失败了，就浪费了一次IO）
  - 不过bloom filter还是会出现假阳性，但没事，最后还是会去查表得
- 这里的问题是，内存不够，会导致hash难以构建，那该怎么办？
  - 需要把一些hash表的数据放到硬盘中






## grace hash join

- 解决hash join的过程中，hash表无法全部放到内存的问题
- phase1：把R表和S表都各做一个hash表‘
- phase2：把R表的hash表1和S表的hash表2，各取一个分区的数据，进行nested loop join
  - 这里的原理就是，都是用的同一种hash算法，能够join的元素必然是在同一个分区当中的



## recursive partitioning

- 问题又来了，如果一个分区的元素都非常多，都放不到内存中，该怎么办
- 解决办法：对这个非常大的分区，对两边的数据表，再用一个新的hash函数进行hash，直到能够分到足够小的块
- <img src="image/recursive partitioning.png" style="zoom:200%;" />



cost

- partitioninh phase：2（M + N） IO
  - 一次是要把数据从硬盘读到内存中，另一次是要把数据写入到hash表中
  - 这里假设hash表的页数也是和原来的数据表同页
- probing phase：M + N IO
  - 两边分别把hash表的数据都读入到内存，所以就是M + N
  - 读到内存的数据再进行nested loop join
- 所以，总共的cost就是3 * （M + N）次的IO



- 如果提前知道外表的大小，就可以用静态的hash表对数据操作，而不是使用动态扩容的hash表



# summary

- <img src="image/join algorithms summary.png" style="zoom:200%;" />
- 如果是两个大表做join的话，最好就是做hash join
- 但，如果需要数据是倾斜的，即发生hash冲突的概率较大（会导致算法退化），那么最好还是选择sort-merge
- 或者，输出结果需要被排序的时候，会选择sort-merge
- 一般，比较好的DBMS会选择hash join和sort-merge join