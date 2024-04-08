import yfinance as yf
data = yf.download("WIPRO.NS",start="2021-01-01",end="2021-02-01")
print(data)