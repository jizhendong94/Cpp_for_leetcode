

//子数组的中最大和 /
int maxsubarray(vector<int>& nums)
{
    int size = nums.size();
    vector<int>dp(size,0);
    dp[0]=nums[0];
    for(int i=1;i<size;i++)
    {
        dp[i]=max(nums[i],dp[i-1]+nums[i]);
    }

    int res= INT_MIN;
    for(int i=0;i<size();i++)
        res=max(res,dp[i]);

}

/*674  最长连续递增序列   子串  
  给定一个未经排序的整数数组，找到最长且 连续递增的子序列，并返回该序列的长度。

  连续递增的子序列 可以由两个下标 l 和 r（l < r）确定，如果对于每个 l <= i < r，都有 nums[i] < nums[i + 1] ，
  那么子序列 [nums[l], nums[l + 1], ..., nums[r - 1], nums[r]] 就是连续递增子序列。

    count 为当前元素峰值，ans为最大峰值
    初始化 count = 1
    从 0 位置开始遍历，遍历时根据前后元素状态判断是否递增，递增则 count++，递减则 count=1
    如果 count>ans，则更新 ans
    直到循环结束

 */

int findLengthOfLCIS(vector<int>& nums) {
    int n=nums.size();
    if(n == 0) return 0;
    int res = 1;
    int count  = 1;
    for(int i=1;i<n;i++)
    {
        if(nums[i]>nums[i-1]){
            count++;
        }else{
            count=1;
        }
        res = max(res,count);
    }
    return res;
}



/*300
  给你一个整数数组 nums ，找到其中最长严格递增子序列的长度。
  dp[i] 以i结尾的LIS
 */
//最长递增子序列
int maxincrease(vector<int>& nums)
{
    int n = nums.size();
    vector<int>dp(n,1);
    for(int i=1;i<n;i++)
    {
        for(int j=0;j<i;j++)
        {
            if(nums[j]<nums[i])
                dp[i]=max(dp[i],dp[j]+1);
        }
    }
    int res = 0;
    for(int i=0;i<n;i++)
        res=max(res,dp[i]);
    return res;
}

/*673 最长递增子序列的个数

  给定一个未排序的整数数组，找到最长递增子序列的个数。

  我们需要定义两个vector数组：
  vector<int> dp(n,1): 表示以nums[i]nums[i]结尾的LISLIS长度
  vector<int> count(n,1): 表示以nums[i]nums[i]结尾的LISLIS的组合的个数

  (1)当dp[j]+1 > dp[i]时,意味着我们第一次找到这个组合
  (2)当dp[j]+1 == dp[i]时,意味着我们不是第一次找到这个组合

  当我们遇到情况(1)时(dp[j]+1 > dp[i]),只需要将LISLIS的长度加一，并且将组合数设为与nums[j]nums[j]一样即可
  当我们遇到情况(2)时(dp[j]+1 == dp[i]),只需要将nums[j]nums[j]的组合数添加上去即可

 */
int findNumberOfLIS(vector<int>& nums) {
    int n =nums.size();
    if(n<=0) return n;

    vector<int>dp(n,1);
    vector<int>count(n,1);

    for(int i=1;i<n;i++)
    {
        for(int j=0;j<i;j++)
        {
            if(nums[j]<nums[i])
            {
                if(dp[j]+1>dp[i]){
                    dp[i]=dp[j]+1;
                    count[i]=count[j];
                }else if(dp[j]+1 == dp[i]){
                    count[i]+=count[j];
                }
            }
        }
    }
    int max_len = 0;
    for(int i:dp)
        max_len = max(max_len,i);
    int res =0;
    for(int i=0;i<n;i++){
        if(dp[i] == max_len)
            res += count[i];
    }
    return res;

}



//最长公共子序列
int longestsubsquence(string text1,string text2)
{
    int m=text1.length();
    int n=text2.length();
    vector<vector<int>>dp(m+1,vector<int>(n+1,0));
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(text1[i-1]==text2[j-1])
                dp[i][j]=dp[i-1][j-1]+1;
            else
                dp[i][j]=max(dp[i][j-1],dp[i-1][j]);
        }
    }
    return dp[m][n];
}


//最长公共子串，最长重复子数组
int longestsubstr(string text1,string text2)
{
    int m = text1.length();
    int n = text2.length();
    int res = 0;
    vector<vector<int>>dp(m+1,vector<int>(n+1,0));
    for(int i=1,i<=m;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(text1[i-1]==text2[j-1])
                dp[i][j]=dp[i-1][j-1]+1;
            else
                dp[i][j]=0;
            res=max(res,dp[i][j]);
        }
    }
    return res;
}



