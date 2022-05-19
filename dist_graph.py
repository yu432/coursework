import matplotlib.pyplot as plt

x = []
y = []
f = open("dist.txt")
for i in f:
    a = i.split()
    x.append(int(a[1]))
    y.append(int(a[2]))
plt.plot(x, y)
plt.xscale('log')
plt.show()
