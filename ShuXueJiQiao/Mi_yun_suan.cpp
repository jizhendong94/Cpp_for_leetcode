/*372 超级次方
你的任务是计算 ab 对 1337 取模，a 是一个正整数，b 是一个非常大的正整数且会以数组形式给出。
*/
int base = 1337;
int mypow(int a,int k)
{
	if(k == 0) return 1;
	//对因子求模
	a%=base;
	if(k%2==1){
		return (a*mypow(a,k-1))%base;
	}else{
		int sub = mypow(a,k/2);
		return (sub*sub)%base;
	}
}

int superPow(int a,vector<int>& b)
{
	//递归的base case
	if(b.empty()) return 1;
	//取出最后一个数
	int last = b.back();
	b.pop_back();
	//将原问题简化，缩小规模求解
	int part1 = mypow(a,last);
	int part2 = mypow(superPow(a,b),10);
	//求模
	return (part1*part2)%base;
}



