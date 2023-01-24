此前使用godweiyang的博客模板+github构建博客的

但是因为上次的一个教训，让我忽然想到，应该需要对博客的内容和动静态文件进行备份，以便后续的操作

所以便有了这篇文章

<br/>

因为是要将博客的源代码上传到github上，所以我建议将仓库设为私密（不是很懂前端，但觉得还是要将源代码保护起来）

同时，开两个分支，hexo分支和main分支

hexo分支用于存储源文件

main分支用于存储静态文件，即博客的静态部署时用的文件

<br/>

PS：

- 在hexo的配置中，注意需要将hexo上传的分支名修改为main分支（在_config.yml中修改）
- 本地需要安装了git，node.js，npm，hexo（具体安装方法上网查，不另叙述）

<br/>

将原来的博客源文件中所有的文件（除了.git）都复制过来

同时修改.gitignore文件

```shell
.DS_Store
Thumbs.db
db.json
*.log
node_modules/
public/
.deploy*/
```

然后上传到hexo分支中

<br/>

那么，在新的电脑上，只需要安装好了PS中的配置，clone仓库的hexo分支

执行以下指令：

```shell
npm install
npm install hexo-deployer-git --save
```

便可像之前一样运作了

<br/>

博客中config.yml配置文件的细则：

https://blog.csdn.net/zemprogram/article/details/104288872

http://events.jianshu.io/p/dbb7d41712df

