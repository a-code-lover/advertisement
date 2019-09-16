---
toc:
  depth_from: 1
  depth_to: 6
  ordered: false
---

# 基础

Git 自带一个**git config**的工具来帮助设置控制 Git 外观和行为的配置变量。 这些变量存储在三个不同的位置：

1. /etc/gitconfig 文件: 包含系统上每一个用户及他们仓库的通用配置。 如果使用带有 --system 选项的 git config 时，它会从此文件读写配置变量。
2. ~/.gitconfig 或 ~/.config/git/config 文件：只针对当前用户。 可以传递 --global 选项让 Git 读写此文件。
3. 当前使用仓库的 Git 目录中的 config 文件（就是 .git/config）：针对该仓库。

.gitignore文件声明git忽略的文件。

git status -s

git commit -a -m

git diff --cached

git rm --cached

git mv from to

git log -p --stat --pretty=oneline

简单撤销：
git commit --amend
git reset HEAD test.md 撤销暂存
git checkout -- test.md 撤销对文件的修改 

git diff --check 检查多余空格

### git commit回退

git log
git reflog
git reset --soft HAEAD^（回退到commit的前一个版本）
git reset --hard HEAD~2（撤销commit和add到前两个版本）
git commit ammend（修改注释）
git reset 旧标志
git checkout 版本

+ `--soft`：只撤销commit，不撤销add，不删除工作空间的修改代码
+ `--mixed`：只撤销commit和add，不删除工作空间的修改代码
+ `--hard`：撤销commit和add，并删除工作空间的修改代码

### git切换https和ssh协议

git remote -v
git remote set-url --delete https://xxx.git
git remote set-url --add git@github.com:XXX.git
fatal:已经commit的无法修改，必须回退后修改

### git remote

git remote / git remote -v
git remote add <shortname> <url>
git remote rm <shortname>
git remote rename <oldname> <newname>
git push <shortname> <branchname> 自动merge跟踪,先pull后merge
git pull 自动跟踪
git fetch <remotename> 手动merge

origin是你克隆远程仓库的默认名字。
master是git init默认生成的分支名，和其他分支是一样的。

### tag

git tag -a v1.2 -m "new edition"
git tag -d v1.2
git tag
git show v1.2
git checkout -b <newbranch> v1.2
git push origin v1.2
git push origin --tags

### branch

HEAD指向当前分支的指针，用星号标志。
git log --oneline --decorate(显示head) --graph --all
git branch <newbranch>
git checkout <branch>
git checkout -b <branch> 等同于branch和checkout两个命令。

git merge <newbranch>
git branch -d <newbranch>
git branch -v
git branch --merged 显示合并的分支 --no-merged 未合并分支

分支开发：长期稳定分支和特性分支

本地有master指针和origin/master指针，在执行git fetch origin时拉取本地数据库没有的数据，并移动origin/master到最新的位置。

跟踪分支：clone时自动创建了origin/master的跟踪分支master。
显示声明跟踪：
git checkout --track origin/serverfix   
git checkout --track sf origin/serverfix 改名
git branch -vv 查看

删除远程分支：
git push origin --delete serverfix
        
### 协议

本地协议：使用共享文件系统。
https：可用性，http/s被广泛使用，一般企业防火墙都会运行这些端口的数据通过。
ssh：安全，所有传输都需要授权和加密，不能匿名访问，一般公司网络是唯一用到这个。
git：快，不需要任何授权。

### 贡献维护

1.git diff --check 检查可能的空白错误。
2.分多次小的提交，避免提交一次巨大的提交。
3.优质的提交信息。

<!-- @import "[TOC]" {cmd="toc" depthFrom=1 depthTo=6 orderedList=false} -->
