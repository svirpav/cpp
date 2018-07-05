#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {

  int i;

  for(i = 0; i < 10; i++){

    cout << "Step :" << i << endl;
    if (i == 4 ) {
      fprintf(stderr, "CONTINUE \n");
      continue;
      cout << "After continue" << endl;
    }
    cout << "Right after the if(i != 1)"<<endl;
  }
  return 0;
}
