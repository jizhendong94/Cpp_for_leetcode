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

/*889 根据前序和后续遍历构造二叉树

返回与给定的前序和后序遍历匹配的任何二叉树。
 pre 和 post 遍历中的值是不同的正整数。

注：前序和后续不能完全确认一颗二叉树，所以可能会有多个结果，题目只要求返回一个结果
*/

TreeNode* buildTree(vector<int>& pre,int preStart,int preEnd,vector<int>& post,int psStart,int psEnd)
{
    if(preStart>preEnd || psStart>psEnd) return nullptr;
    TreeNode* root = new TreeNode(pre[preStart]);
    if(preStart == preEnd) return root; //不能少，否则程序崩溃

    int index = 0;
    for(index = psStart;index<=psEnd;index++){
        if(post[index] == pre[preStart+1])
            break;
    }
    //index 的索引 是post 中左子树的最后一个节点位置
    int leftsize = index-psStart;
    root->left = buildTree(pre,preStart+1,preStart+1+leftsize,post,postStart,index);
    root->right = bulidTree(pre,preStart+1+leftsize+1,preEnd,post,index+1,psEnd-1);

    return root;
}

TreeNode* constructFromPrePost(vector<int>& pre,vector<int>& post)
{
    return bulidTree(pre,0,pre.size()-1,post,0,post.size()-1);
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
//***************可以借用下面二叉搜索树的序列化解法 正确*********************
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

/*449 序列化和反序列化二叉搜索树
序列化是将数据结构或对象转换为一系列位的过程，以便它可以存储在文件或内存缓冲区中，
或通过网络连接链路传输，以便稍后在同一个或另一个计算机环境中重建。

设计一个算法来序列化和反序列化 二叉搜索树 。 对序列化/反序列化算法的工作方式没有限制。
您只需确保二叉搜索树可以序列化为字符串，并且可以将该字符串反序列化为最初的二叉搜索树。

*/

class Codec{
public:
	//Encodes a tree to a single string
	string serialize(TreeNode* root){
		if(root == nullptr) return "#";

		return to_string(root->val) + " " + serialize(root->left) + " " + serialize(root->right);
	}
	// Decodes your encoded data to tree
	TreeNode* deserialize(string data){
		stringstream(ss);
		return rebulidTree(ss);
	}

	TreeNode* rebulidTree(stringstream& ss){
		string temp;
		ss>>temp;
		if(temp == "#" return nullptr);

		TreeNode* node = new TreeNode(stoi(tmep));
		node->left = rebuildTree(ss);
		node->right = rebulidTree(ss);

		return node;
	}
};













/*124 二叉树中的最大路径和

路径 被定义为一条从树中任意节点出发，沿父节点-子节点连接，达到任意节点的序列。
同一个节点在一条路径序列中 至多出现一次 。该路径 至少包含一个 节点，且不一定经过根节点。
路径和 是路径中各节点值的总和。
给你一个二叉树的根节点 root ，返回其 最大路径和 。

思路：
*/

int res = INT_MIN;
//dfs 返回经过root的单边分支最大和，即max(root,root+left,root+right)
int dfs(TreeNode* root){
	if(nullptr == root) return 0;

	//计算左边分支的最大值，左边分支如果为负数还不如不选择
	int leftMax = max(0,dfs(root->left));
	//计算右边分支的最大和，右边分支如果为负数还不如不选择
	int rightMax = max(0,dfs(root->right));
	//left->root->right 作为路径与已经计算过的历史最大值作比较
	res = max(res,root->val + leftMax + rightMax);
	//返回经过root的单边最大分支给root的父节点使用
	return root->val + max(leftMax,rightMax);
}

int maxPathSum(TreeNode* root)
{
	if(nullptr == root) return 0;
	dfs(root);
	return res;
}


/* 331 验证二叉树的前序序列化
序列化二叉树的一种方法是使用前序遍历。当我们遇到一个非空节点时，我们可以记录下这个节点的值。
如果它是一个空节点，我们可以使用一个标记值记录，例如 #。

给定一串以逗号分隔的序列，验证它是否是正确的二叉树的前序序列化。编写一个在不重构树的条件下的可行算法

每个以逗号分隔的字符或为一个整数或为一个表示 null 指针的 '#' 。

你可以认为输入格式总是有效的，例如它永远不会包含两个连续的逗号，比如 "1,,3" 。

*/

//方法1 ：我们想出了本题的一个重磅级的技巧：把有效的叶子节点使用 "#" 代替。
//比如把 4## 替换成 # 。此时，叶子节点会变成空节点！
//https://leetcode-cn.com/problems/verify-preorder-serialization-of-a-binary-tree/solution/pai-an-jiao-jue-de-liang-chong-jie-fa-zh-66nt/
bool isValidSerialization(string preorder)
{
	vector<string>stk;
	string tempPreorder = preorder+",";
	size_t pos = tempPreorder.find(',');
	while(pos != string::npos){
		string temp = tempPreorder.substr(0,pos);
		stk.push_back(temp);

		int len = stk.size();
		while(len>=3 && stk[len-1]=="#" && stk[len-2]=="#" && stk[len-3]!="#"){
			stk.pop_back();
			stk.pop_back();
			stk.pop_back();

			stk.push_back("#");
			len = stk.size();
		}
		tempPreorder = tempPreorder.substr(pos+1);
		pos = tempPreorder.find(',');
	
	}
	return stk.size() == 1 && stk[0]=="#";
}

/*分割函数

// split 函数作用："4,#,#" -> ["4","#","#”]
    vector<string> split(string& preorder) {
        stringstream ss(preorder);
        string temp;
        vector<string> v;
        while(getline(ss, temp, ','))
            v.push_back(temp);
        return v;
    }
*/

//方法2：
//还没遍历到最后呢？肯定不会出现 入度 >= 出度 的时刻
bool isValidSerialization(string preorder)
{
	int indegree = 0,outdegree = 0;
	vector<string>splitPreorder = split(preorder);
	int len = splitPreorder.size();

	//判断第一个位置的两种特殊情况，循环里面就不需要特殊判断了
	if(len == 1 && splitPreorder[0]=="#"){
		return true;
	}
	if(len > 1 && splitPreorder[0]=="#"){
		return false;
	}

	for(int i=0;i<len;i++){
		if(0 == i){
			outdegree += 2;
		}else if(splitPreorder[i] == "#"){
			indegree += 1;
		}else{
			indegree += 1;
			outdegree += 2;
		}

		if(i != len-1 && indegree>=outdegree) return false;

	}
	return indegree == outdegree;
}


/*606 根据二叉树创建字符串
你需要采用前序遍历的方式，将一个二叉树转换成一个由括号和整数组成的字符串。

空节点则用一对空括号 "()" 表示。而且你需要省略所有不影响字符串与原始二叉树之间的一对一映射关系的空括号对。

描述：题目的意思是子节点需要用()来包裹。举例来说，二叉树[root,left,right]，则转换为root(left)(right)。如果只有left为空节点，则输出root()(right)；如果只有right为空节点则可以忽略右节点的()，输出为root(left)。
*/

string tree2str(TreeNode* root)
{
	//递归终止条件
	if(nullptr == root) return "";
	//左右子树都为空返回root->val
	if(root->left == nullptr && root->right == nullptr) return to_string(root->val);
	//右子树为空 返回root->val + (root->left)
	if(root->right == nullptr) return to_string(root->val) + "(" + tree2str(root->left) + ")";
	//右子树不空 左子树空或不空 
	return to_string(root->val)+"("+tree2str(root->left)+")("+tree2str(root->right)+")";
}


/*623 在二叉树中增加一行
给定一个二叉树，根节点为第1层，深度为 1。在其第 d 层追加一行值为 v 的节点。

添加规则：给定一个深度值 d （正整数），针对深度为 d-1 层的每一非空节点 N，
为 N 创建两个值为 v 的左子树和右子树。
将 N 原先的左子树，连接为新节点 v 的左子树；将 N 原先的右子树，连接为新节点 v 的右子树。
如果 d 的值为 1，深度 d - 1 不存在，则创建一个新的根节点 v，原先的整棵树将作为 v 的左子树。

*/

TreeNode* addOneRow(TreeNode* root,int val,int depth)
{
    if(depth == 1){
        TreeNode* root_new = new TreeNode(val);
        root_new->left = root;
        return root_new;
    }

    int tree_d = 1;
    queue<TreeNode*>q;
    q.push(root);
    while(!q.empty()){
        int size = q.size();
        while(size--){
            TreeNode* temp = q.front();
            q.pop();

            if(tree_d == depth - 1){
                TreeNode* temp_left = temp->left;
                TreeNode* temp_right = temp->right;

                temp->left = new TreeNode(val);
                temp->right = new TreeNode(val);

                temp->left->left = temp_left;
                temp->right->right = temp_right;
            }

            if(temp->left) q.push(temp->left);
            if(temp->right) q.push(temp->right);
        }
        tree_d++;
        if(tree_d == depth) break;
    }
    return root;
}

/* 655 输出二叉树
在一个 m*n 的二维字符串数组中输出二叉树，并遵守以下规则：

1. 行数 m 应当等于给定二叉树的高度。
2. 列数 n 应当总是奇数。
3. 根节点的值（以字符串格式给出）应当放在可放置的第一行正中间。
根节点所在的行与列会将剩余空间划分为两部分（左下部分和右下部分）。
你应该将左子树输出在左下部分，右子树输出在右下部分。左下和右下部分应当有相同的大小。
即使一个子树为空而另一个非空，你不需要为空的子树输出任何东西，
但仍需要为另一个子树留出足够的空间。然而，
如果两个子树都为空则不需要为它们留出任何空间。
4. 每个未使用的空间应包含一个空的字符串""。
5. 使用相同的规则输出子树。

*/

vector<vector<string>> printTree(TreeNode* root){
    int m = getheight(root),n = pow(2,m)-1;
    vector<vector<string>>res(m,vector<string>(n,""));
    print(root,0,n-1,0,res);
    return res;
}

int getheight(TreeNode* root){
    if(nullptr == root) return 0;
    return max(getheight(root->left),getheight(root->right)) + 1;
}

void print(TreeNode* root,int start,int end,int row,vector<vector<string>>& res)
{
    if(nullptr == root) return;
    int mid = (start + end)/2;

    res[row][mid] = to_string(root->val);

    print(root->left,start,mid-1,row+1,res);
    print(root->right,mid+1,end,row+1,res);
}


/* 662 二叉树最大宽度
给定一个二叉树，编写一个函数来获取这个树的最大宽度。树的宽度是所有层中的最大宽度。
这个二叉树与满二叉树（full binary tree）结构相同，但一些节点为空。

每一层的宽度被定义为两个端点（该层最左和最右的非空节点，两端点间的null节点也计入长度）
之间的长度。

思路：队列元素使用pair，多用一个int值记录当前层的索引
      左子树是父节点的index * 2,右子树是 index * 2 + 1,
      减去start * 2 便是在该层的位置，用于防止索引太大溢出

*/


int widthOfBinaryTree(TreeNode* root)
{
    if(nullptr == root) return 0;
    queue<pair<TreeNode*,int>>q;  //pair 的第二个位置记录当前是第几个节点
    q.push({root,1});
    int res = 0;

    while(!q.empty()){
        int count = q.size();
        int start = q.front().second,index;//start是本层的起点，index是本层当前遍历到的节点的索引
        
        while(count--){
            TreeNode* tmp = q.front().first;
            index = q.front().second;
            q.pop();

            if(tmp->left) q.push({tmp->left,index*2-start*2}); // 防止索引位置太大溢出
            if(tmp->right) q.push({tmp->right,index*2+1-start*2});
        }
        res = max(res,index-start+1);
    }
    return res;
}

/*894  所有可能的满二叉树 

满二叉树： 如果二叉树中除了叶子结点，每个结点的度都为 2，则此二叉树称为满二叉树。
完全二叉树： 如果二叉树中除去最后一层节点为满二叉树，且最后一层的结点依次从左到右分布，则此二叉树被称为完全二叉树。


满二叉树是一类二叉树，其中每个结点恰好有 0 或 2 个子结点。
返回包含 N 个结点的所有可能满二叉树的列表。 答案的每个元素都是一个可能树的根结点。
答案中每个树的每个结点都必须有 node.val=0。
你可以按任何顺序返回树的最终列表。

思路：  首先偶数是不能构成满二叉树的。 思路是把总node数分别左边，根，右边进行递归，
        如7个node可以分成1,1,5；3,1,5；5,1,1（左,根,右）。 5个node又可以分为1,1,3和3,1,1。
        3个node又可以分为1,1,1。 1个node直接返回。
对于 N≥3，我们可以设定如下的递归策略:FBT(N)= [对于所有的x，所有的树的左子结点来自FBT(x) 而右子结点来自FBT(N−1−x),减去一个根节点。

*/
vector<TreeNode*> allPossibleFBT(int n)
{
    vector<TreeNode*>res;
    if(n%2 == 0) return res;

    if(n == 1){
        TreeNode* head = new TreeNode(0);
        res.push_back(head);
        return res;
    }

    for(int i=1;i<n;i += 2){
        vector<TreeNode*>left = allPossibleFBT(i);
        vector<TreeNode*>right = allPossibleFBT(n-i-1); //- 根节点

        for(TreeNode* l :left){
            for(TreeNode* r:right){
                TreeNode* head = new TreeNode(0);
                head->left = l;
                head->right = r;
                res.push_back(head);
            }
        }
    }
    return res;
}

/*919 完全二叉树插入器

完全二叉树是每一层（除最后一层外）都是完全填充（即，节点数达到最大）的，并且所有的节点都尽可能地集中在左侧。

设计一个用完全二叉树初始化的数据结构 CBTInserter，它支持以下几种操作：

CBTInserter(TreeNode root) 使用头节点为 root 的给定树初始化该数据结构；

CBTInserter.insert(int v)  向树中插入一个新节点，节点类型为 TreeNode，值为 v 。
使树保持完全二叉树的状态，并返回插入的新节点的父节点的值；

CBTInserter.get_root() 将返回树的头节点。

*/
class CBTInsert{
public:
	TreeNode* root = nullptr;
	queue<TreeNode*>q;
	CBTInserter(TreeNode* root){
		this->root = root;
		q.push(root);
		//层序遍历，找到第一个缺失左子树，或者右子树的节点
		while(!q.empty()){
			TreeNode* cur = q.front();
			if(cur->left){
				q.push(cur->left);
			}else{
				break;
			}

			if(cur->right){
				q.push(cur->right);
			}else{
				break;
			}
			q.pop();  //队列最后的头元素，一定是缺少左子树或右子树的节点。
		}
	}

	int insert(int v){
		TreeNode* cur = q.front();
		//如果左子树为空，插入到左子树上
		if(!cur->left){
			cur->left = new TreeNode(v);
			q.push(cur->left);
		//如果右子树为空，插入到右子树上，并将当前节点弹出队列。
		}else{
			cur->right = new TreeNode(v);
			q.push(cur->right);
			q.pop();
		}
		return cur->val;
	}

	TreeNode* get_root(){
		return root;
	}

};

/*951 翻转等价二叉树

我们可以为二叉树 T 定义一个翻转操作，如下所示：选择任意节点，然后交换它的左子树和右子树。
只要经过一定次数的翻转操作后，能使 X 等于 Y，我们就称二叉树 X 翻转等价于二叉树 Y。
编写一个判断两个二叉树是否是翻转等价的函数。这些树由根节点 root1 和 root2 给出。

思路：也就是当 root1 和 root2 的值相等的情况下，需要继续判断 root1 的孩子节点是不是跟 root2 的孩子节点相当。
	  因为可以做翻转操作，所以这里有两种情况需要去判断。
递归分为两种情况：
	  取LL&&RR：flipEquiv(root1.left, root2.left) && flipEquiv(root1.right, root2.right)
	  取LR&RL： flipEquiv(root1.left, root2.right) && flipEquiv(root1.right, root2.left)
*/

bool flipEquiv(TreeNode* root1,TreeNode* root2)
{
	if(roo1 == nullptr && root2 == nullptr) return true;
	if(root1 == nullptr || root2 == nullptr) return false;

	if(root1->val == root2->val){
		return (flipEquiv(root1->left,root2->left) && flipEquiv(root1->right,root2->right))||
		(flipEquiv(root1->left,root2->right)&&flipEquiv(root1->right,root2->left));
	}
	return false;
}


/*958 二叉树的完全性检验

给定一个二叉树，确定它是否是一个完全二叉树。

若设二叉树的深度为 h，除第 h 层外，其它各层 (1～h-1) 的结点数都达到最大个数，
第 h 层所有的结点都连续集中在最左边，这就是完全二叉树。（注：第 h 层可能包含 1~ 2h 个节点。）

*/

bool isCompleteTree(TreeNode* root)
{
	bool flag = false;
	queue<TreeNode*>q;
	q.push(root);
	while(q.empty()){
		TreeNode* temp = q.front();
		q.pop();

		if(temp == nullptr) flag = true;

		if(flag && temp) return false; //遇到nullptr,后面应该都是nullptr

		if(temp){   //与层次遍历不同，只需要判断temp 是否是nullptr 
			q.push(temp->left);
			q.push(temp->right);
		}
	}
	return true;
}

/*968 监控二叉树

给定一个二叉树，我们在树的节点上安装摄像头。

节点上的每个摄影头都可以监视其父对象、自身及其直接子对象。

计算监控树的所有节点所需的最小摄像头数量。

*/
int res = 0;

int minCameraCover(TreeNode* root)
{
	if(nullptr == root) return 0;
	if(dfs(root) == 2) res += 1;
	return res;
}

//0：该节点安装了监视器  1：该节点可观，但是没有监视器 2：该节点不可观
int dfs(TreeNode* root)
{
	if(nullptr == 0) return 1;

	int left = dfs(root->left);
	int right = dfs(root->right);

	if(left == 2 || right == 2){
		res+=1;
		return 0;
	}else if(left == 0 || right ==0){
		return 1;
	}else{
		return 2;
	}
}

/*971 反转二叉树以匹配先序遍历
给你一棵二叉树的根节点 root ，树中有 n 个节点，每个节点都有一个不同于其他节点且处于 1 到 n 之间的值。

另给你一个由 n 个值组成的行程序列 voyage ，表示 预期 的二叉树 先序遍历 结果。

*/

int index = 0; //全局索引比较方便
vector<int>res;

vector<int> flipMatchVoyage(TreeNode* root,vector<int>vogage)
{
	if(dfs(root,vogage))
		return res;
	return vector<int>{-1};
}

bool dfs(TreeNode* root,vector<int>& voyage)
{
	if(nullptr == root || index >= vogage.size())  return true;
	//当前节点不符合预期，肯定不符合
	if(root->val != voyage[index]) return false;

	index++;
	//若先序遍历与预期不符合，尝试返回交换后的遍历结果
	if(nullptr != root->left && root->left->val != vogage[index]){
		res.push_back(root->val);//记录这次交换
		return dfs(root->right,vogage)&&dfs(root->left,vogage);
	}else{
		return dfs(root->left,vogage)&&dfs(root->right,vogage);
	}
}














