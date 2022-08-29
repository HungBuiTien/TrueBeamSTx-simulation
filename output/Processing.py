import numpy as np
import matplotlib.pyplot as plt

depth_dose_file = open(r"gamma-depth-Edep.txt",'r')
depth_dose_lines = depth_dose_file.readlines()
depth_dose_data = []

for line in depth_dose_lines[6:]:
    depth_dose_data.append(float(line))

depth_dose_data = np.array(depth_dose_data)
c = depth_dose_data.shape[0]
tmp = depth_dose_data
depth_dose_data = depth_dose_data*0
for i in range(tmp.shape[0]):
    c = c - 1
    depth_dose_data[c] = tmp[i]
    
depth_dose_data = 100*depth_dose_data/depth_dose_data.max()

# Read experiment data
depth_dose_ex_file = open(r"DepthExp.txt",'r')
depth_dose_ex_lines = depth_dose_ex_file.readlines()
depth_dose_ex_data = []

for line in depth_dose_ex_lines:
    depth_dose_ex_data.append(float(line))
depth_dose_ex_data = np.array(depth_dose_ex_data)

depth = np.linspace(0.15,29.85,100)
depth2 = np.linspace(0, 30, 301)

# Read uncertainty
uncertainty_files = open(r"gamma-depth-Edep-Uncertainty.txt",'r')
uncertainty_lines = uncertainty_files.readlines()
uncertainty_data = []
for line in uncertainty_lines[6:]:
    uncertainty_data.append(float(line))
uncertainty_data = np.array(uncertainty_data)

c = uncertainty_data.shape[0]
tmp = uncertainty_data
uncertainty_data = uncertainty_data*0
for i in range(tmp.shape[0]):
    c = c - 1
    uncertainty_data[c] = tmp[i]    


fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(8, 7))
ax1.set_ylabel("Relative dose(%)")
ax1.set_xlabel("Depth (cm)")
ax1.grid("true")
ax1.plot(depth2, depth_dose_ex_data, label="Golden beam data", color='red', linewidth=3)
ax1.scatter(depth, depth_dose_data, label="GATE simulation", zorder=2, facecolor='C0', edgecolor='k')
ax1.legend(loc="upper right")

ax2.plot(depth, uncertainty_data)
ax2.set_ylabel("Uncertainty")
ax2.set_xlabel("Depth (cm)")
ax2.grid("true")

plt.savefig("DepthDose.png")