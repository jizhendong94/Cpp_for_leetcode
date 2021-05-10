
/*354   俄罗斯套娃信封问题

  给你一个二维整数数组 envelopes ，其中 envelopes[i] = [wi, hi] ，表示第 i 个信封的宽度和高度。
  当另一个信封的宽度和高度都比这个信封大的时候，这个信封就可以放进另一个信封里，如同俄罗斯套娃一样。
  请计算 最多能有多少个 信封能组成一组“俄罗斯套娃”信封（即可以把一个信封放到另一个信封里面）。
  注意：不允许旋转信封。

  思路：
  先对宽度w进行升序排序，如果遇到w相同的情况，则按照高度h降序排序。
  之后把所有的h作为一个数组，在这个数组上计算 LIS 的长度就是答案。
 */



//最长递增子序列
int longestLIS(vector<int>& height)
{
    if(height.size()==0) return 0;
    vector<int>dp(height.size(),1);
    for(int i=1;i<height.size();i++)
    {
        for(int j=0;j<i;j++)
        {
            if(height[j]<height[i]){
                dp[i]=max(dp[i],dp[j]+1);
            }
        }
    }
    int res = 0;
    for(int i=0;i<dp.size();i++)
        res = max(res,dp[i]);
    return res;
}


int maxEnvelopes(vector<vector<int>>& envelopes) {
    if(envelopes.size() ==0 ) return 0;
    sort(envelopes.begin(),envelopes.end(),[](vector<int>& v1,vector<int>& v2){
            if(v1[0] == v2[0]) return v1[1]>v2[1];
            return v1[0]<v2[0];
            });
    vector<int>height;
    for(auto h:envelopes){
        height.push_back(h[1]);
    }

    return longestLIS(height);
}




