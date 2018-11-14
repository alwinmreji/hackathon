#include<iostream>
#include<stdlib.h>
// #include<conio>
using namespace std;

struct cargo
{
  int
}

char menu();
void train_list();
void booking();
// void train_content();
void booking()
{
  char choice;
  re:
  train_list();
  cout<<"\n\tGo to booking counter ??(y/n)";
  cin>>choice;
  if (choice != 'y' || choice != 'Y')
  {
    cout<<"\n\tDisplay train list once more ??(y/n)";
    cin>>choice;
    if (choice == 'y' || choice == 'Y')
      goto re;
    else
    return;
  }
  cout<<"\n\tBOOKING COUNTER";
}
 void train_list()
{
	char choice;
  char ubl_glb[9][4][2]={{{"UBL"},{"HVR"},{"RNR"},{"HRR"},{"DVG"},{"RRB"},{"ASK"},{"TK"},{"YPR"}},{{"UBL"},{"HVR"},{"RNR"},{"HRR"},{"DVG"},{"RRB"},{"ASK"},{"TK"},{"YPR"}}};
	printf("\n\t\tList Of Trains \n1.UBL-YPR \n2.UBL-BJPR \n3.UBL-BLR \n4.UBL-GOA \n5.UBL-HYB\n");
	printf("\nEnter Your choice:\t");
	scanf(" %c",&choice);
	switch(choice)
	{
	case '1':for(int i=0; i<5; i++)
           {
               cout<<ubl_glb[i]<<'\n';
           }
           break;
	// case '2':printf("U have selected hubbali to bijapur\n");
	// 	   break;
  //   case '3':printf("U have selected hubbali to bangalore\n");
	// 	   break;
	// case '4':printf("U have selected hubbali to goa\n");
	// 	   break;
	// case '5':printf("U have selected hubbali to hydrabad\n");
	// 	   break;
   default:printf(" please enter the correct choice\n");
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
  while(1)
  {
    switch (ch)
    {
      case '1':train_list();
             break;
      case '2':booking();
      //          break;
      // case '3':train_content();
      //          break;
      case '4':exit(0);
                  break;
      default : cout<<"\n\n\t!!...INVALID INPUT...!!";
    }
  }
}
