/*言归正传，本文解决一个很经典的贪心算法问题 Interval Scheduling（区间调度问题）。
  给你很多形如[start,end]的闭区间，请你设计一个算法，算出这些区间中最多有几个互不相交的区间。

  思路：从区间集合 intvs 中选择一个区间 x，这个 x 是在当前所有区间中结束最早的（end 最小）。
  把所有与 x 区间相交的区间从区间集合 intvs 中删除。
  重复步骤 1 和 2，直到 intvs 为空为止。之前选出的那些 x 就是最大不相交子集。

  把这个思路实现成算法的话，可以按每个区间的end数值升序排序，因为这样处理之后实现步骤 1 和步骤 2 都方便很多

 */

int intervalSchedule(vector<vector<int>>& intervals)
{
	if(intervals.size() == 0) return 0;
	//按照end 排序升序
	sort(intervals,begin(),intervals.end(),[](vector<int>& v1,vetor<int>& v2){
			return v1[1]<v2[1];
			});
	//至少有一个区间不相交
	int count = 1;

	int x_end = intervals[0][1];
	for(vector<int> temp:intervals){
		int start = temp[0];
		if(start>=x_end){
			count++;
			x_end = temp[1];
		}
	}	
	return count;
}



/*435 无重叠区间
  给定一个区间的集合，找到需要移除区间的最小数量，使剩余区间互不重叠。

  注意:

  可以认为区间的终点总是大于它的起点。
  区间 [1,2] 和 [2,3] 的边界相互“接触”，但没有相互重叠。

 */

int eraseOverlapIntervals(vector<vector<int>>& intervals) {
	int n = intervals.size();
	return n-EverlapIntervals(intervals);
}


/*452  

*/
