#include<iostream>
#include<stdlib.h>
#include<ctime>
#include<stdio.h>

using namespace std;

class train
{
  struct cargo
  {
    int train_no;
    int boarding;
    int deboarding;
    int day;
    int month;
    int year;
    cargo *next;
    char content[20];
  };

  typedef cargo *CARGO;
  public:

  CARGO get_data(CARGO engine)
  {
    CARGO x = new_cargo();
    // time_t t = time(0);
    // struct tm * now = localtime(&t);
    // // cout<<now;
    // int day_t,day = now->tm_mday + 1;
    // int month_t,month = now->tm_mon + 1;
    // int year_t,year = now->tm_year + 1900;
    // yr:
    // cout<<"\n\tEnter the date of Journey";
    // cout<<"\n\tEnter the Year :";
    // cin>>year_t;
    // if(year_t<year || year_t>year+1)
    // {
    //   cout<<"INVALID INPUT";
    //   goto yr;
    // }
    // mnth:
    // cout<<"\n\tEnter the Month :";
    // cin>>month_t;
    // if (((year_t - year==0)&&(month_t<month)) || (month_t>12))
    // {
    //   cout<<"INVALID INPUT";
    //   goto mnth;
    // }
    // d:
    // cout<<"\n\tEnter the Day :";
    // cin>>day_t;
    // if (((month_t-month==0)&&(day_t<day))|| (day_t>31))
    // {
    //     cout<<"INVALID INPUT";
    //     goto d;
    // }
    // x->year = year_t;
    // x->month = month_t;
    // x->day = day_t;
    // cout<<"\n\tThe date of journey is: "<<x->day<<"/"<<x->month<<"/"<<x->year;
    cout<<"\n\tEnter the boarding station no.:\t";
    cin>>x->boarding;
    cout<<"\n\tYou have set "<<station_list[--x->boarding]<<" as boarding station";
    cout<<"\n\tEnter the deboarding station no.:\t";
    cin>>x->deboarding;
    cout<<"\n\tYou have set "<<station_list[--x->deboarding]<<" as deboarding station";
    // cout<<"\n\tEnter the content of the cargo:\t";
    // cin>>x->content;
    if (engine == NULL)
    {
      cout<<"hey";
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


  void display(CARGO engine)
  {
      if (engine == NULL)
      {
        cout<<"\n\tThere is no content!!";
        return;
      }
      CARGO temp = engine;
      while(temp == NULL)
      {
        cout<<"\n\tContent :"<<temp->content;
        cout<<"\n\tDeboarding station:"<<temp->deboarding<<'\n';
        temp=temp->next;
      }
  }


  CARGO sorting(CARGO engine,CARGO present)
  {
    cout<<"hi";
    CARGO temp,prev;
    if (engine->next == NULL)
    {
      if (engine->deboarding>present->deboarding)
      {
        cout<<"vain";
        present->next = engine;
        return present;
      }
    }
    temp =engine;
    while(temp==NULL)
    {
      cout<<"\t"<<temp->deboarding<<"\t";
      if(temp->deboarding>present->deboarding)
      {
        prev->next=present;
        present->next=temp;
      }
      prev= temp;
      temp = temp->next;
    }
    cout<<"vains";
    return engine;
  }

  CARGO engine;

  char station_list[7][5];
  int train_no;

};

train obj[5];

int a;
char menu();
void train_list();
void booking();

void train_content();

/*********************************************************
This function is used to display the sorted content of the
the freight train.
**********************************************************/
void train_content()
{
  int train_no_t;
  cout<<"\n\tEnter the train number whose content is to be displayed";
  cin>>train_no_t;
  for (int i=0; i<5; i++)
  {
    if (train_no_t == obj[i].train_no)
    {
      a=i;
      break;
    }
  }
  obj[a].display(obj[a].engine);
}


/*********************************************************
This function is allows the user to book the cargo
compartment of the freight train.
**********************************************************/
void booking()
{
  int train_no_t,i=0;
  // char choice;
  // re:
  // cout<<"\n\tDo you want to see train list ?(y/n)";
  // cin>>choice;
  // if(choice == 'y' || choice == 'Y')
    // train_list();
  // cout<<"\n\tGo to booking counter ?(y/n)";
  // cin>>choice;
  // if (choice == 'n' || choice == 'N')
  // {
    // cout<<"\n\tDisplay train list once more ?(y/n)";
    // cin>>choice;
    // if (choice == 'y' || choice == 'Y')
      // goto re;
    // else
    // return;
  // }
  cout<<"\n\t\tBOOKING COUNTER";
  train_no:
  cout<<"\n\tEnter the train no.:\t";
  cin>>train_no_t;
  for (i=0; i<5; i++)
  {
    // cout<<obj[i].train_no<<" "<<train_no_t;
    if(obj[i].train_no == train_no_t)
    {
      a=i;
      break;
    }
  }
  if (a!=i)
  {
    cout<<"\n\tINVALID INPUT";
    goto train_no;
  }
  obj[a].engine = obj[a].get_data(obj[a].engine);
}

/*********************************************************
This function is used to display the main MENU of the
program.
**********************************************************/
char menu()
{
  char a;
  cout<<"\n\t\tMenu\n\t1. TrainList\n\t2. Booking\n\t3. Train Content\n\t4. Exit\nEnter Your choice:\t";
  cin>>a;
  return a;
}

/*********************************************************
This function is used to display the available freight
train.
**********************************************************/
void train_list()
{
 char choice;

 printf("\n\t\tList Of Trains \n1.UBL-YPR - 18048 \n2.UBL-BJPR - 12245\n3.UBL-BGK - 12246 \n4.UBL-GOA  - 22864\n5.UBL-HYB - 12864\n");
 printf("\nEnter Your choice:\t");
 scanf(" %c",&choice);
 switch(choice)
 {
 case '1':for(int i=0; i<7; i++)
          {
             cout<<i+1<<". "<<obj[0].station_list[i]<<'\n';
          }
          break;
  case '2':for(int i=0; i<7; i++)
           {
             cout<<i+1<<". "<<obj[1].station_list[i]<<'\n';
           }
           break;
 case '3':for(int i=0; i<7; i++)
           {
             cout<<i+1<<". "<<obj[2].station_list[i]<<'\n';

           }
          break;
 case '4':for(int i=0; i<7; i++)
          {
              cout<<i+1<<". "<<obj[3].station_list[i]<<'\n';
          }
          break;
   case '5':for(int i=0; i<7; i++)
          {
            cout<<i+1<<". "<<obj[4].station_list[i]<<'\n';
          }
          break;
  default:printf(" please enter the correct choice\n");
 }
}


int main()
{
  /*********************************************************
  here we are defining the train nos. which are availabe in
  the program.
  **********************************************************/
  obj[0].train_no=18048;
  obj[1].train_no=12245;
  obj[2].train_no=12246;
  obj[3].train_no=22864;
  obj[4].train_no=12864;
  // train obj[5];
  char stnt_list_t4[7][5]={{"UBL"},{"NGR"},{"GDG"},{"BDM"},{"BGK"},{"LMT"},{"BJPR"}};
  // char stnt_list_t1={{"UBL"},{"NGR"},{"GDG"},{"BDM"},{"BGK"},{"LMT"},{"BJPR"}};
  //a=4;
  //while (a)
  //{
	  //int i,j;
	  for(int i=0 ;i<7 ; i++)
	  {

		  for(int j=0 ; j<5 ;j++)
		  {
			  obj[1].station_list[i][j]=stnt_list_t4[i][j];//{{"UBL"},{"NGR"},{"GDG"},{"BDM"},{"BGK"},{"LMT"},{"BJPR"}};
		  }
	  }
	  //--a;
  //}
  char stnt_list_t1[7][5] ={{"UBL"},{"HVR"},{"RNR"},{"DVG"},{"ASK"},{"TK"},{"YPR"}};
  // obj[0].station_list={{"UBL"},{"HVR"},{"RNR"},{"DVG"},{"ASK"},{"TK"},{"YPR"}};
  //a=5;
  //while (a)
  //{
    for (int i=0; i<7; i++)
    {
      for (int j=0; j<5; j++)
      {
        obj[0].station_list[i][j]=stnt_list_t1[i][j];//{{"UBL"},{"NGR"},{"GDG"},{"BDM"},{"BGK"},{"LMT"},{"BJPR"}};
      }
    }
    //--a;
  //}
  char stnt_list_t2[7][4]={{"UBL"},{"NGR"},{"GDG"},{"HRR"},{"BDM"},{"RRB"},{"BGK"}};
//  obj[2].station_list={{"UBL"},{"NGR"},{"GDG"},{"HRR"},{"BDM"},{"RRB"},{"BGK"}};
  //a=4;
  //while (a)
  //{
	  //int i,j;
	  for(int i=0 ;i<7 ; i++)
	  {

		  for(int j=0 ; j<5 ;j++)
		  {
			  obj[2].station_list[i][j]=stnt_list_t2[i][j];//{{"DWR"},{"LWR"},{"LD"},{"CLR"},{"QLM"},{"YG"},{"VSG"}};
		  }
	  }
	  //--a;
  //}
	  char stnt_list_t5[7][5]={{"UBL"},{"GDG"},{"BGK"},{"MGA"},{"DVG"},{"PNL"},{"GOA"}};
	//  obj[3].station_list={{"DWR"},{"LWR"},{"LD"},{"CLR"},{"QLM"},{"YG"},{"VSG"}};
	  //a=4;
  //while (a)
  //{
	  //int i,j;
	  for(int i=0 ;i<7 ; i++)
	  {
		  for(int j=0 ; j<5 ;j++)
		  {
			  obj[3].station_list[i][j]=stnt_list_t5[i][j];//{{"UBL"},{"GDG"},{"BGK"},{"BJPR"},{"GLB"},{"VKB"},{"HYB"}};
		  }
	  }
    char stnt_list_t3[7][5]={{"UBL"},{"GDG"},{"BGK"},{"BJPR"},{"GLB"},{"VKB"},{"HYB"}};
	//  obj[3].station_list={{"DWR"},{"LWR"},{"LD"},{"CLR"},{"QLM"},{"YG"},{"VSG"}};
	  //a=4;
  //while (a)
  //{
	  //int i,j;
	  for(int i=0 ;i<7 ; i++)
	  {
		  for(int j=0 ; j<5 ;j++)
		  {
			  obj[4].station_list[i][j]=stnt_list_t3[i][j];//{{"UBL"},{"GDG"},{"BGK"},{"BJPR"},{"GLB"},{"VKB"},{"HYB"}};
		  }
	  }
	  //--a
	  //}
  // obj[2].station_list={{"UBL"},{"NGR"},{"GDG"},{"HRR"},{"BDM"},{"RRB"},{"BGK"}};
  // obj[3].station_list={{"DWR"},{"LWR"},{"LD"},{"CLR"},{"QLM"},{"YG"},{"VSG"}};
  // obj[4].station_list={{"UBL"},{"GDG"},{"BGK"},{"BJPR"},{"GLB"},{"VKB"},{"HYB"}};

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
      case '3':train_content();
                break;
      case '4':exit(0);
                  break;
      default : cout<<"\n\n\t!!...INVALID INPUT...!!";
    }
  }
}
