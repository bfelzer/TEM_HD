# TEM_HD
Daily TEM-Hydro
There are two version of TEM-HD here:
1. ttemd_cwd.cpp and xtemd_cwd.cpp are version designed for annual CO2 values, which is the TEM normative
2. ttemd_cwd_insect.cpp and xtemd_cwd_njpine.cpp (should have named them both insect or njpine) are designed for daily CO2 values from the flux towers
Ignore the *ori versions - they are old versions of the code that can be deleted
tem_daily files are for post-processing model results (multi indicate written to process more than one grid); dailym version includes writing out the month)
xml files are used for calibration (hvd, kbm, knz, paw, and lehigh_temd_daily_dout_calib.xml), others are extrapolations