vector<vector<int>>merged(vector<vector<int>>& nums)
{
    if(nums.size()==0) return {};
    sort(nums.begin(),nums.end());
    vector<vector<int>>res;
    for(int i=0;i<nums.size();i++)
    {
        int L=nums[i][0],R=nums[i][1];
        if(!res.size())|| res.back()[1]<L)
        {
            res.push_back({L,R});
        }
        else
        {
            res.back()[1]=max(res.back()[1],R);
        }
    }
    return res;
}


/*1044 最长重复子串  

  给出一个字符串 S，考虑其所有重复子串（S 的连续子串，出现两次或多次，可能会有重叠）。
  返回任何具有最长可能长度的重复子串。（如果 S 不含重复子串，那么答案为 ""。）

  题解：后缀数组法
  1 保存s字符串的所有后缀
  2 对所有后缀进行排序（自然排序）
  3 比较排序后的相邻的后缀的最长公共子串（两个后缀从第一个字符开始的就相等得到公共子串），
  求出最长的公共子串
 */
int getCommlen(string& s1,string& s2)
{
    int i=0;
    for(i=0;i<s1.size()&&i<s2.size();i++)
    {
        if(s1[i]!=s2[i])
            break;
    }
    return i;
}
string longestDupSubString(string s)
{
    vector<string>strs;
    for(int i=0;i<s.size();i++)
        strs.push_back(s.substr(i));
    sort(strs.begin(),strs.end());

    int maxlen = 0;
    string res;
    for(int i=0;i<strs.size()-1;i++)
    {
        int len = getCommlen(strs[i],strs[i+1]);
        if(maxlen<len){
            maxlen = len;
            res = strs[i].substr(0,len);
        }
    }
    return res;
}

/*offer 48 最长不含重复字符的子字符串
  请从字符串中找出一个最长的不包含重复字符的子字符串，计算该最长子字符串的长度。

 */

int lengoflongestSubString(string s)
{
    int map[256]={0},len=0,start=0;
    for(int i=0;i<s.size();i++)
    {
        map[s[i]]++;
        while(map[s[i]]==2){
            map[s[start]]--;
            start++;
        }
        len=max(len,i-start+1);
    }
    return len;
}

/*409 最长回文串
  给定一个包含大写字母和小写字母的字符串，找到通过这些字母构造成的最长的回文串。
  在构造过程中，请注意区分大小写。比如 "Aa" 不能当做一个回文字符串。

  思路：
  在对char数组遍历的时候 只能出现一个个数为奇数的字符 所以我们直接记录有多少个字符出现次数为奇数就可以了啊
 */

int longestPalindrome(string s) {
    unordered_map<char,int>mp;
    for(char c:s) mp[c]++;
    int odd_count = 0;
    // 记录出现为奇数的个数
    for(auto temp:mp){
        odd_count += (temp.second%2);
    }

    return odd_count==0?s.length():(s.length()-odd_count+1);  //只能只有一个奇数出现在回文串的中心
}




/*5 最长回文子串

  给你一个字符串 s，找到 s 中最长的回文子串。

 */
string palindrome(string s,int left,int right)
{
    while(left>=0&&right<s.size() && s[left] == s[right])
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
        string s1 = palindrome(s,i,i);
        string s2 = palindrome(s,i,i+1);

        res = res.size()>s1.size()?res:s1;
        res = res.size()>s2.size()?res:s2;
    }
    return res;
}

/*516 最长回文子序列
  给定一个字符串 s ，找到其中最长的回文子序列，并返回该序列的长度。可以假设 s 的最大长度为 1000 。

  思路：
  dp 数组的定义是：在子串s[i..j]中，最长回文子序列的长度为dp[i][j]。一定要记住这个定义才能理解算法。
  1 首先明确一下 base case，如果只有一个字符，显然最长回文子序列长度是 1，也就是dp[i][j] = 1,(i == j)。

  2 因为i肯定小于等于j，所以对于那些i > j的位置，根本不存在什么子序列，应该初始化为 0。

  3 另外，看看刚才写的状态转移方程，想求dp[i][j]需要知道dp[i+1][j-1]，dp[i+1][j]，dp[i][j-1]这三个位置；
  再看看我们确定的 base case，填入 dp 数组之后是这样：

 */

int longestPalindromeSubseq(string s)
{
    int n = s.size();

    vector<vector<int>>dp(n,vector<int>(n,0));
    //base case
    for(int i=0;i<n;i++)
        dp[i][i] = 1;
    //反向遍历 保证正确的 状态转移
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






















