#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h> //close();

using namespace std;

#define PORT "3040"
#define BACK_LOG 5

int main(int argc, char const *argv[]) {

  struct sockaddr_storage their_addr;
  socklen_t add_size;
  struct addrinfo hints, *res;
  int socketfd, new_fd;

  char *msg;
  int len;
  int bytes_sent;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;


  getaddrinfo(NULL, PORT, &hints, &res);
  socketfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  if(socketfd == -1){

    cout << "Error : Socket creation error" << endl;
  }

  bind(socketfd, res->ai_addr, res->ai_addrlen);
  listen(socketfd, BACK_LOG);

  add_size = sizeof(their_addr);
  new_fd = accept(socketfd, (struct sockaddr*) &their_addr, &add_size);

  msg = "Hello this is message from test server";
  len = strlen(msg);
  bytes_sent = send(new_fd, msg, len,0);
  cout << bytes_sent << " : Bytes sent" << endl;

  close(socketfd);
  close(new_fd);

  return 0;
}
