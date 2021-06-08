/*
有三种葡萄，每种分别有 a, b, c 颗，现在有三个人，第一个人只吃第一种和第二种葡萄，
第二个人只吃第二种和第三种葡萄，第三个人只吃第一种和第三种葡萄。
现在给你输入 a, b, c 三个值，请你适当安排，让三个人吃完所有的葡萄，算法返回吃的最多的人最少要吃多少颗葡萄。


*/
//PS：向上取整是一个常用的算法技巧。大部分编程语言中，
//如果你想计算 M 除以 N，M / N 会向下取整，你想向上取整的话，
//可以改成 (M+(N-1)) / N。
long solution(long a,long b,long c)
{
    vector<int>nums{a,b,c};
    sort(nums.begin(),nums.end());
    long sum = a+b+c;

    //能够构成三角形 可以完全平分 
    if(nums[0] + nums[1] > nums[2]){
        return (sum + 2)/3;
    }

    //不能构成三角形 平分最长边
    if( 2* (nums[0]+nums[1]) < nums[2]){
        return (nums[2]+1)/2;
    }
    // 不能构成三角形，但是依然可以完全平分 
    return (sum+2)/3;
}


