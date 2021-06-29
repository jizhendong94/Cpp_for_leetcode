
/*144 二叉树的前序遍历
给你二叉树的根节点 root ，返回它节点值的 前序 遍历。
*/

//递归
vector<int>res
vector<int> preorderTreaversal(TreeNode* root)
{
    if(nullptr == root) return {};
    res.push_back(root->val);
    preorderTreaversal(root->left);
    preorderTreaversal(root->right);
    return res;
}

/*思路：
首先我们应该创建一个Stack用来存放节点，首先我们想要打印根节点的数据，
此时Stack里面的内容为空，所以我们优先将头结点加入Stack，然后打印。

之后我们应该先打印左子树，然后右子树。所以先加入Stack的就是右子树，然后左子树。
*/


//迭代
vector<int> preorderTraversal(TreeNode* root)
{
    if(nullptr == root) return {};
    stack<TreeNode*>s;
    vector<int>res;
    s.push(root);

    while(!s.empty()){
        TreeNode* cur = s.top();
        s.pop();

        res.push_back(cur->val);
        if(cur->right) s.push(cur->right); //先将右子树加入栈中，左子树先出栈
        if(cur->left) s.push(cur->left);
    }
    return res;
}


/*145 二叉树的后序遍历


*/
//方法1 ：递归
vector<int>res;
vector<int> postorderTraversal(TreeNode* root) {
    if(root == nullptr) return {};
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    res.push_back(root->val);
    return res;
}

//思路：取巧的方法。该写法的访问顺序并不是后序遍历，
//而是利用先序遍历“根左右”的遍历顺序，将先序遍历顺序更改为“根右左”，
//反转结果List，得到结果顺序为“左右根”。
//方法2： 迭代 
vector<int> postorderTraversal(TreeNode* root)
{
    if(nullptr == root) return {};
    stack<TreeNode*>s;
    vector<int>res;
    s.push(root);

    while(!s.empty()){
        TreeNode* cur = s.top();
        s.pop();

        res.push_back(cur->val);
        if(cur->left) s.push(cur->left); //先加入左子树
        if(cur->right) s.push(cur->right);

    }
    reverse(res.begin(),res.end());
    return res;
}


/*94 二叉树的中序遍历
给定一个二叉树的根节点 root ，返回它的 中序 遍历。
*/


//递归
vector<int>res;
vector<int> inorderTraversal(TreeNode* root) {
     if(nullptr == root) return {};
     inorderTraversal(root->left);
     res.push_back(root->val);
     inorderTraversal(root->right);
     return res;
}

//迭代
vector<int> inorderTraversal(TreeNode* root)
{
    if(nullptr == root) return {};
    vector<int>res;
    //栈先进后出
    stack<TreeNode*>s;
    //root 为空且stack为空  遍历结束
    while(root != nullptr || !s.empty()){
        //先根后左  入栈 
        while(root){
            s.push(root);
            root=root->left;
        }
        //此时root==null 说明上一步root没有左子树
        //1. 执行左出栈，因为此时root==null,导致root->right一定为null
        root = s.top();
        s.pop();
        res.push_back(root->val);
        root = root->right;
    }
    return res;
}


/*703 数据流中的第 K 大元素
设计一个找到数据流中第 k 大元素的类（class）。注意是排序后的第 k 大元素，
不是第 k 个不同的元素。

请实现 KthLargest 类：

KthLargest(int k, int[] nums) 使用整数 k 和整数流 nums 初始化对象。
int add(int val) 将 val 插入数据流 nums 后，返回当前数据流中第 k 大的元素。

思路：我们可以使用一个大小为 k的优先队列来存储前k大的元素，
      其中优先队列的队头为队列中最小的元素，也就是第k大的元素。
      在单次插入的操作中，我们首先将元素val加入到优先队列中。
      如果此时优先队列的大小大于 k，我们需要将优先队列的队头元素弹出，
      以保证优先队列的大小为 k。
*/


//小堆顶 
class KthLargest{
    private:
        priority_queue<int,vector<int>,greater<int>>pq;
        int __k;
    public:
        KthLargest(int k,vector<int>& nums){
            __k = k;
            for(auto temp:nums){
                add(temp);
            }
        }

        int add(int val){
            pq.push(val);
            if(pq.size()>__k){
                pq.pop();
            }
            return pq.top();
        }

};









