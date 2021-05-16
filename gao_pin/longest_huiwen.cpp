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





