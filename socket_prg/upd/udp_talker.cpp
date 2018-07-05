/**
* Example of UDP talker
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

using namespace std;

#define PORT "9999"

int main(int argc, char const *argv[]) {


  int sock_fd;
  struct addrinfo hints, *servinfo, *p;
  int rv;
  int numbytes;

  memset(&hints, 0, sizeof(hints));

  hints.ai_family     = AF_UNSPEC;
  hints.ai_socktype   = SOCK_DGRAM;

  if((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0){
    fprintf(stderr, "%s\n", gai_strerror(rv));
    return 1;
  }

  for(p = servinfo; p != NULL; p = p->ai_next){

    if((sock_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1){
      perror("talker:socket");
      continue;
    }

    break;
  }

  if(p == NULL){
    fprintf(stderr, "%s\n", "talker:failed to bind socket");
    return 2;
  }

  if((numbytes = sendto(sock_fd, argv[1], strlen(argv[1]), 0, p->ai_addr, p->ai_addrlen)) == -1){
    perror("talker:faild to send");
    exit(1);
  }

  freeaddrinfo(servinfo);
  cout << "talker sent << " << numbytes << " bytes" << endl;
  close(sock_fd);
  return 0;
}
