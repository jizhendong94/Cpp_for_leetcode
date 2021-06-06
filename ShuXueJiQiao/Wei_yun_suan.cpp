#include<iostream>
using namespace std;
/*

1. 利用 或操作'|' 和空格 将英文字母转换为小写
('a'|' ') = 'a'
(‘A’|' ') = 'a'

2. 利用与操作'&'和下划线将英文字母转换为大写
('b' & '_')= 'B'
('B' & '_')= 'B'

3. 利用异或'^' 和空格 进行英文大小写转换
('d' ^ ' ') = 'D'
('D' ^ ' ') = 'd'

4. 判断两个数是否异号  利用补码编码的符号位
int x = -1,y = 2;
bool f = ((x^y)<0); //true;

int x = 3,y=2;
bool f= ((x^y)<0)  //false;

5. 不用临时变量交换两个数
int a=1,b=2;
a ^= b;
b ^= a;
a ^= b;

6. 加1
int n= 1;
n = -~n;

7. 减一
int n = 2;
n = ~-n;
*/
//////////////////////////////////////////////////

/*算法常用操作
n&(n-1) 消除数字n的二进制表示中的最后一个1 

//191 位1的个数
int hammingWeight(uint32_t n){
	int res = 0;
	while(n){
		res++;
		n = n&(n-1);
	}
	return res;
}

//判断一个数是不是2的指数 
如果一个数是2的指数，那么它的二进制表示一定只含有一个1 :
bool isPowerOfTwo(int n){
	if(n<=0) return false;
	return (n&(n-1))==0;
}

//136 只出现一次的数字 给定一个非空的数组，除了某个元素只出现一次以外，其余元素均出现了两次，
找出那个只出现了一次的元素。

一个数和它本身做异或运算结果为 0，即 a ^ a = 0；一个数和 0 做异或运算的结果为它本身，即 a ^ 0 = a。

int singleNumber(vector<int>& nums){
	int res = 0;
	for(int n:nums){
		res ^= n;
	}
	return res;
}



*/
int main()
{
	int a=1,b=2;
	a = -~a;
	a = -~a;

	b = ~-b;
	b = ~-b;
	cout<<a<<"  "<<b<<endl;
}
