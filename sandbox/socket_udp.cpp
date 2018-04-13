#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

#define PORT "3050"
#define BACK_LOG 5

int main(int argc, char const *argv[]) {

  struct addrinfo hints, *res;
  int sockfd;
  int bytes_sent;
  char ip_str[INET6_ADDRSTRLEN];

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_DGRAM;
  hints.ai_flags = AI_PASSIVE;

  getaddrinfo(NULL, PORT, &hints, &res);
  struct sockaddr_in *server = (struct sockaddr_in *) res->ai_addr;
  cout << inet_ntop(res->ai_family, &(server->sin_addr), ip_str, sizeof(ip_str)) << ":" << ntohs(server->sin_port) << endl;

  sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  cout << "Socket - " << sockfd << " created";

  bind(sockfd, res->ai_addr, res->ai_addrlen);

  return 0;
}
