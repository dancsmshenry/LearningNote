# 使用通配符进行过滤

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