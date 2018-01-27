import usersDbHandler
import json

def createUserHandler(firstName, lastName, email, clearTextPassword):

    #connects to the database
    users = usersDbHandler.usersDbHandler()

    #adds entry to the database
    users.createUser(firstName, lastName, email, clearTextPassword)

def loginParsePrep(parsed_body):
    loginEmail = parsed_body['loginEmail'][0]
    loginClearTextPassword = parsed_body['loginClearTextPassword'][0]

    return loginEmail, loginClearTextPassword
    
def parsePrep(parsed_body):
    firstName = parsed_body['firstName'][0]
    lastName = parsed_body['lastName'][0]
    email = parsed_body['email'][0]
    clearTextPassword = parsed_body['clearTextPassword'][0]

    return firstName, lastName, email, clearTextPassword

def getAllEmailsHandler(posting=False):

    #connect to the database
    users = usersDbHandler.usersDbHandler()

    if posting:
        #reads emails from database and puts it in a list
        emails = users.getAllEmails()

        #creates a json object
        json_string = json.dumps(emails)
        return json_string
    else:
        #creates a json object
        emails = users.getAllEmails()
        json_string = json.dumps(emails)
        return json_string

def getUserByIdHandler(primaryId):

    #connect to the database
    users = usersDbHandler.usersDbHandler()

    user = users.getUserById(primaryId)

    return user

def getUserHandler(loginEmail):
    
    #connect to the database
    users = usersDbHandler.usersDbHandler()

    user = users.getUser(loginEmail)

    #creates a json object
    json_string = json.dumps(user)
    return json_string, user
    
def verifyUserHandler(loginEmail, loginClearTextPassword):

    #connect to the database
    users = usersDbHandler.usersDbHandler()

    return users.verifyUser(loginEmail, loginClearTextPassword)
