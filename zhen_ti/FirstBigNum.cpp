#include<iostream>
#include<vector>
#include<stack>


using namespace std;
/*
数组中每个数右边第一个比它大的元素
如数组A=[1,5,3,6,4,8,9,10] 输出[5, 6, 6, 8, 8, 9, 10, -1]
如数组A=[8, 2, 5, 4, 3, 9, 7, 2, 5] 输出[9, 5, 9, 9, 9, -1, -1, 5, -1]




*/
vector<int> findMaxRight(vector<int>& nums)
{
    int n = nums.size();
    vector<int>res(n);
    stack<int>Stk;
    Stk.push(0);
    int index = 1;
    while(index<n){
        //如果当前值比栈顶元素大 找到第一个比他大的元素 栈顶弹出
        if(!Stk.empty() && nums[index] > nums[Stk.top()]){
            res[Stk.top()]=nums[index];
            Stk.pop();
        }else{ //压入元素
            Stk.push(index);
            index++;
        }
    }
    //元素小 
    while(!Stk.empty()){
        res[Stk.top()] = -1;
        Stk.pop();
    }
	return res;
}

//单调栈解法
vector<int> nextGreaterElement(vector<int>& nums)
{
	vector<int>res(nums.size());
	stack<int>S;
	for(int i=nums.size()-1;i>=0;i--){  //倒着进栈
		while(!S.empty()&& S.top()<=nums[i]) //判定个子高矮
			S.pop();   //矮个子起开，反正也被挡住了
		res[i]=S.empty()?-1:S.top();  //这个元素身后的第一个高个子
		S.push(nums[i]);  //进队
	}
	return res;
}


int main()
{
	vector<int>nums = {1,5,3,6,4,8,9,10}; 
	vector<int>res = nextGreaterElement(nums);
	for(auto iter= res.begin();iter!=res.end();iter++)
	{
		cout<<*iter<<"\t";
	}
	cout<<endl;
	vector<int>nums1 = {8,2,5,4,3,9,7,2,5};
	vector<int>res1 = nextGreaterElement(nums1);
	for(auto iter=res1.begin();iter!=res1.end();iter++)
	{
		cout<<*iter<<"\t";
	}
	cout<<endl;
}
