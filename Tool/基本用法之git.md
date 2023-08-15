# git基本概念

## 工作区

当前目录下的文件

<br/>

## 暂存区

使用 git add 后，会先把文件放到暂存区中

<br/>

## 本地仓库

使用 git commit 后，会把文件放到本地仓库中

<br/>

## 远程仓库

使用 git push 后，会把文件推送到远程仓库中

<br/>

## 远程仓库副本

在本地使用了 git fetch 后，会将远程仓库的副本克隆到本地一份

<br/>

<br/>

<br/>

# git基本配置

## vscode和git的配置

背景：
- git，vscode已安装
- 密钥都已配置
- github上的仓库已建立

首先在本地找一个要用的同名文件夹（不同名的也行），输入指令`git init`（初始化一个git管理的仓库）

然后输入`git remote add origin 仓库的ssh链接`（将本地仓库和远端仓库建立关系）

接着输入`git pull origin main`（将远端仓库的内容拉下来）

其实到这一步，就算是完成了，但vscode有一个比较坑的就是，它默认的分支是master（而前几年github因为某种原因改为了main分支；git的默认分支也是master），所以要记得把本地的master分支给删掉（如果项目本身有master分支的话就当我没说）

vscode的细则
- vscode改不了已经提交了的分支的名字
- vscode左下角切换分支
- 带origin的是远程仓库（github上的）分支，其他的是本地的分支

```shell
# 根据具体的要求对内容进行修改
mkdir muduo
cd muduo
git init
git remote add origin git@github.com:dancsmshenry/annotation_of_muduo.git # 这里需要修改为你的仓库 ssh 链接地址
git pull origin main
git checkout -b main
git branch -d master
```



<br/>

<br/>

<br/>

# git常用命令

## add

```shell
# 将某个文件的修改提交到暂存区
git add filename

# 将所有发生修改的文件都添加到暂存区
git add -A
git add .
```

<br/>

## init

```shell
# 在当前目录创建 git 仓库
git init

# 在指定 path 路径下创建 git 仓库
git init <path>
```

<br/>

## clone

```shell
# 将代码 clone 到当前目录中
git clone <url>

# 将代码 clone 到指定目录中
git clone <url> <dir_name>
```

<br/>

## config

```shell
# 有三个级别 local （项目级别）， global （用户级别）和 system （机器级别）
# 一般默认是 local 级别

# 设置 name
git config --global user.name "username"

# 设置邮箱
git config --global user.email "useremail"

# 查看当前账号信息
git config --global --list
```

<br/>



## status

```shell
# 显示文件和文件夹在工作区和暂存区的状态
git status

# 展示中包含被忽略的文件
git status --ignored
```

<br/>

## log

```shell
# 显示当前仓库的提交 commit 记录（从远到近）
git log

# 将 commit 的日志记录简写
git log --pretty=oneline	# 输出的一串乱码是版本号
git log --oneline	# 只会输出版本号的前几位
```

<br/>

## stash

```shell
# 将当前的工作进度保存到栈里面，并将工作区和暂存区恢复到本次修改之前
# stash 命令默认不包含未跟踪的文件（新建的文件需要被 add 之后，才能被跟踪）
git stash
git stash save message # message 表示对此次保存的声明
git stash -u # 使用该指令可以保存未被 git 跟踪的文件

# 删除所有保存的工作进度
git stash clear

# 显示保存的工作进度列表，编号越小代表保存进度的时间越近
git stash list

# 恢复已保存的工作进度，顺序是先进后出
git stash pop # 不带选项，则默认恢复到最近的一次工作进度中
git stash pop stash@{0} # 带选项，则表示恢复到指定进度上

# 删除已保存的工作进度
git stash drop # 不带选项，则删除最近保存的工作进度中
git stash drop stash@{0} # 带选项，则表示删除指定的工作进度
```

<br/>

## show

```shell
# 依次显示每次 commit 的具体提交信息和数据变更信息
git show

# 显示某次具体的 commitid 对应的提交信息和数据变更信息
git show <commitId>

# 显示某条分支对应的提交信息和数据变更信息
git show <branchName>
```

<br/>

## shortlog

```shell
# 按照不同用户，列出其 commit 次数，并依次显示 commit 的注释
git shortlog

# 按照不同用户，只列出其 commit 次数
git shortlog -sn
```

<br/>

## branch

```shell
# 创建分支
git branch branch_name

# 删除分支
git branch -d branch_name
git branch -D branch_name # 强制删除 dev 分支

# 查看分支
git branch # 查看本地所有分支（其中带有星号的是当前分支）
git branch -a # 查看本地和远程的所有分支

# 重命名分支
git branch -m old_name new_name
```

<br/>

## checkout

```shell
# 切换到指定分支
git checkout branch_name

# 创建分支并切换到该分支上
git checkout -b branch_name

# 放弃工作区中所有对文件的修改（只针对被跟踪的文件）
git checkout .
```

<br/>

## commit

