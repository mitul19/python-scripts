import yfinance as yf
import pandas as pd
import os
import sys

def yf_download(symbol,period="max"):
    data = yf.download(symbol,period=period)
    data.reset_index(inplace=True)
    date_list = pd.to_datetime(data['Date'])
    data['MonthName'] = date_list.dt.month_name()
    data['DayName'] = date_list.dt.day_name()
    data['Week'] = date_list.dt.week
    data['Weekday'] = date_list.dt.weekday
    data['Year'] = date_list.dt.year
    data['Month'] = date_list.dt.month
    data['Day'] = date_list.dt.day
    # print(type(data))  
    data.to_csv("csvs/" + symbol + ".csv")
    print("Done writing {}".format(symbol))

if __name__ == '__main__':
    '''
    This is Main Thread for getting input parameter and starting download.
    '''
    yf_symbol = input("Please provide "
    "1. yahoo finance ticker symbol "
    "2. system default or "
    "3. exit (Valid input symbol/2/3) :")
    if yf_symbol == "3":
        sys.exit()
    elif yf_symbol == "2":
        if not os.path.exists("csvs"):
            os.mkdir("csvs")
        if os.path.isfile("nse500yfticker.txt"):
            tickers = [line.rstrip() for line in open('nse500yfticker.txt')]
            for item in tickers:
                yf_download(item)
        else:
            print("Ticker File nse500yfticker.txt not available in Path {} ."
            .format(os.path.abspath('.')))
            sys.exit()
    elif yf_symbol:
        if not os.path.exists("csvs"):
            os.mkdir("csvs")
        yf_download(symbol=yf_symbol)
    else:
        sys.exit(1)