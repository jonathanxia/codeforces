N = 10
import numpy as np
print(1)
print(N, 2)
z = np.arange(3, N + 1)
np.random.shuffle(z)
print(" ".join([str(s) for s in z] + ["1"]))

for i in range(2, N + 1):
    print(i, 1)