# -*- coding: utf-8 -*-
"""
Created on Thu Aug 18 11:10:24 2022

@author: HungBT
"""

import numpy as np
import matplotlib.pyplot as plt


file = open("output/2E9/gamma-depth-Edep.txt",'r')
lines=file.readlines()
gamma_depth_Edep = []
for line in lines[6:]:
    gamma_depth_Edep.append(float(line))
gamma_depth_Edep = np.array(gamma_depth_Edep)
gamma_depth_Edep_new = []
for i in range(gamma_depth_Edep.shape[0]-1,-1,-1):
    gamma_depth_Edep_new.append(gamma_depth_Edep[i])

gamma_depth_Edep_new = np.array(gamma_depth_Edep_new)
gamma_depth_Edep_new = 100*gamma_depth_Edep_new/gamma_depth_Edep_new.max()

depth = np.linspace(0,29.7,100)
plt.scatter(depth, gamma_depth_Edep_new)

#%%

# read FFF experiment data
exFile = open("6FFF_Depth10_Size10.txt", 'r')
exdat = exFile.readlines()
exData = []

for line in exdat:
    tmp = line.split()
    exData.append(float(tmp[0]))


file = open("output/myDose-DoseToWater.txt",'r')
lines=file.readlines()