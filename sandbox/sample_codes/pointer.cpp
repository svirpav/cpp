#include <iostream>

using namespace std;


void method_A(int *a){

  *a = 20;
}


int main(int argc, char const *argv[]) {

  int *a; //This is just empty pointer
  int b; //Integer declaration

  int m_a;

  b = 15;

  //before assignment
  cout << "addresa of a before assignment : " << a << endl;
  a = &b; //Assign point b to pointer a;

  //after assignment
  cout << "address a after assignment :"<< a << " = "<< *a << endl;

  method_A(&m_a);
  cout << m_a <<endl;
}
