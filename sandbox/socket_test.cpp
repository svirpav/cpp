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

#define PORT "7070"

using namespace std;

int main(int argc, char const *argv[]) {

  int sockfd;
  struct addrinfo hints, *res;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_DGRAM;

  getaddrinfo("192.168.1.118", PORT, &hints, &res);
  struct sockaddr_in *ipv4 = (struct sockaddr_in *)res->ai_addr;
  cout << res->ai_addrlen<<endl;
  cout << res->ai_protocol<<endl;
  cout << res->ai_socktype<<endl;
  return 0;
}
