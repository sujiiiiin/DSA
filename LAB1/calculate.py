from scipy.optimize import fsolve
import numpy as np


def equation(n):
    return n * np.log2(n) - 2.5e6


n_solution = fsolve(equation, 150000)
print(n_solution)

# n = int(input())
# result = n * np.log2(n)
# print(result)
