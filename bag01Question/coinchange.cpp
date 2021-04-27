

/*
 * 凑零钱问题
给定不同面额的硬币 coins 和一个总金额 amount。编写一个函数来计算可以凑成总金额所需的最少的硬币个数。如果没有任何一种硬币组合能组成总金额，返回 -1。

你可以认为每种硬币的数量是无限的。

来源：力扣（LeetCode） 322
链接：https://leetcode-cn.com/problems/coin-change
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


int coinChange(vector<int>& coins,int amount)
{
    vector<int>dp(amount+1,amount+1);
    dp[0] = 0;
    for(int i=0;i<=amount;i++){
        for(int coin:coins)
        {
            //子问题无解，跳过
            if(i-coin<0) continue;
            dp[i]=min(dp[i],dp[i-coin]+1);
        }
    }
    return (dp[amount]==amount+1)?-1:dp[amount];
}





