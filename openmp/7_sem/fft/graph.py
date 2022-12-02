import numpy as np
import matplotlib.pyplot as plt


data = np.genfromtxt("result1.txt")
data2 = np.genfromtxt("result2.txt")
x = np.arange(10, 20, 1)
plt.plot(x, data2, x, data)
plt.xlabel(r'$x$')
plt.ylabel(r'$f(x)$')
plt.title(r'$f_1(x)=\opt,\ f_2(x)=\common')
plt.grid(True)
plt.show()
