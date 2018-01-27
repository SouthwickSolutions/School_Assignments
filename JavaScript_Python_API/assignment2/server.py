#don't forget to erase the messages.txt file when starting over

from http.server import BaseHTTPRequestHandler, HTTPServer
from urllib.parse import parse_qs
import json
import os.path
    
class MyHandler(BaseHTTPRequestHandler):

    def do_GET(self):
        print("GET path:", self.path, '\n')
        if self.path == "/messages":
            #reads from regular text file. Creates file if there is none
            if os.path.exists("messages.txt"):   
                f = open("messages.txt","r")
            else:
                f = open("messages.txt","w")
                f = open("messages.txt","r")

            #puts read data into a list
            data_list = []
            for line in f:
                data_list.append(line)
            f.close()
            print(data_list)
            
            #creates a json dump
            json_data=json.dumps(data_list)

            #creates and sends the header            
            self.send_response(200)
            self.send_header("Content-Type", "application/json")
            self.send_header("Access-Control-Allow-Origin", "*")
            self.end_headers()

            print("\n" + "JSON data: " + json_data)
            print("+----------+" + '\n')
            self.wfile.write(bytes(json_data, "utf-8"))
        else:

            #creates and sends the header
            self.send_response(404)
            self.send_header("Content-Type", "text/html")
            self.send_header("Access-Control-Allow-Origin", "*")
            self.end_headers()
            self.wfile.write(bytes("Did not work", "utf-8"))
            
    def do_POST(self):
        
        print("POST path:", self.path, '\n')
        if self.path == "/messages":
            
            #grabs the body of the request and parses it
            length = int(self.headers["Content-Length"]) #dictionary
            body = self.rfile.read(length).decode("utf-8")
            print("body:", body)
            
            #writes to messages.txt
            body2 = (body.replace("%20", ' ')).split('=', 1)[-1]
            f = open("messages.txt","a")
            f.write(body2 + '\n')
            f.close()

            #creates and sends headers            
            self.send_response(201)
            self.send_header("Access-Control-Allow-Origin", "*")
            self.send_header("Content-Type", "application/json")
            self.end_headers()
            print("+----------+" + '\n')

            self.wfile.write(bytes(body, "utf-8"))
        else:
            #creates and sends the header
            self.send_response(404)
            self.send_header("Content-Type", "text/html")
            self.send_header("Access-Control-Allow-Origin", "*")
            self.end_headers()
            self.wfile.write(bytes("Did not work", "utf-8"))

def main():
    listen = ("127.0.0.1", 8080)
    server = HTTPServer(listen, MyHandler)
    
    print("Listening..." + '\n' + '\n')
    server.serve_forever()

main()
