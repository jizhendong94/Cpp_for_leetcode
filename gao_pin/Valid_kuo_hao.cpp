

//只处理一种括号
bool isValid(string str)
{
    int left = 0;
    for(char c:str){
        if(c == '(')
            left++;
        else
            left--;
        if(left < 0)
            return false;
    }
    return 0 == left;
}


/*20  有效的括号
给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。

有效字符串需满足：
左括号必须用相同类型的右括号闭合。
左括号必须以正确的顺序闭合。
*/

char leftOF(char c)
{
    if(c == ')') return '(';
    if(c == '}') return '{';
    return '[';
}
bool isValid(string str)
{
    stack<char>left;
    for(char c:str){
        if(c == '(' || c == '[' || c == '{')
            left.push(c);
        else{//字符c是右括号
            if(!left.empty() && leftOF(c) == left.top())
                left.pop();
            else
                return false;//和最近的括号不匹配
        }
    }
    //是否所有的括号都匹配了
    return left.empty();
}


/*08 09   括号 
括号。设计一种算法，打印n对括号的所有合法的（例如，开闭一一对应）组合。

说明：解集不能包含重复的子集。

例如，给出 n = 3，生成结果为：

[
  "((()))",
  "(()())",
  "(())()",
  "()(())",
  "()()()"
]

*/

void dfs(string path,int left,int right,int n,vector<string>& res)
{
    if(left>n || right>left) return;
    if(path.size()==n*2){
        res.push_back(path);
        return;
    }
    dfs(path+"(",left+1,right,n,res);
    dfs(path+")",left,right+1,n,res);
}

vector<string> generateParenthesis(int n)
{
    if(n<=0) return {};
    vector<string>res;

    dfs("",0,0,n,res);
    return res;
}















