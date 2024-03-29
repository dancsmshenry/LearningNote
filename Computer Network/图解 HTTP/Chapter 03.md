# HTTP报文内的HTTP信息

## 报文的组成

- 报文首部（服务器端或客户端需处理的请求或响应的内容以及属性）
  - 对于请求（响应）报文：
    - 请求（状态）行
      - 包含请求方法，请求uri和http版本
      - 包含响应结果的状态码，原因短语和http版本
    - 请求（响应）首部字段
    - 通用首部字段
    - 实体首部字段
    - 其他
- 空行
- 报文主体（应被发送的数据）

- 报文主体和实体
  - 报文是http通信中的基本单位，由8位组字节流组成
  - 实体，作为请求或响应的有效载荷数据被传输
  - http报文的主体用于传输请求或响应的实体主体
    - 只有当传输中进行编码操作时，实体主体的内容发生改变，才会导致实体和报文主体的不同





## 提高发送效率

- 压缩发送的内容（将内容压缩为zip格式再发送）
  - 常用的内容编码：gzip,compress,deflate
- 分割发送的分块传输编码





## MIME

- 多用途互联网邮件扩展（英语：Multipurpose Internet Mail Extensions，缩写：MIME）是一个互联网标准，它扩展了电子邮件标准，使其能够支持： 
  - 非ASCII字符文本； 非文本格式附件（二进制、声音、图像等）
  - 由多部分（multiple parts）组成的消息体
  - 包含非ASCII字符的头信息（Header information）。这个标准被定义在 RFC 2045、RFC 2046、RFC 2047、RFC 2048、RFC 2049 等RFC中。



## 范围请求

- 用到首部字段Range来指定资源的byte范围





## 内容协商

- 分类：	
  - 服务器驱动协商
  - 客户端驱动协商
  - 透明协商
- 定义：通过为同一 URI 指向的资源提供不同的展现形式，可以使用户代理选择与用户需求相适应的最佳匹配（例如，文档使用的自然语言，图片的格式，或者内容编码形式）
- 补充：
  - 一份特定的文件称为一项资源。当客户端获取资源的时候，会使用其对应的 URL 发送请求。服务器通过这个 URL 来选择它指向的资源的某一变体——每一个变体称为一种展现形式——然后将这个选定的展现形式返回给客户端
  - 整个资源，连同它的各种展现形式，共享一个特定的 URL
  - 当一项资源被访问的时候，特定展现形式的选取是通过内容协商机制来决定的，并且客户端和服务器端之间存在多种协商方式
- 实现方式：
  - 客户端设置特定的 HTTP 首部 （又称为服务端驱动型内容协商机制或者主动协商机制）；这是进行内容协商的标准方式
  - 服务器返回 300 (Multiple Choices) 或者 406 (Not Acceptable) HTTP 状态码 （又称为代理驱动型协商机制或者响应式协商机制）
- 代理驱动型内容协商机制
  - 在这种协商机制中，当面临不明确的请求时，服务器会返回一个页面，其中包含了可供选择的资源的链接。资源呈现给用户，由用户做出选择
  - 实现方法：过脚本技术来完成的，尤其是 JavaScript 重定向技术
- 服务端驱动型内容协商机制
  - 定义：在服务端驱动型协商机制或者主动协商机制中，浏览器（或者其他任何类型的用户代理）会随同 URL 发送一系列的**消息头**，这些消息头描述了用户倾向的选择。服务器则**以此为线索**，通过内部算法来选择最佳方案提供给客户端。相关算法与具体的服务器相关，并没有在规范中进行规定