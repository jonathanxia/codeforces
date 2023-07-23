#!/usr/bin/env python3

from typing import List

class Solution:
    def maximumJumps(self, nums: List[int], target: int) -> int:
        ans = [0] * len(nums)
        good = [False] * len(nums)
        good[-1] = True

        for i in range(len(nums) - 2, -1, -1):
            for j in range(i + 1, len(nums)):
                if (abs(nums[i] - nums[j]) <= target and good[j]):
                    ans[i] = max(ans[i], ans[j] + 1)
                    good[i] = True
        
        return ans[0] if good[0] else -1


ss = Solution()
print(ss.maximumJumps([1,3,6,4,1,2], 2))