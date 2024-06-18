import numpy as np
import random
import string

def list_to_str(arr):
    if is_iterable(arr):
        return " ".join([str(x) for x in arr])
    else:
        return arr

def uid(a, b, n=None):
    if n == None:
        return np.random.randint(a, b + 1)
    else:
        return np.random.randint(a, b + 1, size=n)

def is_iterable(obj):
    try:
        iter(obj)
        return True
    except TypeError:
        return False

def generate_tree(N, w_max=10 ** 9):
    """
    Generates a tree with N vertices and weights

    A list of triples (u, v, w) which are 1 indexed.
    """
    edges = []
    for i in range(2, N + 1):
        edges.append((i, np.random.randint(1, i), np.random.randint(1, w_max + 1)))
    
    return edges

def generate_random_string(length):
    """
    Generate a random string of the specified length.

    Parameters:
    - length (int): The length of the random string to generate.

    Returns:
    - str: The generated random string.
    """
    characters = string.ascii_letters + string.digits  # You can customize this if you want other characters
    random_string = ''.join(random.choice(characters) for _ in range(length))
    return random_string

def generate_random_lowercase_string(length):
    """
    Generate a random string of lowercase letters with the specified length.

    Parameters:
    - length (int): The length of the random string to generate.

    Returns:
    - str: The generated random string.
    """
    characters = string.ascii_lowercase
    random_string = ''.join(random.choice(characters) for _ in range(length))
    return random_string

def generate_permutation(n, zero_indexed=False):
    """
    Generate a permutation of 1 through n.
    """
    if zero_indexed:
        return random.sample(range(n), n)
    else:
        return [x + 1 for x in random.sample(range(n), n)]

def generate_binary_string(n):
    """
    Generates a binary string of length n, randomly
    """
    return "".join([str(x) for x in uid(0, 1, n)])

# Create your own test case
print(1)
n = uid(1, 20)
print(n)
s = generate_binary_string(n)
t = generate_binary_string(n)

print(s)
print(t)
q = uid(1, 10)
print(q)
for i in range(q):
    l = uid(1, n)
    r = uid(1, n)
    print(min(l, r), max(l, r))
