import numpy as np
N = 100000
print(N)
# print(" ".join([str(s) for s in np.random.randint(0, 10 ** 9 + 1, size=(N,))]))
print(" ".join(
    ["1", "1", "1", "1", "1"] + 
    [str(s // 2) for s in range(50, N + 50 - 5)]
))
# print(" ".join(["2"] * N))

# for i in range(2, N + 1):
#     parent = np.random.randint(1, i)
#     print(i, parent)
# for i in range(N // 2 - 1):
#     print(2 * i + 1, 2 * i + 2)
#     print(2 * i + 1, 2 * i + 3)

# for i in range(2, N + 1):
#     print(i // 3000 + 1, i)

print(1, 2)
print(1, 3)
print(1, 4)
edges = 3
for i in range(5, 30005):
    print(i, 2)
    edges += 1

for i in range(30005, 60005):
    print(i, 3)
    edges += 1

for i in range(60005, 90005):
    print(i, 4)
    edges += 1

for i in range(90005, 100001):
    print(i, 5)
    edges += 1

assert edges == N - 1, edges
