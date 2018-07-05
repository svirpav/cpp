#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {


  struct addrinfo hints, *infoprt, *p;
  int status;
  char ipstr[INET6_ADDRSTRLEN];

  if(argc != 3){
    fprintf(stderr, "Usage of showip : hostname port_name \n");
    return 2;
  }

  memset(&hints, 0, sizeof(hints));

  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  status = getaddrinfo(argv[1], argv[2], &hints, &infoprt);

  cout << "Get info status :" << status << endl;

  for (p = infoprt; p != NULL; p = p->ai_next){

    void *ipv;
    int port;
    char ipv4_str[INET6_ADDRSTRLEN];


    struct sockaddr_in *addr = (struct sockaddr_in*)p->ai_addr;
    ipv = &(addr -> sin_addr);
    port = ntohs(addr -> sin_port);
    inet_ntop(p->ai_family, ipv, ipv4_str, sizeof(ipv4_str));
    cout << " IP - " << ipv4_str << ":" << port << endl;

  }


  freeaddrinfo(infoprt);
  return 0;
}
