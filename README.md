# wsaUpdater

Current Roles

Sever starts
server checks local version
server listen at ports
Client starts
client checks local version
sends current version to server
sever receives version then compares to local version
if same responds with 200
if not same repsonds with 505

client receives status code
if 200 client finishes up and sends a shutdown signal to server
if 505 client sends msg for new data file

server recieves message for new data file and does nothing

 -- This is where the client needs to recv the 


## Created basic client server network. 
The basic layout for communication between a client and server has been crated as well as multiple error testing functions and full commenting.

## \#TODO
When server receives a message to send a file it needs to send the file array
Client needs to listen for file arr, update local file, do math, then shut down

for now shuting down the server after shuting down client is fine.  We can adjust that at the end.

## ISSUE

When our server communicates with Hoggard's client, Hoggard's client receives incorrect numbers. It reads the version number correctly. 

The issue has to be with how we are sending our data. I'm not sure how Hoggard wants it and it is especially confusing because Hoggard's server works with our client. Meaning, his server is sending 3 different values, at 3 different times, that correspond with the 3 numbers in the file. Because of this, his server works with our client. 
