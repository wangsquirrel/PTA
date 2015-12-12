#!/usr/bin/env python
#coding=utf-8
from movie import BYRBT

from BaseHTTPServer import HTTPServer,BaseHTTPRequestHandler
class RequestHandler(BaseHTTPRequestHandler):
    def _writeheaders(self):
        print self.path
        print self.headers
        self.send_response(200);
        self.send_header('Content-type','text/html');
        self.end_headers()
    def do_Head(self):
        self._writeheaders()
    def do_GET(self):
        if self.path == "/torrents.json":
            a = BYRBT()
            a.fetch()
            a.get_torrents()
            for t in a.torrents:
                   t.echo_info()
     
            self._writeheaders()
            self.wfile.write(a.dump_json())
        else:
            self.send_response(404)
            self.wfile.write("<html><body><h1>404 NOT FOUND</h1></body></html>")
    def do_POST(self):
        self._writeheaders()
        length = self.headers.getheader('content-length');
        nbytes = int(length)
        data = self.rfile.read(nbytes)
        self.wfile.write("""<!DOCTYPE HTML>
            <html lang="en-US">
            <head>
            <meta charset="UTF-8">
            <title></title>
            </head>
            <body>
            <p>this is put!</p>
            </body>
            </html>"""+str(self.headers)+str(self.command)+str(self.headers.dict)+data)
addr = ('',8765)
server = HTTPServer(addr,RequestHandler)
server.serve_forever()
