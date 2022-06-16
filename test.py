from random import sample
import matplotlib.pyplot as plt
plt.style.use('seaborn-whitegrid')
import numpy as np

x = []
y =[]
s=0
for i in range(0, 400):
    val = np.sin(2.0 * 3.14159265358979323846264338327950 * 440.0 / 44100 * s) * 10000
    x.append(i)
    y.append(val)
    s = s+1
    if s > ( 44100/440.0 ):
        s = 0

# x = list(range(0, 120))
# y = [0, 575, 1149, 1719, 2283, 2840, 3387, 3923, 4446, 4954, 5446, 5920, 6374, 6807, 7217, 7604, 7965, 8300, 8607, 8886, 9135, 9354, 9542, 9698, 9822, 9914, 9973, 9998, 9991, 9950, 9876, 9770, 9631, 9460, 9258, 9025, 8763, 8471, 8151, 7804, 7431, 7033, 6613, 6170, 5707, 5224, 4725, 4210, 3681, 3139, 2588, 2027, 1460, 888, 314, -261, -836, -1409, -1976, -2537, -3090, -3632, -4162, -4679, -5180, -5664, -6129, -6573, -6996, -7396, -7771, -8120, -8443, -8737, -9003, -9238, -9443, -9617, -9759, -9868, -9945, -9988, -9999, -9976, -9921, -9832, -9711, -9557, -9372, -9156, -8910, -8633, -8329, -7996, -7637, -7253, -6845, -6414, -5962, -5490, -4999, -4493, -3971, -3436, -2890, -2334, -1770, -1201, -627, -52, 523, 1097, 1667, 2232, 2789, 3338, 3875, 4399, 4909, 5402]

plt.plot(x, y, 'o', color='black')

plt.show()
