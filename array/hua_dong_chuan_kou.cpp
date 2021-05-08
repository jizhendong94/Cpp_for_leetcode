/*76 最小覆盖子串

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



































