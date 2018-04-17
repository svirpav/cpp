#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

int main(int argc, char const *argv[]) {

  struct addrinfo hints, *res;
  int sockfd;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  getaddrinfo(NULL, "3490", &hints, &res);
  sockfd = socket(res->ai_family, res -> ai_socktype, res -> ai_protocol);

  cout << "Socket created : " << sockfd << endl;

  bind(sockfd, res->ai_addr, res->ai_addrlen);

  return 0;
}
