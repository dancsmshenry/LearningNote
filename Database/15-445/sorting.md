为什么需要对数据进行排序

- 表中的元组没有按照特定的顺序排列，但是查询往往希望按照特定的顺序检索元组
- 比如说去重操作（DISTINCT），聚合操作（GROUP  BY）



如果数据能够在内存中排序，那么就可以使用标准的排序算法，比如快排等

如果不行，那么就需要一种排序方法，同时兼顾将数据写入磁盘的成本



外部归并排序

- 将数据集分割成单独的运行，然后分别排序
- 阶段一：排序（对装入主存的数据块进行排序，然后将排序后的数据块写回磁盘上的文件中）
- 阶段二：合并（将排序后的子文件合并成一个更大的文件）



两路外部归并排序

- 假设数据集被分解为N个页面，DBMS的缓冲区有B个缓冲页来储存输入和输出数据
- 阶段一：将表中的数据页读入到内存中，将该页的数据进行排序，然后把排序好的结果返回给磁盘
- 阶段二：递归的将数据页成对成对合并（使用三个缓冲页，2个输入页，1个输出页）
- 总共的阶段数：1+log2n
- io总成本：2n * 总次数
- ![](image/2-way external merge sort.png)
- 该算法只需要3个缓冲区页来执行排序
- 但即使我们有更多的缓冲空间，却也没有有效地利用它们



双缓冲技术优化

- 在后台预先取下一次要运行的数据页，并在系统当前处理其他页面的时候把它放到第二个缓冲区
- 不断的利用磁盘读取数据，减少每一步的IO请求的等待时间（有点像muduo中的log系统了）



一般外部归并排序

- 阶段一：使用B个缓冲页，产生[N/B]个大小为B的页面
- 阶段二：使用k路合并对剩余的页面进行合并





使用B+树进行排序

- 如果必须排序的表的属性已经在B+树上有了索引，那么就可以使用它来加速排序
- 通过直接遍历树的叶页，得到排序后的数据来检索元组
- 分类：聚簇索引和非聚簇索引的B+树



聚簇索引

- 遍历最左边的叶页，然后从所有叶页检索元组
- 这总是比外部排序好，因为没有计算成本，而且所有磁盘访问都是顺序的



非聚簇索引

- 相当于随机读数据了



聚合

- 将多个元组聚合为单个标量值
- 有两种方法：排序或哈希
- 排序（将数据过滤后，对数据进行排序，然后聚合去重）
- ![](image/sorting aggregation.png)
- 如果不需要对原数据进行排序，那么上述排序的方法就会很耗费时间
  - 比如说group by分组，不需要特定顺序
  - 比如说distinct中的重复项（不需要顺序）
- 所以在这种情况下，hash是一个更好的选择
  - 只删除重复的数据
  - 比排序更加的高效



hash aggregate

- 对于每个记录，检查hash表中是否有该条目
  - DISTINCT：丢弃重复项
  - 分组依据：执行聚合计算
- 如果所有的数据都放在内存，那么处理就变得十分容易，但如果要溢出磁盘的话，就要特殊处理
- 阶段一：分区（根据hash键将元组划分为桶，当桶填满后将桶里面的数据读入磁盘中）
  - 使用散列函数h1将元组拆分为磁盘上的分区（h1是用于将数据分隔开来的）
  - 所有匹配都位于同一分区中
  - 分区通过输出缓冲区“溢出”到磁盘
  - ![](image/hash_partition.png)
- 阶段二：rehash（为每个分区建立内存哈希表并计算聚合）
  - 对于磁盘上的每个分区，将其读入内存并构建内存哈希表（基于第二个哈希函数h2，h2适用于将数据按照指定条件分割）
  - 然后遍历该hash的bucket以匹配元组
  - ![](image/hash_rehash.png)