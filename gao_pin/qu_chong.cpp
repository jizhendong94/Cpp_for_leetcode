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
			nums[slow]=nums[fast];
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

/*27  移除元素
  给你一个数组 nums 和一个值 val，你需要 原地 移除所有数值等于 val 的元素，并返回移除后数组的新长度。
  不要使用额外的数组空间，你必须仅使用 O(1) 额外空间并 原地 修改输入数组。
  元素的顺序可以改变。你不需要考虑数组中超出新长度后面的元素。

  思路：
  注意这里和有序数组去重的解法有一个重要不同，我们这里是先给nums[slow]赋值然后再给slow++，
  这样可以保证nums[0..slow-1]是不包含值为val的元素的，最后的结果数组长度就是slow。
 */

int removeElement(vector<int>& nums, int val) {
	if(nums.size() == 0) return 0;
	int slow=0,fast=0;
	while(fast < nums.size()){
		if(nums[fast] != val){
			nums[slow]=nums[fast];
			slow++;
		}
		fast++;
	}
	return slow;
}

/*283  移动零

  给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。
 */

int removeElement(vector<int>& nums,int val){
	if(nums.size()==0) return 0;
	int slow=0,fast=0;
	while(fast<nums.size()){
		if(nums[fast] != val){
			nums[slow]=nums[fast];
			slow++;
		}
		fast++;
	}
	return slow;
}
void moveZeroes(vector<int>& nums) {
	int p = removeElement(nums,0);
	for(;p<nums.size();p++)
		nums[p]=0;
	return ;
}

/*316 去除重复字母
  给你一个字符串 s ，请你去除字符串中重复的字母，使得每个字母只出现一次。
  需保证 返回结果的字典序最小（要求不能打乱其他字符的相对位置）。
 */

string removeDuplicateLetters(string s)
{
	//存放去重的结果
	stack<char>stk;
	//记录栈中是否存在某个字符
	vector<char>instack(256,false);
	//维护一个计数器 记录字符串中字符的数量
	vector<int>count(256,0);
	for(char c:s){
		count[c]++;
	}

	for(char c:s){
		//遍历一个字符，将对应的计数--
		count[c]--;
		//如果栈中存在c 直接跳过
		if(instack[c]) continue;
		//插入栈之前，和之前的元素比较一下大小
		//如果字典序比前面的小，pop前面的元素。
		while(!stk.empty() && stk.top()>c){
			//若之后没有了，停止pop
			if(count[stk.top()] == 0) break;
			//若之后还有，弹出栈顶元素，并把该元素标记为不再栈中
			instack[stk.top()]=false;
			stk.pop();
		}
		//如果栈中不存在c  插入栈并且标记
		stk.push(c);
		instack[c]=true;
	}
	string res;
	while(!stk.empty()){
		res += stk.top();
		stk.pop();
	}
	reverse(res.begin(),res.end());
	return res;
}

/*1081  不同字符的最小子序列  和上体一样

  返回 s 字典序最小的子序列，该子序列包含 s 的所有不同字符，且只包含一次。

 */

string smallestSubsequence(string s) {
	stack<char>stk;
	vector<bool>instack(256,false);
	vector<int>count(256,0);
	for(char c:s){
		count[c]++;
	}
	for(char c:s){
		count[c]--;
		if(instack[c]) continue;

		while(!stk.empty() && stk.top() > c){
			if(count[stk.top()]==0) break;

			instack[stk.top()]=false;
			stk.pop();
		}

		stk.push(c);
		instack[c]=true;
	}
	string res;
	while(!stk.empty()){
		res +=stk.top();
		stk.pop();
	}
	reverse(res.begin(),res.end());
	return res;
}




