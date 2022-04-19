# 创建计算字段

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