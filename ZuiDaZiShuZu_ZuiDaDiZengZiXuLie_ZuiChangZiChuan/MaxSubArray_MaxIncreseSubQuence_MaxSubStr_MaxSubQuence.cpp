

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
                dp[i]=max(nums[i],dp[j]+1);
        }
    }
    int res = 0;
    for(int i=0;i<n;i++)
        res=max(res,dp[i]);
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














