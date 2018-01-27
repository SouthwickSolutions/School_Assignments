from http.server import BaseHTTPRequestHandler, HTTPServer
from urllib.parse import parse_qs
import httpFunctions

class MyHandler(BaseHTTPRequestHandler):

    #works on both the collection and the member
    def do_GET(self):
        #grabs a member if there is one
        path = self.path
        member = ''
        if path.count('/') >= 2: member = int(path.split('/')[2])

        #grabs IDs to compare to member variable
        idsTuples = httpFunctions.getIds()
        ids = []
        for i in range(len(idsTuples)):
            ids.append(idsTuples[i][0])

        #on the collection. Lists the collection's members
        if self.path == "/entries":
            json_string = httpFunctions.getAllHandler()

            #returns response as well as all members
            self.send_response(200)
            self.send_header("Content-Type", "application/json")
            self.send_header("Access-Control-Allow-Origin", "*")
            self.end_headers()
            self.wfile.write(bytes(json_string, "utf-8"))

        elif self.path != "/entries" and member == '':
            self.send_response(404)
            self.send_header("Content-Type", "text/html")
            self.send_header("Access-Control-Allow-Origin", "*")
            self.end_headers()
            self.wfile.write(bytes("Incorrect Path.", "utf-8"))
            
        #returns a 404 response if member not part of collection
        elif member not in ids:
            self.send_response(404)
            self.send_header("Content-Type", "text/html")
            self.send_header("Access-Control-Allow-Origin", "*")
            self.end_headers()
            self.wfile.write(bytes("Could not find that member.", "utf-8"))
            return

        #on the member. Lists one collection member
        elif self.path == "/entries" + '/' + str(member):
            json_string = httpFunctions.getOneHandler(member)

            #returns response as well as the member
            self.send_response(200)
            self.send_header("Content-Type", "application/json")
            self.send_header("Access-Control-Allow-Origin", "*")
            self.end_headers()
            self.wfile.write(bytes(json_string, "utf-8"))



            
    #works on the collection and adds a member
    def do_POST(self):
        if self.path == "/entries":
            #receives the request and parses it into a dictionary
            length = int(self.headers["Content-length"])
            body = self.rfile.read(length).decode("utf-8")
            parsed_body = parse_qs(body)

            #preps the entry to be added to the database
            posting = True
            description, priority, dueDate, inputBy, reminder, repeated = httpFunctions.parsePrep(parsed_body, posting)

            #adds to the database
            httpFunctions.postHandler(description, priority, dueDate, inputBy, reminder, repeated)

            #return response
            self.send_response(201)
            self.send_header("Access-Control-Allow-Origin", "*")
            self.end_headers()
            self.wfile.write(bytes("Created", "utf-8"))

        else:
            self.send_response(404)
            self.send_header("Content-Type", "text/html")
            self.send_header("Access-Control-Allow-Origin", "*")
            self.end_headers()
            self.wfile.write(bytes("Could not POST due to path.", "utf-8"))



    #works on the member
    def do_PUT(self):
        
        #grabs a member if there is one
        member = ""
        path = self.path
        if path.count('/')== 2: member = int(path.split('/')[2])

        #grabs IDs to compare to member variable
        idsTuples = httpFunctions.getIds()
        ids = []
        for i in range(len(idsTuples)):
            ids.append(idsTuples[i][0])

        #returns a 404 response if member not part of collection
        if member not in ids:
            self.send_response(404)
            self.send_header("Content-Type", "text/html")
            self.send_header("Access-Control-Allow-Origin", "*")
            self.end_headers()
            self.wfile.write(bytes("Could not find that member to edit.", "utf-8"))
            return
        
        elif self.path == "/entries" + '/' + str(member):
            #receive the request and parse it into dictionary
            length = int(self.headers["Content-length"])
            body = self.rfile.read(length).decode("utf-8")
            parsed_body = parse_qs(body)
            
            #preps the entry to be modified in the database
            putting = True
            posting = False
            description, newDescription = httpFunctions.parsePrep(parsed_body, posting, putting)

            #modifies the entry in the database
            httpFunctions.putHandler(member, newDescription)

            #return response
            self.send_response(200)
            self.send_header("Access-Control-Allow-Origin", "*")
            self.end_headers()
            self.wfile.write(bytes("Modified", "utf-8"))

        elif self.path != "/entries":
            self.send_response(404)
            self.send_header("Content-Type", "text/html")
            self.send_header("Access-Control-Allow-Origin", "*")
            self.end_headers()
            self.wfile.write(bytes("Could not find that member. Check your path.", "utf-8"))





    def do_DELETE(self):
        #grabs a member if there is one
        path = self.path
        if path.count('/')== 2: member = int(path.split('/')[2])
        
        #grabs IDs to compare to member variable
        idsTuples = httpFunctions.getIds()
        ids = []
        for i in range(len(idsTuples)):
            ids.append(idsTuples[i][0])

        #returns a 404 response if member not part of collection
        if member not in ids:
            self.send_response(404)
            self.send_header("Content-Type", "text/html")
            self.send_header("Access-Control-Allow-Origin", "*")
            self.end_headers()
            self.wfile.write(bytes("Could not find that member to delete.", "utf-8"))
            return
        
        elif self.path == "/entries" + '/' + str(member):
            #receives the request and parses it into a dictionary
            length = int(self.headers["Content-length"])
            body = self.rfile.read(length).decode("utf-8")
            parsed_body = parse_qs(body)

            #deletes from the database
            httpFunctions.deleteHandler(member)

            #return response
            self.send_response(200)
            self.send_header("Access-Control-Allow-Origin", "*")
            self.end_headers()
            self.wfile.write(bytes("Deleted", "utf-8"))





    def do_OPTIONS(self):
        if self.path:
            self.send_response(204)
            self.send_header("Access-Control-Allow-Origin", "*")
            self.send_header("Access-Control-Allow-Methods", "POST")
            self.send_header("Access-Control-Allow-Methods", "GET")
            self.send_header("Access-Control-Allow-Methods", "PUT")
            self.send_header("Access-Control-Allow-Methods", "DELETE")
            self.end_headers()





            
def main():
    listen = ("127.0.0.1", 8080)
    server = HTTPServer(listen, MyHandler)

    print("Listening...")
    server.serve_forever()

main()
