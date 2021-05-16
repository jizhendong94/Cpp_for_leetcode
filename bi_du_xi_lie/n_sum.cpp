/*1 两数之和
  给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出和为目标值的那两个整数，
  并返回它们的数组下标。
  你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。
  你可以按任意顺序返回答案。

 */

// hash表  题目要求返回索引值 所以不能排序 打乱顺序
vector<int> twoSum(vector<int>& nums,int target)
{
	vector<int>res;
	unordered_map<int,int>mp;
	for(int i=0;i<nums.size();i++){
		if(mp.count(target-nums[i])){
			res.push_back(i);
			res.push_back(mp[target-nums[i]]);
		}else
			mp[nums[i]]=i;
	}
	return res;
}


// two sum  改编1
/*
   这里我来编一道 twoSum 题目，不要返回索引，返回元素的值：
   如果假设输入一个数组 nums 和一个目标和 target，请你返回 nums 中能够凑出 target 的两个元素的值，
   比如输入 nums = [5,3,1,6], target = 9，那么算法返回两个元素 [3,6]。可以假设只有且仅有一对儿元素可以凑出 target。

   有且仅有一对儿元素

 */

vector<int> twoSum(vector<int>& nums,int target)
{
	sort(nums.begin(),nums.end());

	int left = 0,right = nums.size()-1;
	while(left < right){
		int sum = nums[left] + nums[right];
		if(sum < target){
			left++;
		}else if(sum > target){
			right--;
		}else if(sum == target){
			return {nums[left],nums[right]};
		}
	}
	return {};
}


//two Sum 改编2
/*
   nums 中可能有多对儿元素之和都等于 target，请你的算法返回所有和为 target 的元素对儿，其中不能出现重复。
   对于修改后的问题，关键难点是现在可能有多个和为 target 的数对儿，还不能重复，
   比如上述例子中 [1,3] 和 [3,1] 就算重复，只能算一次

   O(NlogN)
 */

vector<vector<int>> twoSumTarget(vector<int>& nums,int target)
{
	sort(nums.begin(),nums.end());
	int left = 0,right = nums.size()-1;
	vector<vector<int>>res;
	while(left < right){
		int sum = nums[left] + nums[right];
		int l_num = nums[left],r_num = nums[right];
		if(sum < target){
			while(left < right && nums[left] == l_num) left++;
		}else if(sum > target){
			while(left < right && nums[right] == r_num) right--;
		}else if(sum == target){
			res.push_back({left,right});
			while(left < right && nums[left] == l_num) left++;
			while(left < right && nums[right] == r_num) right--;
		}
	}
	return res;
}

//three Sum 


//four Sum


// N Sum  
// Warning 调用这个函数之前 一定要给 nums 排序
/*
   需要注意的是，调用这个 nSum 函数之前一定要先给 nums 数组排序，因为 nSum 是一个递归函数，
   如果在 nSum 函数里调用排序函数，那么每次递归都会进行没有必要的排序，效率会非常低。

// n 为 4，从 nums[0] 开始计算和为 target 的四元组
return nSumTarget(nums, 4, 0, target);
// n 为 3，从 nums[0] 开始计算和为 0 的三元组
return nSumTarget(nums, 3, 0, 0);
 */

sort(nums.begin(),nums.end());

vector<vector<int>> nSumTarget(vector<int>& nums,int n,int start,int target)
{
	int sz = nums.size();
	vector<vector<int>>res;
	//至少是2Sum  且数组大小不应该小于n
	if(n<2 || sz<n) return res;
	//2 Sum  base case
	if(2 == n){
		int left = start,right=sz-1;
		while(left < right){
			int sum = nums[left]+nums[right];
			int l_num = nums[left],r_num=nums[right];
			if(sum < target){
				while(left < right && nums[left] == l_num) left++;
			}else if(sum > target){
				while(left < right && nums[right] == r_num) right--;
			}else if(sum == target){
				res.push_back({left,right});
				while(left < right && nums[left] == l_rum) left++;
				while(left < right && nums[right] == r_num) right--;
			}
		}
	}else {
		// n>2 时  递归计算(n-1)Sum的结果
		for(int i = start;i<sz;i++){
			vector<vector<int>>sub = nSumTarget(nums,n-1,i+1,target-nums[i]);
			for(vector<int>& arr :sub){
				//(n-1)Sum 加上 nums[i] 就是 nSum
				arr.push_back(nums[i]);
				res.push_back(arr);
			}
			while(i<sz-1 && nums[i]==nums[i+1]) i++;
		}
	}
	return res;

}







