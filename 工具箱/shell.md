
### source filename与sh filename及./filename执行脚本的区别

<https://blog.csdn.net/violet_echo_0908/article/details/52056071>

### 操作符与运算

使用分号分割命令
使用反斜杠换行拼接

$#	传递到脚本的参数个数
$*	以一个单字符串显示所有向脚本传递的参数
$$	脚本运行的当前进程ID号
$!	后台运行的最后一个进程的ID号
$@	与$*相同，但是使用时加引号，并在引号中返回每个参数。
$-	显示Shell使用的当前选项，与set命令功能相同。
$?	显示最后命令的退出状态。0表示没有错误，其他任何值表明有错误。

echo "数组的元素为: ${my_array[*]}"
echo "数组的元素为: ${my_array[@]}"
echo "数组元素个数为: ${#my_array[*]}"
echo "数组元素个数为: ${#my_array[@]}"
${#string}

相等：`[ $a = $b ]` 返回 false。
不等：`[ $a != $b ]` 返回 true。
长度为0：`[ -z $a ]` 返回 false。
长度不为0：`[ -n "$a" ]` 返回 true。
为空：`[ $a ]` 返回 true。

布尔：`！ -o -a`
关系：`-eq -ne -gt -lt -ge -le`

-b file	检测文件是否是块设备文件，
-c file	检测文件是否是字符设备文件，
-d file	检测文件是否是目录，
-f file	检测文件是否是普通文件（既不是目录，也不是设备文件），
-g file	检测文件是否设置了 SGID 位，
-k file	检测文件是否设置了粘着位(Sticky Bit)，
-p file	检测文件是否是有名管道，
-u file	检测文件是否设置了 SUID 位，
-r file	检测文件是否可读，
-w file	检测文件是否可写，
-x file	检测文件是否可执行，
-s file	检测文件是否为空（文件大小是否大于0）,
-e file	检测文件（包括目录）是否存在.

echo -e "OK! \c" # -e 开启转义 \c 不换行
echo `date` 这里使用的是反引号`, 而不是单引号'
printf "%-10s %-8s %-4.2f\n" 郭靖 男 66.1234

```bash
[ function ] funname [()]
{
    action;
    [return int;]
}
```

n >& m	将输出文件 m 和 n 合并。
n <& m	将输入文件 m 和 n 合并。
需要注意的是文件描述符 0 通常是标准输入（STDIN），1 是标准输出（STDOUT），2 是标准错误输出（STDERR）。

`command > file 2>&1`
wc -l << EOF 
[EOF使用](https://blog.csdn.net/zongshi1992/article/details/71693045)

`. filename`   #注意点号(.)和文件名中间有一空格
或 `source filename`

### path

%HOMEPATH%
%USERPROFILE%
%WINDIR%
%TEMP%

在cmd窗口中set设置的环境变量为临时变量，如：
set PATH=%PATH%;D:\Program Files\
使用setx设置为永久环境变量,适用于bat中：
setx PATH "%PATH%;D:\Program Files\"