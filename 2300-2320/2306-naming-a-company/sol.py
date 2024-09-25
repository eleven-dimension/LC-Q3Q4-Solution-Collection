from collections import defaultdict
from typing import List

class Solution:
    def distinctNames(self, ideas: List[str]) -> int:
        n = len(ideas)
        suffix_to_first = defaultdict(set)

        for idea in ideas:
            suffix = idea[1:]
            suffix_to_first[suffix].add(idea[0])

        ans = 0
        for c1 in range(ord('a'), ord('z') + 1):
            for c2 in range(ord('a'), ord('z') + 1):
                if c1 == c2:
                    continue
                has_c1_cnt = 0
                has_c2_cnt = 0
                for suffix, st in suffix_to_first.items():
                    has_c1 = chr(c1) in st
                    has_c2 = chr(c2) in st
                    if has_c1 and not has_c2:
                        has_c1_cnt += 1
                    if not has_c1 and has_c2:
                        has_c2_cnt += 1
                ans += has_c1_cnt * has_c2_cnt

        return ans
