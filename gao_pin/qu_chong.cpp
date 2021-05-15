/*26. 删除有序数组中的重复项
  给你一个有序数组 nums ，请你 原地 删除重复出现的元素，使每个元素 只出现一次 ，返回删除后数组的新长度。
  不要使用额外的数组空间，你必须在 原地 修改输入数组 并在使用 O(1) 额外空间的条件下完成。

//数组有序  
 */

int removeDuplicates(vector<int>& nums)
{
	int n = nums.size();
	if(n == 0) return 0;
	int slow = 0,fast = 1;
	while(fast<n){
		if(nums[fast]!=nums[slow]){
			slow++;
			nums[fast]=nums[slow];
		}	
		fast++;
	}
	return slow+1;
}

/*83. 删除排序链表中的重复元素

  存在一个按升序排列的链表，给你这个链表的头节点 head ，请你删除所有重复的元素，使每个元素 只出现一次 。
  返回同样按升序排列的结果链表。

 */

ListNode* deleteDuplicates(ListNode* head)
{
	if(NULL == head) return nullptr;
	ListNode* slow = head,*fast = head->next;
	while(fast!=nullptr){
		if(fast->val != slow->val){
			slow->next = fast;
			slow=slow->next;
		}
		fast=fast->next;
	}
	slow->next = nullptr;
	return head;
}


/*82. 删除排序链表中的重复元素 II
  存在一个按升序排列的链表，给你这个链表的头节点 head ，请你删除链表中所有存在数字重复情况的节点，
  只保留原始链表中 没有重复出现 的数字。

  返回同样按升序排列的结果链表。

 */
ListNode* deleteDuplicates(ListNode* head) {
	if(NULL == head || NULL == head->next) return head;
	ListNode* dummynode = new ListNode(-1);
	dummynode->next = head;
	ListNode* pre = dummynode;
	ListNode* cur = head;
	while(cur){
		//跳过当前的重复节点，使得cur指向当前重复元素的最后一个位置
		while(cur->next && cur->val == cur->next->val)
			cur=cur->next;
		if(pre->next == cur){
			//pre cur 之间没有重复节点 pre后移
			pre = pre->next;
		}else{
			//pre->next指向cur的下一个位置，（相当于跳过当前的重复元素）
			//但是pre不能移动，
			pre->next = cur->next;
		}
		cur=cur->next;
	}
	return dummynode->next;
}















