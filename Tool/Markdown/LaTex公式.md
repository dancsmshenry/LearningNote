##### 上下标

- $$
  a_2, a_{22}\\\\
  a^2,a^{22}\\\\
  P_{5}^{2},P^3_{6}
  $$

- ```html
  a_2,a_{22}
  a^2,a^{22}
  <!--如果是单个字符就是前者，否则就是后者-->
  P_{5}^{2}
  ```





##### 分数

- $$
  \frac{7x+5}{3x+8}
  \frac{\frac{7x+5}{2x+1}}{x+1}\\\\
  \cfrac{b}{a}
  \cfrac{\cfrac{c}{b}}{a}
  $$

- ```html
  \frac{7x+5}{3x+8}
  \frac{\frac{7x+5}{2x+1}}{x+1}
  <!--适应大小-->
  \cfrac{b}{a}
  \cfrac{\cfrac{c}{b}}{a}
  ```





##### 开根号

- $$
  \sqrt{2},\sqrt[n]{5}
  $$

- ```html
  \sqrt{2},\sqrt[n]{5}
  ```





##### 省略号

- $$
  \cdot,\cdots\\\\
  \vdots\\\\
  \ddots
  $$

- ```html
  \cdot,\cdots\\
  \vdots\\
  \ddots
  ```





##### 极限

- $$
  \lim\\\\
  \infty
  $$

- ```html
  \lim\\
  \infty
  ```





##### 括号

- $$
  (\frac{a}{b}),[\frac{b}{a}],\\\\
  \left(\frac{a}{b}\right),\left[\frac{b}{a}\right],
  $$

- ```html
  (\frac{a}{b}),[\frac{b}{a}],
  \left(\frac{a}{b}\right),\left[\frac{b}{a}\right],
  ```

- $$
  \{\frac{a}{b}\},\langle \frac{d}{e}\rangle,\\\\
  \left\{\frac{a}{b}\right\},\left \langle \frac{d}{e} \right\rangle
  $$

- ```html
  \{\frac{a}{b}\},\langle \frac{d}{e}\rangle,\\
  \left\{\frac{a}{b}\right\},\left \langle \frac{d}{e} \right\rangle
  ```

- $$
  \lceil a \rceil, \lfloor a \rfloor\\\\
  \left\lceil \frac{b}{a} \right\rceil, \left\lfloor \frac{b}{a} \right\rfloor
  $$

- ```html
  \lceil a \rceil, \lfloor a \rfloor\\
  \left\lceil \frac{b}{a} \right\rceil, \left\lfloor \frac{b}{a} \right\rfloor
  ```





##### 累加累乘

- $$
  \sum^{N}_{i = 0}\\\\
  \prod^{N}_{i = 0}
  $$

- ```html
  \sum^{N}_{i = 0}\\
  \prod^{N}_{i = 0}
  ```





##### 微积分

- $$
  \int\\\\
  \iint\\\\
  \iiint\\\\
  \iiiint\\\\
  \oint\\\\
  \nabla
  $$

- ```html
  \int
  \iint
  \iiint
  \iiiint
  \oint
  \nabla
  ```





##### 附加标记

- $$
  \tilde{a}\\\\
  \vec{a}\\\\
  \overline{a+b+c+d}\\\\
  \underline{a+b+c+d}\\\\
  \overbrace{a+b+c+d}\\\\
  \underbrace{a+b+c+d}
  $$

- ```html
  \tilde{a}\\
  \vec{a}\\
  \overline{a+b+c+d}\\
  \underline{a+b+c+d}\\
  \overbrace{a+b+c+d}\\
  \underbrace{a+b+c+d}
  ```





##### 分支公式

- $$
  \left\{
  \begin{aligned}
  a=b\\\\
  b=c
  \end{aligned}
  \right.
  $$

- ```html
  \left\{
  \begin{aligned}
  a=b\\
  b=c
  \end{aligned}
  \right.
  ```





##### 三角函数

- $$
  \sin,\cos,\tan\\\\
  \cot,\sec,\csc\\\\
  \bot,\angle\\\\
  90^\circ,180^\circ
  $$

- ```html
  \sin,\cos,\tan
  \cot,\sec,\csc
  \bot,\angle
  90^\circ,180^\circ
  ```





##### 对数函数

- $$
  \ln17,\ln{a+b}\\\\
  \log_2 10\\\\
  \lg7,\lg{a+b}
  $$

- ```html
  \ln17,\ln{a+b}\\
  \log_2 10\\
  \lg7,\lg{a+b}
  ```





##### 二元运算符

- $$
  +,-,\times,\div\\\\
  \ast,\mid
  $$

- ```html
  +,-,\times,\div\\
  \ast,\mid
  ```





##### 关系运算符

- $$
  \neq, \leq, \geq\\\\
  \equiv,\approx
$$
  
- ```html
  \neq, \leq, \geq\\
  \equiv,\approx
  ```





##### 逻辑运算符

- $$
  \because\\\\
  \therefore\\\\
  \forall\\\\
  \vee\\\\
  \wedge
  $$

- ```html
  \because\\
  \therefore\\
  \forall\\
  \vee\\
  \wedge
  ```

- 





##### 集合

- $$
  \emptyset,\in,\notin\\\\
  \subset,\not\subset,\subseteq\\\\
  \cap,\cup
  $$

- ```html
  \emptyset,\in,\notin\\
  \subset,\not\subset,\subseteq\\
  \cap,\cup
  ```





##### 矩阵

- $$
  \begin{matrix}
  	1 & 2 & 3\\\\
  	4 & 5 & 6\\\\
  	7 & 8 & 9
  \end{matrix}\\\\
  \left(
  \begin{matrix}
  	1 & 2 & 3\\\\
  	4 & 5 & 6\\\\
  	7 & 8 & 9
  \end{matrix}
  \right)\\\\
  \left[
  \begin{matrix}
  	1 & 2 & 3\\\\
  	4 & 5 & 6\\\\
  	7 & 8 & 9
  \end{matrix}
  \right]\\\\
  \left\{
  \begin{matrix}
  	1 & 2 & 3\\\\
  	4 & 5 & 6\\\\
  	7 & 8 & 9
  \end{matrix}
  \right\}\\\\
  $$

- ```html
  \begin{matrix}
  	1 & 2 & 3\\
  	4 & 5 & 6\\
  	7 & 8 & 9
  \end{matrix}\\
  \left(
  \begin{matrix}
  	1 & 2 & 3\\
  	4 & 5 & 6\\
  	7 & 8 & 9
  \end{matrix}
  \right)\\
  \left[
  \begin{matrix}
  	1 & 2 & 3\\
  	4 & 5 & 6\\
  	7 & 8 & 9
  \end{matrix}
  \right]\\
  \left\{
  \begin{matrix}
  	1 & 2 & 3\\
  	4 & 5 & 6\\
  	7 & 8 & 9
  \end{matrix}
  \right\}\\
  ```

