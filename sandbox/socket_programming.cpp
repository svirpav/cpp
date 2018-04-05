#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

using namespace std;

int main(int argc, char const *argv[]) {


  int a, b, c;
  struct sockaddr_in sa;
  struct sockaddr_in6 sa6;

  char ip4[INET_ADDRSTRLEN];
  char ip6[INET6_ADDRSTRLEN];

  a = 2001;
  b = htons(a);
  cout << "Host to network short :" << a << "=" << b << endl;
  c = ntohs(b);
  cout << "Network to host short :" << b << "=" << c << endl;
  a = 30001;
  b = htonl(a);
  cout << "Host to network short :" << a << "=" << b << endl;
  c = ntohl(b);
  cout << "Network to host short :" << b << "=" << c << endl;

  inet_pton(AF_INET, "192.168.1.1", &(sa.sin_addr));
  inet_pton(AF_INET6, "2001:db8:63b3:1::3490", &(sa6.sin6_addr));

  inet_ntop(AF_INET, &(sa.sin_addr), ip4,INET_ADDRSTRLEN);
  inet_ntop(AF_INET6, &(sa6.sin6_addr), ip6, INET6_ADDRSTRLEN);

  cout << "Networp to Print IPv4 :" << ip4 << endl;
  cout << "Networp to Print IPv6 :" << ip6 << endl;

  return 0;
}
