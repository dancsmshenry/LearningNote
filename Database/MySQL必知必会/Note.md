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

- ```sql
  SELECT prod_id, prod_price, prod_name FROM products
  ORDER BY prod_price, prod_name;
  /*先按照prod_price排序，如果prod_price都相同，就按照prod_name在排序
  仅在多个行具有相同的prod_price值时才对产品按prod_name排序*/
  ```



5.3 指定排序方向

- ```sql
  SELECT prod_id, prod_price, prod_name FROM products
  ORDER BY prod_price DESC;
  /*加上DESC为降序排序*/
  ```

- ```sql
  SELECT prod_id, prod_price, prod_name FROM products
  ORDER BY prod_price EDSE, prod_name;
  /*DESC关键字只应用到直接位于其前面的列名，所以prod_name列仍然按照标准的升序排序*/
  ```

- 在多个列上降序排序：如果想在多个列上进行降序排序，必须对每个列指定DESC关键字

- ASC指定排序为升序排序

- ORDER BY子句的位置

  - 在给出ORDER BY子句时，应该保证它位于FROM子句之后，如果使用LIMIT，它必须位于ORDER BY之后



# 第6章 过滤数据

6.1 使用where子句

- ```sql
  SELECT prod_name, prod_price FROM products WHERE prod_price = 2.50;
  /*从products表中检索两个列，但不反悔所有行，只返回prod_price值为2.50的行*/
  ```

- WHERE子句的位置：在同时使用ORDER BY和WHERE子句时，应该让ORDER BY位于WHERE之后



6.2 WHERE子句操作符

- ```sql
  /*检查单个值*/
  SELECT prod_name, prod_price FROM products WHERE prod_name = 'fuses';
  /*
  返回prod_name值为fuses的一行
  注：MySQL在执行匹配时默认不区分大小写
  */
  
  SELECT prod_name, prod_price FROM products WHERE prod_price < 10;
  
  SELECT prod_name, prod_price FROM products WHERE prod_price <= 10;
  ```

- ```sql
  /*不匹配检查*/
  SELECT vend_id, prod_name FROM products WHERE vend_id <> 1003;
  ```

- ```sql
  /*范围值检查，为了检查某个范围的值，可以使用BETWEEN操作符*/
  SELECT prod_name, prod_price FROM products WHERE prod_price BETWEEN 5 AND 10;
  /*在使用BETWEEN时，必须指定两个值（所需范围的低端值和高端值）这两个值必须用AND关键字分隔，匹配范围包括开始值和结束值*/
  ```

- ```sql
  /*空值检查，NULL 无值，它与字段包含0、空字段或仅仅包含空格不同*/
  SELECT prod_name FROM products WHERE prod_prices IS NULL;
  ```



# 第7章 数据过滤

7.1 组合WHERE子句

- 操作符：用来联接或改变WHERE子句中的子句的关键字，也称为逻辑操作符

- ```sql
  /*AND操作符，用在WHERE子句中的关键字，用来指示检索满足所有给定条件的行*/
  SELECT prod_id, prod_price, prod_name FROM products WHERE vend_id = 1003 AND prod_price <= 10;
  ```

- ```sql
  /*OR操作符，匹配任一条件而不是同时匹配两个条件，用来标识检索匹配任一给定条件的行*/
  SELECT prod_name, prod_price FROM products WHERE vend_id = 1002 OR vend_id = 1003;
  ```

- ```sql
  /*计算次序*/
  SELECT prod_name, prod_price FROM products WHERE vend_id = 1002 
  OR vend_id = 1003 AND prod_price >= 10;
  /*AND在计算次序中优先级更高，操作符被错误地组合了，这里是先匹配AND组合的条件，在OR的
  用圆括号可以解决问题*/
  ```

- 在WHERE子句中使用圆括号，任何时候使用具有AND和OR操作符的WHERE子句，都应该使用圆括号明确地分组操作



7.2 IN操作符

- ```sql
  /*IN操作符用来指定条件范围，范围中的每个条件都可以进行匹配*/
  SELECT prod_name, prod_price FROM products WHERE vend_id IN (1002, 1003) ORDER BY prod_name;
  /*检索供应商1002和1003制造的所有产品*/
  ```

- IN WHERE子句中用来指定要匹配值的清单的关键字，功能与OR相当



7.3 NOT操作符

- ```sql
  /*NOT WHERE子句中用来否定后跟条件的关键字*/
  SELECT prod_name, prod_price FROM products WHERE vend_id NOT IN (1002, 1003)
  ORDER BY prod_name;
  ```

