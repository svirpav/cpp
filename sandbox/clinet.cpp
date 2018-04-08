#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h> //close();

#define PORT "3040"

using namespace std;


int main(){

	int sockfd;

	struct addrinfo hints, *res;
	char buffer[256];
	int bytes_received;
	int len;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(NULL, PORT, &hints, &res);

	sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	connect(sockfd, res->ai_addr, res->ai_addrlen);

	len = sizeof(buffer);
	bytes_received = recv(sockfd, buffer, len, 0);
	cout << buffer << " : "<< bytes_received << " - Byres bytes_received."<< endl;

	close(sockfd);
	return 0;
}
