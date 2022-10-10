import numpy as np

import scipy.stats as ss
import matplotlib
matplotlib.use("agg")
import matplotlib.pyplot as plt

class ToolGen:
    def __init__(self):
        pass
    def createRandomVariable(self):
        x = np.arange(1,10)
        xU, xL = x + 1, x - 1
        prob = ss.norm.cdf(xU, scale = 3) - ss.norm.cdf(xL, scale = 3)
        prob = prob / prob.sum()
        random_array = np.random.choice(x,size = 100,p = prob)
        return random_array

    def writeTestCase(self,randomInts):
        #axis = np.arange(start=min(randomInts), stop = max(randomInts) + 1)
        pass

    def run(self):


p1 = ToolGen()
p1.run()