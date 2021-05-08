
int binary_search(vector<int>& nums,int target)
{
	int left = 0,right = num.size()-1;
	while(left<=right){
		int mid=left+(right-left)/2;
		if(nums[mid]<target){
			left =mid+1;
		}else if(nums[mid]>target){
			right=mid-1;
		}else if(nums[mid]==target){
			//直接返回
			return mid;
		}
	}
	return -1；
}



int left_bound(vector<int>& nums,int target)
{
	int left = 0,right=nums.size()-1;
	while(left<=right){
		int mid=left+(right-left)/2;
		if(nums[mid]<target){
			left = mid+1;
		}else if(nums[mid]>target){
			right=mid-1;
		}else if(nums[mid]==target){
			//别直接返回，锁定左侧边界
			right = mid -1;
		}
	}
	//检查left的越界情况
	if(left >= num.size() || nums[left]!=target)
		return -1;
	return left;
}


int right_bound(vector<int>& nums,int target)
{
	int left=0,right = nums.size()-1;
	while(left<=right)
	{
		int mid=left+(right-left)/2;
		if(nums[mid]<target){
			left=mid+1;
		}else if(nums[mid]>target){
			right=mid-1;
		}else if(nums[mid]==target){
			//别返回，锁定右边边界
			left =mid+1;
		}
	}
	//最后要检查right越界情况。
	if(right<0 || nums[right]!=target)
		return -1;
	return right;
}
