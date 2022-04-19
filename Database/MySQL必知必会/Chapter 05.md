# 排序检索数据

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