import yfinance as yf
import pandas as pd
import os
import sys
import threading
import concurrent.futures
from concurrent.futures import ThreadPoolExecutor

write_lock = threading.Lock()
def yf_download(symbol,period="max"):
    '''
    This Function takes Single Yahoo Finance Symbol and download data.
    Args: symbol, period (default max) 
    Returns: panda data series with all desired columns
    '''
    # UnComment for debug info 
    name = threading.current_thread().getName()
    print("running csv download for {} via thread {}".format(symbol,name))
    # Download in data variable such that it
    # indetifies differently for threads 
    # data = symbol
    # symbol_local = symbol
    with write_lock:
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
        data.to_csv("csv_par/" + symbol)  
    # # Writing CSV if asked for it
    # print(toCsv)
    # # if toCsv:
    # #     data.to_csv("csv_par/" + symbol + ".csv")
    # data.to_csv("csv_par/" + symbol)
    # return data

def parellel_download():
    '''
    Parellel concurrent.futures.ThreadPoolExecutor() for IO Bound 
    Download for yf_download function
    '''
    tickers = [line.rstrip() for line in open('nse_list.txt')]
    with concurrent.futures.ThreadPoolExecutor(max_workers=5) as pool:
        pool.map(yf_download,tickers)
        # Loop over tickers and submit everything to thread pool 
        # if we dont want to wait
        # for ticker in tickers:
        #     pool.submit(yf_download, ticker)
        # but in our case writing to csv is needed so we will use completed
        # futures = [pool.submit(yf_download, ticker) for ticker in tickers]
        # for f in concurrent.futures.as_completed(futures):
        #     print(futures(f))
        #     print(f.result())
            
            # print("for {} 2nd row is {}".format(symbol,data[2]))
            # data.to_csv("csv_par/" + symbol + ".csv")


if __name__ == '__main__':
    '''
    This is Main Thread for getting input parameter and starting download.
    '''
    yf_symbol = input("Please provide "
    "1. yahoo finance ticker symbol "
    "2. system default or "
    "3. exit (Valid input symbol/2/3) :")
    print(yf_symbol)
    print(type(yf_symbol))
    if yf_symbol == "3":
        sys.exit()
    elif yf_symbol == "2":
        print("running Threaded download for tickers")
        if not os.path.exists("csv_par"):
            os.mkdir("csv_par")
        #From Run Parellel thread pool to fetch everything in parellel
        if os.path.isfile("nse500yfticker.txt"):
            parellel_download()
        else:
            print("Ticker File nse500yfticker.txt not available in Path {} ."
            .format(os.path.abspath('.')))
            sys.exit()
    elif yf_symbol:
        if not os.path.exists("csv_par"):
            os.mkdir("csv_par")
        yf_download(symbol=yf_symbol)
    else:
        sys.exit(1)
