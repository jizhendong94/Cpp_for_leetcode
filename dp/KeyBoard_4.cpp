#include<iostream>
#include<vector>
using namespace std;
/*4键 键盘
假设你有一个特殊的键盘，包含下面的按键：
Key1 : (A) :在屏幕上打印一个A
Key2: (ctrl-A): 选中整个屏幕
Key3: (ctrl-C): 复制整个区域
Key4: (ctrl-V): 将缓冲区内容输出到上次结束位置

现在可以按键N次，请问屏幕上最多可以显示几个'A'

思路：int[] dp = new int[N + 1];
	// 定义：dp[i] 表示 i 次操作后最多能显示多少个 A
for (int i = 0; i <= N; i++) 
    dp[i] = max(
            这次按 A 键，
            这次按 C-V
        )

// 按 A 键，就比上次多一个 A 而已
dp[i] = dp[i - 1] + 1;

刚才说了，最优的操作序列一定是C-A C-C接着若干C-V，所以我们用一个变量j作为若干C-V的起点。
那么j之前的 2 个操作就应该是C-A C-C了：
*/

int MaxA(int N)
{
	vector<int>dp(N+1,0);
	for(int i=1;i<=N;i++)
	{
		//按A键
		dp[i]=dp[i-1]+1;
		for(int j=2;j<i;j++){
			//全选&复制dp[j-2]
			//屏幕上共有dp[j-2]*(i-j+1) 个A
			dp[i]=max(dp[i],dp[j-2]*(i-j+1));
		}
	}

	return dp[N];
}

int main()
{
	cout<<MaxA(3)<<endl;
	cout<<MaxA(7)<<endl;
	return 0;
}
