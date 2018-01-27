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

* The name of my user collection is **users** and I draw user resources from a database called **users.db**. It contains the following attributes:
    * First Name
    * Last Name
    * Email
    * Encrypted Password
* My database schema for this resources as represent by **.schema**:
> `CREATE TABLE users(id INTEGER PRIMARY KEY, firstName VARCHAR(255), lastName VARCHAR(255), email VARCHAR(255), encryptedPassword, VARCHAR(255));`

* REST endpoints implemented by API server for "entries" resource:

Name | Scope | HTTP Method | Path
---- | ------| ----------- | ----
Create | collection | POST | http://127.0.0.1/entries
List | collection | GET | http://127.0.0.1/entries		
Retrieve | member | GET | http://127.0.0.1/entries/[MEMBER]
Update | member | PUT | http://127.0.0.1/entries/[MEMBER]
Delete | member | DELETE | http://127.0.0.1/entries/[MEMBER]
Options | any | OPTIONS | http://127.0.0.1/entries

* REST endpoints implemented by API server for "users" resource:

Name | Scope | HTTP Method | Path
---- | ------| ----------- | ----
Create | collection | POST | http://127.0.0.1/register
List | collection | GET | http://127.0.0.1/register		
Retrieve | member | GET | http://127.0.0.1/login/[MEMBER]
  
* The python class "bcrypt" from the "passlib" library was used to create relevant hashes. The standard class parameters were used to create the hash.