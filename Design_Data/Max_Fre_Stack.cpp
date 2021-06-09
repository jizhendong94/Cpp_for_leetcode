/*895  最大频率栈
实现 FreqStack，模拟类似栈的数据结构的操作的一个类。

FreqStack 有两个函数：

push(int x)，将整数 x 推入栈中。
pop()，它移除并返回栈中出现最频繁的元素。
如果最频繁的元素不只一个，则移除并返回最接近栈顶的元素。

*/

class FreqStack{
    public:
        FreqStack(){

        }
        
        void push(int val){
            //修改VF表，对应的freq + 1
            valtofre[val] += 1;
            int freq = valtofre[val];
            //修改FV表，在freq对应的列表上,加入 val
            freToval[freq].push(val);
            //更新maxFreq
            maxFreq = max(maxFreq,freq);
        }
        
        int pop(){
            //修改FV表，取出一个maxFreq对应的元素val
            int val = freToval[maxFreq].top();

            freToval[maxFreq].pop();

            //修改VF表，val对应的freq - 1
            valTofre[val] -= 1;
            //更新maxFreq
            if(freToval[maxFreq].empty()){
                //如果maxFreq对应的元素空了，更新maxFreq;
                maxFreq--;
            }

            return val;
        }
    private:
        //记录元素最大频率
        int maxFreq = 0;
        //每个val 对应的 频率
        unordered_map<int,int>valTofre;
        //每个频率对应的 val 列表 
        unordered_map<int,stack<int>>freToVal;
};



