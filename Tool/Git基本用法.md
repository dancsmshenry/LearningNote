#### git常用命令



###### 用户邮箱和用户名设置

- git config --global user.name "username"
- git config --global user.email "useremail"



###### 用户邮箱和用户名查看

- git config --global --list



###### 版本库初始化

- git init
  - 将当前的目录作为可使用的版本库



###### 文件夹切换

- `cd "需要切换文件夹的目录"`



###### 文件夹显示

- `pwd`



###### 文件添加

- 首先是将文件添加到仓库的管辖中
  - git add 文件名+拓展名
  - 可以一次添加多次的文件到仓库中
  - 这里是先把文件添加到暂存区
- 然后是将文件提交到仓库中
  - git commit -m "这里填写本次提交的注释"
  - 可以一次提交很多的文件
  - 这里是把文件添加到版本库



###### 文件删除

- 指令：首先`git rm file`因为虽然在文件夹中的确是删除了该文件，但是如果要在`git`的版本库中删除文件，就用该命令
  - 也可以同时在文件夹中和版本库中删除该文件，然后再`git commit -m ""`提交删除



###### 文件重命名

- 指令：`git mv usedfilername newfilrname`
- 注意：不要直接在文件夹中重命名，否则Git会判定为删除了旧文件，添加了新文件
- 注意：这里的操作后都需要进行一次提交，否则有些操作无法进行下去



###### 文件恢复

- 指令：`git checkout id号 file`文件被误删了，用该命令还原
- 从来没有被添加到版本库就被删除的文件，是无法恢复的！
- 本质是让某一个文件回退到之前的某一个版本



###### 版本回退

- `git reset --hard HEAD^`回退到后几个版本就加上几个^
- git reset --hard 版本号（只要窗口没有被关闭，就可以回退到指定的版本号，版本号不一定要写全）
- 注意版本回退并不代表说版本出现提交，而只是说单纯的回到某个版本
- 是指仓库所有的文件都回退到之前的那个版本



###### 标签添加

- 指令一：`git tag nametag`先转到要打标签的分支，然后再打标签
- 指令二：`git tag -a tagnumber -m tagcomment`先是指明标签版本号，再是指明标签文字内容



###### 标签查看

- git tag(不一定按时间来的)



###### 标签详情

- git show tagname



###### 标签删除

- 指令：`git tag -d tagnumber`



###### 标签推送至远程

- 指令：`git push origin tagname`



###### 标签全部推送至远程

- 指令：`git push origin --tags`



###### 标签的远程删除

- 指令：`git push origin: tagname`



###### 分支合并

- 指令：`git merge branchname`将指定分支合并到当前所在的分支



###### 分支查询

- git branch(当前的分支会显示有星号*)



###### 分支删除

- git branch -d pointname



###### 分支创建

- git branch pointname（前提是该分支已经被合并了，然后才删除）
- git branch -D pointname（分支开发完成，但是忽然不要了，也没有合并，所以就用这个指令强制删除，小d是普通删除）



###### 分支切换

- git checkout 分支名
- git switch -c 分支名
  - 特例：git switch master



###### 分支创建并切换

- 指令：`git checkout -b pointname`
  - 等价于：
    - git branch dev
    - git checkout dev
- 指令二：`git switch -c branchname`



###### 远程仓库克隆

- 指令：`git clone storeaddress`



###### 查看仓库中所有文件的情况

- git status
  - 获取当前仓库的状态



###### 查看仓库中某个文件的情况

- git diff 文件名	



###### 查看总共提交的日志

- git log（从近到远）
- git log --pretty=oneline 可以将日志简写，便捷显示
  - 输出的一串乱码是版本号



###### 查看分支合并情况

- git log --graph



###### 查看所有分支的操作记录

- git reflog



###### 撤销暂存区的修改

- git reset HEAD 文件名（即文件写错了，提交到了暂存区里面，但是还没有提交到版本库当中，就可以用这个指令撤销修改）
  - 把已经提交到暂存区的修改撤销掉，重新放回工作区
- 指令二：`git checkout -- file`
  - 两种情况：
    - 文件被修改后但是还没被放入暂存区，即还在工作区，则把文件撤销到版本库的状态
    - 文件被添加到暂存区后，又发生了修改，则把文件撤销到文件被添加到暂存区后的状态







#### git常见概念



###### 工作区

平常看得到的文件夹里的文件



###### 暂存区

就是git add之后会先把文件放到这个暂存区里面，然后通过git commit一起统一提交



###### 版本库

- 即记录了git仓库的每个不同的版本的内容异同以及版本号
- 这里有一个问题，就是如果切换了分支，那么工作区的变化又是什么呢？？
- 出现了，实际文件的修改就是实际文件的修改（即git做什么都不会改变当前的文件的内容和状态），但是如果先修改，提交到暂存区，然后再修改却没有放到暂存区，那么接着提交到仓库的内容就是只有第一次修改的内容
- 说明了git是追踪每次的已经提交到暂存区的修改的



###### 分支冲突

- 合并的时候发现不同分支的内容发生了冲突，这时候需要手动修改内容并提交（add和commit）







#### git和vscode的混合使用



- https://blog.csdn.net/m0_46548070/article/details/105116420
  - 即每次的修改都要先提交代码，然后再推送到GitHub上

- vscode改不了以及提交了的分支的名字
- 带origin的是远程仓库（github上的）分支，其他的是本地的分支
- vscode左下角切换分支.........大无语事件







#### git其他的常用配置



- 切换git常用（默认打开）目录
  - https://www.cnblogs.com/wangxiaoqun/p/12331214.html
- github分支的合并
  - https://blog.csdn.net/qq_30607843/article/details/84404000
  - github合并的时候，是将右边框的数据合并到左边框的数据里面的
  - 合并以后还有再在上面的页面里面点一个确定，然后再销毁原来的分支
- linux，vscode，c++配置
  - https://blog.csdn.net/weixin_43956456/article/details/105674295







#### git的其他操作

- 合并分支时，加上`--no-ff`参数就可以用普通模式合并，合并后的历史有分支，能看出来曾经做过合并，而`fast forward`合并就看不出来曾经做过合并。