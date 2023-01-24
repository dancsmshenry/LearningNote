# git基本概念

## 工作区

- 当前目录下的文件



## 暂存区

- git add之后会先把文件放到这个暂存区里面，然后通过git commit一起统一提交



## 仓库

- OK的数据都会在commit后push到仓库中







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

## add

- ```shell
  git add filename	//	将当前文件的修改提交到暂存区
  git add -A	//	把全部修改了的文件添加到暂存区中；这里必须要大写
  git add .	//	提交当前目录下的所有变化
  git add -u	//	提交被修改(modified)和被删除(deleted)文件，不包括新文件(new)
  ```



## init

- ```shell
  git init // 在当前目录创建git仓库
  git init <path> // 在 path 路径下创建目录并创建 git 仓库
  ```



## clone

- ```shell
  git clone <url>	//	clone对于仓库的代码
  git clone <url> <dir_name>	//	指定本地的存储目录名
  git clone --branch v2 https://github.com/XXXXX.git	//	v2为指定下载的分支名称（clone指定版本的仓库）
  ```



## config

- 注意有三个级别`local`，`global`和`system`，分别对应项目级别，用户级别和机器级别。默认不指定是`local`级别

- ```shell
  git config --global user.name "username"	//	设置name
  git config --global user.email "useremail"	//	设置邮箱
  git config --global --list	//	查看邮箱和用户名 
  ```



## remote

- ```shell
  git remote add <name> <url>	//	添加远程仓库关联
  git remote remove <name>	//	删除远程仓库关联
  git remote rename <old_name> <new_name>	//	更名远程仓库关联
  git remote show <name>	//	// 显示某个远程仓库的信息
  git remote set-url <name> <new_url>	//	更新远程仓库 url
  ```



## rm

- ```shell
  git rm <file> // 用于删除工作区文件，并将此次删除放入到暂存区。（注：要删除的文件没有修改过，就是说和当前版本库文件的内容相同）
  git rm --cached -r .	// 对所有文件进行操作
  git rm -f -r .	// 对所有文件进行操作
  
  //	用于删除工作区和暂存区文件，并将此次删除放入暂存区。（注：要删除的文件已经修改过，就是说和当前版本库文件的内容不同）
  git rm -f <file>
  
  //	用于删除暂存区文件，并将此次删除放入暂存区，但会保留工作区的文件。可以理解成解除 git 对这些文件的追踪，将他们转入 untracked 状态。
  git rm --cached <file>
  ```



## mv

