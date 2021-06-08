#include<iostream>
#include<vector>
using namespace std;
/*
今天讲讲 Union-Find 算法，也就是常说的并查集算法，主要是解决图论中「动态连通性」问题的。
名词很高端，其实特别好理解，等会解释，另外这个算法的应用都非常有趣。

*/

class UF{
private:
    int count;//记录联通分量
    //记录父节点
    vector<int>parent;
    //新增一个数据来记录树的重量
    vector<int>size;

public:
    UF(int n){
        //一开始 互不连通
        this->count = n;

        parent=vector<int>(n,0);
        //最初每棵树只有一个节点，重量初始化为1
        size = vector<int>(n,1);
        //父节点指针初始化指向自己 
        for(int i=0;i<n;i++){
            parent[i] = i;
        }
    }
    //O(N)
    void Union(int p,int q){
        int rootP = find(p);
        int rootQ = find(q);
        if(rootP == rootQ) return;

        //将两颗树合并成一颗
        parent[rootP] = rootQ;
        //parent[rootQ] = rootP; 也一样
        count--; //两个分量合二为一
    }
    //O(logN)
    void Union1(int p,int q){
        int rootP = find(p);
        int rootQ = find(q);
        if(rootP == rootQ) return;

        //小树接到大树下面 较平衡
        if(size[rootP]>size[rootQ]){
            parent[rootQ] = rootP;
            size[rootP] +=size[rootQ];
        }else{
            parent[rootP]=rootQ;
            size[rootQ] +=size[rootP];
        }
        count--;
    }

    //返回某个节点x的根节点
    int find(int x){
        //根节点的parent[x] == x;
        while(parent[x] != x){
            x = parent[x];
        }
        return x;
    }
    //路径压缩
    int find1(int x){
        while(parent[x] != x){
            parent[x]=parent[parent[x]];
            x = parent[x];
        }
        return x;
    }

    //返回当前的连通分量
    int Count(){
        return count;
    }
    //如果节点p和q连通的话，它们一定拥有相同的根节点：
    bool connected(int p,int q){
        int rootP = find(p);
        int rootQ = find(q);

        return rootP == rootQ;
    }
};

int main()
{
    return 0;
}

/*130 被围绕的区域
DFS
给你一个 m x n 的矩阵 board ，由若干字符 'X' 和 'O' ，
找到所有被 'X' 围绕的区域，并将这些区域里所有的 'O' 用 'X' 填充。

思路：任何边界上的 O 都不会被填充为 X。 我们可以想到，所有的不被包围的 O 都直接或间接与边界上的 O 相连。
我们可以利用这个性质判断 O 是否在边界上，具体地说：

对于每一个边界上的 O，我们以它为起点，标记所有与它直接或间接相连的字母 O；
最后我们遍历这个矩阵，对于每一个字母：
如果该字母被标记过，则该字母为没有被字母 X 包围的字母 O，我们将其还原为字母 O；
如果该字母没有被标记过，则该字母为被字母 X 包围的字母 O，我们将其修改为字母 X。

*/

void dfs(vector<vector<char>>& board,int i,int j)
{
    if(i<0 || j<0 || i>=board.size() || j>=board[0].size() || board[i][j] != 'O')
        return;
    board[i][j] = 'A';
    dfs(board,x+1,y);
    dfs(board,x-1,y);
    dfs(board,x,y-1);
    dfs(board,x,y+1);

}

void  slove(vector<vector<char>>& board)
{
    int m = board.size();
    int n = board[0].size();
    //寻找和边界联通的O，我们需要考虑如下情况。
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++){
            bool IsEdge = (i == 0 || i==m-1 || j==0 || j==n-1);
            if(IsEdge && board[i][j]=='O')
                dfs(board,i,j);
        }
    }

    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(board[i][j]) == 'O')
                board[i][j]='X';
            if(board[i][j] == '#')
                board[i][j]='O';
        }
    }
}


/*990 等式方程的可满足性
给定一个由表示变量之间关系的字符串方程组成的数组，
每个字符串方程 equations[i] 的长度为 4，并采用两种不同的形式之一："a==b" 或 "a!=b"。
在这里，a 和 b 是小写字母（不一定不同），表示单字母变量名。

只有当可以将整数分配给变量名，以便满足所有给定的方程时才返回 true，否则返回 false。 
*/

//利用并查集算法解决  UF

bool equationPossible(vector<string>& equations)
{
    UF* uf = new UF(26);

    for(string temp : equations){
        if(temp[1] == '='){
            char x = temp[0];
            char y = temp[3];
            uf->Union(x-'a',y-'a');
        }
    }

    for(string temp:equations){
        if(temp[1] == '!'){
            char x = temp[0];
            char y = temp[3];
            if(uf->connected(x-'a',y-'a'))
                return false;
        }
    }

    return true;
}



