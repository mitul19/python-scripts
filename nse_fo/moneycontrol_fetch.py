from bs4 import BeautifulSoup  
import requests 

def mc_stock_details(link):
    response = requests.get(link)
    # r2 = "noner2"
    r3 = "noner3"
    if response.status_code == 200:
        parsed_html = BeautifulSoup(response.content, features="lxml")
        try:
            r3 = parsed_html.find('div', attrs={'class':'esbx'}).string 
        except AttributeError as e:
            r3 = e
            # try:
            #     r2 = parsed_html.find('div', attrs={'class':'esbx esbx2'}).string 
            # except AttributeError as e:
            #     r2 = e

    return  r3

def mc_stock_list(url):
    table = requests.get(url)
    result = []
    if table.status_code == 200:
        parsed_table = BeautifulSoup(table.content, features="lxml")
        table_list = parsed_table.find('table', attrs={'class':'pcq_tbl MT10'}) 
        rows = table_list.find_all('tr')
        for th in rows:
            for ref in th.find_all('a'):
                result.append(ref['href'])

    return result

if __name__ == '__main__':
    '''
    Basic main function to start working on moneycontrol data.
    '''
    stocks_url = 'https://www.moneycontrol.com/india/stockpricequote/'
    url_list = mc_stock_list(stocks_url)
    # print(url_list)
    # count = 0
    # for url in url_list:
    #     print("For Stock {} - mc_essential_check is {}".format(url,mc_stock_details(url)))
    #     if (count > 5): break
    #     count = count + 5
    for url in url_list:
        print("For Stock {} - mc_essential_check is {}".format(url,mc_stock_details(url)))
    