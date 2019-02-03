#include <WinSock2.h>
#include <Ws2tcpip.h>
#include <iostream>
#include "FileHelper.h"

using namespace std;

#pragma comment(lib, "Ws2_32.lib")

const char FILENAME[] = "data.bin";
const char IPADDR[] = "127.0.0.1";
const int  PORT = 50000;
const int  QUERY = 1;
const int  UPDATE = 2;
const int  BUFFER_LENGTH = 512;	
const int requestVersion = 1;
const int requestFile = 2;

// Returns the version number from the data file
int getLocalVersion();

// Reads the two data values from the data file.
// When the function ends, num1 and num2 will be holding the
// two values that were read from the file.
void readData(int& num1, int& num2);

int main() {
	int			sum;
	int			num1 = 0;
	int			num2 = 0;
	int			localVersion = 0;

	// Add code here to
	// 1) make sure that we are using the current version of the data file
	// 2) update the data file if it is out of data

	// Main purpose of the program starts here: read two numbers from the data file and calculate the sum
	localVersion = getLocalVersion();
	cout << "\nSum Calculator Version " << localVersion << "\n\n";

	//networking starts here

	//initialize Window Socket start
	WSADATA wsaData;

	//ports read as strings
	char port[10];
	snprintf(port, sizeof(port), "%d", PORT);
	//itoa(PORT, port, 10);

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

	// Stores resupts of Window Socket functions
	int wsResult;

	//socket for sending request 
	SOCKET ReqSocket = INVALID_SOCKET;


	// Start Window Socket
	wsResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	// Check Window Socket for errors
	if (wsResult != 0) {
		printf("WSAStartup error: %d\n", wsResult);
		return 1;
	}

	// addrinfo is a socket address structure used by get address info (getaddrinfo)
	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET; //Value 2 , indicates IPv4 family
	hints.ai_socktype = SOCK_STREAM; //Value 1 , indicates 2 way TCP/IP
	hints.ai_protocol = IPPROTO_TCP; //Value 6 , indicates  TCP
	// ^^ socktype and protocol may be auto set when family is set to ipv4... not sure

	// Resolve the req address and port (create socket)
	wsResult = getaddrinfo(IPADDR, port, &hints, &result);
	// test if socket is resolved
	if (wsResult != 0) {
		printf("getaddrinfo error: %d\n", wsResult);
		WSACleanup();
		return 1;
	}

	//Attemp to connect to host:port
	ptr = result;

	// Create a socket for connecting to server
	ReqSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

	//check to see if the socket is valid
	if (ReqSocket == INVALID_SOCKET) {
		printf("Socket error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	// Connect to server.
	wsResult = connect(ReqSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
	// check to osee if the socket connected, if it failed the req must fail
	if (wsResult == SOCKET_ERROR) {
		closesocket(ReqSocket);
		ReqSocket = INVALID_SOCKET;
	}

	//result is freed
	freeaddrinfo(result);

	//check req socket to see if connection was made
	if (ReqSocket == INVALID_SOCKET) {
		printf("Unable to connect to host:port\n %s:%s \n", IPADDR, port);
		WSACleanup();
		return 1;
	}

	// set buffer length as well as req and res
	char buffer[BUFFER_LENGTH] = "";
	int req, res;
	int temp;


	// This sends the buffer, but the third paramater must equal the length of the buffer msg
	req = send(ReqSocket, (char *)&requestVersion, sizeof(requestVersion), 0);
	if (req == SOCKET_ERROR) {
		printf("send error: %d\n", WSAGetLastError());
		closesocket(ReqSocket);
		WSACleanup();
		return 1;
	}
	// if req was sent print amount sent
	// For debugging
	// printf("Bytes Sent: %d\n", req);
	// printf("Message Sent(int): %d\n", requestVersion);


	res = recv(ReqSocket, (char *)&temp, sizeof(temp), 0);
	printf("Received Version: Server %d\n", temp);
	if (temp == localVersion) {
		printf("versions are the same\n");
	}
	else {

		// Window Socket Cleaning
		closesocket(ReqSocket);
		WSACleanup();

		//socket for sending request 
		SOCKET ReqSocket = INVALID_SOCKET;


		// Start Window Socket
		wsResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		// Check Window Socket for errors
		if (wsResult != 0) {
			printf("WSAStartup error: %d\n", wsResult);
			return 1;
		}

		// addrinfo is a socket address structure used by get address info (getaddrinfo)
		struct addrinfo *result = NULL,
			*ptr = NULL,
			hints;

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_INET; //Value 2 , indicates IPv4 family
		hints.ai_socktype = SOCK_STREAM; //Value 1 , indicates 2 way TCP/IP
		hints.ai_protocol = IPPROTO_TCP; //Value 6 , indicates  TCP
		// ^^ socktype and protocol may be auto set when family is set to ipv4... not sure

		// Resolve the req address and port (create socket)
		wsResult = getaddrinfo(IPADDR, port, &hints, &result);
		// test if socket is resolved
		if (wsResult != 0) {
			printf("getaddrinfo error: %d\n", wsResult);
			WSACleanup();
			return 1;
		}

		//Attemp to connect to host:port
		ptr = result;

		// Create a socket for connecting to server
		ReqSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

		//check to see if the socket is valid
		if (ReqSocket == INVALID_SOCKET) {
			printf("Socket error: %ld\n", WSAGetLastError());
			freeaddrinfo(result);
			WSACleanup();
			return 1;
		}

		// Connect to server.
		wsResult = connect(ReqSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		// check to osee if the socket connected, if it failed the req must fail
		if (wsResult == SOCKET_ERROR) {
			closesocket(ReqSocket);
			ReqSocket = INVALID_SOCKET;
		}

		//result is freed
		freeaddrinfo(result);

		//check req socket to see if connection was made
		if (ReqSocket == INVALID_SOCKET) {
			printf("Unable to connect to host:port\n %s:%s \n", IPADDR, port);
			WSACleanup();
			return 1;
		}

		printf("version are not the same\n");

		req = send(ReqSocket, (char *)&requestFile, sizeof(requestFile) + 1, 0);

		// printf("Bytes Sent: %d\n", req);
		// printf("Message Sent(int): %d\n", requestFile);
		if (req == SOCKET_ERROR) {
			printf("send error: %d\n", WSAGetLastError());
			closesocket(ReqSocket);
			WSACleanup();
			return 1;
		}
		ofstream dataFile;
		openOutputFile(dataFile, FILENAME);

		for (int counter = 0; counter != 3; counter++) {
			res = recv(ReqSocket, (char *)&temp, sizeof(temp), 0);
			writeInt(dataFile, temp);

		}
		//do {
		//	printf("In do-while");
		//	res = recv(ReqSocket, (char *)&temp, sizeof(temp), 0);
		//	if (res != -1) {
		//		writeInt(dataFile, temp);
		//	}
		//	printf("recieved bytes %d\n", res);
		//	printf("recieved value %d\n", temp);
			
		//} while (res != -1);
		dataFile.close();
	}
	
	
		
	// Shutdown req Connection
	// the client can still use socket for receiving
	wsResult = shutdown(ReqSocket, SD_SEND);




	//read - print data to client
	readData(num1, num2);
	sum = num1 + num2;
	cout << "The sum of " << num1 << " and " << num2 << " is " << sum << endl;

	// Window Socket Cleaning
	closesocket(ReqSocket);
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

void readData(int& num1, int& num2) {
	ifstream dataFile;
	openInputFile(dataFile, FILENAME);

	// Read the version number and discard it
	int tmp = num1 = readInt(dataFile);

	// Read the two data values
	num1 = readInt(dataFile);
	num2 = readInt(dataFile);

	dataFile.close();
}

