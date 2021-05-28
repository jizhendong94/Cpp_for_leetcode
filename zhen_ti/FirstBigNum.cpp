#include<iostream>
#include<stack>
using namespace std;

vector<int> findMaxRight(vector<int>& nums)
{
    int n = nums.size();
    vector<int>res(n,INT_MIN);
    stack<int>Stk;
    stack.push(0);
    int index = 1;
    while(index<n){
        //如果当前值比栈顶元素大 
        if(!Stk.empty() && nums[index] > nums[Stk.top()]){
            res[Stk.top()]=nums[index];
            Stk.pop();
        }else{
            Stk.push(index);
            index++;
        }
    }
    //元素小 
    if(!Stk.empty()){
        res[Stk.top()] = -1;
        Stk.pop();
    }
}
int main()
{
    
}
