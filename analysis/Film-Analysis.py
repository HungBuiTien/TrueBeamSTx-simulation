# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

import matplotlib.pyplot as plt
import numpy as np
import SimpleITK as sitk
from ipywidgets import interact
import os
from pathlib import Path

#%% Đọc dữ liệu đầu vào

# Set input
print(">>> Chương trình xử lý dữ liệu cho TrueBeam <<<")
print("Hãy chọn trường chiếu")
print("(press 1) Trường chiếu 10x10 cm2 ")
print("(press 2) Trường chiếu 6x6 cm2 ")
print("(press 3) Trường chiếu 4x4 cm2 ")
print("(press 4) Trường chiếu 3x3 cm2 ")
print("(press 5) Trường chiếu 2x2 cm2 ")
print("(press 6) Trường chiếu 1x1 cm2 \n")
sel = int(input("Lựa chọn của bạn: "))

if (sel == 1):
   directory = r"D:\Researchs\TrueBeam\analysis\results\Film\10x10cm2"
                            
if (sel == 2):
    directory = r"D:\Researchs\TrueBeam\analysis\results\Film\6x6cm2\run1"
    
if (sel == 3):
    directory = r"D:\Researchs\TrueBeam\analysis\results\Film\4x4cm2\run2"
    
if (sel == 4):
    directory = r"D:\Researchs\TrueBeam\analysis\results\Film\3x3cm2"
    
if (sel == 5):
    directory = r"D:\Researchs\TrueBeam\analysis\results\Film\2x2cm2\run2"
    
if (sel == 6):
    directory = r"D:\Researchs\TrueBeam\analysis\results\Film\1x1cm2"
    
nfiles = int(input("\nNhập vào số file cần tính: "))

# -----------------------------------------------------------------------------------------------------------------------------
# READING DATA
# -----------------------------------------------------------------------------------------------------------------------------

# Asorbed dose
dose = []
dose_squared = []
dose_uncertainty = []

# Edep
edep = []
edep_squared = []
edep_uncertainty = []

nEvents = []
s = []
std_error = []

def read_sitk(path):
    img_ct = sitk.ReadImage(path)
    arr_ct = sitk.GetArrayFromImage(img_ct)
    return np.array(arr_ct)

def read_static(path):
    file = open(path)
    lines = file.readlines()
    tmp = lines[1]
    tmp1 = tmp.split()
    event = float(tmp1[3])
    
    return event

for i in range(1, nfiles+1):
    # check events
    event = read_static(os.path.join(directory,"film-static")+str(i)+".txt")
    nEvents.append(event)

    # dose
    dose_tmp = read_sitk(os.path.join(directory,"film-dose")+str(i)+"-Dose.mhd")
    dose.append(dose_tmp[:,0,:])
    dose_squared_tmp = read_sitk(os.path.join(directory,"film-dose")+str(i)+"-Dose-Squared.mhd")
    dose_squared.append(dose_squared_tmp[:,0,:])
    dose_uncertainty_tmp = read_sitk(os.path.join(directory,"film-dose")+str(i)+"-Dose-Uncertainty.mhd")
    dose_uncertainty.append(dose_uncertainty_tmp)
    
    # edep
    edep_tmp = read_sitk(os.path.join(directory,"film-dose")+str(i)+"-Edep.mhd")
    edep.append(edep_tmp[:,0,:])
    edep_squared_tmp = read_sitk(os.path.join(directory,"film-dose")+str(i)+"-Edep-Squared.mhd")
    edep_squared.append(edep_squared_tmp[:,0,:])
    edep_uncertainty.append(read_sitk(os.path.join(directory,"film-dose")+str(i)+"-Edep-Uncertainty.mhd"))


#%% Tổng hợp kết quả

