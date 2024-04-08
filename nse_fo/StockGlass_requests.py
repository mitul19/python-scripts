import pandas as pd
import requests
from requests.exceptions import HTTPError
import plotly.express as px
import os
import plotly.graph_objects as go 


# Below function counts momentum return for lookback perior specified . 
# it requires data to be date sorted from Latest to oldest : example from 2020-12-31 to 2020-01-10  where 2020-12-31 would be 0 index
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
    This is main function which will do basic sanity checks and process data
    '''
    symbol = input("Please provide one "
    "Yahoo finance ticker symbol like: AKAM, MSFT, GOOG etc :")

    url = 'https://www.alphavantage.co/query?function=TIME_SERIES_DAILY_ADJUSTED&symbol=' + symbol + '&datatype=csv&apikey=5P2KW31D61IQN6KH&outputsize=full'
    # print("Requested URL is  {}".format(url))
    try:
        with requests.Session() as s:
            download = s.get(url)
            decode_content = download.content.decode('utf-8')
            outHeaders = s.headers
        print(download.status_code)
        # print(decode_content)
        print(outHeaders)
        with open('temp.csv','w') as fp:
            fp.write(decode_content)
    except HTTPError as err:
        print("Got HTTPError {}".format(err))
        exit(1)
    except Exception as e:
        print("Other Exceptions occurred when downloading content {}".format(e))
        exit(1)
    # download = True
    # Now we have downloaded content so utilize that and Manipulate all Data 
    if download.status_code == 200:
        data = pd.read_csv('temp.csv')
        print(data)
        date_list = pd.to_datetime(data['timestamp']) 
        data['MonthName'] = date_list.dt.month_name() 
        data['DayName'] = date_list.dt.day_name()
        data['Week'] = date_list.dt.week  
        data['Weekday'] = date_list.dt.weekday 
        data['Year'] = date_list.dt.year
        data['Month'] = date_list.dt.month 
        data['Day'] = date_list.dt.day  
        data['Range_pct'] = ((data['high']/data['low']) - 1) * 100 
        data['Close_pct'] = ((data['open']/data['close']) - 1) * 100
        column = 'mom1day'
        data = momTable(data, column, 1)
        column = 'mom5day'
        data = momTable(data, column, 5)
        column = 'mom20day'
        data = momTable(data, column, 20)

        # We need to do reverse cummax as series is latest date to old date.  Use current close price to highest seen till date.
        data['MDD'] = ((data['adjusted_close']/data['adjusted_close'][::-1].cummax()[::-1])-1) * 100
        print(data)
        data.to_csv("temp_final.csv")

        #Read and start plots if we have data loaded other wise continue on script 
        # data = pd.read_csv('temp_final.csv')


        #Plots for relevant datas
        if not os.path.exists("charts"):
            os.mkdir("charts")
        if not os.path.exists("charts/"+ symbol +"_mdd.html"):
            outGraph = px.line(data, x = 'timestamp', y = 'MDD', title= "Maximum Drawdown")
            outGraph.write_html("charts/"+ symbol +"_mdd.html",include_plotlyjs="plotlyv1.54.1.js")
        if not os.path.exists("charts/"+ symbol +"_adjusted_close.html"):
            outGraph = px.line(data, x = 'timestamp', y = 'adjusted_close', title="adjusted_close price")
            outGraph.write_html("charts/"+ symbol +"_adjusted_close.html",include_plotlyjs="plotlyv1.54.1.js")
        if not os.path.exists("charts/"+ symbol +"_mom5day.html"):
            outGraph = px.violin(data, y = "mom5day", x = "DayName", box=True, points="all", hover_data=data.columns, title="5day momentum voilin")
            outGraph.write_html("charts/"+ symbol +"_mom5day.html",include_plotlyjs="plotlyv1.54.1.js")
        if not os.path.exists("charts/"+ symbol +"_histo_close_pct.html"):
            outGraph = px.histogram(data, x = "Close_pct", color = "DayName", marginal="rug", hover_data=data.columns, title="daywise Close_pct") 
            outGraph.write_html("charts/"+ symbol +"_histo_close_pct.html",include_plotlyjs="plotlyv1.54.1.js") 
        if not os.path.exists("charts/"+ symbol +"_candlestick.html"):
            outGraph = go.Figure(data=[go.Candlestick(x=data['timestamp'], open=data['open'], high=data['high'], low=data['low'], close=data['close'])])
            outGraph.write_html("charts/"+ symbol +"_candlestick.html", include_plotlyjs="plotlyv1.54.1.js")    
        if not os.path.exists("charts/"+ symbol +"_scatter2d.html"):
            outGraph = px.scatter_matrix(data, dimensions=["mom1day", "mom5day", "mom20day"]) 
            outGraph.write_html("charts/"+ symbol +"_scatter2d.html", include_plotlyjs="plotlyv1.54.1.js") 
        if not os.path.exists("charts/"+ symbol +"_scatter3d.html"):
            outGraph = px.scatter_3d(data, z="mom1day", y="mom5day", x="mom20day", title="momentum scatter 3d plot")
            outGraph.write_html("charts/"+ symbol +"_scatter3d.html", include_plotlyjs="plotlyv1.54.1.js") 
    
    else:
        exit(1)
    