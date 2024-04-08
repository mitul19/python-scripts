import yfinance as yf
import plotly.express as px
import os
import plotly.graph_objects as go 



# sbin = yf.Ticker("SBIN.NS")  
# use yf.download mode to create proper dataframe with reseting index.
# yfdata = sbin.history(period="max")
#data = pd.read_table(yfdata)
# print(yfdata)
#print(data)

# Below function counts momentum return for lookback perior specified . 
# it requires data to be date sorted from Latest to oldest : example from 2020-12-31 to 2020-01-10  where 2020-12-31 would be 0 index
def momTable(data, column, mom):
    count = 0 
    while(count < len(data.index)): 
        if (count + mom < len(data.index)):
            data.loc[count, column] = ((data['Adj Close'][count]/data['Adj Close'][count+mom])-1)*100
        else:
            data.loc[count, column] = 0.0 
        count = count + 1
    return data

if __name__ == '__main__':
    """
    Basic Main Function to take YF symbol and process it 
    """
    # Gather information on debug value and symbol
    yf_symbol = input("Please provide yahoo finance ticker symbol: ")
    Debug = True

    data = yf.download(yf_symbol,period="max")
    if Debug: print(data)
    # Downloaded data needs reset index to make it proper panda frame where Date will become column and we have proer indexes
    data.reset_index(inplace=True)

    data['MDD'] = ((data['Adj Close']/data['Adj Close'].cummax())-1)*100
    if Debug: print(data)

    # Various Drawdown printed 
    if Debug: print("Mean Drawdown Value:",data.quantile(0.5,0)['MDD'] * 100)
    if Debug: print("Ten Quartile Drawdown Value:",data.quantile(0.10,0)['MDD'] * 100)
    if Debug: print("One Quartile Drawdown Value:",data.quantile(0.01,0)['MDD'] * 100)
    if Debug: print("Max Drawdown Value:",data.quantile(0,0)['MDD'] * 100) 
    if Debug: print("Big Drawdown Dates [0.1 Quartile Drawdown]: ")
    if Debug: print(data.loc[data['MDD'] < data.quantile(0.001,0)['MDD']])
    
    data['MonthName'] = data['Date'].dt.month_name() 
    data['DayName'] = data['Date'].dt.day_name()
    data['Week'] = data['Date'].dt.week  
    data['Weekday'] = data['Date'].dt.weekday 
    data['Year'] = data['Date'].dt.year
    data['Month'] = data['Date'].dt.month 
    data['Day'] = data['Date'].dt.day  
    data['Range_pct'] = ((data['High']/data['Low']) - 1) * 100 
    data['Close_pct'] = ((data['Open']/data['Close']) - 1) * 100

    # Data is appended with various columns 
    if Debug: print(data)

    # Our Momentum Return calculation work from latest date to oldest date 
    # so reversing our dataframe and setting indexes 0 to end and dropping older indexes
    data = data[::-1]
    data.reset_index(drop=True, inplace=True) 
    if Debug: print(data)

    #Creating 3 Momentum return colums 
    column = 'mom1day'
    data = momTable(data, column, 1)
    column = 'mom5day'
    data = momTable(data, column, 5)
    column = 'mom20day'
    data = momTable(data, column, 20)

    if Debug: print(data)
    data.to_csv("csvs/"+yf_symbol+".csv")


    #Plots for relevant datas in folder
    if not os.path.exists("yf_charts"):
        os.mkdir("yf_charts")
    if not os.path.exists("yf_charts/"+ yf_symbol +"_mdd.html"):
        outGraph = px.line(data, x = 'Date', y = 'MDD', title= "Maximum Drawdown")
        outGraph.write_html("yf_charts/"+ yf_symbol +"_mdd.html",include_plotlyjs="plotlyv1.54.1.js")
    if not os.path.exists("yf_charts/"+ yf_symbol +"_Adj Close.html"):
        outGraph = px.line(data, x = 'Date', y = 'Adj Close', title="Adj Close price")
        outGraph.write_html("yf_charts/"+ yf_symbol +"_Adj Close.html",include_plotlyjs="plotlyv1.54.1.js")
    if not os.path.exists("yf_charts/"+ yf_symbol +"_mom5day.html"):
        outGraph = px.violin(data, y = "mom5day", x = "DayName", box=True, points="all", hover_data=data.columns, title="5day momentum voilin")
        outGraph.write_html("yf_charts/"+ yf_symbol +"_mom5day.html",include_plotlyjs="plotlyv1.54.1.js")
    if not os.path.exists("yf_charts/"+ yf_symbol +"_histo_close_pct.html"):
        outGraph = px.histogram(data, x = "Close_pct", color = "DayName", marginal="rug", hover_data=data.columns, title="daywise Close_pct") 
        outGraph.write_html("yf_charts/"+ yf_symbol +"_histo_close_pct.html",include_plotlyjs="plotlyv1.54.1.js") 
    if not os.path.exists("yf_charts/"+ yf_symbol +"_candlestick.html"):
        outGraph = go.Figure(data=[go.Candlestick(x=data['Date'], open=data['Open'], high=data['High'], low=data['Low'], close=data['Close'])])
        outGraph.write_html("yf_charts/"+ yf_symbol +"_candlestick.html", include_plotlyjs="plotlyv1.54.1.js")    
    if not os.path.exists("yf_charts/"+ yf_symbol +"_scatter2d.html"):
        outGraph = px.scatter_matrix(data, dimensions=["mom1day", "mom5day", "mom20day"]) 
        outGraph.write_html("yf_charts/"+ yf_symbol +"_scatter2d.html", include_plotlyjs="plotlyv1.54.1.js") 
    if not os.path.exists("yf_charts/"+ yf_symbol +"_scatter3d.html"):
        outGraph = px.scatter_3d(data, z="mom1day", y="mom5day", x="mom20day", title="momentum scatter 3d plot")
        outGraph.write_html("yf_charts/"+ yf_symbol +"_scatter3d.html", include_plotlyjs="plotlyv1.54.1.js") 