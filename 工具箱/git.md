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