/*836 矩形重叠
矩形以列表 [x1, y1, x2, y2] 的形式表示，其中 (x1, y1) 为左下角的坐标，(x2, y2) 是右上角的坐标。
矩形的上下边平行于 x 轴，左右边平行于 y 轴。

如果相交的面积为 正 ，则称两矩形重叠。需要明确的是，只在角或边接触的两个矩形不构成重叠。
给出两个矩形 rec1 和 rec2 。如果它们重叠，返回 true；否则，返回 false 。

思路：两个互相重叠的矩形，它们在 xx 轴和 yy 轴上投影出的区间也是互相重叠的。
	这样，我们就将矩形重叠问题转化成了区间重叠问题。
	判断不重叠： 假设两个区间分别是 [s1, e1] 和 [s2, e2] 的话，
	区间不重叠的两种情况就是 e1 <= s2 和 e2 <= s1。

	我们就得到区间不重叠的条件：e1 <= s2 || e2 <= s1。将条件取反即为区间重叠的条件。
*/

bool isRectangleOverLap(vector<int>& rec1,vector<int>& rec2)
{
	//输入的是一个线段 直接返回false
	if(rec1[0]==rec1[2]||rec1[1]==rec1[3]||rec2[0]==rec2[2]||rec2[1]==rec2[3]) return false;
	//x 轴上是否相交
	bool x_overlap = !(rec1[2]<=rec2[0] || rec2[2]<=rec1[0]);
	//y 轴上是否相交
	bool y_overlap = !(rec1[3]<=rec2[1] || rec2[3]<=rec1[1]);

	return x_overlap && y_overlap;
}



