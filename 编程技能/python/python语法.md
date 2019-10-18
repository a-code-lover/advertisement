https://www.zhihu.com/question/20702054     你是如何自学python的？
https://www.anaconda.com/      python集成安装

语法特点总结：块缩进，弱类型，解释语言，def function，列表[]元组()字典{}，

1.三引号：三引号中可以自由使用单引号和双引号，双引号中可以使用单引号，字符串前加r忽略转义字符，加 u（unicode），自动级联，没有char，单引号和双引号等价。
Microsoft建议对于简单的命名用camelCase，对于复杂的命名用PacalCase。
    
2.#!/usr/bin/python           （注释说明使用哪个解释器）
# Filename : helloworld.py   （文件名）
print（ 'Hello World'）;     print('Area is',area)  is后自动添加一个空格
3.对于Python来说，程序、脚本或者软件都是指同一个东西。命名不能用关键字，避免冲突。

4.help（）帮助，q退出

5.52.3E-4表示52.3 * 10-4，(-5+4j)和(2.3-4.6j)是复数的例子

6.i=5 变量不需要定义类型或声明
Range()函数：http://www.cnblogs.com/buro79xxd/archive/2011/05/23/2054493.html
  
7.一般一个物理行对应一个逻辑行，多个物理行对一个逻辑行时使用'\'（默认连接如括号可以不用）
   使用空格作为缩进，同一层次的语句要有同样的缩进

8.不要混合使用制表符和空格来缩进，因为这在跨越不同的平台的时候，无法正常工作。我 强烈建议 你在每个缩进层次使用 单个制表符 或 两个或四个空格 。选择这三种缩进风格之一。更加重要的是，选择一种风格，然后一贯地使用它，即 只 使用这一种风格。（对于不同的编辑器tab对应的空格不一样）

10.#一般作为注释标志

11.python没有switch，while循环可带一个else（区别在于break跳出）
#!/usr/bin/python
# Filename: if.py
number = 23
guess = int(raw_input('Enter an integer : '))   输入字符串转化为整型raw_input
if guess == number:                                     冒号表明接下来是一个程序块，len( )函数
     print 'Congratulations, you guessed it.' # New block starts here
     print "(but you do not win any prizes!)" # New block ends here
elif guess < number:
     print 'No, it is a little higher than that' # Another block
# You can do whatever you want in a block ...
else:
     print 'No, it is a little lower than that'
# you must have guess > number to reach here

#!/usr/bin/python
# Filename: for.py
for i in range(1, 5):   取值1-4 [1,2,3,4]    range(1,5,2) [1,3]
     print i                 自动回车
else:
     print 'The for loop is over'

12.
def func():
     global x                             #global全局变量
     print 'x is', x
     x = 2
     print 'Changed local x to', x
x = 50
func()
print 'Value of x is', x             #x=2

def say(message, times = 1):     #等号做默认值，默认值必须在形参尾部
     print message *  times     
say('Hello')     #输出一次Hello
say('World', 5)    #输出五次World

13.
例7.6 使用关键参数
#!/usr/bin/python
# Filename: func_key.py
def func(a, b=5, c=10):
print 'a is', a, 'and b is', b, 'and c is', c
func(3, 7)
func(25, c=24)
func(c=50, a=100)

def maximum(x, y):  #如果自己没有return，每个函数末有默认的return None，None是没有任何东西的类型
     if x > y:
          return x
     else:
          return y

def someFunction():
     pass             #pass是空的语句块

14.DocStrings
def printMax(x, y):
     '''Prints the maximum of two numbers.

     The two values must be integers.'''
     x = int(x) # convert to integers, if possible
     y = int(y)
     if x > y:
          print x, 'is maximum'
     else:
          print y, 'is maximum'
printMax(3, 5)
print printMax.__doc__             #DocStrings类似参考文档，即使help（）显示的内容，函数首个逻辑行，第1行总，第2行空，第3行开始详述
                                               #__xxxx__类似的为模块标志
15.列表：
shoplist = ['apple', 'mango', 'carrot', 'banana']
for item in shoplist:
     print item,           #逗号取消换行，带空格， 输出apple mango carrot banana
shoplist.append('rice')
shoplist.sort()
olditem = shoplist[0]
de
l shoplist[0]
print 'My shopping list is now', shoplist            #带符号输出，['','','','']

