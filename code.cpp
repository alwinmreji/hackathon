#include<iostream>
#include<stdlib.h>
// #include<conio>
using namespace std;

char menu();
void train_list();
// void booking();
// void train_content();

char menu()
{
  char a;
  // clrscr();
  cout<<"\n\t\tMenu\n\t1. TrainList\n\t2. Booking\n\t3. Train Content\n\t4. Exit\nEnter Your choice:\t";
  cin>>a;
  return a;
}

int main()
{
  char ch;
  cout<<"Welcome To Train Freight Train Management System";
  ch = menu();
  switch (ch)
  {
    // case '1':train_list();
             // break;
    // case '2':booking();
    //          break;
    // case '3':train_content();
    //          break;
    case '4':exit(0);
             break;
    default : cout<<"\n\n\t!!...INVALID INPUT...!!";
  }
}
