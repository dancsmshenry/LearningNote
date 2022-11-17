# 过滤数据

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
