from http.server import BaseHTTPRequestHandler, HTTPServer
from urllib.parse import parse_qs
from http import cookies
import httpFunctions
import usersFunctions
import sessionStore

allSessions = sessionStore.sessionStore()
alreadySentGetCookie = False
alreadySentPostCookie = False

class MyHandler(BaseHTTPRequestHandler):

    global allSessions

    #works on both the collection and the member
    def do_GET(self):

        self.loadSession()
        global alreadySentGetCookie

        #gets all emails
        if self.path == "/register":
            #preps the json return object
            json_string = usersFunctions.getAllEmailsHandler()

            #returns response as well as all emails
            self.send_response(200)
            self.send_header("Content-Type", "application/json")
            self.send_header("Access-Control-Allow-Origin", self.headers["Origin"])
            self.send_header("Access-Control-Allow-Credentials", "true")
            if alreadySentGetCookie == False:
                self.sendCookie()
                alreadySentGetCookie = True
            self.end_headers()
            self.wfile.write(bytes(json_string, "utf-8"))

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
            self.send_header("Access-Control-Allow-Origin", self.headers["Origin"])
            self.send_header("Access-Control-Allow-Credentials", "true")
            self.end_headers()
            self.wfile.write(bytes(json_string, "utf-8"))

        elif self.path != "/entries" and member == '' and self.path != "/register" and self.path != "/login":
            self.send_response(404)
            self.send_header("Content-Type", "text/html")
            self.send_header("Access-Control-Allow-Origin", self.headers["Origin"])
            self.send_header("Access-Control-Allow-Credentials", "true")
            self.end_headers()
            self.wfile.write(bytes("Incorrect Path.", "utf-8"))

        #returns a 404 response if member not part of collection
        elif member not in ids and self.path != "/register" and self.path != "/login":
            self.send_response(404)
            self.send_header("Content-Type", "text/html")
            self.send_header("Access-Control-Allow-Origin", self.headers["Origin"])
            self.send_header("Access-Control-Allow-Credentials", "true")
            self.end_headers()
            self.wfile.write(bytes("Could not find that member.", "utf-8"))
            return

        #on the member. Lists one collection member
        elif self.path == "/entries" + '/' + str(member):
            json_string = httpFunctions.getOneHandler(member)

            #returns response as well as the member
            self.send_response(200)
            self.send_header("Content-Type", "application/json")
            self.send_header("Access-Control-Allow-Origin", self.headers["Origin"])
            self.send_header("Access-Control-Allow-Credentials", "true")
            self.end_headers()
            self.wfile.write(bytes(json_string, "utf-8"))




    #works on the collection
    def do_POST(self):

        self.loadSession()
        global alreadySentPostCookie

        emailIsUnique = True

        #creates a user during registration
        if self.path == "/register":
            #receives the request and parses it into a dictionary
            length = int(self.headers["Content-length"])
            body = self.rfile.read(length).decode("utf-8")
            parsed_body = parse_qs(body)

            #preps the entry to be added to the database
            firstName, lastName, email, clearTextPassword = usersFunctions.parsePrep(parsed_body)

            #verifies if email is unique
            posting = True
            emailList = usersFunctions.getAllEmailsHandler(posting)
            for i in range(len(emailList)):
                if emailList[i][0] == email:
                    #return 422 if email is not unique
                    self.send_response(422)
                    self.send_header("Access-Control-Allow-Origin", self.headers["Origin"])
                    self.send_header("Access-Control-Allow-Credentials", "true")
                    self.end_headers()
                    self.wfile.write(bytes("Your email is not unique", "utf-8"))
                    emailIsUnique = False
                    break

            #adds user to database if email is unique
            if emailIsUnique:
                #adds to the database
                usersFunctions.createUserHandler(firstName, lastName, email, clearTextPassword)

                #return response
                #json_string is for user agent, userInfo is for server
                json_string, userInfo = usersFunctions.getUserHandler(email)
                self.send_response(201)
                self.send_header("Access-Control-Allow-Origin", self.headers["Origin"])
                self.send_header("Access-Control-Allow-Credentials", "true")
                if alreadySentPostCookie == False:
                    self.sendCookie()
                    alreadySentPostCookie = True
                self.end_headers()
                self.wfile.write(bytes(json_string, "utf-8"))

                #uses userInfo[0][0] (primary key id) to create a session store and session ID and cookie
                sessionId = allSessions.createSession(userInfo[0][0])
                self.cookie["sessionId"] = sessionId

        elif self.path == "/login":
            length = int(self.headers["Content-length"])
            body = self.rfile.read(length).decode("utf-8")
            parsed_body = parse_qs(body)

            #preps the login credentials to be verified
            loginEmail, loginClearTextPassword = usersFunctions.loginParsePrep(parsed_body)

            #verifies user
            if usersFunctions.verifyUserHandler(loginEmail, loginClearTextPassword):
                json_string, userInfo = usersFunctions.getUserHandler(loginEmail)
                self.send_response(303)
                self.send_header("Content-Type", "application/json")
                self.send_header("Access-Control-Allow-Origin", self.headers["Origin"])
                self.send_header("Access-Control-Allow-Credentials", "true")
                self.end_headers()
                self.wfile.write(bytes(json_string, "utf-8"))
            else:
                self.send_response(401)
                self.send_header("Content-Type", "application/json")
                self.send_header("Access-Control-Allow-Origin", self.headers["Origin"])
                self.send_header("Access-Control-Allow-Credentials", "true")
                self.end_headers()
                self.wfile.write(bytes("Wrong username and/or password", "utf-8"))

        elif self.path == "/entries":
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
            self.send_header("Access-Control-Allow-Origin", self.headers["Origin"])
            self.send_header("Access-Control-Allow-Credentials", "true")
            self.end_headers()
            self.wfile.write(bytes("Created", "utf-8"))

        else:
            self.send_response(404)
            self.send_header("Content-Type", "text/html")
            self.send_header("Access-Control-Allow-Origin", self.headers["Origin"])
            self.send_header("Access-Control-Allow-Credentials", "true")
            self.end_headers()
            self.wfile.write(bytes("Could not POST due to path.", "utf-8"))



    #works on the member
    def do_PUT(self):

        self.loadSession()

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
            self.send_header("Access-Control-Allow-Origin", self.headers["Origin"])
            self.send_header("Access-Control-Allow-Credentials", "true")
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
            self.send_header("Access-Control-Allow-Origin", self.headers["Origin"])
            self.send_header("Access-Control-Allow-Credentials", "true")
            self.end_headers()
            self.wfile.write(bytes("Modified", "utf-8"))

        elif self.path != "/entries":
            self.send_response(404)
            self.send_header("Content-Type", "text/html")
            self.send_header("Access-Control-Allow-Origin", self.headers["Origin"])
            self.send_header("Access-Control-Allow-Credentials", "true")
            self.end_headers()
            self.wfile.write(bytes("Could not find that member. Check your path.", "utf-8"))





    def do_DELETE(self):

        self.loadSession()

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
            self.send_header("Access-Control-Allow-Origin", self.headers["Origin"])
            self.send_header("Access-Control-Allow-Credentials", "true")
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
            self.send_header("Access-Control-Allow-Origin", self.headers["Origin"])
            self.send_header("Access-Control-Allow-Credentials", "true")
            self.end_headers()
            self.wfile.write(bytes("Deleted", "utf-8"))





    def do_OPTIONS(self):

        self.loadSession()

        if self.path:
            self.send_response(204)
            self.send_header("Access-Control-Allow-Origin", self.headers["Origin"])
            self.send_header("Access-Control-Allow-Credentials", "true")
            self.send_header("Access-Control-Allow-Methods", "POST")
            self.send_header("Access-Control-Allow-Methods", "GET")
            self.send_header("Access-Control-Allow-Methods", "PUT")
            self.send_header("Access-Control-Allow-Methods", "DELETE")
            self.end_headers()





    def loadSession(self):
        #load the cookie object
        self.loadCookie()

        #find if sessionId exists in cookie?
        if "sessionId" in self.cookie:
            sessionId = self.cookie["sessionId"].value
            userId = allSessions.getSession(sessionId)
            #find if sessionId exists in session store?
            if userId:
                #load the session data
                userInfo = usersFunctions.getUserByIdHandler(userId)
            else:
                #create new sessionId
                sessionId = allSessions.createAnonymousSession()
                #assign sessionId in cookie
                self.cookie["sessionId"] = sessionId
        else:
                #create new sessionId
                sessionId = allSessions.createAnonymousSession()
                #assign sessionId in cookie
                self.cookie["sessionId"] = sessionId





    def loadCookie(self):
        if "Cookie" in self.headers:
            self.cookie = cookies.SimpleCookie(self.headers["Cookie"])
            print("cookie: ", self.cookie)
        else:
            self.cookie = cookies.SimpleCookie()
            print("No cookie yet")






    def sendCookie(self):
        for morsel in self.cookie.values():
            self.send_header("Set-Cookie", morsel.OutputString())





def main():
    listen = ("127.0.0.1", 8080)
    server = HTTPServer(listen, MyHandler)

    print("Listening...")
    server.serve_forever()

main()
