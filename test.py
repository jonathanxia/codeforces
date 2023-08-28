import numpy as np
def print_list(arr):
    print(" ".join([str(x) for x in arr]))

N = 100000
Q = 100000
z = np.random.randint(1, 5 * 10 ** 6, N)
print(N, Q)
print_list(z)

for i in range(Q):
    k = np.random.randint(1, 3)
    x = np.random.randint(1, N)
    y = np.random.randint(1, N)
    print(k, x, y)