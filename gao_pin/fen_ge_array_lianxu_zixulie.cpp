/*659 分割数组为连续子序列
给你一个按升序排序的整数数组 num（可能包含重复数字），
请你将它们分割成一个或多个长度至少为 3 的子序列，
其中每个子序列都由连续整数组成。

如果可以完成上述分割，则返回 true ；否则，返回 false 。

思路：1、当前元素 v 自成一派，「以自己开头」构成一个长度至少为 3 的序列。
      2. 当前元素 v 接到已经存在的子序列后面。
所以元素 4 应该优先判断自己是否能够接到其他序列后面，如果不行，再判断是否可以作为新的子序列开头

freq 记录每个元素出现的次数，比如 freq[3] == 2 说明元素 3 在 nums 中出现了 2 次。

那么如果我发现 freq[3], freq[4], freq[5] 都是大于 0 的，
那就说明元素 3 可以作为开头组成一个长度为 3 的子序列。

need 记录哪些元素可以被接到其他子序列后面。

比如说现在已经组成了两个子序列 [1,2,3,4] 和 [2,3,4]，那么 need[5] 的值就应该是 2，
说明对元素 5 的需求为 2。

*/

bool isPossible(vector<int>& nums)
{
    unordered_map<int,int>freq,need;
    //统计nums中元素的个数
    for(int v:nums) frep[v]++;

    for(int v :nums){
        if(freq[v] == 0){
            //已经被用到其他子序列中
            continue;
        }
        //先判断v 是否能接到其他子序列后面
        if(need.count(v) && need[v] > 0){
            //V 可以接到之前的某个子序列后面
            freq[v]--;
            //对V 的需求减少1 
            need[v]--;
            //对V+1的需求加1 
            need[v+1]++;
        }else if(freq[v]>0 && freq[v+1]>0 && freq[v+2]>0){
            //将V作为开头，新建一个长度3的子序列[v,v+1,v+2]
            freq[v]--;
            freq[v+1]--;
            freq[v+2]--;
            //对v+3的需求加1 
            need[v+3]++;
        }else{
            //两种情况都不符合，则无法分配 
            return false;
        }
    }
    return true;
}

//我们再难为难为自己，如果我想要的不只是一个布尔值，我想要你给我把子序列都打印出来，怎么办？
//其实这也很好实现，只要修改 need，不仅记录对某个元素的需求个数，而且记录具体是哪些子序列产生的需求：

// need[6] = 2 说明有两个子序列需要 6
unordered_map<int, int> need;

// need[6] = {
//     {3,4,5},
//     {2,3,4,5},
// }
// 记录哪两个子序列需要 6
unordered_map<int, vector<vector<int>>> need;



bool isPossible(vector<int>& nums)
{
    unordered_map<int,int>freq;
    unordered_map<int,vector<vector<int>>>need;

    for(int v:nums) freq[v]++;

    for(int v :nums){
        if(freq[v] == 0) continue;

        if(need.count(v) && need[v].size()>0){
            //V可以接到之前某个序列的后面
            freq[v]--;
            //随便取一个需要V的子序列
            vector<int>temp = need[v].back();
            need[v].pop_back();
            //V接到子序列的后面
            temp.push_back(v);
            //这个子序列的需求变成了 V+1 
            need[v+1].push_back(temp);

        }else if(freq[v]>0 && freq[v+1]>0 && freq[v+2]>0){
            //将V作为开头
            freq[v]--;
            freq[v+1]--;
            freq[v+2]--;
            //新建一个长度为3的子序列[v,v+1,v+2]
            vector<int>tmep{v,v+1,v+2};
            //对V+3的需求的加1 
            need[v+3].push_back(temp);
        }else{
            return false;
        }
    }
    
    //打印
    for(auto it : need){
        for(vector<int> temp:it.second){
            for(int v : temp){
                cout<<v<<"  ";
            }
            cout<<endl;
        }
    }
    return true;
}



