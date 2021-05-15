#include<iostream>
using namespace std;

//整个反转 链表反转
ListNode* reverseList(ListNode* head)
{
    if(NULL==head || NULL==head->next) return head;
    ListNode* pre=NULL;
    ListNode* cur = head;
    ListNode* newhead = NULL;
    while(cur)
    {
        if(cur->next == NULL)
            newhead=cur;
        ListNode* next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next;
    }
    return newhead;
}

ListNode* reverseList(ListNode* head)
{
    if(head == NULL ||　head->next==NULL) return head;
    ListNode* last = reverseList(head->next);
    head->next->next = head;
    head->next= NULL;
    return last;
}

ListNode* successor = NULL;
ListNode* reverseBeforN(ListNode* head,int n)
{
    if(n == 1)
    {
        successor = head->next;
        return head;
    }

    ListNode* last = reverseBeforN(head->next,n-1);
    head->next->next=head;
    head->next=successor;
    return last;
}

ListNode* reverseBetween(ListNode* head,int left,int right)
{
    if(left==1)
        return reverseBeforN(head,right);
    head->next = reverseBetween(head->next,left-1,right-1);
    return head;
}


//
ListNode* reseverseBetween(ListNode*head,int left,int right)
{
    ListNode* dummynode = new ListNode(-1);
    dummynode->next = head;
    ListNode* pre = dummynode;

    for(int i =0;i<left-1;i++)
        pre = pre->next;
    ListNode* cur = pre->next;
    ListNode* next;
    for(int i=0;i<right-left;i++)
    {
        next = cur->next;
        cur->next = next->next;
        next->next = pre->next;
        pre->next = next;
    }
    return dummynodei->next;
}


    ListNode* reverseab(ListNode* a,ListNode* b)
    {
        ListNode* pre = NULL;
        ListNode* cur = a;
        ListNode* head_new = NULL;
        while(cur!=b)
        {
            if(cur->next == b)
                head_new = cur;
            ListNode* next_node = cur->next;
            cur->next=pre;
            pre=cur;
            cur=next;
        }
        return head_new;
    }
ListNode* reverseKGroup(ListNode* head, int k) {
    if(head==NULL) return NULL;
    ListNode* a=head;
    ListNode* b=head;
    for(int i=0;i<k;i++)
    {
        if(b==NULL) return head; //
        b=b->next;
    }

    ListNode* head_new = reverseab(a,b);
    a->next = reverseKGroup(b,k);
    return head_new;
}


ListNode* left;
bool traverse(ListNode* right)
{
    if(right==NULL) return true;
    bool res = traverse(right->next);

    res=(res && (right->val == left->val));
    left=left->next;
    return res;
}
bool isPalindrome(ListNode* head) {
    left=head;
    return traverse(head);
}

ListNode* reverse(ListNode* head)
{
    ListNode* last=reverse(head->next);
    head->next->next=head;
    head->next=NULL;
    return last;
}

bool isPalindrome(ListNode* head)
{
    if(head==NULL || head->next==NULL) return true;
    ListNode* slow = head;
    ListNode* fast = head;

    while(fast!=NULL && fast->next!=NULL)
    {
        fast=fast->next->next;
        slow=slow->next;
    }
    if(fast!=NULL)
        slow=slow->next;
    ListNode* left =head;
    ListNode* right = reverse(slow);
    while(right)
    {
        if(left->val!=right->val)
            return false;
        left=left->next;
        right=right->next;
    }
    return true;
}

int maxsubarray(vector<int>& nums)
{
    int n=nums.size();
    if(0 == n) return 0;
    vector<int>dp(n,0);
    dp[0]=nums[0];
    for(int i=1;i<n;i++)
    {
        d[i]=max(nums[i],dp[i-1]+nums[i]);
    }
    int res=INT_MIN;
    for(int i=0;i<n;i++)
        res=max(res,dp[i]);

    return res;

}


int lengthLIS(vector<int>& nums)
{
    int length=nums.size();
    vector<int>dp(length,1);
    for(int i=0;i<length;i++)
    {
        for(int j=0;j<i;j++)
        {
            if(nums[j]<nums[i])
                dp[i]=max(dp[i],dp[j]+1);
        }
    }
    int res=0;
    for(int i=0;i<length;i++)
        res=max(res,dp[i]);
    return res;
}








































