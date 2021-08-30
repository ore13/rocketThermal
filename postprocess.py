import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import os

filename_base = "./output/heatingSimulation{}.csv"
max_temp = []

for i in range(len(os.listdir("./output"))):
    data = pd.read_csv(filename_base.format(i + 1), sep="\t")
    max_temp.append(data.loc[:, "Skin Temperature [K]"].max())

max_temp = np.array(max_temp)
geometry = pd.read_csv("./IO/nosecone.csv", sep=",")
plt.plot(geometry.loc[:, "X"].values[1:] * 1e3, max_temp - 273.15)
plt.xlabel("X coordinate from nose tip (mm)")
plt.ylabel("Temperature [°C]")
plt.ylim([0, 700])
plt.savefig("Max Temperature.png")



