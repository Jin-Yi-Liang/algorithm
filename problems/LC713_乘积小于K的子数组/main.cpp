class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        int l=0,r=0,n=nums.size(),cur=1,ans=0;
        for(;r<n;++r){
            cur*=nums[r];
            while(l<=r && cur>=k){
                cur/=nums[l];
                ++l;
            }
            ans+=(r-l+1);
        }
        return ans;
    }
};