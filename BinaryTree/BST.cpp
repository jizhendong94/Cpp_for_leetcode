/*230 二叉搜索树中第k小的元素

  给定一个二叉搜索树的根节点 root ，和一个整数 k ，
  请你设计一个算法查找其中第 k 个最小元素（从 1 开始计数）。
 */


void helper(TreeNode* root,vector<int>& res)
{
	if(root == NULL) return ;
	helper(root->left,res);
	res.push_back(root->val);
	helper(root->right,res);
}
int kthSmallest(TreeNode* root, int k) {
	vector<int>res;
	helper(root,res);
	return res[k-1];
}



int res = 0 ;
int rank = 0;

void traverse(TreeNode* root,int k)
{
	if(NULL == root) return;
	traverse(root->left,k);
	rank++;
	if(k == rank){
		res = root->val;
		return;
	}
	traverse(root->right,k);
}

int kthSmallest(TreeNode* root,int k)
{
	traverse(root,k);
	return res;
}

/*538 二叉搜索树 转化为累加树
  给出二叉 搜索 树的根节点，该树的节点值各不相同，请你将其转换为累加树（Greater Sum Tree），
  使每个节点 node 的新值等于原树中大于或等于 node.val 的值之和。


  提醒一下，二叉搜索树满足下列约束条件：
  节点的左子树仅包含键 小于 节点键的节点。
  节点的右子树仅包含键 大于 节点键的节点。
  左右子树也必须是二叉搜索树。
 */

int sum = 0;
void traverse(TreeNode* root)
{
	if(NULL == root) return;
	traverse(root->right);
	sum +=root->val;
	root->val = sum;
	traverse(root->left);
}
TreeNode* convertBST(TreeNode* root) {
	traverse(root);
	return root;
}


/*BST的合法性  


*/
//限定以 root 为根的子树节点必须满足 max.val > root.val > min.val
bool isValidBST(TreeNode* root,TreeNode* min,TreeNode* max)
{
	//base case
	if(NULL == root) return true;
	//若 root.val 不符合 max 和 min 的限制，说明不是合法 BST
	if(min!=NULL&&root->val<=min->val) return false;
	if(max!=NULL&&root->val>=max->val) return false;
	//限定左子树的最大值是 root.val，右子树的最小值是 root.val
	return isValidBST(root->left,min,root)&&isValidBST(root->right,root,max);
}

bool isValidBST(TreeNode* root)
{
	return isValidBST(root,NULL,NULL);
}

/* 二叉树 中寻找元素

*/
bool isInBST(TreeNode* root,int target)
{
	if(NULL == root) return false;
	if(target == root->val ) return true;
	//当前节点没有找到，就递归的去左右子树寻找
	return isInBST(root->left,target)||isInBST(root->right,target);
}

//二叉搜索树种寻找元素
bool isInBST(TreeNode* root,int target)
{
	if(NULL == root) return false;
	if(target == root->val) return true;
	if(root->val < target)
		return isInBST(root->right,target);
	if(root->val > target)
		return isInBST(root->left,target);
}

/* BST中 插入一个数

*/
TreeNode* insertIntoBST(TreeNode* root,int val)
{
	if(NULL == root) return new TreeNode(val);
	//if(roo->val == val)
	// BST中一般不会插入已经存在的元素
	if(root->val < val)
		root->right = insertIntoBST(root->right,val);
	if(root->val > val)
		root->left = insertIntoBST(root->left,val);
	return root;
}

/*BST中删除一个数

*/
//BST最左边就是最小的
TreeNode* getMin(TreeNode* root)
{
	while(root->left!=NULL) root=root->left;
	return root;
}
TreeNode* delNode(TreeNode* root,int key)
{
	if(key == root->val){
		//情况1：左右子树都空
		//情况2：左右子树有一个为空，
		//这个两个if把情况1 2 都正确处理了额
		if(root->left == NULL) return root->right;
		if(root->right == NULL) return root->left;
		//处理情况3；
		TreeNode* minNode = getMin(root->right);//找到右子树最小的节点
		root->val = minNode->val;  //root 改成 Minnode 
		root->right = delNode(root->right,minNode->val); //转而去删除MinNode 

	}else if(root->val > key){
		root->left = delNode(root->left,key);
	}else if(root->val < key){
		root->right = delNode(root->right,key);
	}
	return root;
}


