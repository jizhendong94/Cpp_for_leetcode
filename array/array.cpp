/*875 
  珂珂喜欢吃香蕉。这里有 N 堆香蕉，第 i 堆中有 piles[i] 根香蕉。警卫已经离开了，将在 H 小时后回来。
  珂珂可以决定她吃香蕉的速度 K （单位：根/小时）。每个小时，她将会选择一堆香蕉，从中吃掉 K 根。如果这堆香蕉少于 K 根，
  她将吃掉这堆的所有香蕉，然后这一小时内不会再吃更多的香蕉。  
  珂珂喜欢慢慢吃，但仍然想在警卫回来前吃掉所有的香蕉。
  返回她可以在 H 小时内吃掉所有香蕉的最小速度 K（K 为整数）。
 */


/*暴力解决问题

  显然最少为 1，最大为max(piles)，因为一小时最多只能吃一堆香蕉。那么暴力解法就很简单了，
  只要从 1 开始穷举到max(piles)，一旦发现发现某个值可以在H小时内吃完所有香蕉，这个值就是最小速度

  int minEatingSpeed(int[] piles, int H) {
// piles 数组的最大值
int max = getMax(piles);
for (int speed = 1; speed < max; speed++) {
// 以 speed 是否能在 H 小时内吃完香蕉
if (canFinish(piles, speed, H))
return speed;
}
return max;
}


注意这个 for 循环，就是在连续的空间线性搜索，这就是二分查找可以发挥作用的标志。

由于我们要求的是最小速度，所以可以用一个搜索左侧边界的二分查找来代替线性搜索，提升效率：

 */
//NlogN
int getmax(vector<int>& piles)
{
    int maxval=0;
    for(int i=0;i<piles.size();i++)
        maxval=max(piles[i],maxval);
    return maxval;
}

int timeof(int n,int speed)
{
    return n/speed + (n%speed>0?1:0);
}

bool canfinished(vector<int>& piles,int speed,int h)
{
    int time=0;
    for(int n:piles)
        time+=timeof(n,speed);
    return time<=h;
}

int minEatingSpeed(vector<int>& piles, int h) {
    int left =1,right=getmax(piles);
    while(left<=right){
        int mid = left+(right-left)/2;
        if(canfinished(piles,mid,h)){
            right=mid-1;
        }else{
            left=mid+1;
        }
    }
    return left;
}

/*1011 在 D 天内送达包裹的能力
传送带上的包裹必须在 D 天内从一个港口运送到另一个港口。
传送带上的第 i 个包裹的重量为 weights[i]。每一天，我们都会按给出重量的顺序往传送带上装载包裹。我们装载的重量不会超过船的最大运载重量。
返回能在 D 天内将传送带上的所有包裹送达的船的最低运载能力。


首先确定cap的最小值和最大值分别为max(weights)和sum(weights)。
*/


bool canfinished(vector<int>& weights,int cap,int D)
{
    int i=0;
    for(int day=0;day<D;day++)
    {
        int maxcap=cap;
        while((maxcap -= weights[i]) >=0){
            i++;
            if(i==weights.size()) return true;
        }
    }
    return false;
}


int shipWithinDays(vector<int>& weights, int D) {
    int left = getmax(weights);
    int right = getsum(weights);
    while(left<=right){
        int mid = left+(right-left)/2;
        if(canfinished(weights,mid,D)){
            right=mid-1;
        }else{
            left=mid+1;
        }
    }
    return left;
}






















