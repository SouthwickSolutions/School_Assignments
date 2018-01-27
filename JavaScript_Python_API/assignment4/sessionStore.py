import os
import base64
import usersFunctions

class sessionStore:
	def __init__(self):
		self.sessionStore = {}
		self.anonymousSessionStore = {}
		return
	    
	def generateSessionId(self):
		rnum = os.urandom(32) #use the os library to generate a 32 bit random number
		rstr = base64.b64encode(rnum).decode("utf-8")
		return rstr
	    
	def createSession(self, primaryKey):
		sessionId = self.generateSessionId()
		self.sessionStore[sessionId] = {primaryKey}
		return sessionId

	def createAnonymousSession(self):
		sessionId = self.generateSessionId()
		self.anonymousSessionStore[sessionId] = {}
		return sessionId
	    
	def getSession(self, sessionId):
            if sessionId in self.sessionStore:
                return self.sessionStore[sessionId]
            else:
                return None

