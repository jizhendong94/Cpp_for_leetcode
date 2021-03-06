#include<iostream>
#include<vector>
#include<map>
#include<list>
#include<unordered_map>
using namespace std;

/*
LRU 缓存淘汰算法就是一种常用策略。LRU 的全称是 Least Recently Used，
也就是说我们认为最近使用过的数据应该是是「有用的」，
很久都没用过的数据应该是无用的，内存满了就优先删那些很久没用过的数据。

现在你应该理解 LRU（Least Recently Used）策略了。当然还有其他缓存淘汰策略，
比如不要按访问的时序来淘汰，而是按访问频率（LFU 策略）来淘汰等等，各有应用场景。
本文讲解 LRU 算法策略。

LRU算法描述：
首先要接收一个 capacity 参数作为缓存的最大容量，然后实现两个 API，
一个是 put(key, val) 方法存入键值对，另一个是 get(key) 方法获取 key 对应的 val，
如果 key 不存在则返回 -1。

注意哦，get 和 put 方法必须都是 O(1) 的时间复杂度，我们举个具体例子来看看 LRU 算法怎么工作。

 缓存容量为 2 
LRUCache cache = new LRUCache(2);
// 你可以把 cache 理解成一个队列
// 假设左边是队头，右边是队尾
// 最近使用的排在队头，久未使用的排在队尾
// 圆括号表示键值对 (key, val)

cache.put(1, 1);
// cache = [(1, 1)]

cache.put(2, 2);
// cache = [(2, 2), (1, 1)]

cache.get(1);       // 返回 1
// cache = [(1, 1), (2, 2)]
// 解释：因为最近访问了键 1，所以提前至队头
// 返回键 1 对应的值 1

cache.put(3, 3);
// cache = [(3, 3), (1, 1)]
// 解释：缓存容量已满，需要删除内容空出位置
// 优先删除久未使用的数据，也就是队尾的数据
// 然后把新的数据插入队头

cache.get(2);       // 返回 -1 (未找到)
// cache = [(3, 3), (1, 1)]
// 解释：cache 中不存在键为 2 的数据

cache.put(1, 4);    
// cache = [(1, 4), (3, 3)]
// 解释：键 1 已存在，把原始值 1 覆盖为 4
// 不要忘了也要将键值对提前到队头

*/

//哈希链表 
class Node{
public:
    int key,val;
    Node* next,*pre;
    Node(int k,int v){
        this->key = k;
        this->val = v;
    }
};

class DoubleList{
private:
    //头尾虚节点
    Node* head,*tail;
    //链表元素数
    int size;

public:
    DoubleList(){
        //初始化双向链表数据
        head = new Node(0,0);
        tail = new Node(0,0);
        head->next = tail;
        tail->pre = head;
        size = 0;
    }

    //尾部添加节点, 时间O(1)
    void addLast(Node* x){
        x->pre = tail->pre;
        x->next = tail;

        tail->pre->next = x;
        tail->pre = x;
        size++;
    }   

    //删除链表中的x 节点（x 一定存在）
    //双链表，且给的是目标节点，时间O(1)
    void remove(Node* x){
        x->pre->next = x->next;
        x->next->pre = x->pre;
        size--;
    }
    //删除链表中的一个节点，并返回该节点 O(1)
    Node* removeFirst(){
        if(head->next == tail){
            return nullptr;
        }
        Node* first = head->next;
        remove(first);
        return first;
    }

    //返回链表长度 ，时间O(1)
    int Size(){
        return size;
    }

};

class LRUCache{
    private:
        //key -> Node(key,val);
        unordered_map<int,Node*>map;
        //Node(k1,v1) <-> Node(k2,v2) <-> ...
        DoubleList cache;
        //最大容量 
        int cap;
    public:
        LRUCache(int capacity){
            this->cap = capacity;
        }
        //将某个key提升为最近使用的
        void makeRecently(int key){
            if(map.count(key)){
                Node* x = map[key];
                //先从链表中删除这个节点
                cache.remove(x);
                //重新插入到链表尾部 
                cache.addLast(x);
            }
        }
        //添加最近使用的元素 
        void addRecently(int key,int val){
            Node* temp = new Node(key,val);
            //链表尾部就是最近使用的元素
            cache.addLast(temp);
            //在map中添加key的映射
            map[key]=temp;
        }
        //删除某一个key  
        void deleteKey(int key){
            Node* temp = map[key];
            //从链表中删除
            cache.remove(temp);
            //从map中删除
            map.erase(key);
        }
        //删除最久未使用的元素
        void removeleastRecently(){
            //链表头部的第一个元素就是最久未使用的
            Node* deleteNode = cache.removeFirst();
            int deleteKey=deleteNode->key;
            //从map中删除Key
            map.erase(deleteKey);
        }

        int get(int key){
            if(!map.count(key)){
                return -1;
            }
            //将该数据提升为最近使用的
            makeRecently(key);
            return map[key]->val;
        }

        void put(int key,int val){
            //元素存在 
            if(map.count(key)){
                //删除旧的元素
                deleteKey(key);
                //新插入的数据为最近使用的元素
                addRecently(key,val);
                return;
            }
            //元素不存在
            if(cap == cache.Size()){
                //缓存满了，删除最久没有使用的元素
                removeleastRecently();
            }
            //添加为最近使用的元素
            addRecently(key,val);
        }


};


int main()
{
    list<pair<int,int>>test;
    test.push_back({1,10});
    test.push_back({2,20});

    for(auto iter:test){
        cout<<iter.first<<" "<<iter.second<<endl;
    }
    return 0;
}



