#! /usr/bin/python
#coding=utf-8
import requests
import re
import json
import logging
import codecs
from lxml import etree
from BeautifulSoup import BeautifulSoup
from configobj import ConfigObj  
CONFIG = ConfigObj("../pta.conf")  
print CONFIG["sleep_time"]
logging.basicConfig(level=logging.DEBUG)
class Torrent:
    def __init__(self):
        self.id = ''
        self.name = ''
        self.is_hot = False
        self.download_url = ''
        self.add_time = ''
        self.size = ''
        self.u_num = ''
        self.d_num = ''
        self.c_num = ''
    def echo_info(self):
        print self.id, self.name, self.size, self.u_num, self.d_num, self.c_num
    def to_json(self):
        r = {"id":self.id, "name":self.name, "size":self.size, "u_num":self.u_num, 
            "d_num":self.d_num, "c_num":self.c_num}
        return r
class BYRBT:
    def __init__(self):
        self.remark = "BYRBT"
        self.user = "waschzy"
        self.headers= {'User-Agent': 'Mozilla/5.0 (Windows NT 6.2; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/43.0.2357.65 Safari/537.36'}
        self.base = 'http://bt.byr.cn/'
        self.torrent_url = self.base + 'torrents.php'            
        self.torrents = []

        global CONFIG
        self.torrent_dir = CONFIG["torrent_dir"]
        self.cookies = {'c_secure_uid'          : 'ODczMzI%3D',
                        'c_secure_pass'         : '7baad74980c4d1cfc592370f9e65629f',
                        'c_secure_ssl'          : 'bm9wZQ%3D%3D',
                        'c_secure_tracker_ssl'  : 'bm9wZQ%3D%3D',
                        'c_secure_login'        : 'bm9wZQ%3D%3D',
                        'byrbta'                : '1',
                        'byrbta1'               : '1',
                        'byrbta2'               : '0',
                        'byrbta119'             : '0'
                        }
 
    def fetch(self):
        r = requests.get(self.torrent_url, headers = self.headers, cookies = self.cookies)
        self.html = r.content
        f = open("main.html", "w")
        f.write(r.content)
        f.close()
        if r.status_code == 200:
            logging.debug("fetch OK!")
        else:
            logging.warning("got a fetching probem")
    def get_torrents(self):
        soup = BeautifulSoup(self.html)
        body = soup.body
        torrents_table = soup.find('table', attrs={'class' : 'torrents'})

        lines = torrents_table.findAll('tr',recursive = False)
        for line in lines[1:]:
            name_item = line.find('table', attrs= {'class' : 'torrentname'})
            content = name_item.findAll('a')
            tr = Torrent()
            for c in content:
                if 'details' in c['href']:
                    tr.name = c['title']
                elif 'download' in c['href']:
                    tr.download_url = c['href']
                    p = re.compile(r'id=(\d+)')
                    tr.id = p.findall(c['href'])[0]
                else:
                    continue
            hot = name_item.findAll('font', attrs={'class' : 'hot'})
            if  hot:
                tr.is_hot = True
            rows = line.findAll('td',recursive=False)
            
            tr.add_time = rows[3].span['title']
            tr.size = rows[4].text
            tr.u_num = rows[5].text
            tr.d_num = rows[6].text
            tr.c_num = rows[7].text
            self.torrents.append(tr)
    '''
    #利用xpath通用提取 to be done....
    def get_torrents(self):
        tree=etree.HTML(self.html)
        lines = tree.xpath('//table[@class="torrents"]/form/tr')
        for line in lines:
            title = line.xpath("td[2]/table/tr/td[1]/a/b")
            print title[1].text
    '''       
    def dump_json(self):
        result = {}
        result["remark"] = self.remark 
        result["user"] = self.user
        ts = []
        for t in self.torrents:
            ts.append(t.to_json())
        #print str(all_t)
        result["torrents"] = ts
        return json.dumps(result)
        

    def download_torrent(self):
	'''
	only download hot torrents for now
	'''
        for t in self.torrents:
            if t.is_hot == False:
                continue
            f = open('../'+self.torrent_dir+'./%s.torrent' % t.id, 'w')
            r = requests.get(self.base + t.download_url, cookies = self.cookies, headers = self.headers)
            f.write(r.content)
            f.close()
if __name__ == "__main__":
    a = BYRBT()
    a.fetch()
    a.get_torrents()
    for t in a.torrents:
           t.echo_info()
    print a.dump_json()
    a.download_torrent()        
    '''
    r = requests.get("http://mdb.minms.com/douban/10463953/JSON")
    a = r.content
    c = json.loads(a)
    for k,v in c.items():
        print k,v 
    b = eval("u'%s'" % a)
    print b


    eval("print a")
    '''

