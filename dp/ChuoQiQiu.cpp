/*312
有 n 个气球，编号为0 到 n - 1，每个气球上都标有一个数字，这些数字存在数组 nums 中。
现在要求你戳破所有的气球。戳破第 i 个气球，你可以获得 nums[i - 1] * nums[i] * nums[i + 1] 枚硬币。 
这里的 i - 1 和 i + 1 代表和 i 相邻的两个气球的序号。如果 i - 1或 i + 1 超出了数组的边界，
那么就当它是一个数字为 1 的气球。

求所能获得硬币的最大数量。

思路：

dp[i][j]  = x 表示，戳破气球i和气球j之间（开区间，不包括i和j）,的所有气球，
可以获得的最高分数为x。

那么根据这个定义，题目要求的结果就是dp[0][n+1]的值，而 base case 就是dp[i][j] = 0，
其中0 <= i <= n+1, j <= i+1，因为这种情况下，开区间(i, j)中间根本没有气球可以戳。

根据刚才对dp数组的定义，如果最后一个戳破气球k，dp[i][j]的值应该为：
dp[i][j] = dp[i][k] + dp[k][j] 
         + points[i]*points[k]*points[j]
你不是要最后戳破气球k吗？那得先把开区间(i, k)的气球都戳破，再把开区间(k, j)的气球都戳破；
最后剩下的气球k，相邻的就是气球i和气球j，这时候戳破k的话得到的分数就是points[i]*points[k]*points[j]。
*/

int maxCoins(vector<int>& nums)
{
	int n = nums.size();
	vector<int>points;
	//添加两侧的虚拟气球
	points.push_back(1);
	for(int i=0;i<n;i++){
		points.push_back(nums[i]);
	}
	points.push_back(1);
	//base case 初始化为0
	vector<vector<int>>dp(n+2,vector<int>(n+2,0));
	//i 从下往上遍历
	for(int i=n;i>=0;i--)
	{
		//j 从左往右 
		for(int j=i+1;j<n+2;j++)
		{
			//最后戳破的气球是哪一个？
			for(int k=i+1;k<j;k++){
				dp[i][j] = max(dp[i][j],dp[i][k]+dp[k][j]+points[i]*points[k]*points[j]);
			}
		}
	}
	return dp[0][n+1];
}