dose_sum = np.zeros((dose[0].shape[0], dose[0].shape[1]))
dose_squared_sum = np.zeros((dose_squared[0].shape[0],dose_squared[0].shape[1]))
dose_uncertainty_sum = np.zeros((dose_uncertainty[0].shape[0],dose_uncertainty[0].shape[1]))

edep_sum = np.zeros((edep[0].shape[0], edep[0].shape[1]))
edep_squared_sum = np.zeros((edep_squared[0].shape[0],edep_squared[0].shape[1]))
edep_uncertainty_sum = np.zeros((edep_uncertainty[0].shape[0],edep_uncertainty[0].shape[1]))

# Tổng số lịch sử đã mô phỏng
es = sum(nEvents)

# Liều tổng cộng
for i in range(0, len(dose)):
    dose_sum = dose_sum[:,:] + dose[i]
    dose_squared_sum = dose_squared_sum[:,:] + dose_squared[i]
    
    edep_sum = edep_sum[:,:] + edep[i]
    edep_squared_sum = edep_squared_sum[:,:] + edep_squared[i]

# Tính sai số thống kê

q1 = ((1)/(es - 1))
q2 = (dose_squared_sum)/es
q3 = (dose_sum/es)*(dose_sum/es)
unc = np.sqrt((q2-q3)*q1)
ave_dose = (dose_sum/es)
ave_edep = (edep_sum/es)
ave_dose[ave_dose==0] = 1E-8
re = unc/ave_dose
re[re>1] = 1
re = re*100

print(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>")
print("                             SUMMARY                        ")
print("1) Number of files: {}".format(nfiles))
print("2) Number of events: {:.2e}".format(sum(nEvents)))
print("3) Dose: {} - {} Gy".format(dose_sum.min(), dose_sum.max()))
print("4) Edep: {} - {} MeV".format(edep_sum.min(), edep_sum.max()))
print("5) Uncertainty: {} - {} %".format(re.min(), re.max()))
print(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n")
# Vẽ đồ thị

fig, ((ax1, ax2, ax3) ,(ax4, ax5, ax6)) = plt.subplots(2, 3)
fig.suptitle(directory + " - " + str(sum(nEvents)) + " events")

plot1 = ax1.imshow(dose_sum[:,:], extent=(-7.5,7.5,-7.5,7.5), cmap='jet')
ax1.set_ylabel('z position [cm]')
ax1.set_xlabel('x position [cm]')
clb1 = fig.colorbar(plot1, ax=ax1, location='right')
ax1.grid(color='w', linestyle='-', linewidth=0.3)
clb1.set_label('Absorbed dose (Gy)')

plot2 = ax2.imshow(edep_sum[:,:], extent=(-7.5,7.5,-7.5,7.5), cmap='jet')
ax2.set_ylabel('z position [cm]')
ax2.set_xlabel('x position [cm]')
clb2 = fig.colorbar(plot2, ax=ax2, location='right')
ax2.grid(color='w', linestyle='-', linewidth=0.3)
clb2.set_label('Deposited energy (MeV)')

plot3 = ax3.imshow(re[:,:], extent=(-7.5,7.5,-7.5,7.5), cmap='jet')
ax3.set_ylabel('z position [cm]')
ax3.set_xlabel('x position [cm]')
clb3 = fig.colorbar(plot3, ax=ax3, location='right')
ax3.grid(color='w', linestyle='-', linewidth=0.5)
clb3.set_label('Dose uncertainty (%)')

x = np.linspace(-15,15,300)
plot4 = ax4.plot(x,dose_sum[:,150])
ax4.set_xlabel('x position [cm]')
ax4.set_ylabel('Absorbed dose [Gy]')
ax4.grid(color='r', linestyle='-', linewidth=0.3)

x = np.linspace(-15,15,300)
plot5 = ax5.plot(x,re[:,150])
ax5.set_xlabel('x position [cm]')
ax5.set_ylabel('Relative uncertainty [%]')
ax5.grid(color='r', linestyle='-', linewidth=0.3)

