#!/usr/bin/env python
"""
Very simple HTTP server in python.
Usage::
    ./dummy-web-server.py [<port>]
Send a GET request::
    curl http://localhost
Send a HEAD request::
    curl -I http://localhost
Send a POST request::
    curl -d "foo=bar&bin=baz" http://localhost
    
    Auther : Mitul Patel 
    github : https://github.com/mitul19
    Open Source Code.
"""
from http.server import HTTPServer
from http.server import BaseHTTPRequestHandler

# import socketserver
import re
import time


class S(BaseHTTPRequestHandler):
    BaseHTTPRequestHandler.protocol_version = "HTTP/1.1"
    def do_GET(self):
        if "Range" in self.headers:
            r = self.headers["Range"]
            m = re.match("^bytes=([0-9]+)-([0-9]+)$", self.headers["Range"])
            if m:
                start = int(m.group(1))
                end = int(m.group(2))
                filesize = 429489008
                size = end - start + 1
                self.log_message("range=%s s=%s e=%s", r, start, end)
                if start == 0:
                    self.send_response(206)
                    self.send_header("Last-Modified", "Wed, 24 Feb 2016 11:12:15 GMT")
                    self.send_header("ETag", '"56cd900f-19997b70"')
                    self.send_header("Accept-Ranges", "bytes")
                    self.send_header(
                        "Content-Range", "bytes %d-%d/%d" % (start, end, filesize)
                    )
                    self.send_header("Content-Length", size)
                    self.end_headers()
                    self.wfile.write(b"." * size)
                else:
                    self.finish()
                    self.connection.close()

        elif self.path == "/connect-timeout":
            time.sleep(11)
            self.close_connection()
            # self.finish()
            # self.connection.close()

        else:
            self.send_response(400)
            self.end_headers()

    def do_HEAD(self):
        self.send_response(400)
        self.end_headers()


def run(server_class=HTTPServer, handler_class=S, port=8080):
    server_address = ("", port)
    httpd = server_class(server_address, handler_class)
    httpd.timeout = 10
    print("Starting httpd...")
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        pass
    httpd.server_close()


if __name__ == "__main__":
    run()
