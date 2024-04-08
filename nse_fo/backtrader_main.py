from __future__ import (absolute_import, division, print_function,
                        unicode_literals)

import datetime  # For datetime objects
import os.path  # To manage paths
import sys  # To find out the script name (in argv[0])

# Import the backtrader platform
import backtrader as bt
import backtrader.feeds as btfeeds  # to load CSV file
import bt_classes.classes as btc  # to load Strategy Classes 

import matplotlib.pyplot as plt

if __name__ == '__main__':
    # Create a cerebro entity 
    cerebro = bt.Cerebro()
    # Add a strategy for optimizing for moving avg from 10 to 20 for testing 
    # strats = cerebro.optstrategy(
    #     btc.Simple_Moving_Avg,
    #     maperiod=range(10, 21))

    cerebro.addstrategy(btc.RSI_30B_70S)
    # Datas are in a subfolder of the samples. Need to find where the script is
    # because it could have been called from anywhere
    # modpath = os.path.dirname(os.path.abspath(sys.argv[0]))
    # datapath = os.path.join(modpath, '../../datas/orcl-1995-2014.txt')

    # Create a Data Feed from Yahoo Finance 
    # data = bt.feeds.YahooFinanceCSVData(
    #     dataname=datapath,
    #     # Do not pass values before this date
    #     fromdate=datetime.datetime(2019, 1, 1),
    #     # Do not pass values before this date
    #     todate=datetime.datetime(2019, 12, 31),
    #     # Do not pass values after this date
    #     reverse=False)

    data = btfeeds.GenericCSVData(
        dataname='yf_csvs/TCS.csv',
        fromdate=datetime.datetime(2016, 1, 1),
        todate=datetime.datetime(2020, 12, 30),
        nullvalue=0.0,
        dtformat=('%Y-%m-%d'),
        datetime=1,
        high=3,
        low=4,
        open=2,
        close=6,
        volume=7,
        openinterest=-1
    )

    # Add the Data Feed to Cerebro
    cerebro.adddata(data)

    startcash = 1000000
    # Set our desired cash start
    cerebro.broker.setcash(1000000.0)

    # Add a FixedSize sizer according to the stake
    # cerebro.addsizer(bt.sizers.FixedSize, stake=10)

    # Set the commission
    cerebro.broker.setcommission(commission=0.005)

    # Run over everything
    cerebro.run(maxcpus=1)

    #Get final portfolio Value
    portvalue = cerebro.broker.getvalue()
    pnl = portvalue - startcash

    #Print out the final result
    print('Final Portfolio Value: ${}'.format(portvalue))
    print('P/L: ${}'.format(pnl))

    # cerebro.plot()
    cerebro.plot()