元组：元素不可变
zoo = ('wolf', 'elephant', 'penguin')     #len=3
new_zoo = ('monkey', 'dolphin', zoo)     #len=3
print 'Animals brought from old zoo are', new_zoo[2]
print 'Last animal brought from old zoo is', new_zoo[2][2]
含有0个或1个项目的元组。一个空的元组由一对空的圆括号组成，如myempty = ()。然而，含有单个元素的元组就不那么简单了。你必须在第一个（唯一一个）项目后跟一个逗号，这样Python才能区分元组和表达式中一个带圆括号的对象。即如果你想要的是一个包含项目2的元组的时候，你应该指明singleton = (2 , )。

元组作为输出：
age = 22
name = 'Swaroop'
print '%s is %d years old' % (name, age)
print 'Why is %s playing with that python?' % name


字典：
# 'ab' is short for 'a'ddress'b'ook

ab = { 'Swaroop' : 'swaroopch@byteofpython.info',
'Larry' : 'larry@wall.org',
'Matsumoto' : 'matz@ruby-lang.org',
'Spammer' : 'spammer@hotmail.com'
}

print "Swaroop's address is %s" % ab['Swaroop']
# Adding a key/value pair
ab['Guido'] = 'guido@python.org'
# Deleting a key/value pair
del ab['Spammer']
print '\nThere are %d contacts in the address-book\n' % len(ab)
for name, address in ab.items():     
#我们使用字典的items方法，来使用字典中的每个键/值对。这会返回一个元组的列表，其中每个元组都包含一对项目——键与对应的值。
     print 'Contact %s at %s' % (name, address)
if 'Guido' in ab: # OR ab.has_key('Guido')
     print "\nGuido's address is %s" % ab['Guido']

16.序列：
列表(list)、元组(tuple)和字符串(string)都是序列，序列的两个主要特点是索引操作符和切片操作符。索引操作符让我们可以从序列中抓取一个特定项目。切片操作符让我们能够获取序列的一个切片，即一部分序列。
shoplist = ['apple', 'mango', 'carrot', 'banana']
# Indexing or 'Subscription' operation
print 'Item 0 is', shoplist[0]
print 'Item 1 is', shoplist[1]
print 'Item 2 is', shoplist[2]
print 'Item 3 is', shoplist[3]
print 'Item -1 is', shoplist[-1]     #banana
print 'Item -2 is', shoplist[-2]     #carrot
# Slicing on a list
print 'Item 1 to 3 is', shoplist[1:3]
print 'Item 2 to end is', shoplist[2:]
print 'Item 1 to -1 is', shoplist[1:-1]
print 'Item start to end is', shoplist[:]
# Slicing on a string
name = 'swaroop'
print 'characters 1 to 3 is', name[1:3]
print 'characters 2 to end is', name[2:]
print 'characters 1 to -1 is', name[1:-1]
print 'characters start to end is', name[:]
#负数用在从序列尾开始计算的位置。例如，shoplist[:-1]会返回除了最后一个项目外包含所有项目的序列切片。

17.引用
shoplist = ['apple', 'mango', 'carrot', 'banana']
mylist = shoplist # mylist is just another name pointing to the same object!
del shoplist[0]
print 'shoplist is', shoplist            #都是后三个元素
print 'mylist is', mylist
# notice that both shoplist and mylist both print the same list without
# the 'apple' confirming that they point to the same object
print 'Copy by making a full slice'
mylist = shoplist[:] # make a copy by doing a full slice
del mylist[0] # remove first item
print 'shoplist is', shoplist      #三个元素
print 'mylist is', mylist           #两个元素
# notice that now the two lists are different

18.字符串扩展
name = 'Swaroop' # This is a string object
if name.startswith('Swa'):
     print 'Yes, the string starts with "Swa"'
if 'a' in name:
     print 'Yes, it contains the string "a"'
if name.find('war') != -1:
     print 'Yes, it contains the string "war"'
delimiter = '_*_'
mylist = ['Brazil', 'Russia', 'India', 'China']
print delimiter.join(mylist)      #结果Brazil_*_Russia_*_India_*_China

19.备份脚本
import os
import time
# 1. The files and directories to be backed up are specified in a list.
source = ['/home/swaroop/byte', '/home/swaroop/bin']
# If you are using Windows, use source = [r'C:\Documents', r'D:\Work'] or something like that       #r取消转义
# 2. The backup must be stored in a main backup directory
target_dir = '/mnt/e/backup/' # Remember to change this to what you will be using
# 3. The files are backed up into a zip file.
# 4. The current day is the name of the subdirectory in the main directory
today = target_dir + time.strftime('%Y%m%d')                #获取时间20140408
# The current time is the name of the zip archive
now = time.strftime('%H%M%S')
# Take a comment from the user to create the name of the zip file
comment = raw_input('Enter a comment --> ')
if len(comment) == 0: # check if a comment was entered
target = today + os.sep + now + '.zip'                            #自动分隔符，win为\，linux为/，mac为：
else:
target = today + os.sep + now + '_' + \
comment.replace(' ', '_') + '.zip'
# Notice the backslash!
# Create the subdirectory if it isn't already there
if not os.path.exists(today):
os.mkdir(today) # make directory
print 'Successfully created directory', today
# 5. We use the zip command (in Unix/Linux) to put the files in a zip archive
zip_command = "zip -qr '%s' %s" % (target, ' '.join(source))
# Run the backup
if os.system(zip_command) == 0:
print 'Successful backup to', target
else:
print 'Backup FAILED'

