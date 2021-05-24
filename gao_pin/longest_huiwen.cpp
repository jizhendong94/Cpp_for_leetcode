/*最长回文子串


 */

string Palindrome(string s,int left,int right)
{
    while(left>=0 && right<s.size() && s[left] == s[right])
    {
        left--;
        right++;
    }
    return s.substr(left+1,right-left-1);
}

string longestPalindrome(string s)
{
    string res;
    for(int i=0;i<s.size();i++)
    {
        string s1 = Palindrome(s,i,i);
        string s2 = Palindrome(s,i,i+1);

        res = res.size()>s1.size()?res:s1;
        res = res.size()>s2.size()?res:s2;

    }
    return res;
}


/*最长回文子序列


 */

int longestPalindromeSubseq(string s)
{
    int n = s.size();
    vector<vector<int>>dp(n,vector<int>(n,0));
    for(int i=0;i<n;++)
        dp[i][i]=1;

    for(int i=n-1;i>=0;i--)
    {
        for(int j=i+1;j<n;j++)
        {
            if(s[i]==s[j])
                dp[i][j]=dp[i+1][j-1]+2;
            else
                dp[i][j]=max(dp[i+1][j],dp[i][j-1]);
        }
    }
    return dp[0][n-1];
}


/*1312  让字符串成为回文串的最少插入次数
  给你一个字符串 s ，每一次操作你都可以在字符串的任意位置插入任意字符。

  请你返回让 s 成为回文串的 最少操作次数 。

  「回文串」是正读和反读都相同的字符串。

 */
int minInsertions(string s) {
    int n = s.size();
    // 定义：对 s[i..j]，最少需要插入 dp[i][j] 次才能变成回文
    vector<vector<int>>dp(n,vector<int>(n,0));
    // base case：i == j 时 dp[i][j] = 0，单个字符本身就是回文
    // dp 数组已经全部初始化为 0，base case 已初始化
    for(int i=n-1;i>=0;i--)
    {
        for(int j=i+1;j<n;j++){
            // 根据 s[i] 和 s[j] 进行状态转移
            if(s[i] == s[j])
                dp[i][j] = dp[i+1][j-1];
            else{
                dp[i][j]=min(dp[i+1][j],dp[i][j-1])+1;
            }
        }
    }
    return dp[0][n-1];
}









