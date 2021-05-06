

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








