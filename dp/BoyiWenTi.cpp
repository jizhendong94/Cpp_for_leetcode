#include<iostream>
#include<vector>
using namespace std;
/*
你和你的朋友面前有一排石头堆，用一个数组 piles 表示，piles[i] 表示第 i 堆石子有多少个。
你们轮流拿石头，一次拿一堆，但是只能拿走最左边或者最右边的石头堆。
所有石头被拿完后，谁拥有的石头多，谁获胜。

石头的堆数可以是任意正整数，石头的总数也可以是任意正整数，这样就能打破先手必胜的局面了。
比如有三堆石头 piles = [1,100,3]，先手不管拿 1 还是 3，能够决定胜负的 100 都会被后手拿走，后手会获胜。

假设两人都很聪明，请你设计一个算法，返回先手和后手的最后得分（石头总数）之差。
比如上面那个例子，先手能获得 4 分，后手会获得 100 分，你的算法应该返回 -96。

这样推广之后，这个问题算是一道 Hard 的动态规划问题了。
博弈问题的难点在于，两个人要轮流进行选择，而且都贼精明，应该如何编程表示这个过程呢？

dp 含义： dp[i][j].fir表示，对于[i..j]这部分石头，先手能获得的最高分数
		  dp[i][j].sec表示，对于[i..j]这部分石头，后手能获得的最高分数
举个例子 piles = [3,9,1,2] 索引从0开始
	dp[0][1].fir = 9 
	dp[1][3].sec = 2;

状态转移方程：dp[i][j].fir = max(piles[i]+dp[i+1][j].sec,piles[j]+dp[i][j-1].sec)
						     max(选择最左边的石头，选择最右边的石头)
解释：我作为先手，面对pils[i..j]时，有两种选择：
选择左边的石头，然后面对piles[i+1..j] 但此时我变成了后手
选择右边的石头，然后面对piles[i..j-1] 但此时我变成了后手
*/


int StoneGame(vector<int>& nums)
{
	int n = nums.size();
	vector<vector<vector<int>>>dp(n,vector<vector<int>>(n,vector<int>(2,0)));
	//base case
	for(int i=0;i<n;i++){
		dp[i][i][0]=nums[i];
		dp[i][i][1]=0;
	}
	//斜着遍历数组
	for(int l=2;l<=n;l++)
	{
		for(int i=0;i<=n-l;i++)
		{
			int j=l+i-1;
			int left = nums[i] + dp[i+1][j][1];
			int right = nums[j] + dp[i][j-1][1];

			if(left>right){
				dp[i][j][0]=left;
				dp[i][j][1]=dp[i+1][j][0];
			}else{
				dp[i][j][0]=right;
				dp[i][j][1]=dp[i][j-1][0];
			}
		}
	}
	vector<int>res = dp[0][n-1];
	return res[0]-res[1];
}

int main()
{
	vector<int>nums={3,9,1,2};
	cout<<StoneGame(nums)<<endl;
	return 0;
}
