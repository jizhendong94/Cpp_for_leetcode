/*589 N 叉树的前序遍历
给定一个 N 叉树，返回其节点值的 前序遍历 。
N 叉树 在输入中按层序遍历进行序列化表示，每组子节点由空值 null 分隔（请参见示例）。
 
进阶：
递归法很简单，你可以使用迭代法完成此题吗?


// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

*/

//方法1 递归
vector<int>preorder(Node* root)
{
    vector<int>res;
    if(nullptr == root) return res;
    dfs(root,res);
    return res;
}

void dfs(Node* root,vector<int>& res)
{
    if(root == nullptr) return;
    res.push_back(root->val);

    vector<Node*>temp = root->children;
    for(auto cld:temp){
        if(cld != nullptr){
            dfs(cld,res);
        }
    }
}

/*
1. 二叉树的非递归遍历是每次将当前结点右孩子节点和左孩子节点依次压入栈中，注意是先右后左。
2. 然后将出栈节点输出，并且在将其右子节点和左子节点压入栈中。
3. 推广到N叉树，就是将当前结点的孩子节点由右到左依次压入栈中。
4. 然后将出栈节点输出，并且将其孩子节点依次压入栈中。
5. 时间复杂度O（N），空间复杂度O（N）
*/

/*思路: 
我们首先把根节点入栈，因为根节点是前序遍历中的第一个节点。
随后每次我们从栈顶取出一个节点 u，它是我们当前遍历到的节点，
并把 u 的所有子节点逆序推入栈中。例如 u 的子节点从左到右为 v1, v2, v3，
那么推入栈的顺序应当为 v3, v2, v1，这样就保证了下一个遍历到的节点（即 u 的第一个子节点 v1）
出现在栈顶的位置。


*/
//方法2 ：迭代 

vector<int> preorder(Node* root)
{
    if(root == nullptr) return {};
    stack<Node*>s;
    vector<int>res;
    s.push(root);

    while(!s.empty()){
        Node* cur = s.top();
        s.pop();

        res.push_back(cur->val);

        int n = (cur->children).size();
        for(int i=n-1;i>=0;i--){  //反向入栈 前序val v1 v2 v3 ,反向进栈v3 v2 v1 则v1最先被pop
            if(cur->children[i]){
                s.push(cur->children[i]);
            }
        }
    }
    return res;
}


/*590  N叉树的的后序遍历

给定一个 N 叉树，返回其节点值的 后序遍历 。
N 叉树 在输入中按层序遍历进行序列化表示，每组子节点由空值 null 分隔（请参见示例）。

进阶：
递归法很简单，你可以使用迭代法完成此题吗?

*/

//方法1 ： 递归
vector<int> postorder(Node* root)
{
    vector<int>res;
    if(root == nullptr) return res;
    dfs(root,res);
    return res;
}

void dfs(Node* root,vector<int>& res)
{
    if(root == nullptr) return;
    vector<Node*>temp = root->children;
    for(auto cld : temp){
        if(cld != nullptr){
            dfs(cld,res);
        }
    }

    res.push_back(root->val);
}

/*思路：
当前节点u 子节点v1 v2 v3 那后续遍历的结果是 v1 v2 v3 u 将结果反转为

u v3 v2 v1 我们求这个序列 ，这个序列和前序遍历很类似，只不过是正序入栈
*/


//方法2：迭代
vector<int> postorder(Node* root)
{
    if(nullptr == root) return {};
    stack<Node*>s;
    vector<int>res;
    s.push(root);

    while(!s.empty()){
        Node* cur = s.top();
        s.pop();

        res.push_back(cur->val);
        int n = (cur->children).size();
        for(int i=0;i<n;i++){ //正序入栈 
            if(cur->children[i]){
                s.push(cur->children[i]);
            }
        }
    }

    reverse(res.begin(),res.end()); //反转后为所求
    return res;
}












