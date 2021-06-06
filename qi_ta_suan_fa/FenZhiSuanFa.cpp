/*241. 为运算表达式设计优先级
 
 给定一个含有数字和运算符的字符串，为表达式添加括号，改变其运算优先级以求出不同的结果。
 你需要给出所有可能的组合的结果。有效的运算符号包含 +, - 以及 * 。
 
 */

vector<int> diffWaysToCompute(string expression)
{
    vector<int>res;
    
    for(int i=0;i<expression.size();i++){
        char c = expression[i];
        //扫描input的运算符
        if(c == '-'||c == '*'||c == '+'){
            //分
            //以运算符为中心，分割成两个字符串，分别递归计算
            vector<int>left = diffWaysToCompute(expression.substr(0,i));
            vector<int>right = diffWaysToCompute(expression.substr(i+1));
            //治
            //通过自问题 合成原问题的结果
            for(int a:left){
                for(int b:right){
                    if(c == '+'){
                        res.push_back(a+b);
                    }else if(c == '-'){
                        res.push_back(a-b);
                    }else if(c == '*'){
                        res.push_back(a*b);
                    }
                }
            }
        }
    }
    //base case
    //如果res为空 说明算式是一个数字 没有运算符
    if(res.empty())  res.push_back(atoi(expression.c_str()));
    return res;
}
