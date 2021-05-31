/*
   给定一个 m x n 二维字符网格 board 和一个字符串单词 word 。如果 word 存在于网格中，返回 true ；否则，返回 false 。
   单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。
   剑指offer 12
   来源：力扣（LeetCode）
   链接：https://leetcode-cn.com/problems/ju-zhen-zhong-de-lu-jing-lcof
   著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */


int rows=0;
int cols=0;

bool dfs(vector<vector<char>>& board,string word,int i,int j,int k)
{
	if(i<0||j<0||i>=rows||j>=cols||board[i][j]!=word[k]) return false;
	if(k==word.size()-1) return true;

	board[i][j]='\0';
	res=dfs(board,word,i-1,j,k+1)||dfs(board,word,i+1,j,k+1)||
		dfs(board,word,i,j-1,k+1)||dfs(board,word,i,j+1,k+1);
	board[i][j]=word[k];
	return res;
}
bool exist(vector<vector<char>>& board, string word) {
	rows=board.size();
	cols=board[0].size();
	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<cols;j++)
		{
			if(dfs(board,word,i,j,0))
				return true;
		}
	}
	return false;
}

/*
   地上有一个m行n列的方格，从坐标 [0,0] 到坐标 [m-1,n-1] 。一个机器人从坐标 [0, 0] 的格子开始移动，它每次可以向左、右、上、下移动一格（不能移动到方格外），也不能进入行坐标和列坐标的数位之和大于k的格子。例如，当k为18时，机器人能够进入方格 [35, 37] ，因为3+5+3+7=18。但它不能进入方格 [35, 38]，因为3+5+3+8=19。请问该机器人能够到达多少个格子？
   剑指offer  13
   来源：力扣（LeetCode）
   链接：https://leetcode-cn.com/problems/ji-qi-ren-de-yun-dong-fan-wei-lcof
   著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

vector<vector<int>>visited;
int sum(int x,int y){
	int res=0;
	while(x)
	{
		res+=x%10;
		x/=10;
	}
	while(y){
		res+=y%10;
		y/=10;
	}
	return res;
}
int dfs(int m,int n,int i,int j,int k)
{
	if(i<0||j<0||i>=m||j>=n||visited[i][j]||sum(i,j)>k) return 0;
	visited[i][j]=1;
	return 1+dfs(m,n,i-1,j,k)+dfs(m,n,i+1,j,k)+
		dfs(m,n,i,j+1,k)+dfs(m,n,i,j-1,k);
}
int movingCount(int m, int n, int k) {
	visited=vector<vector>(m,vector<int>(n,0));
	return dfs(m,n,0,0,k);
}


/*
 *目标和
 给定一个非负整数数组，a1, a2, ..., an, 和一个目标数，S。现在你有两个符号 + 和 -。对于数组中的任意一个整数，
 你都可以从 + 或 -中选择一个符号添加在前面。
 返回可以使最终数组和为目标数 S 的所有添加符号的方法数。

 来源：力扣（LeetCode） 494
 链接：https://leetcode-cn.com/problems/target-sum
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

https://labuladong.github.io/algo/%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92%E7%B3%BB%E5%88%97/targetSum.html

 */
map<string,int>memo;
int dp(vector<int>& nums,int i,int rest)
{
	if(i==num.size()){
		if(rest == 0) return 1;
		return 0;
	}

	string key = to_string(i)+','+to_string(rest);
	if(memo.count(key)) return memo[key];

	int result = dp(nums,i+1,rest-nums[i])+dp(nums,i+1,rest+nums[i]);
	memo[key]=result;
	return result;

}
int findTargetSumWays(vector<int>& nums,int target)
{
	if(nums.size() == 0) return 0;
	return dp(nums,0,target);
}


/*
 * 全排列
 给定一个 没有重复 数字的序列，返回其所有可能的全排列

 输入: [1,2,3]
 输出:
 [
 [1,2,3],
 [1,3,2],
 [2,1,3],
 [2,3,1],
 [3,1,2],
 [3,2,1]
 ]

 来源：力扣（LeetCode）  46
 链接：https://leetcode-cn.com/problems/permutations
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */
vector<vector<int>>res;

void backtrace(vector<int>& nums,vector<int>& track)
{
	if(nums.size() == track.size())  //触发结束条件
	{
		res.push_back(track);
		return;
	}
	for(int i=0;i<nums.size();i++)
	{
		if(find(track.begin(),track.end(),nums[i])!=track.end())  //排除不合法的选择
			continue;
		track.push_back(nums[i]);  //做选择
		back_trace(nums,track);
		track.pop_back();        //取消选择
	}
}

