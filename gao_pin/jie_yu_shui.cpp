/*42  接雨水
  给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。


  思路：
  water[i] = min(
# 左边最高的柱子
max(height[0..i]),
# 右边最高的柱子
max(height[i..end])
) - height[i]
 */


//暴力解法
//时间复杂度 O(N^2)，空间复杂度 O(1)
int trap(vector<int>& height) {
    int n = height.size();
    int res = 0;
    for(int i=0;i<n;i++){
        int l_max=0,r_max=0;
        //找到右边最高的柱子
        for(int j=i;j<n;j++){
            r_max = max(r_max,height[j]);
        }
        //找到左边最高的柱子
        for(int j=i;j>=0;j--){
            l_max = max(l_max,height[j]);
        }

        res +=min(l_max,r_max)-height[i];
    }
    return res;
}


//备忘录优化
//把时间复杂度降低为 O(N)，已经是最优了，但是空间复杂度是 O(N)
int trap(vector<int>& height) {
    int n = height.size();
    if(0==n) return 0;
    int res = 0;
    //备忘录
    vector<int>l_max(n),r_max(n);
    //base case
    l_max[0]=height[0];
    r_max[n-1]=height[n-1];
    //从左向右计算 l_max;
    for(int i=1;i<n;i++)
        l_max[i]=max(height[i],l_max[i-1]);
    //从右向左计算 r_max;
    for(int i = n-2;i>=0;i--)
        r_max[i]=max(height[i],r_max[i+1]);

    for(int i=1;i<n-1;i++){
        res+=min(l_max[i],r_max[i])-height[i];
    }
    return res;
}


//双指针解法
//

int trap(vector<int>& height) {
    if(height.size() == 0) return 0;
    int n =height.size();
    int left =0,right=n-1;
    int res = 0;
    int l_max = height[0];
    int r_max = height[n-1];
    while(left<=right){
        l_max = max(l_max,height[left]);
        r_max = max(r_max,height[right]);

        if(l_max<r_max){
            res += l_max-height[left];
            left++;
        }else{
            res +=r_max-height[right];
            right--;
        }
    }
    return res;
}



