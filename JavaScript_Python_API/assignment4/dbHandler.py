#see 10_05_2017.py for general notes on some of these methods

import sqlite3

class dbHandler:

    def __init__(self):
        self.connection = sqlite3.connect("todo.db")
        self.cursor = self.connection.cursor()

    def __del__(self):
        self.connection.close()

    def createEntry(self, description, priority, dueDate, inputBy, reminder, repeated):
        self.cursor.execute("INSERT INTO todo(description, priority, dueDate, inputBy, reminder, repeated) VALUES (?, ?, ?, ?, ?, ?)", (description, priority, dueDate, inputBy, reminder, repeated))
        self.connection.commit()

    def getAll(self):
        self.cursor.execute("SELECT * FROM todo")
        rows = self.cursor.fetchall()
        #for i in range(len(rows)):
        #   print(rows[i][0], '\t', str(rows[i][1]), '\t\t', rows[i][2], '\t', rows[i][3])
        return rows
    
    def getOne(self, id):
        self.cursor.execute("SELECT * FROM todo WHERE id=?", (id,))
        row = self.cursor.fetchall()
        #for i in range(len(row)):
        #    print(row[i][0], '\t', str(row[i][1]), '\t\t', row[i][2], '\t', row[i][3])
        return row

    def updateEntry(self, id, newDescription):
        self.cursor.execute("UPDATE todo SET description=? WHERE id=?", (newDescription, id))
        self.connection.commit()

    def deleteEntry(self, id):
        self.cursor.execute("DELETE FROM todo WHERE id=?", (id,))
        self.connection.commit()

    def deleteAll(self):
        self.cursor.execute("DELETE FROM todo")
        self.connection.commit()

    def selectAllIds(self):
        self.connection.row_factory = lambda cursor, row: row[0]
        ids = self.cursor.execute('SELECT id FROM todo').fetchall()
        return ids
