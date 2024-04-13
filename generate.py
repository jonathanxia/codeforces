import numpy as np
import random
import string

def list_to_str(arr):
    return " ".join([str(x) for x in arr])

def uid(a, b, n=1):
    if n == 1:
        return np.random.randint(a, b + 1)
    else:
        return np.random.randint(a, b + 1, size=n)

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

# Create your own test case
arr = uid(-5, 5, (3, 3))
for i in range(3):
    print(list_to_str(arr[i]))