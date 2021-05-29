/*121 买卖股票的最佳时机
给定一个数组 prices ，它的第 i 个元素 prices[i] 表示一支给定股票第 i 天的价格。
你只能选择 某一天 买入这只股票，并选择在 未来的某一个不同的日子 卖出该股票。
设计一个算法来计算你所能获取的最大利润。

返回你可以从这笔交易中获取的最大利润。如果你不能获取任何利润，返回 0 。

*/
int maxProft(vector<int>& prices)
{
	int res = 0;
	int curMin = prices[0];
	for(int sell=1;sell<prices.size();sell++)
	{
		curMin = min(curMin,prices[sell]);//curMin代表从当前位置及其以前的最小值
		res = max(res,prices[sell]-curMin);
	}
	return res;
}


/*122  买卖股票的最佳时机 II
给定一个数组 prices ，其中 prices[i] 是一支给定股票第 i 天的价格。
设计一个算法来计算你所能获取的最大利润。你可以尽可能地完成更多的交易（多次买卖一支股票）。
注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

思路：贪心算法  能赚一点是一点
*/
int maxProfit(vector<int>& price)
{
	int res = 0;
	for(int i=1;i<price.size();i++)
	{
		if(price[i]>price[i-1])
			res += price[i]-price[i-1];
	}
	return res;
}

/*188 买卖股票的最佳时机 IV
给定一个整数数组 prices ，它的第 i 个元素 prices[i] 是一支给定的股票在第 i 天的价格。
设计一个算法来计算你所能获取的最大利润。你最多可以完成 k 笔交易。
注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

*/
//O(k*N^2)
vector<vector<int>>memo;
int dp(int start,int k,vector<int>& prices)
{
	if(start >= prices) return 0;
	if( 0 == k) return 0;
	if(INT_MIN != memo[start][k]) return memo[start][k];
	int res = 0;
	int curMin=prices[start];
	for(int i=start+1;i<prices.size();i++)
	{
		curMin = min(curMin,prices[i]);
		res = max(res,dp(i+1,k-1,prices)+prices[i]-curMin,res);
	}
	memo[start][k] =res;
	return res;
}
int maxProfit(vector<int>& prices,int k)
{
	int n= prices.size();
	memo=vector<vector<int>>(n,vector<int>(k+1,INT_MIN));
	return dp(0,k,prices);
}



/*309. 最佳买卖股票时机含冷冻期
给定一个整数数组，其中第 i 个元素代表了第 i 天的股票价格 。​
设计一个算法计算出最大利润。在满足以下约束条件下，
你可以尽可能地完成更多的交易（多次买卖一支股票）:
你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
卖出股票后，你无法在第二天买入股票 (即冷冻期为 1 天)。

*/
//O(N^2)
vector<int>memo;
int dp(int start,vector<int>& prices)
{
	if(start>=prices.size()) return 0;
	if(memo[start]!=INT_MIN) return memo[start];
	int res = 0;
	int curMin=prices[start];
	for(int i=start+1;i<prices.size();i++)
	{
		curMin=min(curMin,prices[i]);
		res = max(res,dp(i+2,prices)+prices[i]-curMin);
	}
	memo[start]=res;
	return res;
}
int maxProfit(vector<int>& prices)
{
	int n=prices.size();
	memo=vector<int>(n,INT_MIN);
	return dp(0,prices);
}

/*714 买卖股票的最佳时机含手续费
给定一个整数数组 prices，其中第 i 个元素代表了第 i 天的股票价格 ；
非负整数 fee 代表了交易股票的手续费用。
你可以无限次地完成交易，但是你每笔交易都需要付手续费。如果你已经购买了一个股票，
在卖出它之前你就不能再继续购买股票了。
返回获得利润的最大值。
注意：这里的一笔交易指买入持有并卖出股票的整个过程，每笔交易你只需要为支付一次手续费。

*/
//O(N^2)
vector<int>fee;
int dp(int start,vector<int>& prices,int fee)
{
	if(start>=prices.size()) return 0;
	if(memo[start]!=INT_MIN) return memo[start];
	int res=0;
	int curMin=prices[start];
	for(int i=start+1,i<prices.size();i++)
	{
		curMin=min(curMin,prices[i]);
		res=max(res,dp(i+1,prices,fee)+prices[i]-curMin-fee);
	}
	memo[start]=res;
	return res;
}
int maxProfit(vector<int>& prices,int fee)
{
	int n=prices.size();
	memo=vector<int>(n,INT_MIN);
	return dp(0,prices,fee);
}

