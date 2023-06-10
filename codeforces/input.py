# %%
import numpy as np
import matplotlib.pyplot as plt
n = 10 ** 6
print(n)
# %%
d = np.arange(1, 10 ** 5)

x = 1 - (d / n)
plt.plot(d, x ** (1000 - 2 * np.sqrt(d)))
# %%
1000 - 2 * np.sqrt(1000)
# %%
k = 320
d = ((1000 - k) / 2) ** 2

print((1 - d / n) ** k)
print("d=", d)
# %%
