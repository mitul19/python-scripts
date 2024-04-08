#!/usr/local/bin/python3
import string
import json
import urllib
import urllib.request
import httplib2
from bs4 import BeautifulSoup


sec_list = "https://nseindia.com/live_market/dynaContent/live_watch/get_quote/ajaxFOGetQuoteDataTest.jsp?i=FUTSTK&u=SBIN"

http = httplib2.Http()

headers, body = http.request(sec_list)

#print(body.string)

my_json = json.loads(body.decode("utf-8"))

#print(my_json)

#soup = BeautifulSoup(body,"html.parser")
#print(soup.contents)
#print(body)
#my_json = json.loads((soup.contents))

print(my_json['expiries'])
#print(my_json['underlyings'])

for i in my_json['underlyings']:
    print('https://nseindia.com/live_market/dynaContent/live_watch/get_quote/GetQuoteFO.jsp?underlying='+i+'&instrument=FUTSTK&type=-&strike=-&expiry=28SEP2017')

# soup = BeautifulSoup(body,"html.parser")

