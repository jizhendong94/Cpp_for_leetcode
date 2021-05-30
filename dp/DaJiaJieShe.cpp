/*198  打家劫舍
你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，
影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，
如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。

给定一个代表每个房屋存放金额的非负整数数组，计算你 不触动警报装置的情况下 ，一夜之内能够偷窃到的最高金额。

dp[i]=x 表示从第i间房子开始抢劫，最多能抢到的钱为x
base case: dp[n] = 0;

dp[i] = max(dp[i+1],nums[i]+dp[i+2])
			不抢，去下家   抢，去下下家  取最大值
*/


int rob(vector<int>& nums)
{
	int n = nums.size();
	vector<int>dp(n+2,0);
	for(int i=n-1;i>=0;i--){
		dp[i]=max(dp[i+1],nums[i]+dp[i+2]);
	}
	return dp[0];
}



/*213  打家劫舍 II
这道题目和第一道描述基本一样，强盗依然不能抢劫相邻的房子
，输入依然是一个数组，但是告诉你这些房子不是一排，而是围成了一个圈

思路：首先，首尾房间不能同时被抢，那么只可能有三种不同情况：要么都不被抢；
要么第一间房子被抢最后一间不抢；要么最后一间房子被抢第一间不抢。

只要比较情况二和情况三就行了，因为这两种情况对于房子的选择余地比情况一大呀，
房子里的钱数都是非负数，所以选择余地大，最优决策结果肯定不会小。
*/
int robcore(vector<int>& V)
{
	int n = V.size();
	vector<int>dp(n+2,0);
	for(int i=n-1;i>=0;i--){
		dp[i]=max(dp[i+1],V[i]+dp[i+2]);
	}
	return dp[0];
}
int rob(vector<int>& nums)
{
	int n=nums.size();
	if(0 == n) return 0;
	if(1 == n) return nums[0];
	vector<int>V1;
	vector<int>V2;
	for(int i=1;i<n;i++)
		V1.push_back(nums[i]); //第一家不抢
	for(int i=0;i<n-1;i++)
		V2.push_back(nums[i]); //最后一家不抢
	return max(robcore(V1),robcore(V2));
}

/*337 打家劫舍 III
此强盗发现现在面对的房子不是一排，不是一圈，而是一棵二叉树！房子在二叉树的节点上，
相连的两个房子不能同时被抢劫：

O(N)
*/
map<TreeNode*,int>memo;
int rob(TreeNode* root)
{
	if(nullptr == root) return 0;
	//备忘录 消除重叠子问题
	if(memo.count(root)) return memo[root];
	//抢，然后去下下家
	int do_it = root->val + (root->left==nullptr?0:rob(root->left->left)+rob(root->left->right))+
							(root->right==nullptr?0:rob(root->right->left)+rob(root->right->right));
	// 不抢，然后去下家
	int not_do = rob(root->left)+rob(root->right);
	int res = max(do_it,not_do);
	memo[root]=res;
	return res;
}







