import random

for i in range(100000):
    tup = [random.randint(-10000, 10000) for i in range(5)]
    for num in tup:
        print(num, end = " ")
    print()