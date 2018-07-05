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

#define PORT "7070"
#define MAXDATASIZE 1000
#define BACK_LOG 5

using namespace std;

void sigchld_handler(int s){

  while (waitpid(-1, NULL, WNOHANG) >0);
}

void *get_in_addr(struct sockaddr *sa){

  if(sa->sa_family == AF_INET){
    return &(((struct sockaddr_in *)sa)->sin_addr);
  }

  return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

int server_init(int *sock_fd){

  struct addrinfo hints, *servinfo, *p;
  int param = 1;
  int i_init;

  memset(&hints, 0, sizeof(hints));

  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  if((i_init = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0){
    fprintf(stderr, "server:getaddrinfo %s\n", gai_strerror(i_init));
    return 1;
  }

  cout << "server:getaddrinfo " << i_init << endl;



  for(p = servinfo; p!=NULL; p = p->ai_next){

    if((*sock_fd=socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1){
      perror("server:socket");
      continue;
    }

    cout << "server:socket " << sock_fd << endl;

    if((i_init = setsockopt(*sock_fd, SOL_SOCKET, SO_REUSEADDR, &param, sizeof(int))) == -1){
      perror("server:setsockopt");
      exit(1);
    }

    cout << "server:setsockopt " << i_init << endl;

    if((i_init = bind(*sock_fd, p->ai_addr, p->ai_addrlen)) == -1){
      perror("server:bind");
      continue;
    }


    break;
  }

  if(p == NULL){

    fprintf(stderr, "Server failed to bind \n");
  }

  freeaddrinfo(servinfo);
  return *sock_fd;
}

int server_accept(int *sock_fd, int *new_fd){

  int i_init;
  int str_len;

  struct sockaddr_storage their_addr;
  struct sigaction sa;

  socklen_t  addr_size;

  char ip_str[INET6_ADDRSTRLEN];
  char str[MAXDATASIZE];

  if((i_init = listen(*sock_fd, BACK_LOG)) == -1){
    perror("server:listen");
    exit(1);
  }

  cout << "server:listen " << i_init << endl;

  sa.sa_handler = sigchld_handler;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;

  if((i_init = sigaction(SIGCHLD, &sa, NULL)) == -1){
    perror("server:sigaction");
    exit(1);
  }

  cout << "server:sigaction " << i_init << endl;

  cout << "Server is waiting for connection ... " << endl;

  addr_size = sizeof(their_addr);

  if((*new_fd = accept(*sock_fd, (struct sockaddr *)&their_addr, &addr_size)) == -1){
    perror("server:accept");
    exit(0);
  }

  inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *) &their_addr), ip_str, sizeof(ip_str));
  cout << "server:connect accepted from " << ip_str << endl;

  strcat(str, "Connected to server");
  str[MAXDATASIZE-1] = '\0';
  str_len = strlen(str);
  if((i_init = send(*new_fd, "Connected to server", str_len, 0)) == -1){
    perror("server:send");
    close(*sock_fd);
    close(*new_fd);
  }

  return *new_fd;
}

int server_listen(int *new_fd){

  char buffer[MAXDATASIZE];
  int bytes_received;

    memset(&buffer, 0, sizeof(buffer));
    bytes_received = recv(*new_fd, buffer, MAXDATASIZE-1, 0);
    buffer[MAXDATASIZE -1] = '\0';
    printf("server:recieved %s\n", buffer);
    cout << bytes_received << endl;

  return bytes_received;
}


int main(int argc, char const *argv[]) {

  int sock_fd;
  int new_fd;
  int i;

  server_init(&sock_fd);
  server_accept(&sock_fd, &new_fd);
  while ((i = server_listen(&new_fd)) > 0);

  close(sock_fd);

}
