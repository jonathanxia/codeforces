
def process_string(s):
    a = []
    b = []
    tokens = s.split(",")
    for token in tokens:
        stuff = [t.strip() for t in token.split(":")]
        data = [int(x) for x in stuff[1].split(" ")]
        index = int(stuff[0])

        a.append(index)
        b.append(data)

    return a, b

times, dirs = process_string(input())
times, coords = process_string(input())

print(1)
print(3, 9)
print(100)

for i, t in enumerate(times):
    for j in range(len(dirs[i])):
        print(t, dirs[i][j], coords[i][j])