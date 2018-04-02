#include <iostream>
#include <fstream>
#include <ctime>
#include <string>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

using namespace std;

#define PORT 8080

char server_addres[256	] = "127.0.0.1";

void clinent();

int main()
{
	

	clinent();
	return 0;
}

void clinent(){

	int sockfd, n;
	struct  sockaddr_in serv_addr;

	char buffer[256];

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	cout << "Created socket :" << sockfd << endl;


	cout << "Clearing server address" << endl;
	memset(&serv_addr, 0, sizeof(serv_addr));
	

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	//inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
	inet_aton(server_addres, &serv_addr.sin_addr);
	cout << "Server addres - "<<inet_ntoa(serv_addr.sin_addr) << ":"<< htons(serv_addr.sin_port) << endl;


	connect(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));



	cout << "Closing socket :" << sockfd << endl;
	close(sockfd);
}