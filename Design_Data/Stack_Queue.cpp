/*

*/

//两个栈实现一个队列操作
class CQueue{

    public:
        CQueue() {}
        void appendTail(int val){
            stack1.push(val);
        }
        int deletehead(){
            if(stack2.empty()){
                while(!stack1.empty()){
                    stack2.push(stack1.top());
                    stack1.pop();
                }
            }
            if(stack2.empty()) return -1;
            int res = stack2.top();
            stack2.pop();
            return res;
        }
    private:
        stack<int>stack1,stack2;
};


//两个队列实现一个栈 
class Cstack{
    public: 
       Cstack()  {}
       void appendTail(int val){
            if(q1.size() == 0 || q2.size() == 0)
                q1.push(val);
            else if(q1.size()>0)
                q1.push(val);
            else if(q2.size()>0)
                q2.push(val);

       }
       int delTail(){
            if(q2.size() == 0){
                if(q1.size() == 0){
                    return -1;
                }
                while(q1.size()!= 1){
                    q2.push(q1.front());
                    q1.pop();
                }
                int res = q1.front();
                q1.pop();
                return res;
            }
            else{
                while(q2.size() != 1){
                    q1.push(q2.front());
                    q2.pop();
                }
                int res = q2.front();
                q2.pop();
                return res;
            }
       }

    private:
        queue<int>q1,q2;
};