/*450  删除二叉搜索树中的节点
给定一个二叉搜索树的根节点 root 和一个值 key，删除二叉搜索树中的 key 对应的节点，
并保证二叉搜索树的性质不变。返回二叉搜索树（有可能被更新）的根节点的引用。

一般来说，删除节点可分为两个步骤：

首先找到需要删除的节点；
如果找到了，删除它。
说明： 要求算法时间复杂度为 O(h)，h 为树的高度。

*/
TreeNode* getMinRight(TreeNode* root){
	while(root->left){
		root = root->left;
	}	
	return root;
}

TreeNode* deleteNode(TreeNode* root,int key){
	if(nullptr == root) return nullptr;

	if(key == root->val){
		if(root->left == nullptr) return root->right;
		if(root->right == nullptr) return root->left;

		TreeNode* minNodeOfRight = getMinRight(root->right);
		root->val = minNodeOfRight->val;
		root->right = deleteNode(root->right,minNodeofRight->val); //删除右边的最小节点值，不是key
	}else if(key > root->val){
		root->right = deleteNode(root->right,key);
	}else if(key < root->val){  //else if 不能省略
		root->left = deleteNode(root->left,key);
	}
	return root;
}


/*  1373 
给你一棵以 root 为根的 二叉树 ，请你返回 任意 二叉搜索子树的最大键值和。

二叉搜索树的定义如下：

任意节点的左子树中的键值都 小于 此节点的键值。
任意节点的右子树中的键值都 大于 此节点的键值。
任意节点的左子树和右子树都是二叉搜索树。
*/



int maxsum = 0;
//  函数返回 int[]{ isBST, min, max, sum}
/*
traverse(root) 返回一个大小为4的数组，暂且成为res:
res[0]记录以root为根的二叉树是否是BST,1代表是BST，0代表不是BST
res[1]记录以root为跟的二叉树所有节点的最小值
res[2]记录root 为根的二叉树所有节点中的最大值
res[3] 记录以 root 为根的二叉树所有节点值之和。
   */

vector<int> traverse(TreeNode* root)
{
	//base case 
	if(nullptr == root){
		return vector<int>{1,INT_MAX,INT_MIN,0};
	}

	//递归计算左右子树
	vector<int>left=traverse(root->left);
	vector<int>right=traverse(root->right);

	vector<int>res(4,0);
	//这个 if 在判断以 root 为根的二叉树是不是 BST
	if(left[0]==1 && right[0]==1 && root->val>left[2] && root->val<right[1]){
		//以 root 为根的二叉树是 BST
		res[0]=1;
		//计算以 root 为根的这棵 BST 的最小值
		res[1]=min(root->val,left[1]);
		//计算以 root 为根的这棵 BST 的最大值
		res[2]=max(root->val,right[2]);
		//计算以 root 为根的这棵 BST 所有节点之和
		res[3]=root->val+left[3]+right[3];
		//更新全局变量
		maxsum = max(maxsum,res[3]);
	}else{
		res[0]=0;
		//其他的值都没必要计算了，因为用不到
	}
	return res;
}

int maxSumBST(TreeNode* root) {
    traverse(root);
    return maxsum;
}


/*面试题 04.02. 最小高度树
给定一个有序整数数组，元素各不相同且按升序排列，编写一个算法，创建一棵高度最小的二叉搜索树。

思路：
用nums数组的中间值mid作为根节点，根据mid划分左子数组和右子数组。左子数组构建左子树，右子数组构建右子树。
*/
TreeNode* dfs(vector<int>& nums,int left,int right)
{
    if(left > right) return nullptr;
    int mid = left + (right-left)/2;
    TreeNode* root = new TreeNode(nums[mid]);
    root->left = dfs(nums,left,mid-1);
    root->right = dfs(nums,mid+1,right);
    return root;
}

TreeNode* sortedArrayToBST(vector<int>& nums)
{
    if(nums.size()== 0) return nullptr;
    return dfs(nums,0,num.size()-1);
}


/*99 恢复二叉搜索树
给你二叉搜索树的根节点 root ，该树中的两个节点被错误地交换。
请在不改变其结构的情况下，恢复这棵树。

思路：
这里我们二叉树搜索树的中序遍历(中序遍历遍历元素是递增的)

如下图所示，中序遍历顺序是 4,2,3,1，我们只要找到节点 4 和节点 1 交换顺序即可！

这里我们有个规律发现这两个节点：
第一个节点，是第一个按照中序遍历时候前一个节点大于后一个节点，
我们选取前一个节点，这里指节点 4；

第二个节点，是在第一个节点找到之后，后面出现前一个节点大于后一个节点，
我们选择后一个节点，这里指节点 1；

*/
TreeNode* firstNode = nullptr;
TreeNode* secondNode = nullptr;
TreeNode* preNode = new TreeNode(INT_MAX);
void recoverTree(TreeNode* root)
{
    inorder(root);
    int temp = firstNode->val;
    firstNode->val = secondNode->val;
    second->val = temp;
}

