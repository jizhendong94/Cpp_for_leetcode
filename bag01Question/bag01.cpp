//0-1 背包问题
/*
 给你一个可装载重量为W的背包和N个物品，每个物品有重量和价值两个属性
 。其中第i个物品的重量为wt[i]，价值为val[i]，现在让你用这个背包装物品，最多能装的价值是多少？

 */
//dp[i][w]表示：对于前i个物品，当前背包的容量为w时，这种情况下可以装下的最大价值是dp[i][w]。
//base case base case 就是dp[0][..] = dp[..][0] = 0，因为没有物品或者背包没有空间的时候，能装的最大价值就是 0。
int knapsack(int W,int N,vector<int>& wt,vector<int>& val)
{
    //vector全填入0 base case 已经初始化
    vector<vector<int>>dp(N+1,vector<int>(W+1,0));
    for(int i=1;i<=n;i++)
    {
        for(int w=1;w<=W;w++)
        {
            //当前背包容量装不下，只能选择不装入背
            if(w-wt[i-1]<0){
                dp[i][w]=dp[i-1][w];
            }
            else{
                //装入或者不装入 择优
                dp[i][w]=max(dp[i-1][w-wt[i-1]]+val[i-1],dp[i-1][w]);
            }
        }
    }
    return dp[N][W];
}

/*
给你一个 只包含正整数 的 非空 数组 nums 。
请你判断是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。
转化为背包问
*/

//dp[i][j] = x表示，对于前i个物品，当前背包的容量为j时，若x为true，则说明可以恰好将背包装满，
//若x为false，则说明不能恰好将背包装满。
//根据这个定义，我们想求的最终答案就是dp[N][sum/2]，base case 就是dp[..][0] = true和dp[0][..] = false，
//因为背包没有空间的时候，就相当于装满了，而当没有物品可选择的时候，肯定没办法装满背包。
bool canPartition(vector<int>& nums)
{
    int sum = 0;
    for(int num:nums) sum+=num;
    if(sum%2!=0) return false;
    int n=nums.size();
    sum=sum/2;
    vector<vector<bool>>dp(n+1,vector<bool>(sum+1,false));
    for(int i=0;i<=n;i++)
        dp[i][0]=true;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=sum;j++)
        {
            if(j-sum[i-1]<0){
                dp[i][j]=dp[i-1][j];
            }
            else{
                dp[i][j]=dp[i-1][j]||dp[i-1][j-nums[i-1]]
            }
        }
    }
    return dp[n][sum];
}


/*
 *给定不同面额的硬币和一个总金额。写出函数来计算可以凑成总金额的硬币组合数。
 假设每一种面额的硬币有无限个。

 完全背包问:

 有一个背包，最大容量为amount，有一系列物品coins，每个物品的重量为coins[i]，
 每个物品的数量无限。请问有多少种方法，能够把背包恰好装满
*/
// 若只使用coins中的前i个硬币的面值，若想凑出金额j，有dp[i][j]种凑法。
//base case 为dp[0][..] = 0， dp[..][0] = 1。因为如果不使用任何硬币面值，就无法凑出任何金额；
//如果凑出的目标金额为 0，那么“无为而治”就是唯一的一种凑法。

int coinchange2(int amount,vector<int>& coins)
{
    int n = coins.length();
    vector<vector<int>>dp(n+1,vector<int>(amount+1,0));
    for(int i=0;i<=n;i++)  //i=1 i=0 start all OK 
        dp[i][0] = 1;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=amount;j++)
        {
            if(j-coins[i-1] >= 0)
                dp[i][j]=dp[i-1][j] + dp[i][j-coins[i-1]];
            else
                dp[i][j]=dp[i-1][j];
        }
    }
    return dp[n][amount];
}

/*322  零钱兑换 凑硬币 1 
dp[i] = x表示，当目标金额为i时，至少需要x枚硬币。

*/

int coinChange1(vector<int>& coins,int amount)
{
    //数组大小为amount+1  初始值amount+1
    vector<int>dp(amount+1,amount+1);
    //base case 
    dp[0]=[0];
    for(int i=0;i<dp.size();i++)
    {
        for(int coin:coins){
            //子问题无解  跳过
            if(i-coin<0) continue;
            dp[i]=min(dp[i],1 + dp[i-coin]);
        }
    }
    return (dp[amount] == amount+1?-1:dp[amount]);
}





/*
 *回溯和递归  目标和  494
 给定一个非负整数数组，a1, a2, ..., an, 和一个目标数，S。现在你有两个符号 + 和 -。
 对于数组中的任意一个整数，你都可以从 + 或 -中选择一个符号添加在前面。

返回可以使最终数组和为目标数 S 的所有添加符号的方法数。

*/

//回溯

map<string,int>memo;
int dp(vector<int>& nums,int i,int rest)
{
    if(i == nums.size()){
        if(rest == 0) return 1;
        return 0;
    }
    string key = to_string(i)+","+to_string(rest);
    if(memo.count(key)) return memo[key];
    int res = dp(nums,i+1,rest-nums[i]) + dp(nums,i+1,rest+nums[i]);
    memo[key]=res;
    return res;
}

int findTargetSumWay(vector<int>& nums,int target)
{
    if(nums.size() == 0) return 0;
    return dp(nums,0,target);
}

//dp
/*
 *首先，如果我们把 nums 划分成两个子集 A 和 B，分别代表分配 + 的数和分配 - 的数，
 那么他们和 target 存在如下关系：

sum(A) - sum(B) = target
sum(A) = target + sum(B)
sum(A) + sum(A) = target + sum(B) + sum(A)
2 * sum(A) = target + sum(nums)
综上，可以推出 sum(A) = (target + sum(nums)) / 2，也就是把原问题转化成：nums 中存在几个子集 A，
使得 A 中元素的和为 (target + sum(nums)) / 2？
*/
int subset(vector<int>& nums,int sum)
{
    int n = nums.size();
    vector<vector<int>>dp(n+1,vector<int>(sum+1));
    for(int i=0;i<=n;i++)
        dp[i][0] = 1;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=sum;j++)
        {
            if(j-nums[i-1]>=0)
                dp[i][j]=dp[i-1][j]+dp[i-1][j-nums[i-1]];
            else
                dp[i][j]=dp[i-1][j];
        }
    }
    return dp[n][sum];
}

int findTargetSumWay(vector<int>& nums,int target)
{
    int sum = 0;
    for(int n:sum) sum+=n;
    if(sum<target || (sum+target)%2 == 1)
        return 0;

    return subset(nums,(sum+target)/2);
}












