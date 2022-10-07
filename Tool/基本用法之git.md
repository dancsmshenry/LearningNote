# git基本概念

## 工作区

- 平常看得到的文件夹里的文件



## 暂存区

- git add之后会先把文件放到这个暂存区里面，然后通过git commit一起统一提交



## 仓库

- OK的数据都会push到仓库中







# git基本配置

## vscode和git的配置

- 背景：
  - git，vscode已安装
  - 密钥都已配置
  - github上的仓库已建立
- 首先在本地找一个要用的同名文件夹，输入指令`git init`（初始化一个git管理的仓库）
- 然后输入`git remote add origin 仓库的ssh链接`（将本地仓库和远端仓库建立关系）
- 接着输入`git pull origin main`（将远端仓库的内容拉下来）
- 其实到这一步，就算是完成了，但vscode有一个比较坑的就是，它默认的分支是master（而前几年github因为某种原因改为了main分支；git的默认分支也是master），所以要记得把本地的master分支给删掉（如果项目本身有master分支的话就当我没说）
- vscode的细则
  - vscode改不了已经提交了的分支的名字
  - vscode左下角切换分支
  - 带origin的是远程仓库（github上的）分支，其他的是本地的分支







# git常用命令

## init

- ```shell
  git init // 在当前目录创建git仓库
  git init <path> // 在 path 路径下创建目录并创建 git 仓库
  ```



## clone

- ```shell
  git clone <url>	//	clone对于仓库的代码
  git clone <url> <dir_name> //	指定本地的存储目录名
  ```



## config

- 注意有三个级别`local`，`global`和`system`，分别对应项目级别，用户级别和机器级别。默认不指定是`local`级别

- ```shell
  git config user.email "TXYPotato@gmail.com"	//	设置邮箱
  git config user.name "LebronAl"	//	设置name
  ```



## remote

- ```shell
  // 添加远程仓库关联
  git remote add <name> <url>
  // 删除远程仓库关联
  git remote remove <name>
  // 更名远程仓库关联
  git remote rename <old_name> <new_name>
  // 显示某个远程仓库的信息
  git remote show <name>
  // 更新远程仓库 url
  git remote set-url <name> <new_url>
  ```



## rm

- ```shell
  git rm <file> // 用于删除工作区文件，并将此次删除放入到暂存区。（注：要删除的文件没有修改过，就是说和当前版本库文件的内容相同）
  
  //	用于删除工作区和暂存区文件，并将此次删除放入暂存区。（注：要删除的文件已经修改过，就是说和当前版本库文件的内容不同）
  git rm -f <file>
  
  git rm -f -r .	// 对所有文件进行操作
  
  //	用于删除暂存区文件，并将此次删除放入暂存区，但会保留工作区的文件。可以理解成解除 git 对这些文件的追踪，将他们转入 untracked 状态。
  git rm --cached <file>
  
  git rm --cached -r .	// 对所有文件进行操作
  ```



## mv

- ```shell
  git mv <old_file> <new_file>	//用于移动或重命名一个文件、目录或软链接。
  ```

