/* 如何高效的对有序数组和 链表去重

*/

int removeDuplicates(vector<int>& nums)
{
    int n = nums.size();
    if(0 == n) return 0;
    int slow = 0,fast = 1;
    while(fast<n){
       if(nums[fast] != nums[slow]) 
       {
           slow++;
           nums[slow]=nums[fast];
       }
       fast++;
    }
    //长度为索引 + 1
    return slow+1;
}


//删除重复链表 
ListNode* deleteDuplicated(ListNode* head)
{
    if(nullptr == head) return nullptr;
    ListNode* slow = head,*fast=head->next;
    while(fast != nullptr){
        if(fast->val != slow->val){
            slow->next = fast;
            slow = slow->next;
        }
        fast = fast->next;
    }
    slow->next = nullptr;
    return head;
}


//删除重复链表元素，重复的元素全部删除
ListNode* delDuplete(ListNode* head)
{
    if(head == nullptr || head->next == nullptr) return head;
    ListNode* dummynode = new ListNode(-1);
    dummynode->next = head;

    ListNode* pre = dummynode;
    ListNode* cur = head;
    while(cur){
        while(cur->next && cur->val == cur->next->val)
            cur=cur->next;
        if(pre->next == cur)
            pre=pre->next;
        else
            pre->next = cur->next;
        cur = cur->next;
    }

    return dummynode->next;

}






