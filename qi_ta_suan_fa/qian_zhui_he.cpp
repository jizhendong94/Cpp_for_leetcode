/*560. 和为K的子数组
算出一共有几个和为 k 的连续子数组。

思路：
这个前缀和数组preSum的含义也很好理解，preSum[i]就是nums[0..i-1]的和。
那么如果我们想求nums[i..j]的和，只需要一步操作preSum[j+1]-preSum[i]即可，而不需要重新去遍历数组了
*/

//时间复杂度O(N^2)  空间O(N)  //可能超时
int subarraySum(vector<int>& nums,int k)
{
    int n = num.size();
    //构造前缀和    
    vector<int>sum(n+1,0);
    for(int i=0;i<n;i++){
        sum[i+1] = sum[i]+nums[i];
    }   

    int res = 0;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<i;j++)
        {
            // sum of nums[j...i-1]
            if(sum[i]-sum[j] == k)
                res++;
        }
    }
    return res;
}


//优化思路：我直接记录下有几个 sum[j] 和 sum[i] - k 相等，直接更新结果，
//就避免了内层的 for 循环。我们可以用哈希表，在记录前缀和的同时记录该前缀和出现的次数。

//时间复杂度O(N)
int subarraySum(vector<int>& nums,int k)
{
    int n = nums.size();

    unordered_map<int,int>mp;
    mp[0]=1;
    int res = 0,sum0_i = 0;
    for(int i=0;i<n;i++){
        sum0_i += nums[i];

        int sum0_j = sum0_i - k;

        if(mp.count(sum0_j)){
            res += mp[sum0_j];
        }

        mp[sum0_i] += 1;
    }
    return res;
}



