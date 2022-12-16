import numpy as np
import matplotlib.pyplot as plt


data = np.genfromtxt("output.txt")

x = np.linspace(-10, 10, 16385)
plt.plot(x, data)
plt.xlabel(r'$x$')
plt.ylabel(r'$f(x)$')
plt.grid(True)
plt.show()