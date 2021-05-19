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


/*链表求和
给定两个用链表表示的整数，每个节点包含一个数位。
这些数位是反向存放的，也就是个位排在链表首部。
编写函数对这两个整数求和，并用链表形式返回结果。

输入：(7 -> 1 -> 6) + (5 -> 9 -> 2)，即617 + 295
输出：2 -> 1 -> 9，即912
*/
ListNode* addTwoNumbers(ListNode* l1,ListNode* l2)
{
    ListNode* head = new ListNode(-1);
    ListNode* p1=l1,*p2=l2,*p=head;
    int sum = 0,carry = 0;
    while(p1 || p2 || carry){
        sum = 0;
        if(p1){
            sum +=p1->val;
            p1=p1->next;
        }
        if(p2){
            sum +=p2->val;
            p2=p2->next;
        }
        sum +=carry;
        ListNode* temp = new ListNode(sum%10);
        carry = sum/10;
        p->next = temp;
        p=p->next;
    }
    return head->next;
}



/*160   相交链表
编写一个程序，找到两个单链表相交的起始节点。

定义两个指针, 第一轮让两个到达末尾的节点指向另一个链表的头部, 最后如果相遇则为交点(在第一轮移动中恰好抹除了长度差)
两个指针等于移动了相同的距离, 有交点就返回, 无交点就是各走了两条指针的长度

*/

ListNode* getIntersectionNode(ListNode* headA,ListNode* headB)
{
    if(NULL == headA || NULL == headB) return nullptr;
    ListNode* tempa = headA;
    ListNode* tempb = headB;
    while(tempa!=tempb){
        tempa = tempa==NULL?headB:tempa->next;
        tempb = tempb==NULL?headA:tempb->next;
    }
    return tempa;
}

//anthor
ListNode* getIntersectionNode(ListNode* headA,ListNode* headB)
{
    if(nullptr == headA || nullptr == headB) return nullptr;
    ListNode* tempa = headA;
    ListNode* tempb = headB;
    int lena=0,lenb=0;
    while(tempa){
        lena++;
        tempa=tempa->next;
    }
    while(tempb){
        lenb++;
        tempb=temp->next;
    }
    if(tempa == tempb){
        if(lena>lenb){
            while(lena-lenb>0){
                headA=headA->next;
                lena--;
            }
        }
        if(lenb>lena){
            while(lenb-lena>0){
                headB=headB->next;
                lenb--;
            }
        }
        while(headA!=headB){
            headA=headA->next;
            headB=headB->next;
        }
        return headA;


    }else{
        return nullptr;
    }
}


/*141 环形链表
给定一个链表，判断链表中是否有环。
*/

bool hasCycle(ListNode* head)
{
    if(head == nullptr || head->next == nullptr) return false;
    ListNode* slow = head;
    ListNode* fast = head->next->next;
    while(fast && fast->next){

        if(slow == fast) return true;
        slow = slow->next;
        fast = fast->next->next;
    }
    return false;
}


/*环形链表 II
给定一个链表，返回链表开始入环的第一个节点。 如果链表无环，则返回 null。
*/
ListNode* detectCycle(ListNode* head)
{
    ListNode* slow = head;
    ListNode* fast = head;
    while(fast && fast->next){

        slow=slow->next;
        fast=fast->next->next;
        if(slow == fast){

            ListNode* temp = head;
            while(temp != slow){
                temp=temp->next;
                slow=slow->next;
            }
            return temp;
        }
    }
    return NULL;
}

/*奇偶链表
给定一个单链表，把所有的奇数节点和偶数节点分别排在一起。请注意，这里的奇数节点和偶数节点指的是节点编号的奇偶性，
而不是节点的值的奇偶性
*/
ListNode* oddEvenList(ListNode* head)
{
    if(nullptr == head || nullptr == head->next) return head;
    ListNode* odd = head;
    ListNode* even = head->next;
    ListNode* even_head = even;
    while(even && even->next){
        odd->next = even->next;
        odd=odd->next;
        even->next = odd->next;
        even=even->next;
    }
    odd->next=even->head;
    return head;
}











