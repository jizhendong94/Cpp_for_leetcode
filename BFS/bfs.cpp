/*752. 打开转盘锁
你有一个带有四个圆形拨轮的转盘锁。每个拨轮都有10个数字： '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' 。每个拨轮可以自由旋转：例如把 '9' 变为  '0'，'0' 变为 '9' 。每次旋转都只能旋转一个拨轮的一位数字。
锁的初始数字为 '0000' ，一个代表四个拨轮的数字的字符串。
列表 deadends 包含了一组死亡数字，一旦拨轮的数字和列表里的任何一个元素相同，这个锁将会被永久锁定，无法再被旋转。
字符串 target 代表可以解锁的数字，你需要给出最小的旋转次数，如果无论如何不能解锁，返回 -1。

*/

string plusone(string cur,int j)
{
    if(cur[j]=='9')
        cur[j]='0';
    else
        cur[j]+=1;
    return cur;
}
string minusone(string cur,int j)
{
    if(cur[j] == '0')
        cur[j]='9';
    else
        cur[j]-=1;
    return cur;
}
int openLock(vector<string> deadends,string target)
{
    unordered_set<string>deads;
    for(string str: deadends)
        deads.insert(str);
    unordered_set<string>visited;
    queue<string>q;
    int step = 0;
    q.push("0000");
    visited.insert("0000");

    while(!q.empty())
    {
        int size = q.size();
        for(int i=0;i<size;i++)
        {
            string cur = q.front();
            q.pop();
            if(deads.count(cur)) continue;
            if(target == cur) return step;
            for(int j=0;j<4;j++){
                string up = plusone(cur,j);
                if(!visited.count(up)){
                    q.push(up);
                    visited.insert(up);
                }
                string down = minusone(cur,j);
                if(!visited.count(down)){
                    q.push(down);
                    visited.insert(down);
                }
            }
        }
        step++;
    }
    return -1;
}



/*773. 滑动谜题
  
在一个 2 x 3 的板上（board）有 5 块砖瓦，用数字 1~5 来表示, 以及一块空缺用 0 来表示.
一次移动定义为选择 0 与一个相邻的数字（上下左右）进行交换.
最终当板 board 的结果是 [[1,2,3],[4,5,0]] 谜板被解开。
给出一个谜板的初始状态，返回最少可以通过多少次移动解开谜板，如果不能解开谜板，则返回 -1 。


key :
对于第二个问题，我们这里的board仅仅是 2x3 的二维数组，所以可以压缩成一个一维字符串。
其中比较有技巧性的点在于，二维数组有「上下左右」的概念，压缩成一维后，如何得到某一个索引上下左右的索引？
很简单，我们只要手动写出来这个映射就行了：

*/

int slidingPuzzle(vector<vector<int>>& board)
{
    int m=2,n=3;
    string start = "";
    string target = "123450";
    
    //将数组转化为字符串
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            start.push_back(board[i][j]+'0');
        }
    }
    //记录一维字符串的相邻索引
    vector<vector<int>> neighbor = {
        {1,3},
        {0,2,4},
        {1,5},
        {0,4},
        {1,3,5},
        {2,4}
    };

    //BFS start
    queue<string>q;
    unordered_set<string>visited;
    q.push(start);
    visited.insert(start);

    int step = 0;
    while(!q.empty()){
        int sz = q.size();
        for(int i=0;i<sz;i++){
            string cur = q.front();
            q.pop();
            //判断是否达到目标 
            if(target == cur) return step;
            int idx = 0;
            //找到数字0的索引
            for(;cur[idx] != '0';idx++);
            //将数字0 和相邻的数字交换
            for(int adj : neighbor[idx]){
                string new_board = cur;
                swap(new_board[adj],new_board[idx]);
                //防止走回头路  
                if(!visited.count(new_board)){
                    q.push(new_board);
                    visited.insert(new_board);
                }
            }
        }
        step++;
    }
    return -1;
}









