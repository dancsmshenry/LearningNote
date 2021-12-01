# 第1章 了解SQL

1.1.2 表

- 表：某种特定类型数据的结构化清单
- 模式：关于数据库和表的布局及特性的信息



1.1.3 列和数据类型

- 列：表中的一个字段，所有表都是由一个或多个列组成的
- 数据类型：所容许的数据的类型，每个表列都有相应的数据类型，它限制（或容许）该列中存储的数据



1.1.4 行

- 行：表中的一个记录
  - 表中的数据是按行存储的，所保存的每个记录存储在自己的行内，如果把表想象为网络，网络中垂直的列为表列，水平行为表行



1.1.5 主键

- 主键：一列（或一组列），其值能够唯一区分表中每个行
  - 表中每一行都应该有可以唯一标识自己的一列（或一组列）
  - 唯一标识表中每行的这个列（或这组列）称为主键



1.2 什么是SQL

- SQL是结构化查询语言的缩写
  - 不是某个特定数据库供应商专有的语言
  - 简单易学
  - 灵活使用其语言元素，可以进行非常复杂和高级的数据库操作



# 第2章 MySQL简介





# 第3章 使用MySQL



# 第4章 检索数据

4.1 SELECT语句



4.2 检索单个列

- ```sql
  SELECT prod_name FROM PRDUCTS;/*从products表中检索一个名为prod_name的列*/
  ```

- 多条sql语句必须以分号（;）分隔

- SQL语句不区分大小写（建议多用大写）



4.3 检索多个列

- 在选择多个列时，一定要在列名之间加上逗号，但最后一个列名后不加，如果在最后一个列名后加乐都好，将会出现错误

- ```sql
  SELECT prod_id, prod_name, prod_price FROM products;
  /*使用SELECT语句从表products中选择数据，本句指定了3个列名，列名之间用逗号分隔*/
  ```



4.4 检索所有列

- ```sql
  SELECT * FROM products;
  /*如果给定一个通配符（*），则返回表中所有列。列的顺序一半是列在表定义中出现的顺序*/
  ```



4.5 检索不同的行

- ```sql
  SELECT DISTINCT vend_id FROM products;
  /*告诉MySQL只返回不同（唯一）的vend_id行*/
  ```

- 不能部分使用DISTINCT

  - DISTINCT关键字应用于所有列而不仅是前置它的列
  - 如果给出`SELECT DISTINCT vend_id, prod_price`，除非指定的两个列都不同，否则所有行都将被检索出来



4.6 限制结果

- ```sql
  SELECT prod_name FROM products LIMIT 5;
  /*使用SELECT语句检索单个列，LIMIT 5指示MySQL返回不多于5行*/
  
  SELECT prod_name FROM products LIMIT 5, 5;
  /*LIMIT5，5表明MySQL返回从行5开始的5行（第一个数为开始位置，第二个数为要检索的行数）*/
  ```

- ps：检索出来的第一行为行0而不是行1，因此，LIMIT1，1将检索出第二行而不是第一行

- 在行数不够的时候：LIMIT中指定要检索的行数为检索的最大行数。如果没有足够的行，MySQL将只返回它能返回的那么多行



4.7 使用完全限定的表名

- ```sql
  SELECT products.prod_name FROM crashcourse.products;
  /*从特定的数据库的表中取出特定表的列*/
  ```



4.8 小结



# 第5章 排序检索数据

5.1 排序数据

- 子句：

  - SQL语句由子句构成，有些子句是必需的，而有的是可选的
  - 一个子句通常由一个关键字和所提供的数据组成
  - 例如FROM子句

- ```sql
  SELECT prod_name FROM products ORDER BY prod_name;
  /*这条语句除了指示MySQL对prod_name列以字母顺序排序数据的ORDER BY子句外，与前面的语句相同*/
  /*以prod_name的字母顺序进行排序*/
  ```

- 通常，ORDER BY子句中使用的列将是为显示所选择的列，但是也可以用非检索的列排序数据



5.2 按多个列排序

- 