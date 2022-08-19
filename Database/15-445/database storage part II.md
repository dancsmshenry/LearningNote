### 数据表示

- 使用原生cpp的数据类型，通常比任意精度数字块，但是会存在舍入误差的情况
- ![](F:\Code\LearningNote\Database\15-445\image\variable precision numbers.png)
- 小数之类的通常存储在一个精确的、可变长度的二进制表示中，并带有额外的元数据
- 类似于VARCHAR，但是不存储string
- Demo：Postgres, SQL Server, Oracle



- 大多数dbms不允许元组超过单个页面的大小，要存储大于一个页面的值，DBMS使用单独的溢出存储页面
- 有些系统允许在外部文件中存储非常大的值，作为BLOB类型处理
  - Oracle: BFILE数据类型
  - 微软:FILESTREAM数据类型





### 系统目录

- DBMS将关于数据库的元数据存储在其内部目录中。

  →表、列、索引、视图

  →用户,权限

  →内部统计数据

  几乎每个数据库管理系统本身都会存储它们的数据库目录。

  将对象抽象封装在元组上。

  →用于“引导”目录表的专用代码





### 存储模型

关系模型没有指定必须将元组的所有属性一起存储在单个页面中

DBMS可以以不同的方式存储元组，这些方式更适合OLTP或OLAP工作负载

OLTP（行存储）

- On-line Transaction Processing

- 在线事务处理
  - 读取/更新与数据库中单个实体相关的少量数据的简单查询



OLAP（列存储）

- On-line Analytical Processing
- 联机分析处理
  - 跨多个实体读取大量数据库的复杂查询



![](F:\Code\LearningNote\Database\15-445\image\workload characterization.png)





- DBMS将一个元组的所有属性连续地存储在一个页面中（适合OLTP）
- 在这种情况下，查询往往只对单个实体进行操作
- DBMS将一个元组的所有属性连续地存储在一个页面中
- ![](F:\Code\LearningNote\Database\15-445\image\NSM.png)
- 优点
  - 快速插入，更新和删除
  - 适合需要整个元组的查询
- 缺点
  - 不适合扫描表的大部分属性的子集



- DBMS存储一个页面中连续的所有元组的单个属性的值（适合OLAP）
- ![](F:\Code\LearningNote\Database\15-445\image\DSM.png)
- 列式存储的两种方式：
  - 一种是固定长度的偏移，每个值对于一个属性来说都是相同的长度
  - 另一种是对于还有每个属性的列，都加上该元组的id
- ![](F:\Code\LearningNote\Database\15-445\image\tuple identification.png)
- 优点
  - 减少浪费的I/O量，因为DBMS只读取它需要的数据
  - 更好的查询处理和数据压缩
- 缺点
  - 由于元组拆分/拼接，点查询、插入、更新和删除速度较慢