/*752. 打开转盘锁
你有一个带有四个圆形拨轮的转盘锁。每个拨轮都有10个数字： '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' 。每个拨轮可以自由旋转：例如把 '9' 变为  '0'，'0' 变为 '9' 。每次旋转都只能旋转一个拨轮的一位数字。
锁的初始数字为 '0000' ，一个代表四个拨轮的数字的字符串。
列表 deadends 包含了一组死亡数字，一旦拨轮的数字和列表里的任何一个元素相同，这个锁将会被永久锁定，无法再被旋转。
字符串 target 代表可以解锁的数字，你需要给出最小的旋转次数，如果无论如何不能解锁，返回 -1。

*/

string plusone(string cur,int j)
{
    if(cur[j]=='9')
        cur[j]='0';
    else
        cur[j]+=1;
    return cur;
}
string minusone(string cur,int j)
{
    if(cur[j] == '0')
        cur[j]='9';
    else
        cur[j]-=1;
    return cur;
}
int openLock(vector<string> deadends,string target)
{
    unordered_set<string>deads;
    for(string str: deadends)
        deads.insert(str);
    unordered_set<string>visited;
    queue<string>q;
    int step = 0;
    q.push("0000");
    visited.insert("0000");

    while(!q.empty())
    {
        int size = q.size();
        for(int i=0;i<size;i++)
        {
            string cur = q.front();
            q.pop();
            if(deads.count(cur)) continue;
            if(target == cur) return step;
            for(int j=0;j<4;j++){
                string up = plusone(cur,j);
                if(!visited.count(up)){
                    q.push(up);
                    visited.insert(up);
                }
                string down = minusone(cur,j);
                if(!visited.count(down)){
                    q.push(down);
                    visited.insert(down);
                }
            }
        }
        step++;
    }
    return -1;
}
