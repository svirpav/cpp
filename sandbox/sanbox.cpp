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

#define PORT 8080

using namespace std;
std::fstream logFile;

string  time_to_string;
time_t currentTime;

void app_initialization();
void log(string);
void app_closing();
void server();


int main()
{
	
	//app_initialization();
	server();
	app_closing();
	return 0;
}


void app_initialization(){

//
}


void server(){

	int server_socket;
	int client_socket[5];
	socklen_t clilen;
	char buffer[1024];

	struct sockaddr_in serv_addr, cli_addr;
	int n;

	;


	//Create socket
	if((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1){

		cout << "Create socket error line 69" << endl;
	}
	
	cout << "Socket :" << server_socket << " - created" << endl;


	//clear address structure\
	bzero((char *) serv_addr, sizeof(serv_addr));

	

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	cout << "host - " << inet_ntoa(serv_addr.sin_addr)<<":";

	//The htons() function converts the unsigned short integer hostshort from host byte order to network byte order.
	serv_addr.sin_port = htons(PORT);
	cout << htons(serv_addr.sin_port) << endl;


	//Bind socket
	if(bind(server_socket, (struct sockaddr *) &serv_addr, sizeof(serv_addr))  < 1){
		cout << "Error to bind socket" << endl;
	}

	cout << "Socket sucessfully binded" << endl;

	listen(server_socket, 5);

	if((client_socket[0] = accept(server_socket, (struct sockaddr *) &cli_addr, &clilen)) < 0){

		cout << "Cliner refused to be connect" << endl;
	}

	cout << "Server got connection from : " << inet_ntoa(cli_addr.sin_addr) << ":" << ntohs(cli_addr.sin_port);
		
	
	close(server_socket);


}


void log(string msg){

	currentTime = time(0);
	time_to_string = ctime(&currentTime);
	logFile.open("server.log", std::fstream::in | std::fstream::out | std::fstream::app);
	logFile << msg << time_to_string;
	logFile.close();
}





void app_closing(){

	log("Application closing - ");
}

