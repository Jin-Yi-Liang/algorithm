//double pointer
#define INF 100005
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int l=0,r,len=INF,cur=0,n=nums.size();
        for(r=0;r<n;++r){
            cur+=nums[r];
            while(cur>=target){
                len=min(len,r-l+1);
                cur-=nums[l];
                ++l;
            }
        }
        if(len==INF) return 0;
        return len;
    }
};
