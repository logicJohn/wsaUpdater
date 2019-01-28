# wsaUpdater

Abstract
Client sends a trvial request to the server for the current version.
server responds with current version
Client checks to see if client checks to see if server version is same as serever.
if different client updates
then prints answer
if same prints answer

(note this could be done as one or two communications) 
case 1:
Client ask for version numbeer
Server gives version number
Client finds mismatch and ask Server for full version
Server gives full version info

case 2 (this is poor as it ask for more info than is needed, but if we run into parsing issues will result in the same output):
Client ask for version number and full version info
Server gives version number and full version info
Client accepts all and prints answer



## Created basic client server network. 
The basic layout for communication between a client and server has been crated as well as multiple error testing functions and full commenting.

## \#TODO
Test the connection between client and server
Add parsing of data.bin using file manager provided by hoggard
Add parsing of buffer sent between client and server
Add comparison check and updates on clients side of service
