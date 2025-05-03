# 背景

因为搞了个博客，所以需要学习一下常见的 node 之类的指令

<br/>

<br/>

# 常见指令

```shell
nvm list # 查看当前安装的 node 版本

nvm use 13.14.0 # 使用特定版本的 node

hexo -v # 查看 hexo 版本
hexo g # 生成静态网页页面
hexo s # 开启本地服务器
hexo new post "article title"  # 新建文件
hexo d # 上传生成的静态界面
```



# Blog的搭建

- [φ(゜▽゜*)♪咦，又好了！](https://godweiyang.com/2018/04/13/hexo-blog/#toc-heading-8)
- [hexo博客网站主页空白或404 - 简书](https://www.jianshu.com/p/fc6f5a132bf0)
- https://blog.csdn.net/weixin_46087812/article/details/124575202
- [git 更改当前分支的名称 - CSDN](https://www.csdn.net/tags/Ntzacg2sMjI1NS1ibG9n.html)
- https://blog.csdn.net/m0_59464010/article/details/122761887
- https://blog.csdn.net/weixin_41287260/article/details/120254461
- https://tieba.baidu.com/p/5843629195
- https://blog.csdn.net/q1ngqingsky/article/details/123571347
- https://blog.csdn.net/weixin_44543463/article/details/119738094



常见的hexo指令

- `hexo d`上传文件
- `hexo s`本地运行服务器
- `hexo g`生成静态文件
- `hexo new post 'name_artical'`生成新文章（文件夹放source）



hexo上公式渲染错误：

- ```shell
  npm uninstall hexo-renderer-marked --save;npm install hexo-renderer-kramed --save
  
  npm uninstall hexo-renderer-kramed --save;npm install hexo-renderer-marked --save
  ```
  
- 更换 Hexo 的 markdown 渲染引擎，hexo-renderer-kramed 引擎是在默认的渲染引擎 hexo-renderer-marked 的基础上修改了一些 bug ，两者比较接近，也比较轻量级

- 上述方法不行

- 解决办法：在括号和括号之间加上空格，多加几个空格即可
