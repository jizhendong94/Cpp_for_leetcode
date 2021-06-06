/*返回区间[2,n)中有多少个素数


*/

int countPrime(int n)
{
	vector<int>isPrim(n,true);

	for(int i=2;i*i<n;i++){
		if(isPrim[i]){
			for(int j=2*i;j<n;j=j+i)
				isPrim[j]=false;
		}
	}

	int res = 0;
	for(int i=2;i<n;i++)
	{
		if(isPrim[i])
			res++;
	}
	return res;
}


