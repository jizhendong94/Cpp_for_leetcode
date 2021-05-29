#include<iostream>
#include<vector>
using namespace std;
/*887. 鸡蛋掉落

# 当前状态为 (K 个鸡蛋，N 层楼)
# 返回这个状态下的最优结果
def dp(K, N):


递归的 base case 很容易理解：当楼层数N等于 0 时，显然不需要扔鸡蛋；
当鸡蛋数K为 1 时，显然只能线性扫描所有楼层：


如果鸡蛋碎了，那么鸡蛋的个数K应该减一，搜索的楼层区间应该从[1..N]变为[1..i-1]共i-1层楼；

如果鸡蛋没碎，那么鸡蛋的个数K不变，搜索的楼层区间应该从 [1..N]变为[i+1..N]共N-i层楼。


def dp(K, N):
    for 1 <= i <= N:
        # 最坏情况下的最少扔鸡蛋次数
        res = min(res,
                  max(
                        dp(K - 1, i - 1), # 碎
                        dp(K, N - i)      # 没碎
                     ) + 1 # 在第 i 楼扔了一次
                 )
    return res
 */
//时间复杂度  O(K*N^2)
vector<vector<int>>memo;
int dp(int k ,int n)
{
	if(1 == k) return n;
	if(0 == n) return 0;

	if(memo[k][n] != INT_MAX) return memo[k][n];
	int res = INT_MAX;
	for(int i=1;i<=n;i++){
		res = min(res,
				max(dp(k,n-i),dp(k-1,i-1))+1
				);
	}
	memo[k][n]=res;
	return res;
}
int superEggDrop(int k, int n) {
	memo=vector<vector<int>>(k+1,vector<int>(n+1,INT_MAX));
	return dp(k,n);
}

// 二分查找优化 O(K*N*logN)
int dp2(int k,int n)
{
	if(k == 1) return n;
	if(n == 0) return 0;

	if(memo[k][n] != INT_MAX) return memo[k][n];
	int res = INT_MAX;
	int left = 1,right = n; // left = 1 不能=0
	while(left<=right){
		mid=left+(right-left)/2;
		int broken = dp(k-1,i-1);//碎了
		int not_broken = dp(k,n-i);//没有碎
		//res = min(res,max(碎，没碎)+1)
		if(broken>not_broken){
			right = mid-1;
			res = min(res,broken+1);  // + 1
		}else{
			left = mid+1;
			res = min(res,not_broken+1); //  + 1 
		}
	}
	memo[k][n]=res;
	return res;
}
int main()
{
	cout<<superEggDrop(2,6)<<endl;
	cout<<superEggDrop(3,14)<<endl;
	return 0;
}








