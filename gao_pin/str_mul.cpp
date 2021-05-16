/*43  字符串相乘

给定两个以字符串形式表示的非负整数 num1 和 num2，返回 num1 和 num2 的乘积，它们的乘积也表示为字符串形式。

*/

string multiply(string num1,string num2)
{
	int m=num1.size(),n=num2.size();
	//最多m+n 位数
	vector<int>(m+n,0);

	//从个位数开始相乘
	for(int i=m-1;i>=0;i--)
	{
		for(int j=n-1;j>=0;j--)
		{
			int mul = (num1[i]-'0')*(num2[j]-'0');
			//乘积在res对应的索引位置
			int p1=i+j,p2=i+j+1;
			//叠加到 res 上
			int sum = mul + res[p2];
			res[p2] = sum%10;
			res[p1] += sum/10;
		}

	}
	//前缀可能存在的0
	int i=0;
	while(i<res.size()&&res[i]==0) i++;
	//将计算结果转化成字符串
	string str;
	for(;i<res.size();i++)
		str.push_back(res[i]+'0');
	return str.size()==0?"0":str;
}
