import numpy as np
import random
import string

def list_to_str(arr):
    return " ".join([str(x) for x in arr])

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


# Create your own test case
N = 10 ** 12
S = 10 ** 5
T = 10 ** 5
print(N)
print(generate_random_lowercase_string(S))
print(generate_random_lowercase_string(T))