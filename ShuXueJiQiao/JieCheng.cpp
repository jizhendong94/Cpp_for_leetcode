/*172 阶乘后的零
给定一个整数 n，返回 n! 结果尾数中零的数量。
思路：
首先，两个数相乘结果末尾有 0，一定是因为两个数中有因子 2 和 5，因为 10 = 2 x 5。
 也就是说，问题转化为：n!最多可以分解出多少个因子 2 和 5？
 比如说n = 25，那么25!最多可以分解出几个 2 和 5 相乘？这个主要取决于能分解出几个因子 5，i
 因为每个偶数都能分解出因子 2，因子 2 肯定比因子 5 多得多。

 现在，问题转化为：n!最多可以分解出多少个因子 5

 难点在于像 25，50，125 这样的数，可以提供不止一个因子 5，怎么才能不漏掉呢？

这样，我们假设n = 125，来算一算125!的结果末尾有几个 0：

首先，125 / 5 = 25，这一步就是计算有多少个像 5，15，20，25 这些 5 的倍数，它们一定可以提供一个因子 5。

但是，这些足够吗？刚才说了，像 25，50，75 这些 25 的倍数，可以提供两个因子 5，i
那么我们再计算出125!中有 125 / 25 = 5 个 25 的倍数，它们每人可以额外再提供一个因子 5。

够了吗？我们发现 125 = 5 x 5 x 5，像 125，250 这些 125 的倍数，可以提供 3 个因子 5，
那么我们还得再计算出125!中有 125 / 125 = 1 个 125 的倍数，它还可以额外再提供一个因子 5。

这下应该够了，125!最多可以分解出 20 + 5 + 1 = 26 个因子 5，也就是说阶乘结果的末尾有 26 个 0。
*/

//O(logN)
int trailingZeroes(int n){
	int res = 0;
	long divisor = 5;
	while(divisor <= n){
		res += n/divisor;
		divisor *=5;
	}
	return res;
}



/* 793 阶乘函数后 K 个零
 f(x) 是 x! 末尾是 0 的数量。（回想一下 x! = 1 * 2 * 3 * ... * x，且 0! = 1 ）

例如， f(3) = 0 ，因为 3! = 6 的末尾没有 0 ；而 f(11) = 2 ，因为 11!= 39916800 末端有 2 个 0 。
给定 K，找出多少个非负整数 x ，能满足 f(x) = K 。

*/
//注意为了避免整型溢出的问题，trailingZeroes函数需要把所有数据类型改成 long：
long trailingZeroes(int n){
	long res = 0;
	long divisor = 5;
	while(divisor <= n){
		res += n/divisor;
		divisor *= 5;
	}
	return res;
}

long left_bound(int target)
{
	long left = 0,right = LONG_MAX;
	while(left<=right){
		long mid = left + (right -left)/2;
		if(trailingZeroes(mid)<target){
			left = mid + 1;
		}else if(trailingZeroes(mid)>target){
			right = mid - 1;
		}else{
			right = mid - 1;
		}
	}
	return left;
}

long right_bound(int target){
	long left = 0,right = LONG_MAX;
	while(left<=right){
		long mid = left + (right-left)/2;
		if(trailingZeroes(k)<target){
			left = mid + 1;
		}else if(trailingZeroes(k)>target){
			right = mid - 1;
		}else{
			left = mid + 1;
		}
	}
	return right;
}
//O(logN *logN)
int preimageSizeFZF(int k){
	//左边界和右边届只差 + 1 就是答案
	return (right_bound(k)-left_bound(k)+1);
}








