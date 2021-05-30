/*
首先，讲解 Next Greater Number 的原始问题：给你一个数组，返回一个等长的数组，
对应索引存储着下一个更大元素，如果没有更大的元素，就存 -1。不好用语言解释清楚，直接上一个例子：
给你一个数组 [2,1,2,4,3]，你返回数组 [4,2,4,-1,-1]。

思路：
这个问题可以这样抽象思考：把数组的元素想象成并列站立的人，元素大小想象成人的身高。这些人面对你站成一列，
如何求元素「2」的 Next Greater Number 呢？很简单，如果能够看到元素「2」，
那么他后面可见的第一个人就是「2」的 Next Greater Number，因为比「2」小的元素身高不够，
都被「2」挡住了，第一个露出来的就是答案。
*/

//O(n)
vector<int> nextGreaterElement(vector<int>& nums)
{
	vector<int>res(nums.size());
	stack<int>Stk;
	for(int i=num.sizes()-1;i>=0;i--)  //倒着放
	{
		while(!Stk.empty()&&nums[i]>=Stk.top())  //判断个子高矮
			Stk.pop(); //矮个子起开 反正也被挡住了
		res[i]=Stk.empty()?-1:Stk.top(); //这个元素身后的第一个高个子
		Stk.push(nums[i]); //进入队列
	}
	return res;
}

/*
现在，你已经掌握了单调栈的使用技巧，来一个简单的变形来加深一下理解。

给你一个数组 T = [73, 74, 75, 71, 69, 72, 76, 73]，这个数组存放的是近几天的天气气温
（这气温是铁板烧？不是的，这里用的华氏度）。你返回一个数组，
计算：对于每一天，你还要至少等多少天才能等到一个更暖和的气温；如果等不到那一天，填 0 。

*/

vector<int> dailyTemperature(vector<int>& T)
{
	vector<int>res(T.size());
	stack<int>Stk; //这里放的是索引，不是元素
	for(int i=T.size()-1;i>=0;i--)
	{
		while(!Stk.empty() && T[i]>=T[Stk.top()])
			Stk.pop();
		res[i]=Stk.empty()?0:(Stk.top()-i);//得到了索引的间距
		Stk.push(i); //加入索引，而不是元素
	}
	return res;
}
// 503 下一个更大元素II
/* 同样是 Next Greater Number，现在假设给你的数组是个环形的，如何处理？
给你一个数组 [2,1,2,4,3]，你返回数组 [4,2,4,-1,4]。拥有了环形属性，
最后一个元素 3 绕了一圈后找到了比自己大的元素 4 。

你当然可以把这个双倍长度的数组构造出来，然后套用算法模板。
但是，我们可以不用构造新数组，而是利用循环数组的技巧来模拟。直接看代码吧：
*/

vector<int> nextGreaterElement(vector<int>& nums)
{
	int n = num.size();
	vector<int>res(n);
	Stack<int>Stk;
	for(int i=2*n-1;i>=0;i--)
	{
		while(!Stk.empty()&&nums[i%n]>=Stk.top())
			Stk.pop();
		res[i%n]=Stk.empty()?-1:Stk.top();
		Stk.push(nums[i%n]);
	}
	return res;
}

/*496  下一个更大元素 I
给你两个 没有重复元素 的数组 nums1 和 nums2 ，其中nums1 是 nums2 的子集。
请你找出 nums1 中每个元素在 nums2 中的下一个比其大的值。
nums1 中数字 x 的下一个更大元素是指 x 在 nums2 中对应位置的右边的第一个比 x 大的元素。
如果不存在，对应位置输出 -1 。

先对 nums2 中的每一个元素，求出它的右边第一个更大的元素；
将上一步的对应关系放入哈希表（HashMap）中；
再遍历数组 nums1，根据哈希表找出答案。

*/
unordered_map getnextGreater(vector<int>& nums)
{
	unordered_map<int,int>mp;
	int n=nums.size();
	stack<int>Stk;
	for(int i=n-1;i>=0;i--)
	{
		while(!Stk.empty()&&nums[i]>=Stk.top())
			Stk.pop();
		mp[nums[i]]=Stk.empty()?-1:Stk.top();
		Stk.push(nums[i]);
	}
	return mp;
}
vector<int> nextGreaterElement(vector<int>& nums1,vector<int>& nums2)
{
	unordered_map<int,int>mp=getnextGreater(nums2);
	vector<int>res;
	for(int i=0;i<nums1.size();i++)
	{
		if(mp.count(nums1[i])){
			res.push_back(mp[nums1[i]]);
		}
	}
	return res;
}


