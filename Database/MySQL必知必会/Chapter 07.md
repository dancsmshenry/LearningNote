# 数据过滤

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