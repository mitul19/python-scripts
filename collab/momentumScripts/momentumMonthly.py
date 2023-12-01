"""
Created on Sat Dec 31 2022

@author: Chintan Shah --> https://github.com/thecpshah
@edited: Mitul Patel --> https://github.com/mitul19
"""

import pandas as pd
import numpy as np
import time
from scipy.stats import zscore
from datetime import datetime
import yfinance as yf

import matplotlib.pyplot as plt

from utils import *

pd.set_option("display.max_rows", 500)

universe = ["Nifty50", "Nifty100", "Nifty200", "Nifty250", "Nifty500"]
baseurl = "https://www1.nseindia.com/content/indices/"
lookBack = ["6M", "12M"]

# Pick universe, lookback
U = universe[3]  # pick 1, 3, 4
LB = lookBack[0]

# Double ranking method
if LB == "6M":
    rm = ["sharpe6M", "FIP6M"]
elif LB == "12M":
    rm = ["sharpe12M", "FIP12M"]

# Apply various filters
applyFilter = True

print("Universe: ", U)
print("Lookback: ", LB)
print("Ranking:", rm)
print("Filter:", str(applyFilter))
print("\n")

printOutput = True
saveResults = True

# Dates: shift by 1 month at every rebalance
dates = dict()
dates["startDate"] = "2021-12-31"
dates["date6M"] = "2022-06-30"
dates["date1M"] = "2022-11-30"
dates["endDate"] = "2022-12-30"

print("Start Date: ", dates["startDate"])
print("6M Date: ", dates["date6M"])
print("1M Date:", dates["date1M"])
print("End Date: ", dates["endDate"])
print("\n")

# -------
# -------
# -------

# Read index file
if U == "Nifty50":
    df = pd.read_csv(baseurl + "ind_nifty50list.csv")
elif U == "Nifty100":
    df = pd.read_csv(baseurl + "ind_nifty100list.csv")
elif U == "Nifty200":
    df = pd.read_csv(baseurl + "ind_nifty200list.csv")
elif U == "Nifty250":
    df = pd.read_csv(baseurl + "ind_niftylargemidcap250list.csv")
elif U == "Nifty500":
    df = pd.read_csv(baseurl + "ind_nifty500list.csv")

# Pick stocks
if U in ["Nifty50", "Nifty100"]:
    topDecile = 30  # Sort by Sharpe
    pickStocks = 20  # Sort by FIP
    perStock = 30000
    buyStocks = 15

    print("Strategy: pick 20 stocks, buy top 15, hold till rank 20")
    print("Allocation per stock: ", perStock)
else:
    topDecile = 50  # Sort by Sharpe
    pickStocks = 30  # Sort by FIP
    perStock = 25000
    buyStocks = 20

    print("Strategy: pick 30 stocks, buy top 20, hold till rank 30")
    print("Allocation per stock: ", perStock)

print("\n")

# Drop unnecessary columns
df.drop(["Series", "ISIN Code", "Industry"], axis=1, inplace=True)

# Create Yahoo symbol
df["Yahoo_Symbol"] = df.Symbol + ".NS"
df = df.set_index("Yahoo_Symbol")
symbol = list(df.index)

# yf data
CHUNK = 50
close = []
for k in range(0, len(symbol), CHUNK):
    print(k, end=",", flush=True)
    _symlist = symbol[k : k + CHUNK]
    _x = yf.download(_symlist, start=dates["startDate"], progress=False)["Close"]
    close = _x if len(close) == 0 else pd.concat([close, _x], axis=1)
    time.sleep(0.5)

# Keep the data within the date range
data12M = close[: dates["endDate"]].copy()

# At least 12 months of trading is required
data12M.dropna(axis=1, inplace=True)

# Data for the past 6 months
data6M = data12M[dates["date6M"] :].copy()

# Get month end prices
dfMonthEnd = getMonthlyPrices(data12M)

# Get Nifty data
dfNifty = yf.download("^NSEI", start=dates["startDate"], progress=False)["Close"]
dfNifty = dfNifty.to_frame().rename(columns={"Close": "Nifty"})

# Stats DataFrame
dfStats = pd.DataFrame()

# Rate of change
dfStats["roc1M"] = getNMonthRoC(dfMonthEnd, 1)
dfStats["roc3M"] = getNMonthRoC(dfMonthEnd, 3)
dfStats["roc6M"] = getNMonthRoC(dfMonthEnd, 6)
dfStats["roc12M"] = getNMonthRoC(dfMonthEnd, 12)

# Volatility
dfStats["volatility6M"] = getVolatility(getDailyReturns(data6M))
dfStats["volatility12M"] = getVolatility(getDailyReturns(data12M))

# Sharpe using RoC, annualised returns and Frog in the pan
dfStats["sharpe6MRoC"] = getSharpeRoC(dfStats["roc6M"], dfStats["volatility6M"])
dfStats["sharpe6M"] = getSharpe(getDailyReturns(data6M))
dfStats["FIP6M"] = getFIP(data6M)

dfStats["sharpe12MRoC"] = getSharpeRoC(dfStats["roc12M"], dfStats["volatility12M"])
dfStats["sharpe12M"] = getSharpe(getDailyReturns(data12M))
dfStats["FIP12M"] = getFIP(data12M)

# Get stock beta
dfStats["Beta"] = getBeta(dfNifty, data12M)

# close and ema
dfStats["Close"] = round(data12M.iloc[-1], 2)
dfStats["ema100d"] = round(data12M.ewm(span=100).mean().iloc[-1], 2)

# Apply filters: e.g. RoC12M > FD rate
cond1 = dfStats["Close"] < 10000
cond2 = dfStats["Close"] > dfStats["ema100d"]
cond3 = dfStats["roc12M"] > 7
cond = cond1 & cond2 & cond3

if applyFilter == True:
    filtered = dfStats[cond]
elif applyFilter == False:
    filtered = dfStats

# Sort using Sharpe
stocks = filtered.sort_values(rm[0], ascending=False)[:topDecile]

# Sort using FIP
output = (
    stocks.sort_values(rm[1], ascending=False)[:pickStocks]
    .reset_index()
    .rename(columns={"index": "symbol"})
)

# Buy quantity
output["BuyQty"] = np.floor(perStock / output.Close)

# Assign rank
output["Rank"] = range(1, output.shape[0] + 1)

print("\n")

if printOutput == True:
    print(output)

if saveResults == True:
    fileName = (
        "./OutputMonthly/"
        + dates["endDate"]
        + "_"
        + U
        + "_"
        + LB
        + "_lookback"
        + ".csv"
    )
    output.to_csv(fileName, index=False, float_format="%.2f")

    from openpyxl import load_workbook

    book = load_workbook("./OutputMonthly/Stocks.xlsx")
    writer = pd.ExcelWriter("./OutputMonthly/Stocks.xlsx", engine="openpyxl")
    writer.book = book

    # writer.sheets = dict((ws.title, ws) for ws in book.worksheets)

    output.to_excel(writer, sheet_name=dates["endDate"] + "-" + U)

    writer.save()
