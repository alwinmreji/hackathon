#include<iostream>
#include<stdlib.h>
#include<ctime>
#include<stdio.h>
// #include<conio>
using namespace std;
class train
{
struct cargo
{
  int train_no,boarding,deboarding,day,month,year;
  cargo *next;
};
typedef cargo *CARGO;
//CARGO new_cargo();
//CARGO sorting(CARGO engine,CARGO present);
//CARGO get_data(CARGO engine);
//void booking();
//void train_list();
CARGO get_data(CARGO engine)
{
  CARGO x = new_cargo();
  time_t t = time(0);
  struct tm * now = localtime(&t);
  // cout<<now;
  int day_t,day = now->tm_mday + 1;
  int month_t,month = now->tm_mon + 1;
  int year_t,year = now->tm_year + 1900;
  yr:
  cout<<"\n\tEnter the Year :";
  cin>>year_t;
  if(year_t<year || year_t>year+1)
  {
    // printf("INVALID INPUT %d",x->year);
    cout<<"INVALID INPUT";//<<year_t<<" "<<year;//((int)x->year);
    goto yr;
  }
  mnth:
  cout<<"\n\tEnter the Month :";
  cin>>month_t;
  if (((year_t - year==0)&&(month_t<month)) || (month_t>12))
  {
    cout<<"INVALID INPUT";
    goto mnth;
  }
  d:
  cout<<"\n\tEnter the Day :";
  cin>>day_t;
  if (((month_t-month==0)&&(day_t<day))|| (day_t>31))
  {
    cout<<"INVALID INPUT";
    goto d;
  }
  x->year = year_t;
  x->month = month_t;
  x->day = day_t;
  cout<<"\n\tEnter the train no.:";
  cin>>x->train_no;
  cout<<"\n\tEnter the boarding station no.:";
  cin>>x->boarding;
  cout<<"\n\tEnter the deboarding station no.:";
  cin>>x->deboarding;
  if (engine == NULL)
  {
    return x;
  }
  engine = sorting(engine,x);
  return engine;
}
CARGO new_cargo()
{
  CARGO x = (CARGO)malloc(sizeof(cargo));
  return x;
}
CARGO sorting(CARGO engine,CARGO present)
{
  CARGO temp,prev;
  if (engine->next == NULL)
  {
    if (engine->deboarding>present->deboarding)
    {
      present->next = engine;
      return present;
    }
  }
  temp =engine;
  while(temp==NULL)
  {
    if(temp->deboarding>present->deboarding)
    {
      prev->next=present;
      present->next=temp;
    }
    prev= temp;
    temp = temp->next;
  }
}

public:
char station_list[7][5];
// char menu();

};

// train n[10];
train obj[5];


int a;
char menu();
void train_list();
void booking();

// void train_content();
void booking()
{
  CARGO engine=NULL;
  char choice;
  re:
  train_list();
  cout<<"\n\tGo to booking counter ?(y/n)";
  cin>>choice;
  if (choice == 'n' || choice == 'N')
  {
    cout<<"\n\tDisplay train list once more ?(y/n)";
    cin>>choice;
    if (choice == 'y' || choice == 'Y')
      goto re;
    else
    return;
  }
  cout<<"\n\t\tBOOKING COUNTER";
  cout<<"\n\tEnter the train no.:\t"
  engine = get_data(engine);
}
char menu()
{
  char a;
  cout<<"\n\t\tMenu\n\t1. TrainList\n\t2. Booking\n\t3. Train Content\n\t4. Exit\nEnter Your choice:\t";
  cin>>a;
  return a;
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
             cout<<i+1<<". "<<obj[0].station_list[i]<<'\n';
          }
          break;
  case '2':for(int i=0; i<7; i++)
           {
             cout<<i+1<<". "<<obj[1].station_list[i]<<'\n';
           }
           break;
 case '3':for(int i=0; i<5; i++)
           {
             cout<<i+1<<". "<<obj[2].station_list[i]<<'\n';

           }
          break;
 case '4':for(int i=0; i<6; i++)
          {
              cout<<i+1<<". "<<obj[3].station_list[i]<<'\n';
          }
          break;
   case '5':for(int i=0; i<9; i++)
          {
            cout<<i+1<<". "<<obj[4].station_list[i]<<'\n';
          }
          break;
  default:printf(" please enter the correct choice\n");
 }
}

int main()
{
  // train obj[5];
  obj[0].station_list={{"UBL"},{"HVR"},{"RNR"},{"DVG"},{"ASK"},{"TK"},{"YPR"}};
  obj[1].station_list={{"UBL"},{"NGR"},{"GDG"},{"BDM"},{"BGK"},{"LMT"},{"BJPR"}};
  obj[2].station_list={{"UBL"},{"NGR"},{"GDG"},{"HRR"},{"BDM"},{"RRB"},{"BGK"}};
  obj[3].station_list={{"DWR"},{"LWR"},{"LD"},{"CLR"},{"QLM"},{"YG"},{"VSG"}};
  obj[4].station_list={{"UBL"},{"GDG"},{"BGK"},{"BJPR"},{"GLB"},{"VKB"},{"HYB"}};

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
