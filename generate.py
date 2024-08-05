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

def generate_binary_string(n, char_set = ("0", "1")):
    """
    Generates a binary string of length n, randomly
    """
    return "".join([char_set[x] for x in uid(0, len(char_set) - 1, n)])

# Create your own test case
n = 10
k = uid(1, 20)
w = uid(1, 9)
h = uid(1, 9)
print(1)
print(n, k, w, h)
print(generate_binary_string(n, ("L", "R", "D", "U")))