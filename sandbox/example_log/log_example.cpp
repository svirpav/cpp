#include "server.hpp"


void log_open(){

  log_file.open("server.log", std::fstream::in | std::fstream::out | std::fstream::app);
}

void log_close() {

  log_file.close();
}

void get_current_time() {

  current_time = time(0);
  i_to_s = ctime(&current_time);
  strtok(i_to_s, "\n");
}

void init_server(){

  log_open();
  get_current_time();
  log_file << i_to_s << " - Server initialization" << endl;

  sleep(300);
  log_file << i_to_s << " - sleep 3000 ms" << endl;
}



int main() {

  init_server();
  return 0;
}