- ```shell
  git mv <old_file> <new_file>	//	用于移动或重命名一个文件、目录或软链接
  git mv -f <old_file> <new_file>	//	新文件名已经存在，若想强制覆盖则可以使用 -f 参数
  ```
  
  - 等价于`mv old_file new_file`，`git rm old_file`，`git add new_file`这三条命令一起运行，具体可参考此[博客](https://www.cnblogs.com/mf001/p/8663386.html)
  - 可以直接重命名，但是git会判定为删除了旧文件，添加了新文件
  - 如果文件名中带有空格，需要用''括起来，比如`git mv 'clone 01.pdf' 'clone 02.pdf'`
  



## reset

- 用于将指定 commit 和 branch 的文件替换暂存区的文件。有三个常用参数，分别是`--hard`，`--soft`，`--mixed`，默认是`--mixed`。具体细节和应用场景可参考此[博客](https://www.jianshu.com/p/c2ec5f06cf1a)

- **用于版本的回退，只进行对commit操作的回退，不影响工作区的文件**（如果当前的commit出现了问题，就reset回之前的版本）

- git reset --mixed commitid，是将commit的内容回放到工作区中，而--soft是回放到暂存区中，hard是将指定 commit id 撤回并清空工作目录及暂存区所有修改

- 定义三种动作：

  - 1、替换引用的指向，指向新的提交
  - 2、替换暂存区。暂存区内容将和指定的提交内容一样
  - 3、替换工作区。工作区和指定的提交内容一样

- ```shell
  git reset --soft [commitId]/<branch> // 执行 1。常用于合并多个 commit，类似于 squash
  git reset (--mixed) <commitId>/<branch>	// 执行 12。常用于移出暂存区的文件以作为 add 命令的反动作
  git reset --hard <commitId>/<branch>	// 执行 123。常用于无条件放弃本地所有变更以向远程分支同步
  git reset (--mixed) HEAD	// 将暂存区的所有改动撤销到工作区（将暂存区恢复到和HEAD一致）
  git reset filename	//	取消暂存区中filename文件的修改，使其回到工作区（filename也可以加上路径）可以理解为撤销暂存区的修改
  
  git reset --soft commitid	//	当前的commit出现了错误，希望将当前版本回到commitid的情况（id可以只写前面几位）,而在其期间修改的数据就会放到暂存区中（就是说发生了错误的commit的数据会回到暂存区中）
  
  git reset --hard HEAD^	//	回退到后几个版本就加上几个^
  
  git reset --hard 版本号	//	只要窗口没有被关闭，就可以回退到指定的版本号，版本号不一定要写全(版本回退并不代表说版本出现提交，而只是说单纯的回到某个版本,是指仓库所有的文件都回退到之前的那个版本)
  ```



## status

- ```shell
  git status //	显示文件和文件夹在工作区和暂存区的状态
  git status --ignored	// 展示中包含被忽略的文件
  ```



## log

- 用来回顾提交历史。可参考此[文档](https://git-scm.com/book/zh/v2/Git-%E5%9F%BA%E7%A1%80-%E6%9F%A5%E7%9C%8B%E6%8F%90%E4%BA%A4%E5%8E%86%E5%8F%B2)和此[博客](https://www.cnblogs.com/lenomirei/p/8379457.html)

- ```shell
  git log	//	从远到近
  git log --pretty=oneline //	可以将日志简写，便捷显示（输出的一串乱码是版本号）
  git log --oneline
  git log --graph --pretty=format:'%Cred%h%Creset -%C(yellow)%d%Creset %s %Cgreen(%cr) %C(bold blue)<%an>%Creset' --abbrev-commit --date=relative
  git log --grep <key>	// 从 commit 信息中查找包含指定字符串的 commit
  git log -S <key>	// 从更改内容中查找包含指定字符串的 commit ，比如想查找哪些 commit 对代码中名为 <key> 的函数进行了更改
  git log --graph	//	查看分支的合并情况（图表的形式生成的）
  ```



## stash

- 常用来保存和恢复工作进度。注意该命令只对被 git 跟踪的文件有效。这是一个非常有用的命令，具体相关用法可查看此[博客](https://blog.csdn.net/andyzhaojianhui/article/details/80586695)

- ```shell
  // 保存当前工作进度，将工作区和暂存区恢复到修改之前。默认 message 为当前分支最后一次 commit 的 message（将当前工作区的修改暂时存放到stack中）
  git stash
  
  // 作用同上，message 为此次进度保存的说明
  git stash save message
  
  // 显示此次工作进度做了哪些文件行数的变化，此命令的 stash@{num} 是可选项，不带此项则默认显示最近一次的工作进度相当于 git stash show stash@{0}
  git stash show stash@{num}
  
  // 显示此次工作进度做了哪些具体的代码改动，此命令的 stash@{num} 是可选项，不带此项则默认显示最近一次的工作进度相当于 git stash show stash@{0} -p
  git stash show stash@{num} -p
  
  // 显示保存的工作进度列表，编号越小代表保存进度的时间越近
  git stash list
  
  // 恢复工作进度到工作区，此命令的 stash@{num} 是可选项，在多个工作进度中可以选择恢复，不带此项则默认恢复最近的一次进度相当于 git stash pop stash@{0}
  git stash pop stash@{num}
  
  // 恢复工作进度到工作区且该工作进度可重复恢复，此命令的 stash@{num} 是可选项，在多个工作进度中可以选择恢复，不带此项则默认恢复最近的一次进度相当于 git stash apply stash@{0}
  git stash apply stash@{num}
  
  // 删除一条保存的工作进度，此命令的 stash@{num} 是可选项，在多个工作进度中可以选择删除，不带此项则默认删除最近的一次进度相当于 git stash drop stash@{0}
  git stash drop stash@{num}
  
  // 删除所有保存的工作进度
  git stash clear
  
  //	把修改逐步放回来，修改是先进后出
  git stash pop
  ```

- 此外有时我们只想保存部分文件，可以通过 add 一些不想保存的文件到暂存区去，然后使用`git stash --keep-index`来将工作区的工作进度保存，从而保留暂存区的进度并保存工作区的进度。具体可参考此[博客](https://juejin.im/post/6844903961770606605)

  此外虽然 stash 命令默认不包含未跟踪的文件，但我们可以通过显示声明`-u`的方式来保存未被 git 追踪的文件。即`git stash -u`



## show

- ```shell
  //	用来显示某个 commit 的具体提交信息和元信息
  git show
  git show <commitId>
  git show <branchName>
  ```



## shortlog

- 用于汇总 git 日志输出

- ```shell
  git shortlog	//	按照用户列出其 commit 的次数以及每次 commit 的注释
  git shortlog -sn	//	按照 commit 数量从多到少的顺序列出本仓库的贡献者并省略注释
  ```



## diff

- 用来比较文件之间的不同。具体用法可参考此[博客](https://blog.csdn.net/wq6ylg08/article/details/88798254)。diff 结果的格式可参考此[博客](http://www.ruanyifeng.com/blog/2012/08/how_to_read_diff.html)了解

- ```shell
  git diff	// 查看工作区与暂存区所有文件的变更
  git diff --cached	// 查看暂存区与最后一次 commit 之间所有文件的变更（比较暂存区和HEAD文件的差异）
  git diff HEAD	// 查看工作区与最后一次 commit 之间所有文件的变更
  git diff <commitId>...<commitId>	// 查看两次 commit 之间的变动
  git diff <branch>...<branch>	// 查看两个分支上最后一次 commit 的内容差别
  git diff filename	//	查看某个文件在工作区或是暂存区的修改差异
  ```



## branch

- ```shell
  git branch -vv	// 可以查看本地分支对应的远程分支
  git branch -r	// 查看远程版本库分支列表
  git branch -a	// 查看所有分支列表，包括本地和远程
  git branch <name>	// 在当前位置新建 name 分支
  git branch <name> <commitId>	// 在指定 commit 上新建 name 分支
  git branch -f <name>	// 强制创建 name 分支，原来的分支会被新建分支覆盖，从而迁移 name 分支指针（分支开发完成，但是忽然不要了，也没有合并，所以就用这个指令强制删除，小d是普通删除）
  git branch -d dev	// 删除 dev 分支，如果在分支中有一些未 merge 的提交则会失败
  git branch -D dev	// 强制删除 dev 分支
  git branch -m <oldName> <newName>	// 重命名分支
  git branch	//	查询当前仓库的分支（当前的分支会显示有星号*）
  ```



## checkout

- 用于切换分支或更新工作树文件以匹配索引或指定树中的版本，具体可参考此[博客](https://www.jianshu.com/p/cad4d2ec4da5)

- ```shell
  git checkout <branch>	// 切换到指定分支
  git switch -c <branch>	//	同样是切换分支（特例：git switch master）
  
  git checkout -b <branch>	// 在当前位置新建分支并切换
  git switch -c branchname	//	二者等价
  
  git checkout -b <branch> <commitId>	// 在指定 commit 上新建分支并切换
  git checkout tags/v1.2	// 切换到指定 v1.2 的标签
  git checkout <commitId>	// 切换到指定 commit
  git checkout .	// 放弃工作区所有文件的变更（不包含未跟踪的）
  
  // 基于当前所在分支新建一个赤裸分支，该分支没有任何的提交历史但包含当前分支的所有内容，相当于 git checkout -b <new_branch> 和 git reset --soft <firstCommitId> 两条命令 
  git checkout --orphan <new_branch>
  
  // 放弃工作区单个文件的变更，默认会从暂存区检出该文件，如果暂存区为空，则该文件会回滚到最近一次的提交状态
  git checkout -- <filepath>
  
  //	文件被误删了，用该命令还原;从来没有被添加到版本库就被删除的文件，是无法恢复的;本质是让某一个文件回退到之前的某一个版本
  git checkout id <filename>
  ```



## commit

- 用于将暂存区里的改动给提交到本地的版本库

- ```shell
  git commit -m "message"	// 提交一个描述为 message 的 commit
  
  // 相当于 git add -a 和 git commit -m "message" 两条命令
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



## revert

- 撤销某个 commit 的改动。在多人协作中如果某个 commit 已经被推到了远程，此时使用 revert 相比 reset + force-update 是更优雅的撤销变更方式。可参考此[博客](https://www.cnblogs.com/0616--ataozhijia/p/3709917.html)和[博客](https://www.jianshu.com/p/5e7ee87241e4)

- ```shell
  git revert <commitId>	// 可以撤销指定的提交
  git revert <commit1>...<commit2>	// 可以撤销不包括 commit1，但包括 commit2 的一串提交
  git revert --abort	// 退出 revert 过程，常在处理冲突出错时使用
  git revert --continue	// 继续 revert 过程，常在处理完冲突时使用
  
  // revert 命令会对每个撤销的 commit 进行一次提交，--no-commit 后可以最后一起手动提交
  git revert --no-commit <commit1>...<commit2>
  ```



## merge

- 用于将两个或两个以上的开发历史合并在一起的操作，具体详细命令及介绍可看此[博客](https://www.jianshu.com/p/58a166f24c81)

- https://blog.csdn.net/qq_30607843/article/details/84404000

- ```shell
  git merge <branch>	// 合并某个分支(将指定分支合并到当前所在的分支)
  git merge --abort	// 退出 merge 过程，常在处理冲突出错时使用
  git merge --continue	// 继续 merge 过程，常在处理完冲突时使用
  ```



## push

- 用于将本地版本库的分支推送到远程服务器上对应的分支，具体用法可查看此[博客](https://www.cnblogs.com/qianqiannian/p/6008140.html)

- 此外，当本地版本库的分支和远程版本库的对应分支有冲突时，如果想要强制覆盖，千万不要用`git push -f`，而是应该用`git push --force-with-lease`，具体原因可查看此[博客](https://www.cnblogs.com/walterlv/p/10236461.html)

- ```shell
  git push <remote> <branch>	// 向远程推送指定分支
  git push -u <remote> <branch>	// 向远程推送指定分支并绑定
  git push <remote> :<branch>	// 删除远程分支
  git push <remote> <tagName>	// 向远程推送 tag
  git push <remote> :<tagName>	// 删除远程 tag
  git push --tags <remote>	// 向远程推送本地所有 tag
  ```



## pull

- 用于从远程获取代码并合并本地的版本，其实就是`git fetch`和`git merge FETCH_HEAD`的简写。有关其与 fetch 的区别，可以参考此[博客](https://www.cnblo gs.com/ruiyang-/p/10764711.html)

- ```shell
  // 相当于 fetch + merge
  git pull <remote> <remote_branch>:<local_branch>
  // 相当于 fetch + rebase
  git pull --rebase <remote> <remote_branch>:<local_branch>
  ```



## rebase

- 相比 merge，合并分支历史的另一种管理方式，区别可查看此[博客](https://www.jianshu.com/p/6960811ac89c)

- 此外也可以使用`git rebase -i HEAD~n` 来合并 n 个 commit，具体过程可参考此[博客](https://www.jianshu.com/p/6960811ac89c)。切记不要在共用的分支上进行 rebase，具体原因可查看此[博客](https://segmentfault.com/a/1190000005937408)

- 此外也可以使用`git rebase --onto <branch> <fromCommitId> <toCommitId>`来将 (fromCommitId,toCommitId] 上的所有 commit 合并到指定分支上，具体可参考此[博客](https://www.cnblogs.com/rickyk/p/3848768.html)。其实类似于 cherry-pick 多个提交

- ```shell
  git rebase <branch>	// 变基某个分支
  git rebase --abort	// 退出 rebase 过程，常在处理冲突出错时使用
  git rebase --continue	// 继续 rebase 过程，常在处理完冲突时使用
  ```



## reflog

- ```shell
  git reflog // 查看所有分支的操作记录
  ```



## tag

- ```shell
  git push origin --tags	//	标签全部推送至远程
  git push origin tagname	//	标签推送至远程
  git tag -d tagnumber	//	删除标签
  git show tagname	//	查看标签详情
  git tag	//	查看所有标签
  git push origin:tagname	//	远程删除标签
  git tag nametag	//	添加标签：先转到要打标签的分支，然后再打标签
  git tag -a tagnumber -m tagcomment	//	先是指明标签版本号，再是指明标签文字内容
  ```







# git commit message规范

`<type>[(<scope>)]: <subject>`

type：
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

scope：
- 用于声明本次代码提交的影响范围（建议英文，选填项）
- 如Model层、Dao层、Service层、Controller层、View层等等
- 如果涉及多个scope，可以置空或用*代替

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