
import matplotlib.pyplot as plt
import numpy as np                
import os
from pathlib import Path

#%% The following command display the current working directory (where jupyter has been launched)
cwd = os.getcwd()
print('The Current Working Directory (CWD) is: \n', cwd)

#%% Display the content of a folder
output_folder = Path('./output')                            # <--------------------------------------TO CHANGE BY YOUR OWN OUTPUT FOLDER 
if (not output_folder.is_dir()):
    print('ERROR: {} is not a folder.'.format(output_folder))
else:
    print('The folder and contains the following files:'.format(output_folder))
    p = output_folder.glob('**/*')
    files = [x for x in p if x.is_file()]
    for x in files:
        print(x)

# Set the filenames (d = depth, p = profile)
f_d_edep = os.path.join(output_folder, 'gamma-depth-Edep.txt')
f_d_uncert = os.path.join(output_folder, 'gamma-depth-Edep-Uncertainty.txt')
f_p_edep = os.path.join(output_folder, 'gamma-profile-Edep.txt')
f_p_uncert = os.path.join(output_folder, 'gamma-profile-Edep-Uncertainty.txt')

#%% Load data from txt files
d_edep = np.loadtxt(f_d_edep)
d_uncert = np.loadtxt(f_d_uncert)
p_edep = np.loadtxt(f_p_edep)
p_uncert = np.loadtxt(f_p_uncert)

#%%
# Declare a single figure (one row, one column)
fig, ax = plt.subplots(ncols=1, nrows=1, figsize=(12, 6))

# X values from 0 to n, n is the length of d_edep
n = len(d_edep)
x = np.linspace(0, n, n)

# First curve, gamma depth in green
y = d_edep
c1 = ax.plot(x, y, 'g-', label='edep', linewidth=2)

# Second curve, gamma uncertainty in blue, share the same x axis, but use a
# different y axis
y = d_uncert
ax2 = ax.twinx()
c2 = ax2.plot(x, y, 'b-', label='$\sigma$ (uncertainty)')

# Add the legend and the title
lns = c1+c2
labs = [l.get_label() for l in lns]
ax.legend(lns, labs, loc=0)
ax.set_title('Depth deposited energy')
ax.set_xlabel('Distance in mm')
ax.set_ylabel('Deposited energy in MeV')
f = ax2.set_ylabel('Uncertainty')

# save on disk (optional)
plt.savefig('depth_dose.png',dpi=300,bbox_inches="tight",pad_inches=None)

#%%
# Declare a figure 
fig, ax = plt.subplots(ncols=1, nrows=1, figsize=(12, 6))

# Third curve, gamma profile in green
n = len(p_edep)
x = np.linspace(0, n, n)
y = p_edep
c3 = ax.plot(x, y, 'g-', label='edep', linewidth=2)

# Last curve, gamma uncertainty profile
y = p_uncert
ax2 = ax.twinx()
c4 = ax2.plot(x, y, 'b-', label='$\sigma$ (uncertainty)')

# Add the legend and the title
lns = c3+c4
labs = [l.get_label() for l in lns]
ax.legend(lns, labs, loc=0)
ax.set_title('Deposited energy profile')
ax.set_xlabel('Distance in mm')
ax.set_ylabel('Deposited energy in MeV')
f = ax2.set_ylabel('Uncertainty')