////////////////////////////////最优解法//////////////////////////////
/*
比如说 dp[3][2][1] 的含义就是：今天是第三天，我现在手上持有着股票，至今最多进行 2 次交易。
再比如 dp[2][3][0] 的含义：今天是第二天，我现在手上没有持有股票，至今最多进行 3 次交易。
很容易理解，对吧
dp[i][k][0] = max(dp[i-1][k][0],dp[i-1][k][i]+prices[i])
			  max(选择reset    ,选择sell)
今天我没有持有股票，两种可能：
要么我昨天就没有持有，
昨天持有，今天卖出了

dp[i][k][1] = max(dp[i-1][k][1],dp[i-1][k-1][0]-prices[1]);
昨天持有，今天也持有
昨天没有，今天有了，选择buy

base case

dp[-1][k][0]=dp[i][0][0] = 0;
dp[-1][k][1]=dp[i][0][1] =INT_MIN
*/

//309. 最佳买卖股票时机含冷冻期 O(N)
int maxProfit(vector<int>& prices) {
        int n= prices.size();
        vector<vector<int>>dp(n,vector<int>(2,INT_MIN));
        for(int i=0;i<n;i++)
        {
            if(i == 0){
                dp[0][0]=0;
                dp[0][1]=-prices[0];
                continue;
            }
            if(i == 1){
                dp[1][0]=max(0,prices[1]-prices[0]);
                dp[1][1]=max(-prices[0],-prices[1]);
                continue;

            }
            dp[i][0]=max(dp[i-1][0],dp[i-1][1]+prices[i]);
            dp[i][1]=max(dp[i-1][1],dp[i-2][0]-prices[i]);
        }
        return dp[n-1][0];
    }

//买卖股票的最佳时机含手续费

    int maxProfit(vector<int>& prices, int fee) {
        int size=prices.size();
        vector<vector<int>>dp(size,vector<int>(2,0));
        for(int i=0;i<size;i++)
        {
            if(i==0){
                dp[0][0] = 0;
                dp[0][1] = -prices[0]-fee;
                continue;
            }
            dp[i][0]=max(dp[i-1][0],dp[i-1][1]+prices[i]);
            dp[i][1]=max(dp[i-1][1],dp[i-1][0]-prices[i]-fee);
        }
        return dp[size-1][0];
    }


//188. 买卖股票的最佳时机 IV   K次交易
/*
一次交易由买入和卖出构成，至少需要两天。所以说有效的限制次数 k 应该不超过 n/2，
如果超过，就没有约束作用了，相当于 k = +infinity。这种情况是之前解决过的。
*/
    int help(vector<int>& prices)   //k 等于无穷
    {
        int res = 0;
        for(int i=1;i<prices.size();i++)
        {
            if(prices[i]>prices[i-1])
                res+=prices[i]-prices[i-1];
        }
        return res;
    }


    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        if(k>n/2) return help(prices);
        vector<vector<vector<int>>>dp(n,vector<vector<int>>(k+1,vector<int>(2,0)));
        for(int i=0;i<n;i++)
        {
            for(int j=k;j>=1;j--){
                if(i == 0){
                    dp[0][j][0]=0;
                    dp[0][j][1]=-prices[0];
                    continue;
                }
                dp[i][j][0]=max(dp[i-1][j][0],dp[i-1][j][1]+prices[i]);
                dp[i][j][1]=max(dp[i-1][j][1],dp[i-1][j-1][0]-prices[i]);
            }
        }
        return dp[n-1][k][0];
    }