vector<vector<int>> permute(vector<int>& nums)
{
	vector<int>track;
	backtrace(nums,track);
	return res;
}



/*47  全排列2   和字符串排列一样的代码  剑指offer  38
  给定一个可包含重复数字的序列 nums ，按任意顺序 返回所有不重复的全排列。
  输入：nums = [1,1,2]
  输出：
  [[1,1,2],
  [1,2,1],
  [2,1,1]]

 */

vector<vector<int>>res;
void backtrack(vector<int>& nums,vector<int>& path,vector<bool>visited)
{
	if(nums.size() == path.size()){
		res.push_back(path);
		return;
	}
	for(int i=0;i<nums.size();i++){
		if(!visited[i]){
			//1 nums[i-1] 没用过 说明回溯到了同一层 此时接着用num[i] 则会与 同层用num[i-1] 重复
			//2 nums[i-1] 用过了 说明此时在num[i-1]的下一层 相等不会重复
			if(i>=1&&nums[i-1]==nums[i]&&!visited[i-1]) continue;
			path.push_back(nums[i]);
			visited[i]=true;
			backtrack(nums,path,visited);
			path.pop_back();
			visited[i]=false;
		}
	}
}
vector<vector<int>> permuteUnique(vector<int>& nums) {
	if(nums.size() == 0) return res;
	vector<int>path;
	vector<bool>visited(nums.size(),false);
	sort(nums.begin(),nums.end());
	backtrack(nums,path,visited);
	return res;
}




/* N皇后  51  

   n 皇后问题 研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。
   给你一个整数 n ，返回所有不同的 n 皇后问题 的解决方案。
   每一种解法包含一个不同的 n 皇后问题 的棋子放置方案，该方案中 'Q' 和 '.' 分别代表了皇后和空位。

   这个问题很经典了，简单解释一下：给你一个 N×N 的棋盘，让你放置 N 个皇后，使得它们不能互相攻击。
   PS：皇后可以攻击同一行、同一列、左上左下右上右下四个方向的任意单位。

 */
vector<vector<string>>res;

bool valid(vector<string>& board,int row,int col)
{
	int n = board.size();
	//检查列是否有皇后互相冲突
	for(int i=0;i<n;i++){
		if(board[i][col]=='Q')
			return false;
	}
	//检查右上方是否有皇后互相冲突
	for(int i=row-1,j=col+1;i>=0&&j<n;i--,j++){
		if(board[i][j] == 'Q')
			return false;
	}
	//检查左上方是否有皇后互相攻击
	for(int i=row-1,j=col-1;i>=0&&j>=0;i--,j--){
		if(board[i][j]=='Q')
			return false;
	}
	return true;
}
//路径：board中小于row的那些行都已经成功放置了皇后
//选择列表：第row行的所有列都是放置皇后的选择
//结束条件：row超过了board的最后一行
void backtrack(vector<string>& board,int row)
{
	if(row == board.size()){   //结束条件
		res.push_back(board);
		return;
	}
	int n = board[row].size();
	for(int col = 0;col<n;col++){
		if(!valid(board,row,col)) continue;
		//做选择
		board[row][col] ='Q';
		//进入下一行决策
		backtrack(board,row+1);
		//撤销选择
		board[row][col]='.';
	}
}

vector<vector<string>> solveNQueens(int n)
{
	vector<string>board(n,vector<string>(n,'.'));
	backtrack(board,0);
	return res;
}


/*offer 34  二叉树中和为某一值得路径 
  输入一棵二叉树和一个整数，打印出二叉树中节点值的和为输入整数的所有路径。
  从树的根节点开始往下一直到叶节点所经过的节点形成一条路径。

 */

void backtrack(TreeNode* root,int target,vector<int>& path)
{
	if(NULL == root) return;
	path.push_back(root->val);
	target -= root->val;
	if(target == 0 && root->left==NULL && root->right==NULL)
		res.push_back(path);
	backtrack(root->left,target,path);
	backtrack(root->right,target,path);
	path.pop_back();
}

vector<vector<int>>PathSum(TreeNode* root,int target)
{
	vector<int>path;
	backtrack(root,target,path);
	return res;
}




/* 698 划分K个相等的子集  labuladong 回溯算法

   给定一个整数数组  nums 和一个正整数 k，找出是否有可能把
   这个数组分成 k 个非空子集，其总和都相等

 */

