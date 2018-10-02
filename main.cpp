#include<iostream>
#include<stdlib.h>
// #include<conio>
using namespace std;

char menu();
// void train_list();
// void booking();
// void train_content();

 void train_list()
{
{
	int choice;
	printf("\n1.UBL-GLB \n2.UBL-BJPR \n3.UBL-BLR \n4.UBL-GOA \n5.UBL-HYB\n");
	printf("enter the choice");
	scanf_s("%d",&choice);

	switch(choice)
	{
	case 1:printf("U have selected hubbali to gulbarga\n");
           break;
	case 2:printf("U have selected hubbali to bijapur\n");
		   break;
    case 3:printf("U have selected hubbali to bangalore\n");
		   break;
	case 4:printf("U have selected hubbali to goa\n");
		   break;
	case 5:printf("U have selected hubbali to hydrabad\n");
		   break;
   default:printf(" please enter the correct choice\n");
	}
}


}

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
