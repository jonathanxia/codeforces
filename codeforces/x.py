from collections import defaultdict

counts = defaultdict(lambda: 0)
# for i in range(1, 31058):
for i in range(1, 3000):
    d = str(i)    
    sum_digits = sum([int(dd) for dd in d])
    counts[sum_digits] += 1

s = 0
for i in range(1, 20):
    s += counts[i]

print(s)