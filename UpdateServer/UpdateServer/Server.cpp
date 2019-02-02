#include <WinSock2.h>
#include <Ws2tcpip.h>
#include <iostream>
#include "FileHelper.h"
using namespace std;

#pragma comment(lib, "Ws2_32.lib")

const char FILENAME[] = "data3.bin";
const char IPADDR[] = "127.0.0.1";
const int  PORT = 50000;
const int  QUERY = 1;
const int  UPDATE = 2;
const int  BUFFER_LENGTH = 512;
int requestsHandled = 0;

// Returns the version number from the data file
// Writen by Bobby Hoggard :)
int getLocalVersion();

// Return the contents of data.bin
void getFile(int file[], int size);

// return the number of ints in data.bin
int getFileSize();

int main()
{
	// Add your code here for the server
	cout << "Update server\n";
	// Declare sockets for listening and server, initialize to invalid
	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;
	
	char port[10];
	snprintf(port, sizeof(port), "%d", PORT);

	int localVersion = getLocalVersion();
	printf("Current data file version: v%d\n", localVersion);
	printf("Running on port number %d\n\n", PORT);

	//Create Windows Socket data object
	
	WSADATA wsaData;
	/*
		*****WSADATA STUCT LAYOUT*****
		typedef struct WSAData {
		  WORD           wVersion;
		  WORD           wHighVersion;
		  unsigned short iMaxSockets;
		  unsigned short iMaxUdpDg;
		  char           *lpVendorInfo;
		  char           szDescription[WSADESCRIPTION_LEN + 1];
		  char           szSystemStatus[WSASYS_STATUS_LEN + 1];
		} WSADATA;
	*/


	//Start up Windows Socket 
	// wsResult will be used to store window socket functions for testing
	int wsResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	//Test windows startup result
	if (wsResult != 0) {
		printf("WSAStartup error: %d\n", wsResult);
		return 1;
	}

	//Used by getaddrinfo *get address info* 
	struct addrinfo *result = NULL, 
					*ptr = NULL,
					hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;  // value 2 - ipv4 family
	hints.ai_socktype = SOCK_STREAM; // value 1 - provides 2 way connection on TCP/IP 
	hints.ai_protocol = IPPROTO_TCP; // value 6 - TCP I don't know if we need this as SOCK_STREAM may auto set


	// resolve host:port to be used by server
	wsResult = getaddrinfo(IPADDR, port, &hints, &result);
	if (wsResult != 0) {
		printf("getaddrinfo error: %d\n", wsResult);
		WSACleanup();
		return 1;
	}

	// Initialize socket based off of hints
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

	// Test Socket 
	if (ListenSocket == INVALID_SOCKET) {
		printf("Listeen Socket error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	// Call bind passing socket and socket struct
	wsResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	// test to see if bind holds
	if (wsResult == SOCKET_ERROR) {
		printf("binding error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	else { //this is a pointless else just for orginizational purpose
		//free's the result section
		freeaddrinfo(result);
	}
	
	// receive data until shutdown
	// buffer length of bytes
	char buffer[BUFFER_LENGTH] = "\n";
	int req = 0, res; // request, response
	int checkVersion = 0; // When this is 4 the server should set this to 0 and check the local version number 
	int temp;

	// Listen for request on socket
		wsResult = listen(ListenSocket, SOMAXCONN);
		// Test to see if socket is listening
		if (wsResult == SOCKET_ERROR)
		{
			printf("Listen error: %ld\n", WSAGetLastError());
			closesocket(ListenSocket);
			WSACleanup();
			return 1;
		}

		// Accept a client socket
		ClientSocket = accept(ListenSocket, NULL, NULL);
		//Test to see if accept worked
		if (ClientSocket == INVALID_SOCKET)
		{
			printf("accept socket error: %d\n", WSAGetLastError());
			closesocket(ListenSocket);
			WSACleanup();
			return 1;
		}
		else
		{
			// this can be commented out
			printf("Listening on %s:%s\n", IPADDR, port);
		}

		//store the request from client
		if (checkVersion > 4)
		{
			checkVersion = 0;
			localVersion = getLocalVersion();
		}

		req = recv(ClientSocket, (char *)&temp, BUFFER_LENGTH, 0);
		if (req > 0)
		{
			printf("bytes received: %d\n", req);
			printf("message received: %d\n", temp);
			printf("temp received %d\n", temp);


			if (temp == 1)
			{
				res = send(ClientSocket, (char *)&localVersion, sizeof(localVersion), 0);
			}

			else if(temp == 2)
			{
				//Send over the file
				ifstream inputFile;
				openInputFile(inputFile, FILENAME);

				res = send(ClientSocket, (char *)readInt(inputFile), sizeof(inputFile), 0);
				inputFile.close();
				//res = send(ClientSocket, (char *)&localVersion, sizeof(localVersion), 0);
			}
			//if sends failed send error
			if (res == SOCKET_ERROR)
			{
				printf("failed to send: %d\n", WSAGetLastError());
				closesocket(ClientSocket);
				WSACleanup();
				return 1;
			}
		}

		// Shouldn't happen
		else if (req == 0)
		{
			int size = getFileSize();
			int *file = new int[size];
			getFile(file, size);
			for (int i = 0; i < size; i++)
			{
				printf("%d\n", file[i]);
			}
			delete file;
		}

		requestsHandled++;
		printf("Requests handled:\d\n", requestsHandled);
	} while (req != -1);

	//This wont run unless we create a shutdown signal
	//cleaning
	closesocket(ClientSocket);
	WSACleanup();
	return 0;
}

int getLocalVersion() {
	ifstream dataFile;
	openInputFile(dataFile, FILENAME);

	int version = readInt(dataFile);
	dataFile.close();

	return version;
}

void getFile(int file[], int size) {
	ifstream dataFile;
	openInputFile(dataFile, FILENAME);
	
	for (int i = 0; i < size; i++) {
		file[i] = readInt(dataFile);
	}
	dataFile.close();


}

int getFileSize() {
	ifstream dataFile;
	openInputFile(dataFile, FILENAME);

	int counter = 0;
	int temp;
	do {
		temp = readInt(dataFile);
	} while (temp != EOF);

	dataFile.close();

	return counter;

