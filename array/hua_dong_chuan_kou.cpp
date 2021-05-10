/*76 最小覆盖子串
  给你一个字符串 s 、一个字符串 t 。返回 s 中涵盖 t 所有字符的最小子串。
  如果 s 中不存在涵盖 t 所有字符的子串，则返回空字符串 "" 。

  注意：如果 s 中存在这样的子串，我们保证它是唯一的答案。
 */


string minWindow(string s,string t)
{
	unordered_map<char,int>need,window;
	for(char c:t) need[c]++;

	int left=0,right=0;
	int valid = 0;
	//记录最小子串起始索引和长度
	int start =0,len=INT_MAX;
	int valid=0;

	while(right<s.size()){
		//c 是 要 移入窗口的字符
		char c=s[right];
		right++; //窗口右移
		//进行窗口的更新
		if(need.count(c)){
			window[c]++;
			if(window[c] == need[c])
				valid++;
		}

		//判断左侧是否要收缩
		while(valid == need.size()){
			if(right-left<len){
				start=left;
				len = right-left;
			}
			//d是要移除窗口的字符
			char d = s[left];
			//左移窗口
			left++;

			if(need.count(d)){
				if(window[d]==need[d])
					valid--;
				window[d]--;
			}
		}


	}
	return len==INT_MAX?"":s.substr(start,len);

}


/*567 
  给定两个字符串 s1 和 s2，写一个函数来判断 s2 是否包含 s1 的排列。

  换句话说，第一个字符串的排列之一是第二个字符串的 子串 。
 */

bool checkInclusion(string s1, string s2) {
	unordered_map<char,int>need,window;
	for(char c:s1) need[c]++;
	int left=0,right=0;
	int valid = 0;
	while(right<s2.size()){
		char c =s2[right];
		right++;
		if(need.count(c)){
			window[c]++;
			if(window[c]==need[c])
				valid++;
		}
		//判断左侧窗口是否要收缩
		while(right-left>=s1.size()){
			//找到了合法的子串
			if(valid == need.size())
				return true;
			char d = s2[left];
			left++;
			if(need.count(d)){
				if(window[d]==need[d])
					valid--;
				window[d]--;
			}
		}

	}
	return false;
}

/*438  找出所有字母的异位词
  给定一个字符串 s 和一个非空字符串 p，找到 s 中所有是 p 的字母异位词的子串，返回这些子串的起始索引。

  字符串只包含小写英文字母，并且字符串 s 和 p 的长度都不超过 20100。

  呵呵，这个所谓的字母异位词，不就是排列吗，搞个高端的说法就能糊弄人了吗？相当于，
  输入一个串S，一个串T，找到S中所有T的排列，返回它们的起始索引。
 */

vector<int> findAnagrams(string s, string p) {
	unordered_map<char,int>need,window;
	for(char c:p) need[c]++;
	int left=0,right=0;
	int valid = 0;
	vector<int>res;
	while(right<s.size()){
		char c = s[right];
		right++;
		if(need.count(c)){
			window[c]++;
			if(window[c]==need[c])
				valid++;
		}

		while(right-left>=p.size()){
			if(valid==need.size())
				res.push_back(left);
			char d = s[left];
			left++;
			if(need.count(d)){
				if(window[d]==need[d])
					valid--;
				window[d]--;
			}
		}
	}
	return res;
}












