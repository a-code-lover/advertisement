# 刷题汇总

## 性能分析

```c++
int x=[](){
    std::ios::sync_with_stdio(false);  //关闭STDIN和CIN同步 减少CIN读入的时间，可以减少50%以上。
    cin.tie(NULL);
    return 0;
}();
```

## summary

1. [二分查找](https://octman.com/blog/2013-09-27-binary-search-and-variants/)

2. [排列组合](https://octman.com/blog/2013-10-10-permutation/)

3. [树遍历查找](https://octman.com/blog/2013-10-20-note-tree-traverse-nonrecursive/)

4. 字符串匹配

5. [随机数问题]  
   <https://octman.com/blog/2013-10-20-interview-questions-random-numbers/>
   <https:/****/blog.csdn.net/jinzhao1993/article/details/69056135b>

## 4. median of two sorted array(二分查找)

+ <https://octman.com/blog/2013-09-27-binary-search-and-variants/>  
+ <https://blog.csdn.net/yutianzuijin/article/details/11499917>

## 5.LPS

思路：二维dp, brutal

## 10. regular expression matchming

思路：二维dp，双指针

## 22.generate parenthesis

思路：递归或迭代

## 23.merge k sorted lists

思路：1. priority_queue(不够熟练)  2. incursive, merge 2 to merge n

## 28.implement strstr

<https://leetcode.com/problems/implement-strstr/discuss/12956/Explained-4ms-Easy-C++-solution>  
思路：1. brutal  2.kmp

## 29.divide two integer

思路：不能使用乘除求余运算，因此使用位运算，左移运算 + 符号。

## 33.search in rotated sorted array

思路：binary search， mid and realmid(clever idea).

## 49.group anagrams

思路：prime number

## all. 排列组合问题

<https://octman.com/blog/2013-10-10-permutation/>

## all. substring 问题

<https://leetcode.com/problems/minimum-window-substring/discuss/26808/Here-is-a-10-line-template-that-can-solve-most-'substring'-problems>

<details>
<summary>findSubstring</summary>

```c++
int findSubstring(string s){
    vector<int> map(128,0);
    int counter; // check whether the substring is valid
    int begin=0, end=0; //two pointers, one point to tail and one  head
    int d; //the length of substring

    for() { /* initialize the hash map here */ }

    while(end<s.size()){

        if(map[s[end++]]-- ?){  /* modify counter here */ }

        while(/* counter condition */){

            /* update d here if finding minimum*/

            //increase begin to make it invalid/valid again

            if(map[s[begin++]]++ ?){ /*modify counter here*/ }
        }  

        /* update d here if finding maximum*/
    }
    return d;
}
```

</details>

## 79.word search

思路：bfs

## 91.decode ways

思路：iterative, (recursive search from back to front?)

## 94.binaty tree inorder traversal

思路：use iterative instead of recursive.
注：递归和迭代的运行时间是一样的，只是递归用到系统内存的栈，迭代使用数据结构的栈。

## all. use iterative to deal with binary tree

## 121. best time to sell stocks

思路： dp

## 124. binary tree maximum path sum

## 134. gas station can complete circle

## 最小圆覆盖

平面上有n个点，给定n个点的坐标，试找一个半径最小的圆，将n个点全部包围，点可以在圆上, 这个圆叫最小包围圆, 求出求出这个圆的圆心坐标和半径。

## [647.palidrome substring](https://leetcode.com/problems/palindromic-substrings/discuss/105698/5-lines-C%2B%2B-solution-that-beats-80%2B)

[正则表达式应用](https://leetcode.com/problems/evaluate-reverse-polish-notation/discuss/47514/Fancy-C%2B%2B-lambda-expression-solution)

c++语法：switch参数只能取基本类型和enum,不能是string等复杂类型。

max point on a line

numeric_limits

[sort list](https://leetcode.com/submissions/detail/187960592/)
参考答案简洁
[reorderList](https://leetcode.com/problems/reorder-list/)
[linked list circle](https://leetcode.com/problems/linked-list-cycle-ii/)

[**word break 2](https://leetcode.com/problems/word-break-ii/)
[word break](https://leetcode.com/problems/word-break/)
[copy list with random pointer](https://leetcode.com/problems/copy-list-with-random-pointer/)
[clone graph](https://leetcode.com/problems/clone-graph/)
[candy](https://leetcode.com/problems/candy/)
[gas station](https://leetcode.com/problems/gas-station/)
[palindrome partition](https://leetcode.com/problems/palindrome-partitioning/)
[longest consecutive sequence](https://leetcode.com/problems/longest-consecutive-sequence/discuss/41088/Possibly-shortest-cpp-solution-only-6-lines.)
[binary-tree-maximum-path](https://leetcode.com/problems/binary-tree-maximum-path-sum/)
[distinct sequence](https://leetcode.com/problems/distinct-subsequences/)
[**distinct sequence ii](https://leetcode.com/problems/distinct-subsequences-ii/)
[path sum ii](https://leetcode.com/problems/path-sum-ii/discuss/36683/DFS-with-one-LinkedList-accepted-java-solution)
[balanced binary tree](https://leetcode.com/problems/balanced-binary-tree/)

### bit manipulate

single number 1,2,3
n & (~(n - 1)) ： 取第一位的1

palindrome problem
[palindrome partition](https://leetcode.com/problems/palindrome-partitioning/)

分割问题如word break, palindrome partition：dfs+backtrack，dp

光看答案没有用的，一定要动手写。

20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38

surrounded region 未解决

[longest consecutive sequence](https://leetcode.com/problems/longest-consecutive-sequence/discuss/41088/Possibly-shortest-cpp-solution-only-6-lines.)

word problem

backtrack效率太低经常超时

word ladder

isalpha, isalnum, toupper, tolower, isdigit, isspace, isblank, islower, isupper

distinct sequence:递归dp，迭代dp。

[dfs和backtrack的区别](https://www.cnblogs.com/ganganloveu/p/4188131.html)
[get rid of TLE](https://leetcode.com/problems/word-break-ii/discuss/44185/Getting-rid-of-TLE)

```java
//binary tree maximum path
public class Solution {
    int maxValue;

    public int maxPathSum(TreeNode root) {
        maxValue = Integer.MIN_VALUE;
        maxPathDown(root);
        return maxValue;
    }

    private int maxPathDown(TreeNode node) {
        if (node == null) return 0;
        int left = Math.max(0, maxPathDown(node.left));
        int right = Math.max(0, maxPathDown(node.right));
        maxValue = Math.max(maxValue, left + right + node.val);
        return Math.max(left, right) + node.val;
    }
}
```

```c++
//找到linklist中点
  ListNode *slow = head, *fast = head, *pre = slow;
  while (fast && fast->next) {
    pre = slow;
    slow = slow->next;
    fast = fast->next->next;
  }
```

```c++
//典型回溯，path sum ii
class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int> > paths;
        vector<int> path;
        findPaths(root, sum, path, paths);
        return paths;  
    }
private:
    void findPaths(TreeNode* node, int sum, vector<int>& path, vector<vector<int> >& paths) {
        if (!node) return;
        path.push_back(node -> val);
        if (!(node -> left) && !(node -> right) && sum == node -> val)
            paths.push_back(path);
        findPaths(node -> left, sum - node -> val, path, paths);
        findPaths(node -> right, sum - node -> val, path, paths);
        path.pop_back();
    }
};
```