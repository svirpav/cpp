#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

int i_port = 8080;
int server_socket;
int client_socket;
int n;


char *i_to_s;
char buffer[1024];

fstream log_file;
time_t current_time;
socklen_t client_length;
struct sockaddr_in server_addr, client_addr;

void log_open();
void log_close();
void get_current_time();
void string_handler(char *msg_1, char *msg_2);
void int_to_str(int i);
void log_writer(char *msg);
void init_server();

#endif
