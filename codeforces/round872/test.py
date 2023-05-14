import numpy as np
N = 100000
print(N)
print(" ".join([str(s) for s in np.random.randint(0, 10 ** 9 - 1, size=(N,))]))
# print(" ".join(["2"] * N))

# for i in range(2, N + 1):
#     parent = np.random.randint(1, i)
#     print(i, parent)
for i in range(N // 2 - 1):
    print(2 * i + 1, 2 * i + 2)
    print(2 * i + 1, 2 * i + 3)