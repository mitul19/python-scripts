#!/usr/local/bin/python3
import json
import httplib2
from bs4 import BeautifulSoup
import sys
import requests

# Get all get possible expiry date details for the given script
def get_expiry_from_future_list (symbol):

    # Base url page for the symbole with default expiry date
    Base_url = "https://www.nseindia.com/live_market/dynaContent/live_watch/fomwatchsymbol.jsp?key=" + symbol + "&Fut_Opt=Futures"

    # Load the page and sent to HTML parse
    page = requests.get(Base_url)
    #print(page)
    soup = BeautifulSoup(page.content, 'html.parser')
    #print(soup)

    table_cls_2 = soup.find(id="tab26Content")
    #print(table_cls_2)
    req_row = table_cls_2.find_all('tr')
    #print(req_row)


    expiry_list = []

    for row_number, tr_nos in enumerate(req_row):

        # This ensures that we use only the rows with values
        if row_number <= 0 or row_number == len(req_row):
            continue

        td_columns = tr_nos.find_all('td')
        expiry = BeautifulSoup(str(td_columns[2]), 'html.parser').get_text()
        expiry_list.append(expiry)

    return expiry_list

def get_sec_list():

    #base url to get Json
    sec_list = "https://nseindia.com/live_market/dynaContent/live_watch/get_quote/ajaxFOGetQuoteDataTest.jsp?i=FUTSTK&u=SBIN"
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

    return sec_json


#try both functions:
#print(get_expiry_from_future_list("SBIN"))
#print(get_sec_list())