20.面向对象：域（分为实例变量和类变量）和方法可以合称为类的属性。
class Person:     
     def __init__(self, name):    #初始化函数，(__del__)自动调用，也可手动调用
#类的方法与普通的函数只有一个特别的区别——它们必须有一个额外的第一个参数名称，但在调用这个方法你不为这个参数赋值，Python会提供这个值。                                                  
          self.name = name                                                
     def sayHi(self):
          print 'Hello, my name is', self.name
p = Person('Karl')
p.sayHi()
Python中的self等价于C++中的self指针和Java、C#中的this参考。你一定很奇怪Python如何给self赋值以及为何你不需要给它赋值。举一个例子会使此变得清晰。假如你有一个类称为MyClass和这个类的一个实例MyObject。当你调用这个对象的方法MyObject.method(arg1, arg2)的时候，这会由Python自动转为MyClass.method(MyObject, arg1,arg2)——这就是self的原理了。这也意味着如果你有一个不需要参数的方法，你还是得给这个方法定义一个self参数。

Python中所有的类成员（包括数据成员）都是 公共的 ，所有的方法都是 有效的 。只有一个例外：如果你使用的数据成员名称以 双下划线前缀 比如__privatevar，Python的名称管理体系会有效地把它作为私有变量。


21.继承：继承完全可以理解成类之间的 类型（父类，超类）和子类型 关系。一个子类型在任何需要父类型的场合可以被替换成父类型，即对象可以被视作是父类的实例，这种现象被称为多态现象。
class SchoolMember:
     '''Represents any school member.'''
     def __init__(self, name, age):
          self.name = name
          self.age = age
          print '(Initialized SchoolMember: %s)' % self.name
     def tell(self):
          '''Tell my details.'''
          print 'Name:"%s" Age:"%s"' % (self.name, self.age),
class Teacher(SchoolMember):     #多个父类即是多重继承
     '''Represents a teacher.'''
     def __init__(self, name, age, salary):
          SchoolMember.__init__(self, name, age)  #Python不会自动调用基本类的constructor，你得亲自专门调用它。
          self.salary = salary
          print '(Initialized Teacher: %s)' % self.name
     def tell(self):
          SchoolMember.tell(self)
          print 'Salary: "%d"' % self.salary
class Student(SchoolMember):
     '''Represents a student.'''
     def __init__(self, name, age, marks):
          SchoolMember.__init__(self, name, age)
          self.marks = marks
          print '(Initialized Student: %s)' % self.name
     def tell(self):
          SchoolMember.tell(self)
          print 'Marks: "%d"' % self.marks
t = Teacher('Mrs. Shrividya', 40, 30000)
s = Student('Swaroop', 22, 75)
print # prints a blank line
members = [t, s]
for member in members:
     member.tell() # works for both Teachers and Students

22.文件
poem ="love you more than i can say"
f = open('poem.txt', 'w') # open for 'w'riting
f.write(poem) # write text to file
f.close() # close the file
f = open('poem.txt')           #默认为r
# if no mode is specified, 'r'ead mode is assumed by default
while True:
     line = f.readline()    #read,readline,readlines(一次存为list),当文件过大时直接read会内存爆炸
     if len(line) == 0: # Zero length indicates EOF
          break
     print line,            #readline()读取一行返回带有换行符，所有加逗号
# Notice comma to avoid automatic newline added by Python
f.close() # close the file

存储器：
import cPickle as p                             #cPickle在3.x中移除了,用pickle代替
shoplistfile = 'shoplist.data'
shoplist = ['apple', 'mango', 'carrot']
f = open(shoplistfile, 'w')
p.dump(shoplist, f) # dump the object to a file
f.close()
f = file(shoplistfile)
storedlist = p.load(f)
print storedlist

23. if __name__ ==  '__main__'   http://blog.konghy.cn/2017/04/24/python-entry-program/

24.lambda    http://www.cnblogs.com/evening/archive/2012/03/29/2423554.html
     sort  sorted排序    http://www.runoob.com/python/python-func-sorted.html

25.一行写不下： 空格\ 

26.str(list) 直接转换为字符串