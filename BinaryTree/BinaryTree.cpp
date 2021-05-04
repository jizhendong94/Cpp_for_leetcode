/*226  反转二叉树
  翻转一棵二叉树。

  示例：

  输入：

  4
  /   \
  2     7
  / \   / \
  1   3 6   9
  输出：

  4
  /   \
  7     2
  / \   / \
  9   6 3   1


 */

TreeNode* invertTree(TreeNode* root) {
	if(NULL == root) return NULL;
	TreeNode* temp = root->left;
	root->left = root->right;
	root->right = temp;

	invertTree(root->left);
	invertTree(root->right);
	return root;
}



/*27 offer  二叉树的镜像   

 */

//递归
TreeNode* mirrorTree(TreeNode* root) {
	if(NULL == root) return NULL;
	TreeNode* temp = root->left;
	root->left = root->right;
	root->right = temp;

	mirrorTree(root->left);
	mirrorTree(root->right);
	return root;
}

//迭代

TreeNode* mirrorTree(TreeNode* root) {
	if(NULL == root) return root;
	queue<TreeNode*>q;
	q.push(root);
	while(!q.empty())
	{
		TreeNode* temp = q.front();
		q.pop();
		swap(temp->left,temp->right);
		if(temp->left) q.push(temp->left);
		if(temp->right) q.push(temp->right);
	}
	return root;
}

/*116    填充每个节点的下一个右侧节点的指针  
  给定一个 完美二叉树 ，其所有叶子节点都在同一层，每个父节点都有两个子节点。二叉树定义如下：
  struct Node {
  int val;
  Node *left;
  Node *right;
  Node *next;
  }
  填充它的每个 next 指针，让这个指针指向其下一个右侧节点。
  如果找不到下一个右侧节点，则将 next 指针设置为 NULL。
  初始状态下，所有 next 指针都被设置为 NULL。
 */

//递归

void connectTwoNode(Node* node1,Node* node2)
{
	if(NULL == node1 || NULL == node2) return;
	//前序遍历位置 将传入的两个节点连接
	node1->next = node2;
	//将相同父节点的两个节点连接
	connectTwoNode(node1->left,node1->right);
	connectTwoNode(node2->left,node2->right);

	//连接跨越父节点的两个子节点
	connectTwoNode(node1->right,node2->left);
}
Node* connect(Node* root) {
	if(NULL == root) return NULL;
	connectTwoNode(root->left,root->right);
	return root;
}

//迭代方式
Node* connect(Node* root) {
	if(NULL == root) return NULL;
	queue<Node*>q;
	q.push(root);
	while(!q.empty())
	{
		int size = q.size();
		for(int i=0;i<size;i++)
		{
			Node* temp = q.front();
			q.pop();
			if(i!=size-1)
				temp->next = q.front();
			if(temp->left)  q.push(temp->left);
			if(temp->right) q.push(temp->right);
		}
	}
	return root;
}


/*114 二叉树展开为链表
  给你二叉树的根结点 root ，请你将它展开为一个单链表：
  展开后的单链表应该同样使用 TreeNode ，其中 right 子指针指向链表中下一个结点，而左子指针始终为 null 。
  展开后的单链表应该与二叉树 先序遍历 顺序相同。

 */
//递归解法

//定义 将以root为根的树拉平为链表
void flatten(TreeNode* root) {
	if(NULL == root) return;
	flatten(root->left);
	flatten(root->right);

	//后序遍历
	//左右子树已经被拉平成了一个链表
	TreeNode* left = root->left;
	TreeNode* right = root->right;

	//将左子树 作为右子树
	root->left = NULL;
	root->right = left;

	//将原先的右子树接到当前右子树的末端
	TreeNode* p =root;
	while(p->right != NULL){
		p=p->right;
	}
	p->right = right;
}

//迭代
public void flatten(TreeNode root) {
    while (root != null) {
        //左子树为 null，直接考虑下一个节点
        if (root.left == null) {
            root = root.right;
        } else {
            // 找左子树最右边的节点
            TreeNode pre = root.left;
            while (pre.right != null) {
                pre = pre.right;
            }
            //将原来的右子树接到左子树的最右边节点
            pre.right = root.right;
            // 将左子树插入到右子树的地方
            root.right = root.left;
            root.left = null;
            // 考虑下一个节点
            root = root.right;
        }
    }
}












