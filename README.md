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

If we run a server and then try to connect our client when it is initially out of date, it will make num2 the same as num1. It doesn't happen always and I'm not sure why it is doing it, but I imagine it is limited to the lines of code in the client that get the file data from the server.
