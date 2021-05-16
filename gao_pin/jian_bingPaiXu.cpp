/*969 煎饼排序
  烧饼排序是个很有意思的实际问题：假设盘子上有n块面积大小不一的烧饼，
  你如何用一把锅铲进行若干次翻转，让这些烧饼的大小有序（小的在上，大的在下）？

  一次煎饼翻转的执行过程如下：

  选择一个整数 k ，1 <= k <= arr.length
  反转子数组 arr[0...k-1]（下标从 0 开始）

  思路：递归思想 

  1、找到n个饼中最大的那个。
  2、把这个最大的饼移到最底下。
  3、递归调用pancakeSort(A, n - 1)。
  base case：n == 1时，排序 1 个饼时不需要翻转。


  那么，最后剩下个问题，如何设法将某块烧饼翻到最后呢？
  其实很简单，比如第 3 块饼是最大的，我们想把它换到最后，也就是换到第n块。可以这样操作：
  1、用锅铲将前 3 块饼翻转一下，这样最大的饼就翻到了最上面。
  2、用锅铲将前n块饼全部翻转，这样最大的饼就翻到了第n块，也就是最后一块。
 */
vector<int>res;

void reverse(vector<int>& arr,int i,int j)
{
	while(i<j){
		int temp = arr[i];
		arr[i]=arr[j];
		arr[j]=temp;
		i++;
		j--;
	}
}
void cakesort(vector<int>& arr,int n)
{
	//base case
	if(1 == n) return;
	//寻找最大烧饼的索引
	int maxcake = 0;
	int maxcakeIndex = 0;
	for(int i=0;i<n;i++){
		if(maxcake<arr[i]){
			maxcake=arr[i];
			maxcakeIndex=i;
		}
	}
	//第一反转 将最大的烧饼翻到最上面 
	reverse(arr,0,maxcakeIndex);
	res.push_back(maxcakeIndex+1);
	//第二次 反转 将最大的烧饼翻到最小面
	reverse(arr,0,n-1);
	res.push_back(n);
	//递归调用
	cakesort(arr,n-1);
}
//主函数
vector<int> pancakeSort(vector<int>& arr) { 
	cakesort(arr,arr.size());
	return res;
}
