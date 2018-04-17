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
#include <iostream>

using namespace std;

#define PORT "7070"
#define MAXDATASIZE 1000


void *get_in_addr(struct sockaddr *sa){

  if(sa->sa_family == AF_INET){
    return &(((struct sockaddr_in*)sa)->sin_addr);
  }
  return &(((struct sockaddr_in6*)sa)->sin6_addr);


}

int main(int argc, char const *argv[]) {

  int sock_fd, bytes_received;
  int rv;

  struct addrinfo hints, *servinfo, *p;

  char s[INET6_ADDRSTRLEN];
  char buf[MAXDATASIZE];

  memset(&hints, 0, sizeof(hints));

  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  if((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0){
    fprintf(stderr, "getaddrinfo %s\n", gai_strerror(rv));
    return 1;
  }

  for(p = servinfo; p != NULL; p=p->ai_next){

    if((sock_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1){
      perror("socket");
      continue;
    }

    if(connect(sock_fd, p->ai_addr, p->ai_addrlen) == -1){
      close(sock_fd);
      perror("client :connect");
      continue;
    }
    break;
  }

  inet_ntop(p->ai_family, get_in_addr((struct sockaddr*)p->ai_addr), s, sizeof(s));
  freeaddrinfo(servinfo);

  if((bytes_received = recv(sock_fd, buf, MAXDATASIZE-1, 0)) == -1){
    perror("recieve");
    exit(1);
  }

  buf[MAXDATASIZE-1] = '\0';
  printf("client received : %s\n", buf);
  close(sock_fd);

  return 0;
}
