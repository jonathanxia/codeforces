N = 200000
import numpy as np
print(1)
print(N, 1)
z = np.arange(2, N + 1)
np.random.shuffle(z)
print(" ".join([str(s) for s in z]))

for i in range(2, N + 1):
    print(i, np.random.randint(1, i))