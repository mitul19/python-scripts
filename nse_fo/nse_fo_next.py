#!/usr/local/bin/python3
import json
import httplib2
from bs4 import BeautifulSoup
import sys

sec_list = "https://nseindia.com/live_market/dynaContent/live_watch/get_quote/ajaxFOGetQuoteDataTest.jsp?i=FUTSTK&u=SBIN"

try:
    try:
        http = httplib2.Http()
        headers, sec_body = http.request(sec_list)
    except httplib2.ServerNotFoundError:
        print('Unable to find the server at' + sec_list)
        sys.exit(1)

    try:
        sec_json = json.loads(sec_body.decode("utf-8"))
    except json.JSONDecodeError or KeyError or json.decoder.JSONDecodeError or ValueError:
        print('unable to Decode Json Object in' + sec_list)
        sys.exit(1)

    for i in sec_json['underlyings']:
        headers, body = http.request('https://nseindia.com/live_market/dynaContent/live_watch/get_quote/GetQuoteFO.jsp?underlying='
                                     +i+'&instrument=FUTSTK&type=-&strike=-&expiry=30NOV2017')
        soup = BeautifulSoup(body, "html.parser")
        try:
            my_json = json.loads(soup.find(id="responseDiv").string)
        except KeyError or json.JSONDecodeError or json.decoder.JSONDecodeError:
            pass
        try:
            try:
                SB = int((my_json['data'][0]['totalSellQuantity']).replace(",", ""))/int((my_json['data'][0]['totalBuyQuantity']).replace(",", ""))
            except:
                SB = '-'
            try:
                pchangeinOpenInterest = my_json['data'][0]['pchangeinOpenInterest']
            except:
                pchangeinOpenInterest = '-'
            try:
                dailyVolatility = my_json['data'][0]['dailyVolatility']
            except:
                dailyVolatility = '-'
            try:
                lastUpdateTime = my_json['lastUpdateTime']
            except:
                lastUpdateTime = '-'
            try:
                pChange = my_json['data'][0]['pChange']
            except:
                pChange = '-'
            try:
                numberOfContractsTraded = my_json['data'][0]['numberOfContractsTraded']
            except:
                numberOfContractsTraded = '-'
            try:
                lastPrice = my_json['data'][0]['lastPrice']
            except:
                lastPrice = '-'
            print(lastUpdateTime, i, dailyVolatility, numberOfContractsTraded, lastPrice, pChange, pchangeinOpenInterest, SB, sep='\t')
        except KeyError or ValueError:
            pass

except KeyboardInterrupt:
    sys.exit(1)
