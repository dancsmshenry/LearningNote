# 委托相关设计

委托（delegation）和继承（inheritance）
- 设计模式中的composite模式，组合模式
  - 文件夹里面放文件和文件夹，里面的文件夹又可以放文件和文件夹
  - 因此，抽象出一个具有两者共性的类component，一个文件夹类composite，和一个文件类primitive
  - 然后，让composite和primitive继承component（继承），其中composite又具有一个vector，这个vector装载component类（委托）
- 设计模式中的prototype模式，原型模式
  - 通过一个抽象原型类，去实现多个具体原型类
  - 背景：对于一个照片，未来可能会有很多的照片，但我现在不知道这些照片的类型究竟有多少，所以就有了这种设计模式
  - 即对于每一个新的照片，我都准备一个**clone函数**（这里的clone要在父类中设为纯虚函数），用来创建一个新的自己，同时给这个类准备一个**静态的编号**，并把这个编号填入原型类的一个数组当中（或者不是储存编号，而是直接把这个对象储存到里面）
  - 原型类就可以通过编号调用创建不同的类了
  - 细节：为什么会有一个protected的构造函数？
    - 因为正常的构造函数会把一个函数原型添加到原型类的数组当中，如果当我们clone一个新的对象的是时候，调用的又是这个构造函数，那么又会添加一个重复的函数原型。为了防止这种情况发生，就新写一个带参数的构造函数，让clone调用的是这个带参数的构造函数
    - 不能放在公有区域，加一个参数是为了区分原来的构造函数