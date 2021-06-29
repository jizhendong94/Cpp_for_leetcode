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
    root->left = NULL;  //必须将左子树设置为nullptr
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

/*111 二叉树的最小深度
给定一个二叉树，找出其最小深度。
最小深度是从根节点到最近叶子节点的最短路径上的节点数量。
说明：叶子节点是指没有子节点的节点。
*/

int minDepth(TreeNode* root)
{
    if(NULL == root) return 0;
    queue<TreeNode*>q;
    q.push(root);
    int depth=1;
    while(q.size())
    {
        int sz = q.size();
        while(sz--){
            TreeNode* temp=q.front();
            q.pop();
            if(temp->left == nullptr && temp->right == nullptr)
                return depth;
            if(temp->left)
                q.push(temp->left);
            if(temp->right)
                q.push(temp->right);
        }
        depth++;
    }
    return depth;
}

/* 814 二叉树剪枝
给定二叉树根结点 root ，此外树的每个结点的值要么是 0，要么是 1。
返回移除了所有不包含 1 的子树的原二叉树。
*/

//将root这棵树剪枝，返回剪枝后的树
TreeNode* pruneTree(TreeNode* root)
{
    if(nullptr == root) return nullptr;

    root->left = pruneTree(root->left); //左子树剪枝，返回剪枝后的左子树
    root->right = pruneTree(root->right);//右子树剪枝，返回剪枝后的右子树
    //判断root节点是否需要剪掉
    if(root->left == nullptr && root->right == nullptr && root->val == 0){
        return nullptr;
    }
    //返回剪枝后的结果
    return root;
}

/*863 二叉树中所有距离为 K 的结点

给定一个二叉树（具有根结点 root）， 一个目标结点 target ，和一个整数值 K 。
返回到目标结点 target 距离为 K 的所有结点的值的列表。 答案可以以任何顺序返回。

思路：
1. 按照例子给出的结果，这里遍历不是简单子节点，也可能是父节点的子节点（如例子里的1）
2. 为了查找父节点，需要构建一个额外的map来保存节点的父节点，这样子就可以做三个方向的遍历：父节点，左子节点和右子节点
3. 从target节点从三个方向做广度优先的遍历，每次距离加1，正好为k的时候，在queue里的节点就是答案
4. 坑： 这里遍历会三个方向存在循环的问题，所以需要记录哪些结点已经遍历了

*/

//父节点的映射表
unordered_map<TreeNode*,TreeNode*>node2parent;

//递归方式来构造父节点信息
void dfs(TreeNode* cur,TreeNode* parent)
{
    if(cur != nullptr){
        node2parent[cur]=parent;
        dfs(cur->left,cur);
        dfs(cur->right,cur);
    }
}

vector<int> distanceK(TreeNode* root,TreeNode* target,int k)
{
    //构建好映射表
    dfs(root,nullptr);
    //广度遍历使用的queue
    queue<TreeNode*>q;
    //避免死循环的记录遍历的点
    unordered_set<TreeNode*>visited;

    q.push(target);
    visited.insert(target);
    //记录当前遍历的层数，其实就是距离
    int dist = 0;

    while(!q.empty()){
        if(dist == k){
            vector<int>res;
            while(!q.empty()){
                res.push_back(q.front()->val);
                q.pop();
            }
            return res;
        }

        int size = q.size(); //当前层数的节点数
        for(int i=0;i<size;i++){
            TreeNode* cur = q.front();
            q.pop();

            //超三个方向遍历
            if(cur->left != nullptr &&(visited.count(root->left)==0)){
                q.push(cur->left);
                visited.insert(cur->left);
            }

            if(cur->right != nullptr &&(visited.count(cur->right)==0)){
                q.push(cur->right);
                visited.insert(cur->right);
            }

            TreeNode* parent = node2parent[cur];
            if(parent != nullptr && visited.count(parent)==0){
                q.push(parent);
                visited.insert(parent);
            }
        }
        //一层遍历完成距离+1
        ++dist;
    }
    //默认返回空
    return {};
}

/*865  具有所有最深节点的最小子树
给定一个根为 root 的二叉树，每个节点的深度是 该节点到根的最短距离 。
如果一个节点在 整个树 的任意节点之间具有最大的深度，则该节点是 最深的 。
一个节点的 子树 是该节点加上它的所有后代的集合。
返回能满足 以该节点为根的子树中包含所有最深的节点 这一条件的具有最大深度的节点。


*/

//一样的题目

/*1123 最深叶节点的最近公共祖先
给你一个有根节点的二叉树，找到它最深的叶节点的最近公共祖先。

回想一下：
叶节点 是二叉树中没有子节点的节点
树的根节点的 深度 为 0，如果某一节点的深度为 d，那它的子节点的深度就是 d+1
如果我们假定 A 是一组节点 S 的 最近公共祖先，
S 中的每个节点都在以 A 为根节点的子树中，且 A 的深度达到此条件下可能的最大值。

思路：
*******************************************************
// 思路：从每个树开始，获得当前节点的左右子树的最大深度
// 深度相同，说明最深的节点在这个节点两边，那这个节点就是结果
// 如果深度不相同，则去深度大的子树继续判断，最终就能得到结果
*/

TreeNode* subtreeWithAllDeepest(TreeNode* root)
{
    if(nullptr == root) return root;
    //获取当前节点的左右子树的最大深度
    int leftMaxDepth = getMaxDepth(root->left);
    int rightMaxDepth = getMaxDepth(root->right);

    //如果两边的最大深度相同，则这个节点就是结果
    if(leftMaxDepth == rightMaxDepth) return root;
    //不相等，去深度最大的子树继续找
    if(leftMaxDepth > rightMaxDepth){
        return subtreeWithAllDeepest(root->left);
    }else{
        return subtreeWithAllDeepest(root->right);
    }
}

int getMaxDepth(TreeNode* root)
{
    if(nullptr == root) return 0;
    return 1+max(getMaxDepth(root->left),getMaxDepth(root->right));
}














