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


/*407  接雨水 2 
  给你一个 m x n 的矩阵，其中的值均为非负整数，代表二维高度图每个单元的高度，请计算图中形状最多能接多少体积的雨水。

  思路：
  用堆来维护周围这一圈中的最小元素。为什么是维护最小的元素不是最大的元素呢，因为木桶原理呀。
  这个最小的元素从堆里弹出来，和它四个方向的元素去比较大小，看能不能往里灌水，怎么灌水呢，如果用方向就比较复杂了，
  我们可以用visited数组来表示哪些遍历过，哪些没遍历过。如果当前弹出来的高度比它周围的大，
  他就能往矮的里面灌水了，灌水后要把下一个柱子放进去的时候，放的高度要取两者较大的，也就是灌水后的高度，
  不是它原来矮的时候的高度了，如果不能灌水，继续走。

 */

struct Cell{
	int x,y,h;
	Cell(int _x,int _y,int _h):x(_x),y(_y),h(_h) {};
	bool operator<(const Cell& c) const{
		return h>c.h;
	}
};
int trapRainWater(vector<vector<int>>& heightMap) {
	int n = heightMap.size(),m = heightMap[0].size();
	if(0 == n || 0 == m) return 0;
	//visited数组表示这个位置有没有被访问过 
	vector<vector<int>>visited(n,vector<int>(m,false));
	//优先级队列  小顶堆  Cell = [x,y,h] 坐标和高度
	priority_queue<Cell>pq;
	//最外面一圈放进去
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(0 == i || i==n-1||j==0||j==m-1){
				pq.push({i,j,heightMap[i][j]});
				visited[i][j]=true;
			}
		}
	}
	int res = 0;
	//方向数组，把dx dy 压缩成一维来做
	int dirs[] = {-1,0,1,0,-1};
	while(!pq.empty()){
		Cell c = pq.top();
		pq.pop();
		//看一下周围四个方向
		for(int i=0;i<4;i++){
			int nx = c.x + dirs[i];
			int ny = c.y + dirs[i+1];
			//位置合法而且没有被访问过
			if(nx>=0&&nx<n&&ny>=0&&ny<m&&!visited[nx][ny]){
				//外围一圈中最小的比当前还高，可以灌水
				if(c.h>heightMap[nx][ny]){
					res += c.h - heightMap[nx][ny];
				}
				//灌水后的高度得是你灌完之后的高度的，如果没灌水也要去高的
				pq.push({nx,ny,max(c.h,heightMap[nx][ny])});
				visited[nx][ny]=true;
			}
		}
	}
	return res; 
}

/*11 盛最多水的容器
给你 n 个非负整数 a1，a2，...，an，每个数代表坐标中的一个点 (i, ai) 。
在坐标内画 n 条垂直线，垂直线 i 的两个端点分别为 (i, ai) 和 (i, 0) 。
找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。

示例 2：

输入：height = [1,1]
输出：1
示例 3：

输入：height = [4,3,2,1,4]
输出：16
示例 4：

输入：height = [1,2,1]
输出：2

思路：和接雨水思路一致，结果是求最大值
*/

int maxArea(vector<int>& height)
{
	int res = 0;
	int n = height.size();
	if(n<=1) return 0;
	int left=0,right=n-1;
	int l_max = height[left];
	int r_max = height[right];
	while(left<=right){
		l_max = max(l_max,height[left]);
		r_max = max(r_max,height[right]);

		if(l_max<r_max){
			int temp = l_max*(right-left);
			res = max(res,temp);
			left++;
		}else{
			int temp = r_max*(right-left);
			res = max(res,temp);
			right--;
		}
	}
	return res;
}















