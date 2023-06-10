import numpy as np
n, m = 3, 9
r = 100

T = 5

print(1)
print(n, m)
print(r)

for i in range(r):
    d = np.random.randint(1, 3)
    if d == 1:
        print(np.random.randint(1, T), d, np.random.randint(1, n + 1))
    if d == 2:
        print(np.random.randint(1, T), d, np.random.randint(1, m + 1))