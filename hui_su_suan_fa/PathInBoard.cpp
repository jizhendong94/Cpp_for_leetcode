/*
给定一个 m x n 二维字符网格 board 和一个字符串单词 word 。如果 word 存在于网格中，返回 true ；否则，返回 false 。
单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。
剑指offer 12
来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/ju-zhen-zhong-de-lu-jing-lcof
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


int rows=0;
int cols=0;

bool dfs(vector<vector<char>>& board,string word,int i,int j,int k)
{
    if(i<0||j<0||i>=rows||j>=cols||board[i][j]!=word[k]) return false;
    if(k==word.size()-1) return true;

    board[i][j]='\0';
    res=dfs(board,word,i-1,j,k)||dfs(board,word,i+1,j,k)||
        dfs(board,word,i,j-1,k)||dfs(board,word,i,j+1);
    board[i][j]=word[k];
    return res;
}
bool exist(vector<vector<char>>& board, string word) {
    rows=board.size();
    cols=board[0].size();
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            if(dfs(board,word,i,j,k))
                return true;
        }
    }
    return false;
}

/*
地上有一个m行n列的方格，从坐标 [0,0] 到坐标 [m-1,n-1] 。一个机器人从坐标 [0, 0] 的格子开始移动，它每次可以向左、右、上、下移动一格（不能移动到方格外），也不能进入行坐标和列坐标的数位之和大于k的格子。例如，当k为18时，机器人能够进入方格 [35, 37] ，因为3+5+3+7=18。但它不能进入方格 [35, 38]，因为3+5+3+8=19。请问该机器人能够到达多少个格子？
剑指offer  13
来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/ji-qi-ren-de-yun-dong-fan-wei-lcof
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

vector<vector<int>>visited;
int sum(int x,int y){
    int res=0;
    while(x)
    {
        res+=x%10;
        x/=10;
    }
    while(y){
        res+=y%10;
        y/=10;
    }
    return res;
}
int dfs(int m,int n,int i,int j,int k)
{
    if(i<0||j<0||i>=m||j>=m||visited[i][j]||sum(i,j)>k) return 0;
    visited[i][j]=1;
    return 1+dfs(m,n,i-1,j,k)+dfs(m,n,i+1,j,k)+
             dfs(m,n,i,j+1,k)+dfs(m,n,i,j-1,k);
}
int movingCount(int m, int n, int k) {
    visited=vector<vector>(m,vector<int>(n,0));
    return dfs(m,n,0,0,k);
}


/*
 *目标和
给定一个非负整数数组，a1, a2, ..., an, 和一个目标数，S。现在你有两个符号 + 和 -。对于数组中的任意一个整数，
你都可以从 + 或 -中选择一个符号添加在前面。
返回可以使最终数组和为目标数 S 的所有添加符号的方法数。

来源：力扣（LeetCode） 494
链接：https://leetcode-cn.com/problems/target-sum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

https://labuladong.github.io/algo/%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92%E7%B3%BB%E5%88%97/targetSum.html

*/
map<string,int>memo;
int dp(vector<int>& nums,int i,int rest)
{
    if(i==num.size()){
        if(rest == 0) return 1;
        return 0;
    }

    string key = to_string(i)+','+to_string(rest);
    if(memo.count(key)) return memo[key];
    
    int result = dp(nums,i+1,rest-nums[i])+dp(nums,i+1,rest+nums[i]);
    memo[key]=result;
    return result;

}
int findTargetSumWays(vector<int>& nums,int target)
{
    if(nums.size() == 0) return 0;
    return dp(nums,0,target);
}


/*
 * 全排列
给定一个 没有重复 数字的序列，返回其所有可能的全排列

输入: [1,2,3]
输出:
[
  [1,2,3],
  [1,3,2],
  [2,1,3],
  [2,3,1],
  [3,1,2],
  [3,2,1]
]

来源：力扣（LeetCode）  46
链接：https://leetcode-cn.com/problems/permutations
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
vector<vector<int>>res;

void backtrace(vector<int>& nums,vector<int>& track)
{
    if(nums.size() == track.size())
    {
        res.push_back(track);
        return;
    }
    for(int i=0;i<nums.size();i++)
    {
        if(find(track.begin(),track.end(),nums[i])!=track.end())
            continue;
        track.push_back(nums[i]);
        back_trace(nums,track);
        track.pop_back();
    }
}

vector<vector<int>> permute(vector<int>& nums)
{
    vector<int>track;
    backtrace(nums,track);
    return res;
}













