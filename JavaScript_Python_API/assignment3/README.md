# Readme.md

### _**Documented notes:**_
 * The name of my collection is **entries** and I draw resources from a database called **todo.db**. It is a todo list of sorts with the following attributes:
	 * Priority
	 * Description
	 * Due Date
	 * Originator
	 * Reminder (Y/N)
	 * Repeated Item (Y/N)
 * My database schema as represented by **.schema**:	
> `CREATE TABLE todo (id INTEGER PRIMARY KEY, description VARCHAR(255), priority INTEGER, dueDate VARCHAR(255), inputBy VARCHAR(255), reminder INTEGER, repeated INTEGER);`

 * REST endpoints implemented by API server:

Name | Scope | HTTP Method | Path
---- | ------| ----------- | ----
Create | collection | POST | http://127.0.0.1/entries
List | collection | GET | http://127.0.0.1/entries		
Retrieve | member | GET | http://127.0.0.1/entries/[MEMBER]
Update | member | PUT | http://127.0.0.1/entries/[MEMBER]
Delete | member | DELETE | http://127.0.0.1/entries/[MEMBER]
Options | any | OPTIONS | http://127.0.0.1/entries
 
 
 * Refer to this link for [RESTful API Design](http://restful-api-design.readthedocs.io/en/latest/methods.html).