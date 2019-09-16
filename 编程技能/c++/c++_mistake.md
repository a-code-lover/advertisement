# 错误汇总

## 1

+ sizeof: return the sizes of Byte，size：return the sizes of element，

+ operator []: no array bounds check, the program would crash while running, use at() in class vector would check the bounds while compiling.

+ mind the difference between int []a and int a[]

+ get out_of_range many many times

+ by adding "cout" in some critical points of unsure programs to debug.

+ be concentrated, mistake of a num or letter can cause sevious consumption of debugging time.

+ 变量规范必须初始化，默认初始化会出现问题，如果指针不初始化，那么判断``root == NULL``会为否，但此时root是不可访问的。

+ `vector<int>`做函数参数，传值还是传引用
+ 下标i,j很容易写错

## 2.leetcode mistake

### (1)"variable length array bound evaluates to non-positive value 0"

    without consideration the condition that the size of array is 0.

### (2)"Warning: operation on 'i' may be undefined, -Wsequence-point"

    func(i++)+func1(i),the operation order of two function is undefined, so.

### (3)"CompileError: expected unqualified -id before string constant"

    missing colon after a class definition, missing {} or ()

### (4)"Warning: Comparison between signed and unsigned integer expressions": note that every warning may cause fatal error, syntax warning but logic error

    for (int i = 0; i < s.size() - 1; ++i) {}  
    while s.size() equals to 0, this cause running error.  
    for (int i = 0; (int)i < s.size() - 1; ++i) {}

### (5)"Runtime Error:  access within null pointer of type 'struct ListNode'"

    access data member or function member of a null pointer.

### (6)"CompileError: Line 9: 'bool operator<(const ListNode*, const ListNode*)' must have an argument of class or enumerated type"

### (7)"Runtime Error: double free or corruption (out): 0x00000000011abe70 ***" : <https://www.cnblogs.com/zhenjing/archive/2011/01/26/memory_overwrite.html>

### (8)"Runtime Error: reference binding to null pointer of type 'value_type'"

    accessing to data member of null vector results in error.

### (9)

如果int变量取值INT_MAX那么递增会出错：
`long long i = INT_MAX + 1;` `long long i = (long long)INT_MAX + 1;` `int i = INT_MAX + 1;`
永远不会退出循环：
``for (size_t i = nums.size() - 1; i >= 0; i--) {}``

### (10)实现vector的`next_permutation()`接口，在next_per参数中缺少引用&导致错误。

```c++
bool next_per(vector<int> &nums) { //如果缺少&号，程序死循环
    int i = nums.size() - 1, j = nums.size() - 1;
    for (; i > 0 && nums[i] < nums[i - 1]; i--); //注意有分号和没分号的差别
    if (i == 0) return false;
    for (; j >= 0 && nums[j] < nums[i - 1]; j--);
    swap(nums[i - 1], nums[j]);
    reverse(nums.begin() + i, nums.end());
    //for (auto elem : nums) cout << elem << " ";
    //cout << endl;
    return true;
}

vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> res;
    std::sort(nums.begin(), nums.end());
    do {
        res.push_back(nums);
        for (auto elem : nums) cout << elem << " ";
        cout << endl;
    } while(next_per(nums));
    return res;
}
```

### (11)数据集合(vector, string)动态变化时，迭代器begin(),end()失效，size()的值变化。

## 3.project mistake

&emsp;&emsp;"error C3646:未知重写声明符"：[循环引用，顺序错误，语法错误](https://blog.csdn.net/biubiu741/article/details/54958861)

## 4.使用临时变量构建链表，返回临时变量地址。

&emsp;&emsp; 指针在内存中会分配一个四个字节的内存空间，**内存中的内容是指针所指的地址**，为NULL则存0x00。**函数拷贝指针分配临时四个字节，拷的是指针所指的地址**。

```c++
//merge k sorted lists
bool operator< (const ListNode a, const ListNode b) {
    return a.val > b.val;
}
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        //q内的变量都是拷贝进来的，分配queue的内存，属于临时变量。
        priority_queue<ListNode> q;
        ListNode head(0), *cur = &head;
        for (int i = 0; i < lists.size(); ++i) {
            if (lists[i] != NULL) {
                q.push(*lists[i]);
            }
        }
        while (!q.empty()) {
            //每次分配的tmp地址是一样的，都是q的top地址。
            ListNode tmp = (ListNode)q.top();
            cur->next = &tmp;  
            q.pop();
            cur = &tmp;
            if (tmp.next != NULL) q.push(*tmp.next);
        }
        return head.next;
    }
}；
```

```c++
Node* foo(Node* root, ···) {
    if (root == NULL) {
        root = new Node();  //new 的空间要手动销毁
        return root;
    }
    ···
}
```

## warning

1. [-Wsign-compare](https://stackoverflow.com/questions/3660901/a-warning-comparison-between-signed-and-unsigned-integer-expressions)