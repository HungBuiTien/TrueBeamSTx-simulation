import numpy as np
import matplotlib.pyplot as plt

file = open(r"gamma-profile-Edep.txt", 'r')
lines = file.readlines()

data = []
for line in lines[6:]:
    data.append(float(line))

data = np.array(data)
plt.plot(data)

