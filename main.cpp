#include<iostream>
#include<stdlib.h>
#include<ctime>
#include<stdio.h>
// #include<conio>
using namespace std;

struct cargo
{
  int train_no,boarding,deboarding,day,month,year;
  cargo *next;
};

typedef cargo *CARGO;
char ubl_glb[9][4]={{"UBL"},{"HVR"},{"RNR"},{"HRR"},{"DVG"},{"RRB"},{"ASK"},{"TK"},{"YPR"}};
char ubl_bjpr[7][5]={{"UBL"},{"NGR"},{"GDG"},{"BDM"},{"BGK"},{"LMT"},{"BJPR"}};
char ubl_bgk[5][4]={{"UBL"},{"NGR"},{"GDG"},{"BDM"},{"BGK"}};
char ubl_goa[6][4]={{"DWR"},{"LWR"},{"LD"},{"CLR"},{"QLM"},{"VSG"}};
char ubl_hyb[9][5]={{"UBL"},{"GDG"},{"BDM"},{"BGK"},{"BJPR"},{"GLB"},{"YG"},{"VKB"},{"HYB"}};
char menu();
void train_list();
void booking();
// void train_content();

CARGO new_cargo()
{
  CARGO x = (CARGO)malloc(sizeof(cargo));
  return x;
}
CARGO get_data(CARGO engine)
{
  CARGO x = new_cargo();
  time_t t = time(0);
  struct tm * now = localtime(&t);
  int day_t,day = now->tm_mday + 1;
  int month_t,month = now->tm_mon + 1;
  int year_t,year = now->tm_year + 1900;
  yr:
  cout<<"\n\tEnter the Year :";
  cin>>year_t;
  if(year_t<x->year)
  {
    cout<<"INVALID INPUT";
    goto yr;
  }
  mnth:
  cout<<"\n\tEnter the Month :";
  cin>>month_t;
  if ((year_t - x->year==0)&&(month_t<x->month))
  {
    cout<<"INVALID INPUT";
    goto mnth;
  }
  d:
  cout<<"\n\tEnter the Day :";
  cin>>day_t;
  if ((month_t-x->month==0)&&(day_t<x->day))
  {
    cout<<"INVALID INPUT";
    goto d;
  }
  cout<<"\n\tEnter the train no.:";
  cin>>x->train_no;
  cout<<"\n\tEnter the boarding station no.:";
  cin>>x->boarding;
  cout<<"\n\tEnter the deboarding station no.:";
  cin>>x->deboarding;
}


void booking()
{
  CARGO engine=NULL;
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
  cout<<"\n\t\tBOOKING COUNTER";
  engine = get_data(engine);
}
 void train_list()
{
	char choice;

	printf("\n\t\tList Of Trains \n1.UBL-YPR - 12246 \n2.UBL-BJPR - 12247\n3.UBL-BGK - 12298 \n4.UBL-GOA  - 12270\n5.UBL-HYB - 12345\n");
	printf("\nEnter Your choice:\t");
	scanf(" %c",&choice);
	switch(choice)
	{
	case '1':for(int i=0; i<9; i++)
           {
               cout<<i+1<<". "<<ubl_glb[i]<<'\n';
           }
           break;
   case '2':for(int i=0; i<7; i++)
            {
              cout<<i+1<<". "<<ubl_bjpr[i]<<'\n';
            }
         	  break;
  case '3':for(int i=0; i<5; i++)
            {
              cout<<i+1<<". "<<ubl_bgk[i]<<'\n';

            }
         	 break;
	case '4':for(int i=0; i<6; i++)
           {
               cout<<i+1<<". "<<ubl_goa[i]<<'\n';
           }
         	 break;
  	case '5':for(int i=0; i<9; i++)
           {
             cout<<i+1<<". "<<ubl_hyb[i]<<'\n';
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
  // booking();
  char ch;
  cout<<"Welcome To Freight Train Management System";
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
