/*215. 数组中的第K个最大元素
在未排序的数组中找到第 k 个最大的元素。请注意，你需要找的是数组排序后的第 k 个最大的元素，i
而不是第 k 个不同的元素。

*/

//排序 取nums[k-1]元素   时间复杂度O(NlogN)



//二叉堆 

/*
C++ 优先级队列 #include<queue>  

priority<int>a 默认是大堆顶 等同于 priority<int,vector<int>,less<int>>a;

小堆顶 priority<int,vector<int>,greater<int>>c; 

自定义类型
struct tmp1{
	int x;
	tmp1(int a) {x = a;}
	bool operator<(const tmp1& a) const
	{
		return x<a.x; // 大顶堆 
	}
};

//重写仿函数
strcut tmp2{
	bool operator()(tmp1 a,tmp1 b)
	{
		return a.x < b.x; // 大顶堆
	}
};

使用： priority<tmp1>d; 使用< 大顶堆
	   priority<tmp1,vector<tmp1>,tmp2>f;  



可以把小顶堆pq理解成一个筛子，较大的元素会沉淀下去，较小的元素会浮上来；当堆大小超过k的时候，
我们就删掉堆顶的元素，因为这些元素比较小，而我们想要的是前k个最大元素嘛。
当nums中的所有元素都过了一遍之后，筛子里面留下的就是最大的k个元素，
而堆顶元素是堆中最小的元素，也就是「第k个最大的元素」。
*/

// 时间复杂度 O(NlogK)  
int findKthLargest(vector<int>& nums,int k)
{
	//构造小堆顶 默认的priority_queue是大堆顶
	priority_queue<int,vector<int>,greater<int>>pri_q;
	for(int temp:nums){
		pri_q.push(temp);
		if(pri_q.size()>k){
			pri_q.pop();
		}
	}
	return pri_q.top();
}
//////////////////////////快速选择算法////////////////////////////

//时间复杂度 O(N)

void quickSort(vector<int>& nums,int left,int right)
{
	int privot = 0;
	if(left<right){
		privot = patirion(nums,left,right);
		quickSort(nums,left,privot-1);
		quickSort(nums,privot+1,right);
	}
}

int patition(vector<int>& nums,int left,int right)
{
	int key = nums[left];
	while(left<right){
		while(left<right&&nums[right]>=key)
			right--;
		nums[left]=nums[right];
		while(left<right&&nums[left]<=key)
			left++;
		nums[right]=nums[left];
	}
	nums[left]=key;
	return left;
}

///////////////////////
/*
我们刚说了，partition函数会将nums[p]排到正确的位置，使得nums[lo..p-1] < nums[p] < nums[p+1..hi]。

那么我们可以把p和k进行比较，如果p < k说明第k大的元素在nums[p+1..hi]中，
如果p > k说明第k大的元素在nums[lo..p-1]中。

所以我们可以复用partition函数来实现这道题目，不过在这之前还是要做一下索引转化：

题目要求的是「第k个最大元素」，这个元素其实就是nums升序排序后「索引」为len(nums) - k的这个元素。

*/
int findKthLargest(vector<int>& nums,int k)
{
	int left = 0,right = nums.size()-1;
	int kth = nums.size()-1; //kth 是数组最终的索引位置
	while(left<=right){
		int privot = patition(nums,left,right);
		if(privot<kth){
			left = privot+1;
		}else if(privot>kth){
			right = privot-1;
		}else{
			return nums[privot];
		}
	}
	return -1;
}