```shell
# 提交 commit，并添加 commit 信息
git commit -m "message"

# 等价于 git add -a 和 git commit -m "message"
git commit -am "message"

# 在不增加一次新 commit 的情况下将新修改的代码追加到上一次的 commit 中（会弹出一个编辑器界面重新编辑 message 信息）
# 一般用于代码 review 后出现问题，修改后再提交
git commit --amend

# 在不增加一个新 commit 的情况下将新修改的代码追加到前一次的 commit 中（不需要再修改 message 信息）
git commit --amend --no-edit
```

<br/>

## remote

```shell
# 添加与远程仓库关联
git remote add <name> <url>

# 删除与远程仓库关联
git remote remove <name> <url>
```

<br/>

## rm

```shell
# 删除工作区某个文件，并将此次删除放入到暂存区
git rm file_name
git rm -f -r . # 删除工作区所有的文件

# 删除工作区和暂存区的某个文件，并将此次删除放入暂存区
git rm -f file_name

# 删除暂存区文件，并将此次删除放入暂存区，但会保留工作区的文件
# 可以理解成解除 git 对这些文件的追踪，将他们转入 untracked 状态
git rm --cached file_name
```

<br/>

## mv

```shell
# 给文件/文件夹重命名
# 如果文件名中有空格，需要用""括起来
git mv old_name new_name
git mv -f old_name new_name	# 若新文件/文件夹已经存在，可以强制覆盖

# 可以直接给文件重命名，但是 git 会判定为删除了旧文件，并添加了新文件
```

<br/>

## merge

```shell
# 合并分支(将指定分支合并到当前分支中)
git merge branch_name

# 退出 merge 过程
git merge --abort

# 继续 merge 过程
git merge --continue
```

<br/>

## push

```shell
# 推送代码到远程仓库的指定分支上
# 向远程仓库推送指定分支
git push remote_name branch_name
```

<br/>

## pull

```shell
# 拉取远程仓库指定分支上最新的代码
# 等价于 fetch + merge
git pull remote_name branch_name
```

<br/>

## rebase（wait）

相比 merge，合并分支历史的另一种管理方式，区别可查看此[博客](https:#www.jianshu.com/p/6960811ac89c)

此外也可以使用`git rebase -i HEAD~n` 来合并 n 个 commit，具体过程可参考此[博客](https:#www.jianshu.com/p/6960811ac89c)。切记不要在共用的分支上进行 rebase，具体原因可查看此[博客](https:#segmentfault.com/a/1190000005937408)

此外也可以使用`git rebase --onto <branch> <fromCommitId> <toCommitId>`来将 (fromCommitId,toCommitId] 上的所有 commit 合并到指定分支上，具体可参考此[博客](https:#www.cnblogs.com/rickyk/p/3848768.html)。其实类似于 cherry-pick 多个提交

```shell
git rebase <branch>		# 变基某个分支
git rebase --abort		# 退出 rebase 过程，常在处理冲突出错时使用
git rebase --continue	# 继续 rebase 过程，常在处理完冲突时使用
```

<br/>

## reset

```shell
# 常用的三个参数： --hard，--soft，--mixed

# 将当前仓库的版本，回退到过去某次 commit 的时候
# 此处的 HEAD^ （回退多少个版本，就加几个^）可以换成 commitid（可以只写 id 的前几位）
git reset --hard HEAD^ # 回退到某个版本，并将当时 commit 提交的内容以及当前工作区和暂存区的内容全部删掉
git reset --soft HEAD^ # 回退到某个版本，并将当时 commit 提交的内容保存至暂存区，且不会破坏当前工作区和暂存区（一般用于撤销本地仓库中未提交（到远程仓库）的 commit）

# 将暂存区的修改撤销回工作区
git reset filename
git reset # 撤销所有的修改回工作区
```

<br/>

# git commit message规范

`<type>[(<scope>)]: <subject>`

type：声明本次代码提交的类型（英文名，必填项）

- feat：新功能特性
- fix：bug修复
- perf：功能优化，包括性能优化、体验优化等
- refactor：代码重构（大范围的代码结构重构，不涉及代码功能）
- style：格式调整（小范围的代码格式调整，不涉及代码功能）
- merge：代码分支合并
- revert：代码版本回滚
- test：测试代码变动
- doc：文档变动
- chroe：工具的变动

<br/>

scope：用于声明本次代码提交的影响范围（建议英文，选填项）

- 如Model层、Dao层、Service层、Controller层、View层等等
- 如果涉及多个scope，可以置空或用*代替

<br/>

subject：用于声明本次代码提交的描述信息（建议中文，必填项）。通常控制在50个字符内，且省略句末标点符号

<br/>

<br/>

<br/>

# github网页上的操作

## 删除分支

<img src="image/删除分支_01.png" style="zoom:150%;" />

点进view all branches

<img src="image/删除分支_02.png" style="zoom:150%;" />

点进右边的垃圾桶

<br/>

## 将仓库设为私有

点进settings

<img src="image/修改仓库权限.png" style="zoom:150%;" />