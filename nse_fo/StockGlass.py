import pandas as pd
import os
import sys
import yfinance as yf 

def momTable(data, column, mom):
    count = 0 
    while(count < len(data.index)): 
        if (count + mom < len(data.index)):
            data.loc[count, column] = ((data['adjusted_close'][count]/data['adjusted_close'][count+mom])-1)*100
        else:
            data.loc[count, column] = 0.0 
        count = count + 1
    return data


if __name__ == '__main__':
    '''
    This is main function which will do basic sanity checks 
    '''
    url = 'https://www.alphavantage.co/query?function=TIME_SERIES_DAILY_ADJUSTED&symbol=IBM&datatype=csv&apikey=5P2KW31D61IQN6KH'
    try:
        data = yf.download()
    except Exception as e:
        print("Other Exceptions occurred when downloading content {}".format(e))
        exit(1)
    if response == 'OK':
        data = pd.read_csv(content.decode('utf-8'))
        print(data.head)
        # date_list = pd.to_datetime(data['timestamp']) 
        # data['MonthName'] = date_list.dt.month_name() 
        # data['DayName'] = date_list.dt.day_name()
        # data['Week'] = date_list.dt.week  
        # data['Weekday'] = date_list.dt.weekday 
        # data['Year'] = date_list.dt.year
        # data['Month'] = date_list.dt.month 
        # data['Day'] = date_list.dt.day  
        # data['Range_pct'] = ((data['high']/data['low']) - 1) * 100 
        # data['Close_pct'] = ((data['open']/data['close']) - 1) * 100
        # column = 'mon1day'
        # data = momTable(data, column, 1)
        # print(data)
    else:
        print(response.status_code)
        exit(1)
    