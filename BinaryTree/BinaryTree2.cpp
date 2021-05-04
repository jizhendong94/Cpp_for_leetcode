/*654 最大二叉树
  给定一个不含重复元素的整数数组 nums 。一个以此数组直接递归构建的 最大二叉树 定义如下：

  二叉树的根是数组 nums 中的最大元素。
  左子树是通过数组中 最大值左边部分 递归构造出的最大二叉树。
  右子树是通过数组中 最大值右边部分 递归构造出的最大二叉树。
  返回有给定数组 nums 构建的 最大二叉树 。


 */

//将nums[l..r] 构造成符合条件的树，返回根节点
TreeNode* build(vector<int>& nums,int l,int r)
{
	if(l>r) return NULL; // base case

	//找到数组中的最大值和对应的索引值
	int index = -1,max_val = INT_MIN;
	for(int i=l;i<=r;i++){
		if(max_val<nums[i]){
			index = i;
			max_val=nums[i];
		}
	}

	TreeNode* root = new TreeNode(max_val);
	//递归构造左右子树
	root->left = build(nums,l,index-1);
	root->right = build(nums,index+1,r);
	return root;
}
TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
	if(nums.size() == 0) return NULL;
	return build(nums,0,nums.size()-1);
}




/*105  从前序和中序遍历序列构造二叉树


 */

TreeNode* buildTree(vector<int>&preorder,int preStart,int preEnd,vector<int>& inorder,int inStart,int inEnd)
{
	if(preStart>preEnd || inStart>inEnd) return NULL;
	int rootval = preorder[preStart];
	int index = 0;
	for(int i = inStart;i<=inEnd;i++){
		if(inorder[i]==rootval){
			index = i;
			break;
		}
	}
	int leftsize = index-inStart;
	TreeNode* root = new TreeNode(rootval);
	root->left = buildTree(preorder,preStart+1,preStart+leftsize,inorder,inStart,index-1);  //画图确定索引
	root->right = buildTree(preorder,preStart+leftsize+1,preEnd,inorder,index+1,inEnd);
	return root;
}
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
	return buildTree(preorder,0,preorder.size()-1,inorder,0,inorder.size()-1);
}


/*106 从后序和中序来构造二叉树

 */

TreeNode* buildTree(vector<int>& inorder,int inStart,int inEnd,vector<int>& postorder,int psStart,int psEnd)
{
	if(inStart>inEnd || psStart>psEnd) return NULL;
	int rootval = postorder[psEnd];
	int index = 0;
	for(int i=inStart;i<=inEnd;i++){
		if(inorder[i] == rootval){
			index = i;
			break;
		}
	}
	int leftsize = index-inStart;
	TreeNode* root = new TreeNode(rootval);
	root->left = buildTree(inorder,inStart,index-1,postorder,psStart,psStart+leftsize-1);
	root->right = buildTree(inorder,index+1,inEnd,postorder,psStart+leftsize,psEnd-1);
	return root;
}
TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
	return buildTree(inorder,0,inorder.size()-1,postorder,0,postorder.size()-1);
}

/*652  寻找重复的子树  labuladong
  给定一棵二叉树，返回所有重复的子树。对于同一类的重复子树，你只需要返回其中任意一棵的根结点即可。
  两棵树重复是指它们具有相同的结构以及相同的结点值。

 */


unordered_map<string,int>memo;
vector<TreeNode*>res;
string traverse(TreeNode* root)
{
	//空节点 用一个特殊的字符表示
	if(NULL == root) return "#";
	//将左右子树序列化成字符串
	string left = traverse(root->left);
	string right = traverse(root->right);
	//后序遍历
	//左右子树加自己，就是以自己为根的二叉树序列化的结果
	string subTree = left + "," + right + "," +to_string(root->val);

	if(memo[subTree]==1) res.push_back(root);
	memo[subTree]++;
	return subTree;
}
vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
	traverse(root);
	return res;
}

/*297 序列化与反序列化二叉树  labuladong

  序列化是将一个数据结构或者对象转换为连续的比特位的操作，进而可以将转换后的数据存储在一个文件或者内存中，
  同时也可以通过网络传输到另一个计算机环境，采取相反方式重构得到原数据。

  请设计一个算法来实现二叉树的序列化与反序列化。这里不限定你的序列 / 反序列化算法执行逻辑，
  你只需要保证一个二叉树可以被序列化为一个字符串并且将这个字符串反序列化为原始的树结构。
 */

//前序遍历解法

void serialize(TreeNode* root,string& build)  //一定要传入引用 保存结果
{
	if(root == NULL){
		build += "#,";
		return;
	}
	//前序遍历
	build +=to_string(root->val)+",";
	serialize(root->left,build);
	serialize(root->right,build);

}
// Encodes a tree to a single string.
string serialize(TreeNode* root) {
	string build;
	serialize(root,build);
	return build;
}




TreeNode* deserialize(vector<string>& node)
{
	if(node.size() == 0) return NULL;

	string first = node[0];
	node.erase(node.begin());  //位置不可变 取出第一个元素后，立刻删除
	if("#" == first) return NULL;
	int rootval = atoi(first.c_str());
	TreeNode* root = new TreeNode(rootval);

	root->left = deserialize(node);
	root->right = deserialize(node);
	return root;
}
// Decodes your encoded data to tree.
TreeNode* deserialize(string data) {
	vector<string>node;
	size_t pos = data.find(',');
	while(pos != string::npos){
		string x = data.substr(0,pos);
		node.push_back(x);
		data=data.substr(pos+1);
		pos=data.find(',');
	}
	return deserialize(node);
}












