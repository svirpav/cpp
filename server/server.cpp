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
#define BACK_LOG 10

void sigchld_handler(int s){

  (void) s;
  int saved_error = errno;
  while (waitpid(-1, NULL, WNOHANG) > 0);
  errno = saved_error;
}

void *get_in_addr(struct sockaddr *sa){

  if(sa->sa_family == AF_INET){

    return &(((struct sockaddr_in *) sa) -> sin_addr);
  }

  return &(((struct sockaddr_in6 *) sa) -> sin6_addr);
}

int main(int argc, char const *argv[]) {

  int sock_fd, new_fd;
  int rv;
  int yes = 1;

  struct addrinfo hints, *servinfo, *p;
  struct sockaddr_storage their_addr;
  struct sigaction sa;

  socklen_t sin_size;

  char s[INET6_ADDRSTRLEN];

  memset(&hints, 0, sizeof(hints));

  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  if((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0){
    fprintf(stderr, " get addrinfo :%s\n", gai_strerror(rv));
    return 1;
  }


  for(p = servinfo; p != NULL; p = p->ai_next){

    if((sock_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1){
      perror("server : socket");
      continue;
    }
    if(setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int))== -1){
      perror("setsockopt");
      exit(1);
    }
    if(bind(sock_fd, p->ai_addr, p->ai_addrlen) == -1){
      close(sock_fd);
      perror("server : bind");
      continue;
    }

    break;
  }

  freeaddrinfo(servinfo);

  if(p == NULL){
    fprintf(stderr, "server faild to bind\n");
  }

  if(listen(sock_fd, BACK_LOG) == -1){
    perror("listen");
    exit(1);
  }

  sa.sa_handler = sigchld_handler;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;

  if(sigaction(SIGCHLD, &sa, NULL) == -1){
    perror("sigaction");
    exit(1);
  }

  cout << "Server waiting for connection ..." << endl;

  while(1){

    sin_size = sizeof(their_addr);
    new_fd = accept(sock_fd, (struct sockaddr*) &their_addr, &sin_size);

    if(new_fd == -1){
      perror("accept");
      exit(1);
    }

    inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *) &their_addr), s, sizeof(s));

    cout << "Server got connection for IP : " << s << endl;

    if(!fork()){
      close(sock_fd);
      char message[256] = "Response from server";
      if(send(new_fd, message, strlen(message), 0) == -1){
        perror("send");
         close(new_fd);
         exit(0);
      }
    }
    close(new_fd);
  }

  return 0;
}
