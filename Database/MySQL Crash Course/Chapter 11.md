# 使用数据处理函数

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
