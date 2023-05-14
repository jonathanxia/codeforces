import numpy as np
N = 10 ** 4
print(N)
print(" ".join([str(s) for s in np.random.randint(0, 10 ** 9 - 1, size=(N,))]))

for i in range(N // 2):
    print(2 * i + 1, 2 * i + 2)
    print(2 * i + 1, 2 * i + 3)