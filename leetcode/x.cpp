

#define METHOD maxIncreasingGroups

class Solution {
public:
    int maxIncreasingGroups(vector<int>& usageLimits) {
        vl usage_limits = LC(ll(x), x, usageLimits);
        return 0;
    }
};


#ifdef DEBUG
int main() {
    Solution s;
    vi parent = {1, 2, 5};
    print(s.METHOD(parent));
    return 0;
}
#endif