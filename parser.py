import subprocess
import sys
import numpy as np
import matplotlib.pyplot as plt
import os

seed = "88129"
count_streams = "10000"

compile_cpp = ["clang++", "-std=c++20", "main.cpp"]
process_one = subprocess.Popen(compile_cpp, stdout=subprocess.PIPE)
process_one.wait()
run_cpp = ["./a.out", seed, count_streams]
process_two = subprocess.run(run_cpp, stdout=open('output.txt', 'w'))

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


plt.plot(mean_classic, 'o', color='r', markersize=2)
plt.plot(mean_conservative, 'o', color='b', markersize=2)
##plt.yscale('log')

plt.xscale('log')
plt.show()



