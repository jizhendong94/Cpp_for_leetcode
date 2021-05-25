/*55 跳跃游戏
给定一个非负整数数组 nums ，你最初位于数组的 第一个下标 。

数组中的每个元素代表你在该位置可以跳跃的最大长度。

判断你是否能够到达最后一个下标。
*/

bool canJump(vector<int>& nums)
{
    int n = nums.size();
    int farthest = 0;
    for(int i=0;i<n-1;i++)
    {
        //不断计算能跳到的最远距离
        farthest = max(farthest,i+nums[i]);
        //可能碰到了 0，卡住跳不动了
        if(farthest<=i) return false;
    }
    return farthest>=n-1;
}


/*45 跳跃游戏 II
给定一个非负整数数组，你最初位于数组的第一个位置。
数组中的每个元素代表你在该位置可以跳跃的最大长度。
你的目标是使用最少的跳跃次数到达数组的最后一个位置。
假设你总是可以到达数组的最后一个位置。


思路：  i和end标记了可以选择的跳跃步数，farthest标记了所有可选择跳跃步数[i..end]中能够跳到的最远距离，jumps记录了跳跃次数。
        本算法的时间复杂度 O(N)，空间复杂度 O(1)，可以说是非常高效，动态规划都被吊起来打了。
        0 1 2 3 4    5   6   7
        3 1 4 2 ... ... ... ...
          i   end       farthest
*/

int jump(vector<int>& nums)
{
    int n = nums.size();
    int end = 0,farthtest = 0;
    int jumps = 0;
    for(int i=0;i<n-1;i++)
    {
        farthest = max(farthest,i+nums[i]);

        if(i == end){
            jumps++;
            end = farthest;
        }
    }
    return jumps;
}