bool backtrack(vector<int>& nums,int index,vector<int>& bucket,int target)
{
	if(index == nums.size()){
		//检查所有的桶的数字之和是否都是target
		for(int i=0;i<bucket.size();i++){
			if(bucket[i]!=target){
				return false;
			}
		}
		//成功平分
		return true;
	}

	//穷举Nums[index]可能装入的桶
	for(int i=0;i<bucket.size();i++){
		//剪枝 桶装满了
		if(bucket[i]+nums[index] > target){
			continue;
		}
		//将Num[index]装入bucket[i]
		bucket[i]+=nums[index];
		//穷举下一个数字
		if(backtrack(nums,index+1,bucket,target)){
			return true;
		}
		//撤销选择
		bucket[i]-=nums[index];
	}
	return false;
}

bool canPartitionKSubsets(vector<int>& nums,int k)
{
	//排除一些基本情况
	if(k>num.size()) return false;
	int sum = 0;
	for(int v:nums) sum+=v;
	if(sum%k !=0) return false;

	//k个桶，记录每个桶装的数字之和
	vector<int>bucker(k,0);
	int target = sum/k;

	//可以升序排序，提高速率 

	//穷举 看看nums能否划分为K个和为target的子集
	return backtrack(num,0,bucket,target);
}

/* 78  子集
   问题很简单，输入一个不包含重复数字的数组，要求算法输出这些数字的所有子集。
//不含重复元素 
 */
vector<vector<int>>res;

void backtrack(vector<int>& nums,int start,vector<int>& track)
{
	res.push_back(track);
	for(int i=start;i<nums.size();i++) //i从start开始递增
	{
		track.push_back(nums[i]);  //做选择
		backtrack(nums,i+1,track); //回溯
		track.pop_back();          //撤销选择
	}
}

vector<vector<int>> subsets(vector<int>& nums) {
	vector<int>path; //记录走过的路径
	backtrack(nums,0,path);
	return res;
}


/* 90 子集 2

   给你一个整数数组 nums ，其中可能包含重复元素，请你返回该数组所有可能的子集（幂集）。
   解集 不能 包含重复的子集。返回的解集中，子集可以按 任意顺序 排列。

 */
vector<vector<int>>res;

void backtrack(vector<int>& nums,int start,vector<int>& path)
{
	res.push_back(path);
	for(int i = start;i<nums.size();i++){
		if(i>start&&nums[i]==nums[i-1]) continue;
		path.push_back(nums[i]);
		backtrack(nums,i+1,path);
		path.pop_back();
	}
}

vector<vector<int>> subsetsWithDup(vector<int>& nums)
{
	vector<int>path;
	sort(nums.begin(),nums.end());
	backtrack(nums,0,path);
	return res;
}





/* 38 offer  字符串的排列


 */


/*17 电话号码的组合

  给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。答案可以按 任意顺序 返回。
  给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。

  输入：digits = "23"
  输出：["ad","ae","af","bd","be","bf","cd","ce","cf"]
 */
void backtrace(vector<string>& res,string str,string digits,unordered_map<char,string>& table,int k)
{
	if(str.size() == digits.size()){
		res.push_back(str);
		return;
	}
	string tmp = table[digits[k]];
	for(char w:tmp){
		str+=w;
		backtrace(res,str,digits,table,k+1);
		str.pop_back();
	}
	return;
}
vector<string> letterCombinations(string digits)
{
	unordered_map<char,string>table{
		{'2',"abc"},{'3',"def"},{'4',"ghi"},
			{'5',"jkl"},{'6',"mno"},{'7',"pqrs"},
			{'8',"tuv"},{'9',"wxyz"}
	};
	vector<string>res;
	if(digits.size() ==0 ) return res;
	backtrace(res,"",digits,table,0);
	return res;
}

/*39  组合总和
  给定一个无重复元素的数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。
  candidates 中的数字可以无限制重复被选取。

  说明：
  所有数字（包括 target）都是正整数。
  解集不能包含重复的组合。 

 */
vector<vector<int>>res;
vector<int>path;
void backtrace(vector<int>& candidates,int target,int sum,int startIndex)
{
	if(sum > target) return;
	if(sum == target){
		res.push_back(path);
		return;
	}
	//如果sum+candidates[i]>target 就终止
	for(int i=startIndex;i<candidates.size()&& sum+candidates[i]<=target;i++)
	{
		sum += candidates[i];
		path.push_back(candidates[i]);
		backtrace(candidates,target,sum,i); //不用i+1,可以重复
		sum -= candidates[i];//回溯
		path.pop_back(); //回溯
	}
}
vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
	sort(candidates.begin(),candidates.end());
	backtrace(candidates,target,0,0);
	return res;
}








