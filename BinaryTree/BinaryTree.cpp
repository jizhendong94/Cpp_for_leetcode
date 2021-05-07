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

/*297  
  序列化是将一个数据结构或者对象转换为连续的比特位的操作，进而可以将转换后的数据存储在一个文件或者内存中，
  同时也可以通过网络传输到另一个计算机环境，采取相反方式重构得到原数据。
  请设计一个算法来实现二叉树的序列化与反序列化。这里不限定你的序列 / 反序列化算法执行逻辑，
  你只需要保证一个二叉树可以被序列化为一个字符串并且将这个字符串反序列化为原始的树结构。

 */

void serialize(TreeNode* root,string& build)
{
    if(nullptr == root){
        build +="#,";
        return;
    }
    build+=to_string(root->val)+","	;
    serialize(root->left,build);
    serialize(root->right,build);
}

string serialize(TreeNode* root){
    string build;
    serialize(root,build);
    return build;
}
//
TreeNode* deserialize(vector<string>& node)
{
    if(node.size() == 0) return NULL;
    string first=node[0];
    node.erase(node.begin());
    if("#" == first) return NULL;
    int rootval = atoi(first.c_str());
    TreeNode* root = new TreeNode(rootval);
    root->left=deserialize(node);
    root->right=deserialize(node);
    return root;
}
TreeNode* deserialize(string data)
{
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

/*236 二叉树的最近公共祖先
  给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。

  百度百科中最近公共祖先的定义为：“对于有根树 T 的两个节点 p、q，
  最近公共祖先表示为一个节点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”

 */

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if(NULL == root || root==p || root ==q ) return root;

    TreeNode* left = lowestCommonAncestor(root->left,p,q);
    TreeNode* right = lowestCommonAncestor(root->right,p,q);
    if(NULL == left) return right;
    if(NULL == right) return left;

    return root;
}



/*222  完全二叉树的节点个数
  给你一棵 完全二叉树 的根节点 root ，求出该树的节点个数。

  完全二叉树 的定义如下：在完全二叉树中，除了最底层节点可能没填满外，其余每层节点数都达到最大值，
  并且最下面一层的节点都集中在该层最左边的若干位置。若最底层为第 h 层，则该层包含 1~ 2h 个节点。
 */

//O(N) 解法 
int countNodes(TreeNode* root)
{
    if(nullptr == root) return 0;
    return 1+countNodes(root->left)+countNodes(root->right);
}


//O(logN * logN)
int countNodes(TreeNode* root)
{
    TreeNode* left = root,*right=root;
    int hl=0,hr=0;
    while(left!=NULL){
        left=left->left;
        hl++;
    }

    while(right!=NULL){
        right=right->right;
        hr++;
    }
    // 如果左右子树的高度相同，则是一棵满二叉树
    if(hl==hr){
        return pow(2,hl)-1;
    }
    // 如果左右高度不同，则按照普通二叉树的逻辑计算
    return 1+countNodes(root->left)+countNodes(root->right);
}

/*offer 55 二叉树的深度

  输入一棵二叉树的根节点，求该树的深度。从根节点到叶节点依次经过的节点（含根、叶节点）形成树的一条路径，最长路径的长度为树的深度。
 */

int maxDepth(TreeNode* root)
{
    if(NULL == root) return 0;
    int left = maxDepth(root->left);
    int right = maxDepth(root->right);

    return 1+max(left,right);
}




int maxDepth(TreeNode* root) {
    if(NULL == root) return 0;
    queue<TreeNode*>q;
    q.push(root);
    int depth=0;
    while(!q.empty())
    {
        int size = q.size();
        while(size--){
            TreeNode* temp = q.front();
            q.pop();
            if(temp->left) q.push(temp->left);
            if(temp->right) q.push(temp->right);
        }
        depth++;
    }
    return depth;
}

































