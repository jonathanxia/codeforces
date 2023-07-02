class Solution:
    def minimizedStringLength(self, s: str) -> int:
        a = set()
        for ch in s:
            a.add(ch)
        
        return len(a)

ss = Solution()
print(ss.minimizedStringLength("aaabc"))