- 相当于`mv old_file new_file`，`git rm old_file`，`git add new_file`这三条命令一起运行，具体可参考此[博客](https://www.cnblogs.com/mf001/p/8663386.html)。

- 新文件名已经存在，若想强制覆盖则可以使用 -f 参数：

  ```shell
  git mv -f <old_file> <new_file>
  ```





## 文件操作

### 添加文件

- `git add filename`

  - `git add -A`（把全部修改了的文件添加到暂存区中；这里必须要大写）
  - `git add .`（提交当前目录下的所有变化）
  - `git add -u` 提交被修改(modified)和被删除(deleted)文件，不包括新文件(new)
  - 将文件添加到仓库的管辖中（把文件添加到暂存区）

- git commit -m "注释"
  - 将文件提交到仓库中（把文件添加到版本库）

  - ```shell
    // 提交一个描述为 message 的 commit
    git commit -m "message"
    // 相当于 git add -A 和 git commit -m "message" 两条命令
    git commit -am "message"
    // 在不增加一个新 commit 的情况下将新修改的代码追加到前一次的 commit 中，会弹出一个编辑器界面重新编辑 message 信息
    git commit --amend
    // 在不增加一个新 commit 的情况下将新修改的代码追加到前一次的 commit 中，不需要再修改 message 信息
    git commit --amend --no-edit
    // 提交一次没有任何改动的空提交，常用于触发远程 ci
    git commit --allow-empty -m "message"
    // 修改 commit 时间
    git commit -m "message" --date=" Wed May 27 00:35:36 2020 +0800"
    ```

  - 



### 删除文件

- `git rm <file>`
  - 用于删除工作区文件，并将此次删除放入到暂存区



### 恢复文件

- git checkout id 文件名
  - 文件被误删了，用该命令还原
  - 从来没有被添加到版本库就被删除的文件，是无法恢复的
  - 本质是让某一个文件回退到之前的某一个版本



### 重命名文件

- `git mv 旧文件(夹)名 新文件(夹)名`
  - 相当于`mv old_file new_file`，`git rm old_file`，`git add new_file`这三条命令一起运行
  - 可以直接重命名，但是git会判定为删除了旧文件，添加了新文件
  - 如果文件名中带有空格，需要用''括起来，比如`git mv 'clone 01.pdf' 'clone 02.pdf'`
  



## 标签操作

### 标签添加

- 指令一：`git tag nametag`先转到要打标签的分支，然后再打标签
- 指令二：`git tag -a tagnumber -m tagcomment`先是指明标签版本号，再是指明标签文字内容



### 标签查看

- git tag(不一定按时间来的)



### 标签详情

- git show tagname



### 标签删除

- git tag -d tagnumber



### 标签推送至远程

- git push origin tagname



### 标签全部推送至远程

- git push origin --tags



### 标签的远程删除

- git push origin: tagname





## 分支操作

### 分支合并

- 指令：`git merge branchname`将指定分支合并到当前所在的分支
- github分支的合并
  - https://blog.csdn.net/qq_30607843/article/details/84404000
  - github合并的时候，是将右边框的数据合并到左边框的数据里面的
  - 合并以后还有再在上面的页面里面点一个确定，然后再销毁原来的分支



### 分支查询

- git branch(当前的分支会显示有星号*)



### 分支删除

- git branch -d pointname



### 分支创建

- git branch pointname（前提是该分支已经被合并了，然后才删除）
- git branch -D pointname（分支开发完成，但是忽然不要了，也没有合并，所以就用这个指令强制删除，小d是普通删除）



### 分支切换

- git checkout 分支名
- git switch -c 分支名
  - 特例：git switch master



### 分支创建并切换

- 指令：`git checkout -b pointname`
  - 等价于：
    - git branch dev
    - git checkout dev
- 指令二：`git switch -c branchname`



## 其他操作

### 修改最新的commit的message

- git commit --amend
  - 进入界面修改message，快捷键和vim一样



### 比较暂存区和HEAD文件的差异

- git diff --cached



### 比较暂存区和工作区的差异

- git diff



### 将暂存区恢复到和HEAD一致

- git reset HEAD



### 取消暂存区部分文件的更改

- git reset HEAD -- 文件名（文件路径/文件名）



### 版本回退

- `git reset --hard HEAD^`回退到后几个版本就加上几个^
- git reset --hard 版本号（只要窗口没有被关闭，就可以回退到指定的版本号，版本号不一定要写全）
- 注意版本回退并不代表说版本出现提交，而只是说单纯的回到某个版本
- 是指仓库所有的文件都回退到之前的那个版本



### 远程仓库克隆

- 指令：`git clone storeaddress`



### 查看仓库状况

- git status



### 查看仓库中某个文件的情况

- git diff 文件名	



### 查看总共提交的日志

- git log（从近到远）
- git log --pretty=oneline 可以将日志简写，便捷显示
  - 输出的一串乱码是版本号



### 查看分支合并情况

- git log --graph



### 查看所有分支的操作记录

- git reflog



### 撤销暂存区的修改

- git reset HEAD 文件名（即文件写错了，提交到了暂存区里面，但是还没有提交到版本库当中，就可以用这个指令撤销修改）
  - 把已经提交到暂存区的修改撤销掉，重新放回工作区
- 指令二：`git checkout -- file`
  - 两种情况：
    - 文件被修改后但是还没被放入暂存区，即还在工作区，则把文件撤销到版本库的状态
    - 文件被添加到暂存区后，又发生了修改，则把文件撤销到文件被添加到暂存区后的状态



### 设置邮箱和用户名

- git config --global user.name "username"
- git config --global user.email "useremail"



### 查看邮箱和用户名

- git config --global --list





### clone指定分支版本的仓库

- `git clone --branch v2 https://github.com/XXXXX.git`
- v2为指定下载的分支名称





# Git commit message规范

- `<type>[(<scope>)]: <subject>`
- type：
  - 声明本次代码提交的类型（英文名，必填项）
  - feat：新功能特性
  - fix：bug修复
  - perf：功能优化，包括性能优化、体验优化等
  - refactor：代码重构（大范围的代码结构重构，不涉及代码功能）
  - style：格式调整（小范围的代码格式调整，不涉及代码功能）
  - merge：代码分支合并
  - revert：代码版本回滚
  - test：测试代码变动
  - doc：文档变动
- scope：
  - 用于声明本次代码提交的影响范围（建议英文，选填项）
  - 如Model层、Dao层、Service层、Controller层、View层等等
  - 如果涉及多个scope，可以置空或用*代替
- subject：
  - 用于声明本次代码提交的描述信息（建议中文，必填项）。通常控制在50个字符内，且省略句末标点符号