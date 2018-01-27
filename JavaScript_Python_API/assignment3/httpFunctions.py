import json
import dbHandler



def deleteHandler(id):

    #connects to the database
    todo = dbHandler.dbHandler()

    #deletes entry from the database
    todo.deleteEntry(id)



def getAllHandler():
    
    #connects to database
    todo = dbHandler.dbHandler()
    
    #reads from database and puts it in a list
    rows = todo.getAll()

    #creates a json object
    json_string = json.dumps(rows)

    return json_string



def getIds():

    #connects to the database
    todo = dbHandler.dbHandler()

    #reads from database and puts IDs in a list
    ids = todo.selectAllIds()

    return ids


def getOneHandler(description):
    
    #connects to database
    todo = dbHandler.dbHandler()
    
    #reads from database and puts it in a list
    record = todo.getOne(description)

    #creates a json object
    json_string = json.dumps(record)

    return json_string



def parsePrep(parsed_body, posting = False, putting = False):
    #receives the parsed query string and sets it to variables if POSTing
    if posting:
        description = parsed_body['description'][0]
        priority = parsed_body['priority'][0]
        dueDate = parsed_body['dueDate'][0]
        inputBy = parsed_body['inputBy'][0]
        reminder = parsed_body['reminder'][0]
        repeated = parsed_body['repeated'][0]
        
    #receives the parsed query string and sets it to variables
    if posting == False and putting == False:
        print(parsed_body)
        id = parsed_body['id'][0]
        description = parsed_body['description'][0]
        priority = parsed_body['priority'][0]
        dueDate = parsed_body['dueDate'][0]
        inputBy = parsed_body['inputBy'][0]
        reminder = parsed_body['reminder'][0]
        repeated = parsed_body['repeated'][0]

    #sets newDescription if it exists and returns accordingly
    #this is meant for the PUT method
    if 'newDescription' in parsed_body:
        description = parsed_body['description'][0]
        newDescription = parsed_body['newDescription'][0]
        return description, newDescription
    elif posting:
        return description, priority, dueDate, inputBy, reminder, repeated
    else:
        return id, description, priority, dueDate, inputBy, reminder, repeated



def putHandler(id, newDescription):

    #connects to the database
    todo = dbHandler.dbHandler()

    #modifies entry to database
    todo.updateEntry(id, newDescription)



def postHandler(description, priority, dueDate, inputBy, reminder, repeated):

    #connects to database
    todo = dbHandler.dbHandler()

    #adds entry to the database
    todo.createEntry(description, priority, dueDate, inputBy, reminder, repeated)
