from passlib.hash import bcrypt
import sqlite3


class Password:
    
    def hashPassword(self, clearTextPassword):
        hashed = bcrypt.hash(clearTextPassword)
        return hashed

    def verifyPassword(self, clearTextPassword, hashedPassword):
        return bcrypt.verify(clearTextPassword, hashedPassword)





class usersDbHandler:
    def __init__(self):
        self.connection = sqlite3.connect("users.db")
        self.cursor = self.connection.cursor()

    def __del__(self):
        self.connection.close()
        
    def createUser(self, firstName, lastName, email, clearTextPassword):
        #hashes the password and deletes clearTextPassword
        password = Password()
        encryptedPassword = password.hashPassword(clearTextPassword)
        del clearTextPassword

        #inserts new user into the user database
        self.cursor.execute("INSERT INTO users(firstName, lastName, email, encryptedPassword) VALUES(?, ?, ?, ?)", (firstName, lastName, email, encryptedPassword))
        self.connection.commit()
    
    def getAllEmails(self):
        self.cursor.execute("SELECT email FROM users")
        emails = self.cursor.fetchall()
        return emails

    def getUser(self, email):
        self.cursor.execute("SELECT * FROM users WHERE email=?", (email,))
        user = self.cursor.fetchall()
        return user

    def getUserById(self, primaryId):
        self.cursor.execute("SELECT * FROM users WHERE id=?", (primaryId,))
        user = self.cursor.fetchall()
        return user 

    def verifyUser(self, loginEmail, loginClearTextPassword):
        password = Password()
        self.cursor.execute("SELECT encryptedPassword FROM users WHERE email=?", (loginEmail,))
        hashedPassword = self.cursor.fetchall()

        if not hashedPassword: return False
        if bcrypt.verify(loginClearTextPassword, hashedPassword[0][0]): return True
            
        return False
        




