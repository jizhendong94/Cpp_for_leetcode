/*931 下降路径最小和
  给你一个 n x n 的 方形 整数数组 matrix ，请你找出并返回通过 matrix 的下降路径 的 最小和 。

  下降路径 可以从第一行中的任何元素开始，并从每一行中选择一个元素。
  在下一行选择的元素和当前行所选元素最多相隔一列（即位于正下方或者沿对角线向左或者向右的第一个元素）
  。具体来说，
  位置 (row, col) 的下一个元素应当是 (row + 1, col - 1)、(row + 1, col) 或者 (row + 1, col + 1) 。

 */
vector<vector<int>>memo;

int dp(vector<vector<int>>& matrix,int i,int j)
{
	if(i<0||j<0||i>=matrix.size()||j>=matrix[0].size()) return INT_MAX;
	if(i == 0) return maxtrix[0][j];
	if(memo[i][j]!=INT_MAX) return memo[i][j];

	memo[i][j]=matrix[i][j]+min_three(dp(matrix,i-1,j),dp(matrix,i-1,j-1),dp(matrix,i-1,j+1));

	return memo[i][j];
}
int minFallingPathSum(vector<vector<int>>& matrix) {
	int n = matrix.size();
	int res = INT_MAX;
	memo=vector<vector<int>>(n,vector<int>(n,INT_MAX));
	for(int j=0;j<n;j++)
		res = min(res,dp(matrix,n-1,j));
	return res;
}


/*64 最小路径和

  给定一个包含非负整数的 m x n 网格 grid ，请找出一条从左上角到右下角的路径，
  使得路径上的数字总和为最小。

  说明：每次只能向下或者向右移动一步。

 */

int minPathSum(vector<vector<int>>& grid) {
	int m = grid.size();
	int n = grid[0].size();
	vector<vector<int>>dp(m,vector<int>(n,0));
	//base case
	dp[0][0] = grid[0][0];

	for(int i=1;i<m;i++)
		dp[i][0]=dp[i-1][0]+grid[i][0];
	for(int j=1;j<n;j++)
		dp[0][j]=dp[0][j-1]+grid[0][j];

	//状态转移
	for(int i=1;i<m;i++)
	{
		for(int j=1;j<n;j++){
			dp[i][j]=min(dp[i-1][j],dp[i][j-1])+grid[i][j];
		}
	}
	return dp[m-1][n-1];
}


/*offer  47 礼物的最大价值
  在一个 m*n 的棋盘的每一格都放有一个礼物，每个礼物都有一定的价值（价值大于 0）。
  你可以从棋盘的左上角开始拿格子里的礼物，并每次向右或者向下移动一格、直到到达棋盘的右下角。
  给定一个棋盘及其上面的礼物的价值，请计算你最多能拿到多少价值的礼物？

 */

int maxValue(vector<vector<int>>& grid) {
	int m = grid.size();
	int n =grid[0].size();

	vector<vector<int>>dp(m,vector<int>(n,0));
	dp[0][0] = grid[0][0];

	for(int i=1;i<m;i++)
		dp[i][0]=dp[i-1][0]+grid[i][0];
	for(int j=1;j<n;j++)
		dp[0][j]=dp[0][j-1]+grid[0][j];
	for(int i=1;i<m;i++)
	{
		for(int j=1;j<n;j++){
			dp[i][j]=max(dp[i-1][j],dp[i][j-1])+grid[i][j];
		}
	}
	return dp[m-1][n-1];
}









