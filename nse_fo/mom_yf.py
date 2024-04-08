import yfinance as yf
import numpy as np
import pandas as pd


# Price Change function which calcuate over next day/row value
def priceChange(p):
    nrows = p.shape[0]
    pc = np.zeros(nrows)
    for i in range(1,nrows):
        pc[i] = (p[i]-p[i-1])/p[i-1]
    return pc

start_date ='2019-12-01'
end_date ='2020-12-01'

symbols = ['HDFCBANK', 'HDFC', 'NTPC', 'TCS', 'INFY', 'RELIANCE', 'WIPRO', 'SUNPHARMA', 'MARUTI', 'KOTAKBANK']   

dates=pd.date_range(start_date,end_date)
df1=pd.DataFrame(index=dates)

for symbol in symbols:
    df_temp = yf.download(symbol + ".NS", start=start_date, end=end_date)
    df_temp.reset_index(inplace=True)
    df_temp['priceChange'] = priceChange(df_temp['Close']) 
    df_temp = pd.DataFrame(df_temp, columns=['priceChange'])
    df_temp = df_temp.rename(columns={'priceChange':symbol})
    df1=df1.join(df_temp.set_index('Date'), on='Date')
    print(df1)