#!/usr/local/bin/python3
import string
import json
import urllib
import urllib.request
import httplib2
from bs4 import BeautifulSoup

site = "https://nseindia.com/live_market/dynaContent/live_watch/get_quote/GetQuoteFO.jsp?underlying=EQUITAS&instrument=FUTSTK&type=-&strike=-&expiry=28SEP2017"

sec_list = "https://nseindia.com/live_market/dynaContent/live_watch/get_quote/ajaxFOGetQuoteDataTest.jsp?i=FUTSTK&u=SBIN"

http = httplib2.Http()

headers, body = http.request(site)

soup = BeautifulSoup(body,"html.parser")

print(len(soup.contents))

my_json = json.loads(soup.find(id="responseDiv").string)

print(int((my_json['data'][0]['totalSellQuantity']).replace(",",""))/int((my_json['data'][0]['totalBuyQuantity']).replace(",","")))

