# 返回结果的HTTP状态码

## 1XX

- 信息性状态码，接收的请求正在处理



## 2XX

- 成功状态码，请求正常处理完毕

- 200，OK，请求被正常处理
- 204，No Content，请求处理成功，但没有资源可返回
- 206，Partial Content，请求时对内容的范围请求



## 3XX

- 重定向状态码，需要进行附加操作以完成请求

- 301，Moved Permanently，永久性重定向，表示请求的资源已被分配了新的uri，以后需要使用该资源应该指向该资源
- 302，Found，临时性重定向，资源被临时定位到了其他的地方
- 303 ，See Other，请求对应的资源存在着另一个URI，应使用GET方法定向获取请求资源
- 304，Not Modified，资源已经找到，但是不符合条件请求
- 307，Temporary Redirect，临时重定向



## 4XX

- 客户端错误状态码，服务器无法处理请求

- 400，Bad Request，客户端错误
- 401，Unauthorized，表示发送的请求需要有通过HTTP认证的认证信息
- 403，Forbidden，请求资源的访问被服务器拒绝
- 404，Not Found，服务器上没有请求的资源



## 5XX

- 服务器错误状态码，服务器处理请求错误

- 500，Internal Server Error，服务器端执行请求发生错误
- 503，Service Unavailable，服务器超负载或停机维护