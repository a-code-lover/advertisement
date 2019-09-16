### DDL,DML,DCL

data definition language：用于定义数据库的三个级别，定义数据的完整性、安全控制等约束，如：`create`,`alter`,`drop`,`truncate`,`rename`

data manipulation language：有DBMS提供让用户或程序员使用。

data control language：`grant`,`revoke`

### 基本查询

基本查询，条件查询，投影查询，排序，分页查询，聚合查询，多表查询，连接查询
`LIKE`：判断相似，`ORDER BY`：排序，`DESC`：降序
`LIMIT<pagesize>OFFSET<n>`：分页，
聚合函数：`COUNT` `SUM` `AVG` `MAX` `MIN`
`group by`：分组
设置列别名
join：将其他表的行有选择地连接到主表的查询结果上，`INNER JOIN ON`：交集
`RIGHT/LEFT/FULL OUTER JOIN`：交并
`having`：筛选分组后的数据
`in`：值在集合中
`between`
`union`：纵向合并
`exists`

顺序：`select [] from [] wherer [] group by [] having [] order by[] limit []`

### 基本修改

增删改查：crud(create，retreive， update， delete)

`INSERT INTO <表名> (字段1, 字段2, ...) VALUES (值1, 值2, ...);`
`INSERT INTO students (class_id, name, gender, score) VALUES(1, '大宝', 'M', 87),(2, '二宝', 'M', 81)`
`INSERT INTO, REPLACE INTO, INSERT IGNORE`
`UPDATE <表名> SET 字段1=值1, 字段2=值2, ... WHERE ...;`
`DELETE FROM <表名> WHERE ...;`

### 管理数据库

`show databases;` `create database name;` `drop database name;` `use database;`
`show tables;` `DESC tablename;`：查看表结构 `show create table tablename;`：显示怎样创建表
`ALTER TABLE ... ADD/DROP/CHANGE COLUMN ... VARCHAR(10) NOT NULL;`
create table + select：创建快照

### 基本例子

```sql
UPDATE salary SET sex  = (CASE WHEN sex = 'm'
        THEN  'f'
        ELSE 'm'
        END);
UPDATE salary SET sex = IF(sex = 'm', 'f', 'm');

select * from cinema where id % 2 = 1 and description != "boring" order by rating DESC;

select E1.Name
from Employee as E1, Employee as E2
where E1.ManagerId = E2.Id and E1.Salary > E2.Salary;

# leetcode183
select c.Name from Customers c
where c.Id not in (select customerId from Orders)

select c.Name from Customers c
where (select count(*) from Orders o where o.customerId=c.id)=0

select c.Name from Customers c
where not exists (select * from Orders o where o.customerId=c.id)

# fuck，要错多少次才能记住`join...on`
SELECT Person.FirstName, Person.LastName, Address.City, Address.State from Person LEFT JOIN Address on Person.PersonId = Address.PersonId;

CREATE FUNCTION getNthHighestSalary(N INT) RETURNS INT
BEGIN
DECLARE M INT;
SET M=n-1;
  RETURN (
      # Write your MySQL query statement below.
      SELECT DISTINCT Salary FROM Employee ORDER BY Salary DESC limit M,1
  );
END

```

### drop,delete,truncate

+ drop删表，删除内容如结构，释放空间，没有备份表之前慎用；
+ truncate：删除表的内容，并释放空间，但不删除表的定义，表的结构还在，不可恢复；
+ delete：每次删除一行，并将操作记录到事务日志以便回滚；删除表的内容，不释放空间，保留表的定义；

### limit,offset

+ limit N : 返回 N 条记录
+ offset M : 跳过 M 条记录, 默认 M=0, 单独使用似乎不起作用
+ limit N,M : 相当于 limit M offset N , 从第 N 条记录开始, 返回 M 条记录

### mysql实现rank排序

参考：<https://www.jianshu.com/p/bb1b72a1623e>