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











































