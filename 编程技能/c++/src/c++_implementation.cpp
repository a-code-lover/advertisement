/**
 *基础函数的实现
 *
 */ 
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <algorithm>
#include <climits>
#include <cmath>

using namespace std;

struct Node {
    int value;
    Node * next;
};

class Linklist {

};

// KMP
vector<int> kmpProcess(string s) {
    int size = s.size();
    vector<int> lps(size, 0);
    for (int i = 1, len = 0; i < size; ) {
        if (s[i] == s[len]) {
            lps[i++] = ++len;
        }
        else if (len) len = lps[len - 1];
        else i++;
    }
    return lps;
}

int strstr_kmp(string haystack, string needle) {
    int n = haystack.size(), m = needle.size();
    vector<int> lps = kmpProcess(needle);
    for (int i = 0, j = 0; i < n;) {
        if (j < m && haystack[i] == needle[j]) {
            i++; j++;
        }
        if (j == m) return i - m;
        if (haystack[i] != needle[j]) {
            if (j == 0) i++;
            else j = lps[j - 1];
        }
    }
    return -1;
}

// iterativer for binart tree traverssal
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {};
};
vector<int> inorderTraversal(TreeNode* root) {
    vector<int> inorder;
    if (!root) return inorder;
    TreeNode *cur = root;
    stack<TreeNode *> s;
    while (cur || !s.empty()) {
        while (cur) {
            s.push(cur);
            cur = cur->left;
        }
        // 这里添加一个if(!s.empty)的判断，逻辑会更清晰
        cur = s.top();
        s.pop();
        inorder.push_back(cur->val);
        cur = cur->right;
    }
}
vector<int> preorderTraversal(TreeNode *root) {
  stack<TreeNode*> nodeStack;
  vector<int> res;
  if (!root) return res;
  nodeStack.push(root);
  while (!nodeStack.empty()) {
    TreeNode *cur = nodeStack.top();
    res.push_back(cur->val);
    nodeStack.pop();
    if (cur->right) nodeStack.push(cur->right);
    if (cur->left) nodeStack.push(cur->left);
  }
  return res;
}
void postOrder3(TreeNode *root)     //非递归后序遍历
{
    stack<TreeNode*> s;
    TreeNode *cur;                      //当前结点 
    TreeNode *pre=NULL;                 //前一次访问的结点 
    s.push(root);
    while(!s.empty())
    {
        cur=s.top();
        if((cur->left==NULL&&cur->right==NULL)||
           (pre!=NULL&&(pre==cur->left||pre==cur->right)))
        {
            cout<<cur->val<<" ";  //如果当前结点没有孩子结点或者孩子节点都已被访问过 
              s.pop();
            pre=cur; 
        }
        else
        {
            if(cur->right!=NULL)
                s.push(cur->right);
            if(cur->left!=NULL)    
                s.push(cur->left);
        }
    }    
}

// quick_sort with c++
template<class ForwardIt, class UnaryPredicate>
ForwardIt partition(ForwardIt first, ForwardIt last, UnaryPredicate p)
{
    first = std::find_if_not(first, last, p);
    if (first == last) return first;
 
    for (ForwardIt i = std::next(first); i != last; ++i) {
        if (p(*i)) {
            std::iter_swap(i, first);
            ++first;
        }
    }
    return first;
}

template <class ForwardIt>
void quicksort(ForwardIt first, ForwardIt last)
{
    if(first == last) return;
    auto pivot = *std::next(first, std::distance(first,last)/2);
    ForwardIt middle1 = std::partition(first, last, 
                            [pivot](const auto& em){ return em < pivot; });
    ForwardIt middle2 = std::partition(middle1, last, 
                            [pivot](const auto& em){ return !(pivot < em); });
    quicksort(first, middle1);
    quicksort(middle2, last);
}

// template<class InputIt1, class InputIt2, class OutputIt>
// OutputIt merge(InputIt1 first1, InputIt1 last1,
//                InputIt2 first2, InputIt2 last2,
//                OutputIt d_first)
// {
//     for (; first1 != last1; ++d_first) {
//         if (first2 == last2) {
//             return std::copy(first1, last1, d_first);
//         }
//         if (*first2 < *first1) {
//             *d_first = *first2;
//             ++first2;
//         } else 
//             *d_first = *first1;
//             ++first1;
//         }
//     }
//     return std::copy(first2, last2, d_first);
// }

// template <class ForwardIter, class OutputIter
// void mergeSort(ForwardIter first, ForwardIter last, OutputIter outFirst) {
//     if (first == last) return;
//     auto mid = std::next(first, std::distance(first, last)/2);
//     mergeSort(first, mid);
//     mergeSort(mid+1, last);
//     merge();
// }

// Summary: next_permutaion for array without or without duplication.
// Parameters:
// Return:
bool next_permutation(vector<int> &nums) {
	int i = nums.size() - 1, j = nums.size() - 1;
	for (; i > 0 && nums[i] <= nums[i - 1]; i--);
	if (i == 0) return false;
	for (; j >= 0 && nums[j] <= nums[i - 1]; j--);
	swap(nums[i - 1], nums[j]);
	reverse(nums.begin() + i, nums.end());
	//for (auto elem : nums) cout << elem << " ";
	//cout << endl;
	return true;
}

// Summary: recursion for all subsets of combination.
// Parameters:
// Return:
void all_subset(vector<vector<int>> &res, vector<int> nums, vector<int> &arr, size_t i) {
	if (i == arr.size()) {
		res.push_back(nums);
		return;
	}
	all_subset(res, nums, arr, i + 1);
	nums.push_back(arr[i]);
	all_subset(res, nums, arr, i + 1);
}

// Summary: recursion for permutation without duplication.
// Parameters:
// Return:
// Reference: https://octman.com/blog/2013-10-10-permutation/
void permutation(vector<vector<int>> &res, vector<int> &arr, size_t i) {
	if (i == arr.size() - 1) {
		res.push_back(arr);
	}
	for (size_t j = i; j < arr.size(); j++) {
		swap(arr[i], arr[j]);
		permutation(res, arr, i + 1);
		swap(arr[i], arr[j]);
	}
}

// Summary: Recusion for permutation with duplication.
// Parameters:
// Return:
void permutationUnique(vector<vector<int>> &res, vector<int> &arr, size_t i) {
	if (i == arr.size() - 1) {
		res.push_back(arr);
	}

	auto checkSwapvalid = [=](const vector<int> arr, int idxBegin, int idxEnd)->bool {
		for (int i = idxBegin; i < idxEnd; i++) {
			if (arr[i] == arr[idxEnd]) {
				return false;
			}
		}
		return true;
	};

	for (size_t j = i; j < arr.size(); j++) {
		if (checkSwapvalid(arr, i, j)) {
			swap(arr[i], arr[j]);
			permutation(res, arr, i + 1);
			swap(arr[i], arr[j]);
		}		
	}
}

int main() {
    vector<int> nums = kmpProcess("ababaaaba");

    for (auto item : nums) {
        cout << item << ends;
    }
    cout << endl;
    cin.get();
    cin.get();
    return 0;
}