void inorder(TreeNode* root)
{
    if(nullptr == root) return;
    inorder(root->left);
    if(nullptr == firstNode && preNode->val > root->val) firstNode = pre;
    if(nullptr != firstNode && preNode->val > root->val) secondNode = root;
    preNode = root;
    inorder(root->right);
}


/*98 验证二叉搜索树
给定一个二叉树，判断其是否是一个有效的二叉搜索树。

假设一个二叉搜索树具有如下特征：

节点的左子树只包含小于当前节点的数。
节点的右子树只包含大于当前节点的数。
所有左子树和右子树自身必须也是二叉搜索树。

*/
bool isValidBST(TreeNode* root)
{
    return isValidBST(root,nullptr,nullptr);
}

bool isValidBST(TreeNode* root,TreeNode* min,TreeNode* max)
{
    if(nullptr == root) return true;
    if(nullptr != min && min->val >= root->val) return false;
    if(nullptr != max && root->val >= max->val) return false;

    return isValidBST(root->left,min,root)&&isValidBST(root->right,root,max);
}

/*109 有序链表转换成二叉搜索树
给定一个单链表，其中的元素按升序排序，将其转换为高度平衡的二叉搜索树。

本题中，一个高度平衡二叉树是指一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过 1。

*/

//思路1 ： 转换成数组  构成二叉搜索树

TreeNode* sortedListToBST(ListNode* head)
{
    if(head == nullptr) return nullptr;
    vector<int>temp;
    while(head){
        temp.push_back(head->val);
        head=head->next;
    }
    return vectorToBST(temp,0,temp.size()-1);
}

TreeNode* vectorToBST(vector<int>& temp,int left,int right)
{
    if(left >right) return nullptr;
    int mid = left + (right-left)/2;

    TreeNode* root = new TreeNode(temp[mid]);
    root->left = vectorToBST(temp,left,mid-1);
    root->right = vectorToBST(temp,mid+1,right);
    return root;
}


// 链表直接转化 
TreeNode* sortListToBST(ListNode* head){
	TreeNode* root = nullptr;
	if(head == nullptr) return nullptr;
	if(head->next == nullptr){
		root = new TreeNode(head->val);
		return root;
	}
	//快慢指针找到中点
	ListNode* slow = head;
	ListNode* fast = head;
	while(fast && fast->next){
		fast = fast->next->next;
		slow = slow->next;
	}

	//找到中点的前一个指针
	ListNode* pre = head;
	while(pre->next != slow) pre = pre->next;
	
	ListNode* headRight = slow->next;
	root = new TreeNode(slow->val);
	pre->next = nullptr;  //断开链表

	root->right = sortListToBST(headright);
	root->left = sortListToBST(head);

	return root;
}


/*173 二叉搜索树迭代器
实现一个二叉搜索树迭代器类BSTIterator ，表示一个按中序遍历二叉搜索树（BST）的迭代器：
BSTIterator(TreeNode root) 初始化 BSTIterator 类的一个对象。BST 的根节点 root 会作为构造函数的一部分给出。指针应初始化为一个不存在于 BST 中的数字，且该数字小于 BST 中的任何元素。
boolean hasNext() 如果向指针右侧遍历存在数字，则返回 true ；否则返回 false 。
int next()将指针向右移动，然后返回指针处的数字。
注意，指针初始化为一个不存在于 BST 中的数字，所以对 next() 的首次调用将返回 BST 中的最小元素。

你可以假设 next() 调用总是有效的，也就是说，当调用 next() 时，BST 的中序遍历中至少存在一个下一个数字。

*/

//思路：我们可以对二叉树做一次完全的递归操作，获取中序遍历的全部结果，并保存在数组中，
//随后，我们用得到的数组本身来实现迭代器。
class BSTIterator{
private:
	void inorderCore(TreeNode* root,vector<int>& res){
		if(nullptr == root) return;
		inorder(root->left,res);
		res.push_back(root->val);
		inorder(root->right,res);
	}
	vector<int> inorder(TreeNode* root){
		vector<int>res;
		inorder(root,res);
		return res;
	}
	vector<int>arr;
	int idx;
public:
	//需要实现的函数1
	BSTIterator(TreeNode* root):idx(0),arr(inorder(root)){

	}
	//需要实现的函数2
	int next(){
		return arr[idx++];
	}
	//需要实现的函数3
	bool hasNext(){
		return (idx<arr.size());
	}
};



















