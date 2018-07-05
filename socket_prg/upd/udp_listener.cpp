/*
** Sample of UDP listener
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

#define PORT "9999"
#define MAXBUFFER 100

using namespace std;

//port for connection
// get sockaddr IPv4 or IPv6

void *get_addr(struct sockaddr *sa){

  if(sa -> sa_family == AF_INET){

    return &(((struct sockaddr_in*)sa)->sin_addr);
  }
  else
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(void){

  int sock_fd;
  int rv;
  int numbytes;

  struct addrinfo hints, *servinfo, *p;
  struct sockaddr_storage their_addr;

  char buf[MAXBUFFER];
  char ip[INET6_ADDRSTRLEN];

  socklen_t addr_len;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;          //Set AF_INET to sellecte between IPv4 and IPv6
  hints.ai_socktype = SOCK_DGRAM;       // Set socket to UDP
  hints.ai_flags = AI_PASSIVE;          //Use my IP

  if((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0){
    fprintf(stderr, "listener:getaddrinfo %s\n", gai_strerror(rv));
    return 1;
  }

  cout << "listener:getaddrinfo << " << rv << endl;
  cout << "ai_family << "<< servinfo->ai_family << endl;
  cout << "ai_addr << "<< servinfo->ai_addr << endl;
  cout << "ai_socktype << "<< servinfo->ai_socktype << endl;
  cout << "ai_protocol << "<< servinfo->ai_protocol << endl;
  cout << "ai_addrlen << "<< servinfo->ai_addrlen << endl;

  for(p = servinfo; p != NULL; p = p->ai_next){

    if((sock_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1){
      perror("listener:socket");
      continue;
    }

    cout << "listener:socket << " << sock_fd << endl;

    if(bind(sock_fd, p->ai_addr, p->ai_addrlen) == -1){
      close(sock_fd);
      perror("listener-bind");
      continue;
    }

    break;
  }

  if (p == NULL){
    fprintf(stderr, "listener:error to bind socket \n");
    return 2;
  }

  freeaddrinfo(servinfo);

  cout<<"listener: waiting to recieve from... " << endl;

  addr_len = sizeof(their_addr);

  if((numbytes = recvfrom(sock_fd, buf, MAXBUFFER - 1, 0,(struct sockaddr*)&their_addr, &addr_len)) == -1){
    perror("listener: recvfrom error");
    exit(1);
  }

  cout << "listener: got packets from - " << inet_ntop(their_addr.ss_family, get_addr((struct sockaddr*)&their_addr), ip, sizeof(ip)) << endl;
  cout << "listener: packet is " << numbytes << "bytes" << endl;

  buf[numbytes] = '\0';
  printf("listener: packet contains \"%s\"\n", buf);
  close(sock_fd);
  return 0;
}
