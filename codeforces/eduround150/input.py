# %%
import numpy as np
# N = 300000
# a = np.random.randint(1, 5, N)
# print(N)
# print(" ".join([str(x) for x in a]))

N = 500
a = np.random.randint(0, 5, N)
values = np.array(["A", "B", "C", "D", "E"])[a]
print(1)
print("".join(values))