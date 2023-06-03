import numpy as np
N = 2500000
a = np.random.randint(0, 10 ** 9, N)
b = np.random.randint(0, 10 ** 9, N)

print(N - 1)
print(" ".join([str(s) for s in a]))
print(" ".join([str(s) for s in b]))