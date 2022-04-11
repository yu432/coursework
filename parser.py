import numpy as np
import matplotlib.pyplot as plt

f = open("output.txt")
counter = 0
errors_classic = []
errors_conservative = []
for i in f:
    counter += 1
    if counter % 4 == 2:
        errors_classic.append(list(map(float, i.split())))
    elif counter % 4 == 0:
        errors_conservative.append(list(map(float,  i.split())))
    else:
        continue

errors_classic = np.array(errors_classic)
errors_conservative = np.array(errors_conservative)

mean_classic = np.mean(errors_classic, axis=0)
mean_conservative = np.mean(errors_conservative, axis=0)


plt.plot(mean_classic, 'r')
plt.plot(mean_conservative, 'b')


plt.show()