- MySQL支持使用NOT对IN、BETWEEN和EXISTS子句取反



# 第8章 使用通配符进行过滤

8.1 LIKE操作符

- 通配符：用来匹配值的一部分的特殊字符

- 搜索模式：由字面值、通配符或两者组合构成的搜索条件

- ```sql
  /*百分号（%）通配符*/
  SELECT prod_id, prod_name FROM products WHERE prod_name LIKE 'jet%';
  /*该语句将检索任意以jet起头的词，%告诉MySQL接受jet之后的任意字符，不管他有多少的字符
  ps：这里''里面的内容是区分大小写的*/
  SELECT prod_id, prod_name FROM products WHERE prod_name LIKE '%anvil%';
  /*匹配任何位置包含文本anvil的值*/
  SELECT prod_name FROM products WHERE prod_name LIKE 's%e';
  /*s起头e结尾的字符*/
  /*即使是WHERE prod_name LIKE '%'也不能匹配用值NULL作为产品名的行*/
  ```

- ```sql
  /*下划线_通配符，下划线只匹配单个字符而不是多个字符*/
  SELECT prod_id, prod_name FROM products WHERE prod_name LIKE '_ ton anvil'
  /*与%能匹配0个字符不一样，_总是匹配一个字符*/
  ```



8.2 使用通配符的技巧

- 不要过度使用通配符
- 除非有必要，否则不要把它们用在搜索模式的开始处
- 仔细注意通配符的位置



# 第九章 用正则表达式搜索

9.1 正则表达式介绍

- 定义：用来匹配文本的特殊的串（字符集合）



9.2 使用MySQL正则表达式

- ```sql
  /*基本字符匹配*/
  SELECT prod_name FROM products WHERE prod_name REGEXP '1000'
  ORDER BY prod_name;
  ```

感觉用不上，所以先不看



# 第10章 创建计算字段

10.1 计算字段

- 字段：基本上与列的意思相同，经常互换使用



10.2 拼接字段

- 拼接：将值连结到一起构成单个值

- ```sql
  /*Concat拼接串，即把多个串连接起来形成一个较长的串*/
  SELECT Concat(vend_name, '(', vend_country, ')')
  FROM vendors
  ORDER BY vend_name;
  
  /*RTrim函数去掉右边的所有空格*/
  SELECT Concat(RTrim(vend_name), '(', vend_country, ')')
  FROM vendors
  ORDER BY vend_name;
  ```

- ```sql
  /*使用别名，别名用AS关键字赋予，是一个字段或值得替换名，又叫做导出列*/
  SELECT Concat(vend_name, '(', vend_country, ')') AS vend_title
  FROM vendors
  ORDER BY vend_name;
  ```

- 



10.3 执行算术计算

- ```sql
  SELECT prod_id, quantity, item_price, quantity * item_price AS expanded_price
  FROM orderitems WHERE order_num = 20005;
  /*输出显示的expanded_price列为一个计算字段，此计算为 quantity * item_price*/
  ```

- 基本运算符 +   -   /   *



# 第11章 使用数据处理函数

11.2 使用函数

- ```sql
  /*文本处理函数*/
  SELECT vend_name, Upper(vend_name) AS vend_name_upcase FROM vendors
  ORDER BY vend_name;
  /*Upper将文本转换为大写*/
  /*
  	Left() 返回串左边的字符
  	Length() 串的长度
  	Locate() 找出串的一个子串
  	Lower() 将串转换为小写
  */
  ```

- ```sql
  /*日期和时间处理函数*/
  SELECT cust_id, order_num FROM orders WHERE Date(order_data) = '2005-09-01'
  SELECT cust_id, order_num FROM orders WHERE Date(order_data) BETWEEN '2005-09-01' AND '2005-09-30'
  SELECT cust_id, order_num FROM orders WHERE Date(order_data) WHERE Year(order_date) = 2005
  AND Month(order_date) = 9;
  ```

- ```sql
  /*数值处理函数*/
  /*
  	abd,cos,exp,mod,rand,sin,sqrt,tan
  */
  ```



# 第12章 汇总数据

基本就是一些avg()，count()，max()，min()，sum()，等函数api的使用



# 第13章 分组数据

13.2 创建分组

- ```sql
  SELECT vend_id, COUNT(*) AS num_prods FROM products GROUP BY vend_id;
  /*GROUP BY指示MySQL分组数据，对每个*/
  ```

- 