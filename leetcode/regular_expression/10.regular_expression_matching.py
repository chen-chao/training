'''
LeetCode 10: Regular Exression Matching

Given an input string (s) and a pattern (p), implement regular expression matching with support for '.' and '*'.

'.' Matches any single character.
'*' Matches zero or more of the preceding element.

The matching should cover the entire input string (not partial).

Dynamic Programming Solution:

Use boolean table match(i, j) to represent wheather pattern[i:] matches string[j:].
We can get:

match(i, j) = match(i+2, j) if pattern[i+1] == *
              match(i, j+1) if pattern[i+1] == * and pattern[i] == string[j]
              match(i+1, j+1) if pattern[i+1] != * and (pattern[i] == '.' or pattern[i] == string[j])
              False otherwise
'''


def top_down_match(pattern, string):
    cache = {}
    plen = len(pattern)
    slen = len(string)
    cache[plen, slen] = True
    def _match(i, j):
        if (i, j) not in cache:
            if i+1 < plen and pattern[i+1] == '*':
                if pattern[i] != string[j]:
                    cache[i, j] = _match(i+2, j)
                else:
                    cache[i, j] = _match(i+2, j) or _match(i, j+1)
            else:
                if pattern[i] == '.' or pattern[i] == string[j]:
                    cache[i, j] = _match(i+1, j+1)
                else:
                    cache[i, j] = False

        return cache[i, j]
    return _match(0, 0)


# this is from the leetcode solution
def bottom_up_match(pattern, text):
    dp = [[False] * (len(pattern) + 1) for _ in range(len(text) + 1)]

    dp[-1][-1] = True
    for i in range(len(text), -1, -1):
        for j in range(len(pattern) - 1, -1, -1):
            first_match = i < len(text) and pattern[j] in {text[i], '.'}
            if j+1 < len(pattern) and pattern[j+1] == '*':
                dp[i][j] = dp[i][j+2] or first_match and dp[i+1][j]
            else:
                dp[i][j] = first_match and dp[i+1][j+1]

    return dp[0][0]


if __name__ == '__main__':
    import sys
    argv = sys.argv
    if len(argv) < 3:
        print('Usage: python 10.regular_expression_matching.py pattern s1 [s2...] ')
    else:
        for s in argv[2:]:
            if top_down_match(argv[1], s):
                print('top_down_match Found: ', s)
            if bottom_up_match(argv[1], s):
                print('bottom_up_match Found: ', s)
