#!/usr/bin/env python3

from typing import List

class Solution:
    def splitWordsBySeparator(self, words: List[str], separator: str) -> List[str]:
        output = []
        for word in words:
            xs = word.split(separator)
            for x in xs:
                if x:
                    output.append(x)
        return output
