"""
https://www.hackerrank.com/challenges/fair-cut/problem
4 2
4 3 1 2 should output 6
4 1
3 3 3 1 should output 2
"""

size, take_num = [int(i) for i in input().split()]
arr = sorted(int(i) for i in input().split())

best_unfairness = [[float('inf')] * (take_num + 1) for _ in range(size + 1)]
# set our base case
best_unfairness[0][0] = 0

for i in range(1, size + 1):
    n = arr[i - 1]  # just a shorthand
    # we can only take at most i elements, so yeah
    for t in range(min(i, take_num) + 1):
        # case 1: we include the number in our set
        include = float('inf')
        if t > 0:
            include = (
                    best_unfairness[i - 1][t - 1]
                    + n * (i - t) - n * ((size - i) - (take_num - t))
            )

        # case 2: we just don't
        dont = float('inf')
        if best_unfairness[i - 1][t] != float('inf'):
            dont = (
                    best_unfairness[i - 1][t]
                    + n * t - n * (take_num - t)
            )

        best_unfairness[i][t] = min(include, dont)

print(best_unfairness[size][take_num])
