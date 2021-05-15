/*876. 链表的中间结点
给定一个头结点为 head 的非空单链表，返回链表的中间结点。
如果有两个中间结点，则返回第二个中间结点。
*/
ListNode* middleNode(ListNode* head)
{
    if(head==nullptr || head->next==nullptr) return head;
    ListNode* slow = head;
    ListNode* fast = head; //2个中间节点 返回第2个
    //ListNode* fast = head->next   //2个中间节点 返回第1个
    while(fast && fast->next){
        fast=fast->next->next;
        slow=slow->next;
    }
    return slow;
}


/*21 21. 合并两个有序链表
将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。 
*/

//递归 


//迭代
ListNode* mergeTwoList(ListNode* l1,ListNode* l2)
{
    if(l1 == nullptr) return l2;
    if(l2 == nullptr) return l1;
    ListNode* dummynode = new ListNode(-1);
    ListNode* temp = dummynode;
    while(l1 && l2){
        if(l1->val < l2->val){
            temp->next = l1;
            temp=l1;
            l1=l1->next;
        }else{
            temp->next=l2;
            temp=l2;
            l2=l2->next;
        }
    }
    if(l1!=nullptr) temp->next=l1;
    if(l2!=nullptr) temp->next=l2;
    return dummynode->next;
}


/*148. 排序链表
给你链表的头结点 head ，请将其按 升序 排列并返回 排序后的链表 。
*/
ListNode* Merge(ListNode* l1,ListNode* l2)
{
    if(l1 == nullptr) return l2;
    if(l2 == nullptr) return l1;

    if(l1->val < l2->val){
        l1->next = Merge(l1->next,l2);
        return l1;
    }else{
        l2->next = Merge(l1,l2->next);
        return l2;
    }
}

ListNode* sortList(ListNode* head)
{
    if(head == nullptr || head->next == nullptr) return head;
    ListNode* slow = head,*fast = head->next;
    while(fast && fast->next){
        fast=fast->next->next;
        slow=slow->next;
    }
    fast=slow->next;   //先找到中点，然后断开链表，归并排序 
    slow->next=nullptr;//

    return Merge(sortList(head),sortList(fast));
}

/*88. 合并两个有序数组
给你两个有序整数数组 nums1 和 nums2，请你将 nums2 合并到 nums1 中，使 nums1 成为一个有序数组。
初始化 nums1 和 nums2 的元素数量分别为 m 和 n 。你可以假设 nums1 的空间大小等于 m + n，
这样它就有足够的空间保存来自 nums2 的元素。

*/

void merge(vector<int>& nums1,int m,vector<int>& nums2,int n)
{
    int n1_right = m-1;
    int n2_right = n-1;
    int temp=m+n-1;
    while(n1_right>=0 && n2_right>=0){
        if(nums1[n1_right]>nums2[n2_right]){
            nums1[temp--]=nums1[n1_right--];
        }else{
            nums1[tmep--]=nums2[n2_right--];
        }
    }
    while(n2_right>=0){
        nums1[temp--]=nums2[n2_right--];
    }
}








