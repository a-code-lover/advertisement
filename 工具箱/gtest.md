## 断言

ASSERT_* 系列的断言，当检查点失败时，退出当前函数（注意：并非退出当前案例）。
EXPECT_* 系列的断言，当检查点失败时，继续往下执行。

`EXPECT_EQ(3, Add(1, 2))`

```c++
for (int i = 0; i < x.size(); ++i)
{
    EXPECT_EQ(x[i], y[i]) << "Vectors x and y differ at index " << i;
}
```

类型检查：

+ ASSERT_EQ 
+ ASSERT_NE
+ ASSERT_TRUE
+ ASSERT_FALSE
+ ASSERT_STREQ

+ SUCCEED()
+ FAIL()

## 事件机制

gtest提供了多种事件机制，非常方便我们在案例之前或之后做一些操作。总结一下gtest的事件一共有3种：

1.全局的，所有案例执行前后。
写一个类，继承testing::Environment类，实现里面的SetUp和TearDown方法。

2.TestSuite级别的，在某一批案例中第一个案例前，最后一个案例执行后。
继承testing::Test，然后实现两个静态方法
SetUpTestCase() 方法在第一个TestCase之前执行
TearDownTestCase() 方法在最后一个TestCase之后执行

3.TestCase级别的，每个TestCase前后。
继承testing::Test, 实现里面的SetUp和TearDown方法。