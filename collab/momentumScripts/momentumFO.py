"""
@auther: Mitul Patel --> https://github.com/mitul19
"""

import pandas as pd
import time
from datetime import datetime, date, timedelta
import yfinance as yf
from openpyxl import load_workbook  # For excel writing work

from utils import *  # Our local functions.

pd.set_option("display.max_rows", 10)

universe = ["F&O"]
lookBack = ["6M", "12M"]

# Pick universe, lookback
U = universe[0]
LB = lookBack[0]

printOutput = True
saveResults = True
saveExcel = True
debug = False

topDecile = 25  # Sort by sharpe6M
pickStocks = 10  # Sort by FIP

# Double ranking method
if LB == "6M":
    rm = ["sharpe6M", "FIP6M"]
elif LB == "12M":
    rm = ["sharpe12M", "FIP12M"]

print("Universe: ", U)
print("Lookback: ", LB)
print("Ranking:", rm)
print("\n")

# Dates
dates = dict()
dates["startDate"] = str(date.today() - timedelta(days=365))
dates["date6M"] = str(date.today() - timedelta(days=180))
dates["endDate"] = str(date.today() - timedelta(days=1))

print("Start Date: ", dates["startDate"])
print("6M Date: ", dates["date6M"])
print("End Date: ", dates["endDate"])
print("\n")

# Symbol Loading
df = pd.read_csv("./indices/fo.csv")
if debug:
    print(df)

# Create Yahoo symbol
df["Yahoo_Symbol"] = df.Symbol + ".NS"
df = df.set_index("Yahoo_Symbol")
symbol = list(df.index)
if debug:
    print(symbol)

# yf data dowload in chunkns
CHUNK = 50
close = []
for k in range(0, len(symbol), CHUNK):
    print(k, end=",", flush=True)
    _symlist = symbol[k : k + CHUNK]
    _x = yf.download(_symlist, start=dates["startDate"], progress=False)["Close"]
    close = _x if len(close) == 0 else pd.concat([close, _x], axis=1)
    time.sleep(0.5)

if debug:
    print(close)

# Keep the data within the date range
data12M = close[: dates["endDate"]].copy()
if debug:
    print(data12M)

# Data for the past 6 months
data6M = data12M[dates["date6M"] :].copy()
if debug:
    print(data6M)

# Get month end prices
dfMonthEnd = getMonthlyPrices(data12M)
if debug:
    print(dfMonthEnd)

# Get Nifty data
dfNifty = yf.download("^NSEI", start=dates["startDate"], progress=False)["Close"]
dfNifty = dfNifty.to_frame().rename(columns={"Close": "Nifty"})
if debug:
    print(dfNifty)

# Stats DataFrame
dfStats = pd.DataFrame()

# Rate of change
dfStats["roc1M"] = getNMonthRoC(dfMonthEnd, 1)
dfStats["roc3M"] = getNMonthRoC(dfMonthEnd, 3)
dfStats["roc6M"] = getNMonthRoC(dfMonthEnd, 6)
dfStats["roc12M"] = getNMonthRoC(dfMonthEnd, 12)
if debug:
    print(dfStats)

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
if debug:
    print(dfStats)

# close and ema
dfStats["Close"] = round(data12M.iloc[-1], 2)
dfStats["ema100d"] = round(data12M.ewm(span=100).mean().iloc[-1], 2)
if debug:
    print(dfStats)

# Apply filters: for buy and sell condition creation
cond1 = dfStats["Close"] > dfStats["ema100d"]
cond2 = dfStats["sharpe6M"] > 0
cond3 = dfStats["FIP12M"] > 0
cond4 = dfStats["sharpe12M"] > 0
cond5 = dfStats["FIP6M"] > 0
buyList = cond1 & cond2 & cond3 & cond4 & cond5

sellcond1 = dfStats["Close"] < dfStats["ema100d"]
sellcond2 = dfStats["sharpe6M"] < 0
sellcond3 = dfStats["FIP12M"] < 0
sellcond4 = dfStats["sharpe12M"] < 0
sellcond5 = dfStats["FIP6M"] < 0
sellList = sellcond1 & sellcond2 & sellcond3 & sellcond4 & sellcond5
# Sort using sharpe6M
print()
print("Total buylist: ")
print(dfStats[buyList]["Close"].count())
print(dfStats[buyList]["Close"].index)
print()
print("Total SellList: ")
print(dfStats[sellList]["Close"].count())
print(dfStats[sellList]["Close"].index)
print()

stocksBuy = dfStats[buyList].sort_values(rm[0], ascending=False)[:topDecile]
stocksSell = dfStats[sellList].sort_values(rm[0], ascending=True)[:topDecile]

# Sort using FIP
outputBuy = (
    stocksBuy.sort_values(rm[1], ascending=False)[:pickStocks]
    .reset_index()
    .rename(columns={"index": "symbol"})
)
outputSell = (
    stocksSell.sort_values(rm[1], ascending=True)[:pickStocks]
    .reset_index()
    .rename(columns={"index": "symbol"})
)

print("\n")

if printOutput == True:
    print("Buy List: ")
    print(outputBuy)
    print("\n")
    print("Sell List: ")
    print(outputSell)

if saveResults == True:
    fileName = (
        "./OutputMonthly/"
        + dates["endDate"]
        + "_"
        + U
        + "_"
        + LB
        + "_lookback"
        + "full.csv"
    )
    fileNameBuy = (
        "./OutputMonthly/"
        + dates["endDate"]
        + "_"
        + U
        + "_"
        + LB
        + "_lookback"
        + "buy.csv"
    )
    fileNameSell = (
        "./OutputMonthly/"
        + dates["endDate"]
        + "_"
        + U
        + "_"
        + LB
        + "_lookback"
        + "sell.csv"
    )

    dfStats.to_csv(fileName, index=True, float_format="%.2f")
    outputBuy.to_csv(fileNameBuy, index=False, float_format="%.2f")
    outputSell.to_csv(fileNameSell, index=False, float_format="%.2f")
    print("CSVs saved")

if saveExcel == True:
    book = load_workbook("./OutputMonthly/FO.xlsx")
    writer = pd.ExcelWriter("./OutputMonthly/FO.xlsx", engine="openpyxl")
    writer.book = book

    # writer.sheets = dict((ws.title, ws) for ws in book.worksheets)

    dfStats.to_excel(writer, sheet_name=dates["endDate"] + "-" + U)
    outputBuy.to_excel(writer, sheet_name=dates["endDate"] + "-Buy-" + U)
    outputSell.to_excel(writer, sheet_name=dates["endDate"] + "-Sell-" + U)
    writer.save()
    print("Excel book saved")
