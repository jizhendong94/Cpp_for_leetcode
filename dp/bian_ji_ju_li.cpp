/*72 编辑距离

  给你两个单词 word1 和 word2，请你计算出将 word1 转换成 word2 所使用的最少操作数 。

  你可以对一个单词进行如下三种操作：

  插入一个字符
  删除一个字符
  替换一个字符

  dp[i-1][j-1]
  存储 s1[0..i] 和 s2[0..j] 的最小编辑距离

  dp(i - 1, j - 1) + 1 # 替换
# 解释：
# 我直接把 s1[i] 替换成 s2[j]，这样它俩就匹配了
# 同时前移 i，j 继续对比
# 操作数加一

dp(i - 1, j) + 1,    # 删除
# 解释：
# 我直接把 s[i] 这个字符删掉
# 前移 i，继续跟 j 对比
# 操作数加一

dp(i, j - 1) + 1,    # 插入
# 解释：
# 我直接在 s1[i] 插入一个和 s2[j] 一样的字符
# 那么 s2[j] 就被匹配了，前移 j，继续跟 i 对比
# 别忘了操作数加一

 */

int minofthree(int a,int b,int c)
{
    return min(a,min(b,c));
}
int minDistance(string word1, string word2) {
    int m = word1.size();
    int n = word2.size();
    vector<vector<int>>dp(m+1,vector<int>(n+1,0));
    //base case 
    for(int i=1;i<=m;i++)
        dp[i][0]=i;
    for(int j=1;j<=n;j++)
        dp[0][j]=j;
    //自底向上
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(word1[i-1] == word2[j-1])
                dp[i][j] = dp[i-1][j-1];
            else{
                dp[i][j] = 1 + minofthree(dp[i-1][j],dp[i][j-1],dp[i-1][j-1]);
            }
        }
    }
    //存储整个s1 s2的最小编辑距离  
    return dp[m][n];
}










