"""
Created on Sat Dec 31 2022

@author: Chintan Shah,
@editor: Mitul patel
"""

import numpy as np
import pandas as pd


def getDailyReturns(data):
    return data.pct_change()


def getAbsReturns(data):
    x = (data.iloc[-1] / data.iloc[0] - 1) * 100
    return round(x, 2)


def getVolatility(data):
    return round(np.std(data) * np.sqrt(252) * 100, 2)


def getMonthlyPrices(data):
    grps = data.groupby([data.index.year, data.index.month])
    monthlyPrices = pd.DataFrame()
    for k in grps:
        monthlyPrices = pd.concat([monthlyPrices, k[1].tail(1)])
        # monthlyPrices = monthlyPrices.append(k[1].tail(1))
    return monthlyPrices


def getMonthlyReturns(data):
    return data.pct_change()


def getSharpe(data):
    return round(np.sqrt(252) * data.mean() / data.std(), 2)


def getSortino(data):
    return np.sqrt(252) * data.mean() / data[data < 0].std()


def getMaxDrawdown(data):
    cummRet = (data + 1).cumprod()
    peak = cummRet.expanding(min_periods=1).max()
    drawdown = (cummRet / peak) - 1
    return drawdown.min()


def getCalmar(data):
    return data.mean() * 252 / abs(getMaxDrawdown(data))


def getAbsMomentumVolAdjusted(absReturn, volatility):
    return absReturn / volatility


def getNMonthRoC(data, N):
    ret = round((data.iloc[-1] / data.iloc[-1 - N] - 1) * 100, 2)
    return ret


def getFIP(data):
    retPos = np.sum(data.pct_change()[1:] > 0)
    retNeg = np.sum(data.pct_change()[1:] < 0)
    return retPos - retNeg


def getSharpeRoC(roc, volatility):
    return round(roc / volatility, 2)


def getBeta(dfNifty, data12M):
    dailyReturns = getDailyReturns(pd.concat([dfNifty, data12M], axis=1))[1:]

    var = dailyReturns.loc[:, "Nifty"].var()

    cov = dailyReturns.cov()

    cols = cov.columns[1:]

    beta = []

    for k in cols:
        beta.append(round(cov.loc[k, "Nifty"] / var, 2))

    return beta
