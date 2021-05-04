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
	if(target == root->val) return false;
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


















































