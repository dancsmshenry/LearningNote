# 检索数据

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