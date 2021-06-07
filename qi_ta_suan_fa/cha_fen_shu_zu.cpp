/*
差分数组的主要适用场景是频繁对原始数组的某个区间的元素进行增减。

int[] diff = new int[nums.length];
// 构造差分数组
diff[0] = nums[0];
for (int i = 1; i < nums.length; i++) {
    diff[i] = nums[i] - nums[i - 1];
}

//根据差分数组构造出原始数组
int[] res = new int[diff.length];
// 根据差分数组构造结果数组
res[0] = diff[0];
for (int i = 1; i < diff.length; i++) {
    res[i] = res[i - 1] + diff[i];
}


这样构造差分数组diff，就可以快速进行区间增减的操作，
如果你想对区间nums[i..j]的元素全部加 3，那么只需要让diff[i] += 3，
然后再让diff[j+1] -= 3即可：

原理很简单，回想diff数组反推nums数组的过程，
diff[i] += 3意味着给nums[i..]所有的元素都加了 3，
然后diff[j+1] -= 3又意味着对于nums[j+1..]所有元素再减 3，那综合起来，
是不是就是对nums[i..j]中的所有元素都加 3 了

*/

class Difference{
    private:
        vector<int>diff;
    public:
        Difference(vector<int>& nums){
            diff=vector<int>(nums.size(),0);
            //构造差分数组
            diff[0]=nums[0];
            for(int i=1;i<nums.size();i++){
                diff[i] = nums[i] - nums[i-1];
            }
        }
        //给区间[i,j]增加val  （可以是负数）
        void increment(int i,int j,int val){
            diff[i] += val;
            if(j+1 < diff.size()){
                diff[j+1] -= val;
            }
        }

        vector<int> result(){
            vector<int>res(diff.size(),0);
            //根据差分数组构造结果
            res[0] = diff[0];
            for(int i=1;i<diff.size();i++){
                res[i] = res[i-1] + diff[i];
            }
            return res;
        }

};

/*1109 航班预订统计
  这里有 n 个航班，它们分别从 1 到 n 进行编号。

有一份航班预订表 bookings ，表中第 i 条预订记录 bookings[i] = [firsti, lasti, seatsi] 
意味着在从 firsti 到 lasti （包含 firsti 和 lasti ）的 每个航班 上预订了 seatsi 个座位。
请你返回一个长度为 n 的数组 answer，其中 answer[i] 是航班 i 上预订的座位总数。
*/

vector<int> corpFlightBookings(vector<vector<int>>& bookings,int n)
{
    vector<int>res(n,0);
    vector<int>diff(n+1,0);

    for(int k=0;k<bookings.size();k++){
        int i = bookings[k][0] - 1;
        int j = bookings[k][1] - 1;

        int seat = bookings[k][2];
        diff[i] = diff[i] + seat;
        diff[j+1] = diff[j+1] - seat;
    }
    res[0] = diff[0];
    for(int k=1;k<n;k++){
        res[k] = res[k-1] + diff[k];
    }
    return res;
}





