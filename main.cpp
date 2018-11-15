#include<iostream>
#include<stdlib.h>
#include<stdio.h>
// #include<conio>
using namespace std;

struct cargo
{
  int train_no,boarding,deboarding;
  cargo *next;
};

typedef cargo *CARGO;

CARGO new_cargo()
{
  CARGO x = (CARGO)malloc(sizeof(cargo));
}

char menu();
void train_list();
void booking();
// void train_content();
void booking()
{
  CARGO engine;
  char choice;
  re:
  train_list();
  cout<<"\n\tGo to booking counter ??(y/n)";
  cin>>choice;
  if (choice == 'n' || choice == 'N')
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
  char ubl_glb[9][4]={{"UBL"},{"HVR"},{"RNR"},{"HRR"},{"DVG"},{"RRB"},{"ASK"},{"TK"},{"YPR"}};
  char ubl_bjpr[7][5]={{"UBL"},{"NGR"},{"GDG"},{"BDM"},{"BGK"},{"LMT"},{"BJPR"}};
  char ubl_bgk[5][4]={{"UBL"},{"NGR"},{"GDG"},{"BDM"},{"BGK"}};
  char ubl_goa[6][4]={{"DWR"},{"LWR"},{"LD"},{"CLR"},{"QLM"},{"VSG"}};
  char ubl_hyb[9][5]={{"UBL"},{"GDG"},{"BDM"},{"BGK"},{"BJPR"},{"GLB"},{"YG"},{"VKB"},{"HYB"}};
	printf("\n\t\tList Of Trains \n1.UBL-YPR \n2.UBL-BJPR \n3.UBL-BLR \n4.UBL-GOA \n5.UBL-HYB\n");
	printf("\nEnter Your choice:\t");
	scanf(" %c",&choice);
	switch(choice)
	{
	case '1':for(int i=0; i<9; i++)
           {
               cout<<ubl_glb[i]<<'\n';
           }
           break;
   case '2':for(int i=0; i<7; i++)
            {
              cout<<ubl_bjpr[i]<<'\n';
            }
         	  break;
  case '3':for(int i=0; i<5; i++)
            {
              cout<<ubl_bgk[i]<<'\n';

            }
         	 break;
	case '4':for(int i=0; i<6; i++)
           {
               cout<<ubl_goa[i]<<'\n';
           }
         	 break;
  	case '5':for(int i=0; i<9; i++)
           {
             cout<<ubl_hyb[i]<<'\n';
           }
         	 break;
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
  while(1)
  {
    ch = menu();
    switch (ch)
    {
      case '1':train_list();
             break;
      case '2':booking();
             break;
      // case '3':train_content();
      //          break;
      case '4':exit(0);
                  break;
      default : cout<<"\n\n\t!!...INVALID INPUT...!!";
    }
  }
}
