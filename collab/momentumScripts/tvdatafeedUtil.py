"""
@author: Mitul Patel --> https://github.com/mitul19
"""

import numpy as np
import pandas as pd


def getVolatility(data):
    return round(np.std(data) * np.sqrt(252) * 100, 2)


def getDailyReturns(data):
    return data.pct_change()


def getSharpe(data):
    return round(np.sqrt(252) * data.mean() / data.std(), 2)


def getSortino(data):
    return round(np.sqrt(252) * data.mean() / data[data < 0].std(), 2)


def getMaxDrawdown(data):
    cummRet = (data + 1).cumprod()
    peak = cummRet.expanding(min_periods=1).max()
    drawdown = (cummRet / peak) - 1
    return drawdown.min()


def getCalmar(data):
    return data.mean() * 252 / abs(getMaxDrawdown(data))


def getFIP(data):
    retPos = np.sum(data.pct_change()[1:] > 0)
    retNeg = np.sum(data.pct_change()[1:] < 0)
    return retPos - retNeg
