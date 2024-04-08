import requests
import os
import sys
from requests.exceptions import HTTPError


if __name__ == '__main__':
    '''
    This is main function which will do basic sanity checks and process data from yahoo API
    '''
    symbols = ["MRF.NS","TCS.NS"] #List of symbols to iterate 
    start = 1025481600 #Start utc timestamp
    end = 1626566400  #End UTC timestamp

    if not os.path.exists("yf_api"):
        os.mkdir("yf_api")

    for symbol in symbols:
        print(symbol)
        api_url = f'http://query1.finance.yahoo.com/v7/finance/download/{symbol}?period1={start}&period2={end}&interval=1d&events=history&includeAdjustedClose=true' 
        print(api_url)

        data = requests.get(api_url)
        print(data.reason)
        print(data.status_code)

        #Lets download csv files and save it 
        # try:
        #     with requests.Session() as s:
        #         download = s.get(api_url, stream=True)
        #         decode_content = download.content.decode('utf-8')
        #         outHeaders = s.headers
        #     print(download.status_code)
        #     # print(decode_content)
        #     print(outHeaders)
        #     with open("yf_api"+f'{symbol}.csv','w') as fp:
        #         fp.write(decode_content)
        # except HTTPError as err:
        #     print("Got HTTPError {}".format(err))
        #     exit(1)
        # except Exception as e:
        #     print("Other Exceptions occurred when downloading content {}".format(e))
        #     exit(1)