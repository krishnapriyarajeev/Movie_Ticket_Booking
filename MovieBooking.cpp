//   PHOENIX MOVIE TICKETING SOURCE CODE:
//   HEADER FILES USED:
  #include<fstream.h>
  #include<conio.h>
  #include<process.h>
  #include<string.h>
  #include<dos.h>
  #include<stdio.h>
  #include<ctype.h>
  #include<stdlib.h>
  #include<graphics.h>

//   GLOBAL VARIABLES:

  char ch;
  int i;
  int x;

  fstream fio;
  ofstream ofile;
  ifstream ifile;

//   GLOBAL FUNCTIONS:

  void menu();
  void displayall();

//   CLASSES USED:

   class admin
  {
    private:
    char pass[10];
    void modifym();
    void edit();
    void deletem();
    public:
    char mname[30];
    admin();
    char mlang[10];
    int mstars;
    int amt;
    int mprice;
    char mactor[50];
    char mdirector[20];
    char mdesc[50];
    void addm();
    void adminm();
    void displaym();
    void displaylang(char a[]);
    void displaystar();
  };

   admin a1;            //OBJECT OF CLASS ADMIN

   void admin::admin()   //CONSTRUCTOR OF ADMIN
  {
    strcpy(mname,"NOT ASSIGNED");
    strcpy(mlang,"NOT ASSIGNED");
    mstars=0;
    strcpy(mactor,"NOT ASSIGNED");
    strcpy(mdirector,"NOT ASSIGNED");
    strcpy(mdesc,"NOT ASSIGNED");
  }


   class user
  {
    public:
    user();
    int price;
    long int phone;
    int seatno;
    char mtemp[25];
    int mseat;
    int nseats;
    int tickno;
    int movtickno[50];
    int movseatno[50];
    void userm();
    void ucancel();
    void booking();
    int amtcal(int n);
    void seatmanage(int t);
    void ticketprint();
  };

  user u1;            //OBJECT OF CLASS USER

   void user::user()  //CONSTRUCTOR OF USER
  {
    for(i=0;i<50;i++)
    movtickno[i]=0;
    for(i=0;i<50;i++)
    movseatno[i]=0;
    tickno=4530;
    nseats=0;
    phone=0;
    price=0;
    seatno=1;
    mseat=100;
  }

 //   MEMBER FUNCTIONS OF ADMIN:

  void admin::adminm()
 {
   clrscr();
   strcpy(pass,"AKA");
   int op=1,i,co;
   char ch,a[10];
   clrscr();
   cout<<"\n\n\tAUTHENTICATION REQUIRED\n";
   cout<<endl;
     while(op<=3)
    {
      cout<<"\n\tEnter the password :";
      cout<<endl;
      cout<<endl;
      cout<<"\t\t";
	for(i=0;i<strlen(pass);i++)
      {
	ch=getch();
	if(ch==13)
	break;
	cout<<"*";
	a[i]=ch;
      }
       a[i]='\0';
	 if(strcmp(pass,a)==0)
	{
	  cout<<"\n\tACCESS GRANTED\n";
	  break;
	}
	 else
	{
	  cout<<"\n\tIncorrect password\n";
	  cout<<"\tNumber of chances left "<<3-op<<"\n";
	   if(op==3)
	   {
	     cout<<"\tACCESS DENIED\n";
	     delay(1000);
	     exit(0);
	   }
	}
	 op++;
    }
     clrscr();

    cout<<"\n\n\tWELCOME TO ADMIN MENU\n\n";

    cout<<"\tPlease enter choice to continue\n\n";

    cout<<"\t1.Add movies\n\n"
	<<"\t2.Modify movie\n\n"
	<<"\t3.Display available movies\n\n"
	<<"\t4.Go to main menu\n\n"
	<<"\t5.Exit\n\n";
    cin>>co;

     switch(co)
    {
      case 1:

       addm();
       break;

      case 2:

       modifym();
       break;

      case 3:

       displaym();
       break;

      case 5:

       exit(0);
       break;

      case 4:

       menu();
       break;

      default:
       cout<<"\n\tInvalid choice ";
       delay(500);
       adminm();
    }

 }  //END OF ADMIN MENU FUNCTION

  void admin::addm()
 {
   clrscr();
   char ch;
   cout<<"\n\nEnter the details of the movie\n";
   ofile.open("movie",ios::app|ios::binary);
    do
   {
     cout<<"\nMovie name:  ";
     gets(mname);
     cout<<"\nLanguage:  ";
     gets(mlang);
     cout<<"\nRating:  ";
     cin>>mstars;
     cout<<"\nDescription:  ";
     gets(mdesc);
     cout<<"\nActors:  ";
     gets(mactor);
     cout<<"\nDirector:  ";
     gets(mdirector);
     cout<<endl;
     ofile.write((char*)&a1,sizeof(a1));
     cout<<"\nMovie details added successfully\n";
     cout<<"\nDo you want to add more movies?(Y/N)\n";
     cin>>ch;
   }while(toupper(ch)=='Y');
   ofile.close();
   cout<<"\nRedirecting to admin menu \n";
   a1.adminm();
 }                    //END OF ADD MOVIES FUNCTION

  void admin::modifym()
 {
   clrscr();
   cout<<"\t\tMODIFYING DATA\n\n\n";
     do
    {
      cout<<"\t\t\tMENU"
	  <<"\n\n\n";
	gotoxy(10,5);
      cout<<"EDIT\n";
	gotoxy(10,6);
      cout<<"  E\n";
	gotoxy(20,9);
      cout<<"DELETE\n";
	gotoxy(20,10);
      cout<<"  D\n";
	gotoxy(30,13);
      cout<<"ADD\n";
	gotoxy(30,14);
      cout<<"  A\n";
	gotoxy(40,17);
      cout<<"ADMIN'S MENU\n";
	gotoxy(40,18);
      cout<<"  M\n";
      cout<<"\t\tEnter your choice.\n\n\t\t";
      cin>>ch;

      if(ch=='E'||ch=='e')
	 edit();

      else

      if(ch=='D'||ch=='d')
	 deletem();

      else

      if(ch=='A'||ch=='a')
	 addm();

      else

      if(ch=='M'||ch=='m')
	 adminm();

      cout<<"\t\tDo you want to continue?(Y/N)\n\n";
      cin>>ch;
      clrscr();
    }while(toupper(ch)=='Y');
 }                           //END OF MODIFY FUNCTION

  void admin::edit()
 {
   clrscr();
   long pos;
   char edstr[30];
   int edrate;
   int n;
   int rec_count=0;
   char found='N';
   displayall();
  cout<<"Enter the movie number to be edited\n\n";
      cin>>x; //Movienumber
       clrscr();
	cout<<"\t\t\tMENU:\n\n";
	cout<<"\tA. MOVIENAME\n\n"
	    <<"\t  B. MOVIELANGUAGE\n\n"
	    <<"\t    C. RATING\n\n"
	    <<"\t      D. DESCRIPTION\n\n"
	    <<"\t        E. ACTORS\n\n"
	    <<"\t          F. DIRECTOR\n\n";
	cout<<"Enter your choice.\n\n";
	cin>>ch;
	toupper(ch);
	i=1;
	fio.open("movie",ios::out|ios::in|ios::binary);
	fio.seekg(0);
      while(fio)
     {   fio.read((char*)&a1,sizeof(a1));
	 if(x==i)
	{
	  found='Y';
	  cout<<"Enter the new details.\n\n";
	   switch(ch)
	  {
	    case 'A':

		 cout<<"MOVIE NAME (Enter '*' to retain old one)\n";
		 gets(edstr);
		 if(strcmpi(edstr,"*")==0)
			goto l;
		 else
			strcpy(mname,edstr);
		 fio.seekg(rec_count*sizeof(admin),ios::beg);
		 fio.write((char*)&a1,sizeof(a1));
		 break;

	    case 'B':

		cout<<"MOVIE LANGUAGE  (Enter '*' to retain old one)\n";
		gets(edstr);
		if(strcmpi(edstr,"*")==0)
			goto l;
		else
			strcpy(mlang,edstr);
		fio.seekg(rec_count*sizeof(admin),ios::beg);
		fio.write((char*)&a1,sizeof(a1));
		break;

      case 'C':

		cout<<"RATING (Enter '6' to retain old one)\n";
		cin>>edrate;
		if(edrate==6)
			goto l;
		else
			mstars=edrate;
		fio.seekg(rec_count*sizeof(admin),ios::beg);
		fio.write((char*)&a1,sizeof(a1));
		break;

      case 'D':

		cout<<"MOVIE DESCRIPTION (Enter '*' to retain old one)\n";
		gets(edstr);
	      if(strcmpi(edstr,"*")==0)
		goto l;
	      else
	      strcpy(mdesc,edstr);
	       fio.seekg(rec_count*sizeof(admin),ios::beg);
	       fio.write((char*)&a1,sizeof(a1));
	      break;

      case 'E':

		cout<<"MOVIE ACTORS (Enter '*' to retain old one)\n";
	      gets(edstr);
	      if(strcmpi(edstr,"*")==0)
		      goto l;
	      else
		      strcpy(mactor,edstr);
	       fio.seekg(rec_count*sizeof(admin),ios::beg);
	       fio.write((char*)&a1,sizeof(a1));
	      break;

      case 'F':

	      cout<<"MOVIE DIRECTOR (Enter '*' to retain old one)\n";
	      gets(edstr);
	      if(strcmpi(edstr,"*")==0)
		      goto l;
	      else
		      strcpy(mdirector,edstr);
	      fio.seekg(rec_count*sizeof(admin),ios::beg);
	      fio.write((char*)&a1,sizeof(a1));
	      break;

      default :
	      cout<<"Invalid choice!!!!!\n";
	      goto l;

     }
       cout<<"EDITING";
       for(i=0;i<5;i++)
      {
	delay(100);
	cout<<".";
      }
      clrscr();
      if(toupper(found)=='Y')
	cout<<"\n\n\tRECORD FOUND AND UPDATED\n\n";
      else
	cout<<"\n\n\tRECORD NOT FOUND\n\n";

   }
   rec_count++;
clrscr();
l:
	cout<<"\n\n\nIf you want to\n"
	<<"\nContinue editing - Press 'E'"
	<<endl
	<<"\ngo to modify menu - Press 'M'"
	<<endl
	<<"\nGo to admin's menu - Press 'A'"
	<<endl
	<<"\nDisplay movies _ Press 'D'"
	<<endl;
	cout<<"\nEnter your choice\n\n";
	cin>>ch;
	toupper(ch);
	switch(ch)
       {
	  case 'E':
			edit();
			break;

	  case 'M':
		     modifym();
		     break;

      case 'A':
		     adminm();
		     break;

     case 'D':
		     displayall();
		     break;

      default:
		      cout<<"Invalid choice";
		      break;

     }
     i++;
}
fio.close();
}                //END OF EDIT FUNCTION

void admin::deletem()
{
	 i=0;
	 int p;
	 char dname[30];
	 ifile.open("movie",ios::in|ios::binary);
	 ifile.seekg(0,ios::beg);
	 clrscr();
	 cout<<"\n\n\tShowing movies in phoenix\n\n\n";
	 while(ifile.read((char*)&a1,sizeof(a1)))
	 {
		  delay(200);
		  i++;
		  cout<<i<<". : ";
		  cout<<a1.mname;
		  cout<<endl;
		  cout<<endl;
	 }
	 ifile.close();
	 ifile.open("movie",ios::in|ios::binary);
	 ofile.open("temp",ios::out|ios::binary);
	 cout<<"\nEnter the movie number to be deleted\n";
	 cout<<endl;
	 cin>>x;
	 i=1;
	 while(ifile.read((char*)&a1,sizeof(a1)))
	 {
		if(i==x)
		{
			cout<<"Movie selected for deletion...\n";
			delay(100);
			cout<<"\n\tMOVIENAME: "<<a1.mname;
			  cout<<"\n\tMOVIELANGUAGE: "<<a1.mlang;
			  cout<<"\n\tRATING: "<<a1.mstars;
			  p=1;
			  cout<<"Are you sure you want to delete?(y/n)";
			  cin>>ch;
			  toupper(ch);
			  if(ch=='N')
			  {
				   clrscr();
				   gotoxy(40,5);
				   cout<<"Redirecting to modify menu\n";
				   for(i=0;i<10;i++)
				  {
				     delay(200);
				     cout<<'.';
				  }
			  modifym();
			 }
			if(ch=='Y')
			cout<<"MOVIE SUCCESSFULLY DELETED \n\n";
	  }
	  else
		  ofile.write((char*)&a1,sizeof(a1));
	i++;
 }

 if(p!=1)
 {
	  cout<<"Wrong movie number\n\n ";
	  delay(900);
	  cout<<"Returning......\n\n";
	  delay(200);
	  modifym();
 }
 ifile.close();
 ofile.close();
 remove("movie");
 rename("temp","movie");
 ifile.open("movie",ios::in|ios::binary);
 clrscr();
 cout<<"movies still available\n\n";
 delay(100);
 displayall();
 cout<<"Redirecting to admin menu\n\n";
 getch();
 adminm();
}

void admin::displaym()
{
 char c1;
 int ch;
 char z[10];
 do
 {
 cout<<"Please select display movies according to"
     <<"\n1.Language"
     <<"\n2.Rating"
     <<"\n3.All\n";
 cin>>ch;

  switch(ch)
 {
  case 1:
  {
   cout<<"Movie languages available"
       <<"\n1.English"
       <<"\n2.Malayalam"
       <<"\n3.Hindi\n"
       <<"\n4.tamil\n";
   cout<<"\nEnter the language\n";
   gets(z);
   displaylang(z);
  }
   break;

  case 2:
    displaystar();
  break;

  case 3:
   displayall();
   break;

  default:
  cout<<"\nInvalid choice";


 }
  cout<<"\nDo you want to display more\n(Y/N)";

  cin>>c1;

 }while(c1=='y'||c1=='Y');
   menu();
 getch();
 }
 void admin::displaylang(char q[10])
 {
   ifile.open("movie",ios::app|ios::in|ios::binary);
   while(ifile.read((char*)&a1,sizeof(a1)))
  {
   if(strcmpi(a1.mlang,q)==0)
   cout<<a1.mname;
   cout<<endl;
  }
   ifile.close();
 }

 void admin::displaystar()
 {
ifstream  gfile;

 for(i=5;i>=1;--i)
 {
    gfile.open("movie",ios::in|ios::binary);

   while(gfile)
   {
   gfile.read((char*)&a1,sizeof(a1));
   if(a1.mstars==i)
    { cout<<a1.mname;
     cout<<endl;
    }
   }
   gfile.close();
 }

}


 void displayall()
{ admin a1;
i=1;
ifstream fin;
fin.open("movie",ios::in|ios::binary);
fin.seekg(0,ios::beg);
while(fin.read((char*)&a1,sizeof(a1)))
{
  cout<<i<<". :  ";
   i++;
 cout<<"\nMOVIENAME: "<<a1.mname;
 cout<<"\t\tMOVIE LANGUAGE: "<<a1.mlang;
 cout<<"\nRATING: "<<a1.mstars;
 cout<<"\t\tDIRECTOR: "<<a1.mdirector;
 cout<<"\n\t\tDESCRIPTION: "<<a1.mdesc;
 cout<<"\n";
}
 getch();
 fin.close();

}                //END OF FUNCTION DISPLAY ALL

//   MEMBER FUNCTIONS OF USER:

  void user::userm()
 {
   clrscr();
   cout<<"\n\n\tWELCOME TO USER MENU\n";
   cout<<"\n\tPlease enter choice to continue\n";
   cout<<"\n\t1.Display movies\n"
       <<"\n\t2.Book ticket\n"
       <<"\n\t3.Cancel booking\n"
       <<"\n\t4.Go to main menu\n"
       <<"\n\t5.Exit\n\n";
   cin>>x;

     switch(x)
    {
      case 1:
      a1.displaym();
      break;

      case 2:
      u1.booking();
      break;

      case 3:
      u1.ucancel();
      break;

      case 4:
       menu();
       break;

      case 5:
      cout<<"\nEXITING.....";
      delay(500);
      exit(0);

      default:
       cout<<"\n\tInvalid choice ";
       menu();
  }
 }                   //END OF FUNCTION USERM

 void user::seatmanage(int t)
{
 if(mseat-t>t)
 {
  cout<<"\nREDIRECTING";
  delay(1000);
  for(int i=0;i<10;i++)
  cout<<".";

 cout<<"\n";
 cout<<mseat;
 cout<<" Seats available";
 cout<<"\n\nYour ticket numbers are";
 for(i=0;i<t;i++)
 {
 movtickno[i]=tickno;
 cout<<"\n";
 delay(500);
 cout<<movtickno[i];
 tickno++;
 }
 cout<<"\n\nYour seat no.s are";
 for(i=0;i<t;i++)
 {
 movseatno[i]=seatno;
 cout<<"\n";
 delay(500);
 cout<<movseatno[i];
 seatno++;
 }
 }
  else
  cout<<"\n\nhousefull";
  delay(700);
}              //END OF FUNCTION SEAT MANAGEMENT


void user::ticketprint()
{
 clrscr();
 ofile.open("ticket",ios::app|ios::binary);
 fio.open("movie",ios::in|ios::binary);
 fio.read((char*)&a1,sizeof(a1));
 fio.seekg(-sizeof(a1),ios::cur);
 cout<<"PHOENIX CINEMAS....";
 delay(500);
 seatmanage(nseats);
 delay(600);
 cout<<"\n\nPhone number: "<<phone;
 delay(500);
 cout<<"\n\nMovie selected: "<<a1.mname;
 delay(400);
 cout<<"\n\nMovie language: "<<a1.mlang;
 delay(300);
 cout<<"\n\nAmount payable: "<<price;
 ofile.write((char*)&u1,sizeof(u1));
 fio.close();
 ofile.close();
}

 int user::amtcal(int t)
 {
 int ch;
 int w;
 cout<<"\nChoose seat type"
     <<"\n1.Balcony"
     <<"\n2.Ordinary seats\n";
 delay(500);
 cout<<"\nEnter your choice\n";
 cin>>ch;
 if(ch==1)
 {
  w=t*200;
  cout<<"\nAmount payable: "<<w;
  }
 else
 {
  w=t*150;
  cout<<"\nAmount payable: "<<w;
  }
 return w;
}

  void user::booking()
 {
   char mtemp[25];
   char ch1;
  clrscr();
   cout<<"\n\n\tShowing all the available movies\n\n\n";
   displayall();
   ofile.open("ticket",ios::app|ios::binary);

     cout<<"\tEnter the movie name\n\t";
     cin>>mtemp;
     cout<<"\tEnter the number of seats\n\t";
     cin>>nseats;
     cout<<"\tEnter your phone number\n\t";
     cin>>phone;
     price=amtcal(nseats);
     cout<<"\n\tAre you sure you want to confirm your booking(Y/N)\n\t";
     cin>>ch1;

     if(ch1=='Y'||ch1=='y')
      ofile.write((char*)&u1,sizeof(u1));
     else
      userm();

    ofile.close();
    ticketprint();
 }

  void user::ucancel()
 {
   clrscr();
   int found=0;
   int tno;

   ifile.open("ticket",ios::in|ios::binary);
   ofile.open("temp",ios::out|ios::binary);

   cout<<"\n\n\t\tT I C K E T  C A N C E L L A T I O N\n\n\n";
   cout<<"Enter the ticket number to be cancelled\n\n";
   cin>>tno;
   cout<<endl;

   ifile.seekg(0,ios::beg);
   while(ifile.read((char*)&u1,sizeof(u1)))
  {
    cout<<"\tDo you wish to proceed?\n";
    cout<<"\tPress 1 to stop\n\n";
    gotoxy(20,10);
    cin>>i;
     if(i==1)
    {
      cout<<"\tREDIRECTING TO USER'S MENU\n\n";
       for(i=0;i<5;i++)
      {
	delay(200);
	cout<<".";
      }
       u1.userm();
    }

   if(tickno==tno)
    {
      found=1;
      cout<<"\tFOUND MOVIE\n\n";
      cout<<"\tBOOKING DETAILS:\n\n";
      ticketprint();
    }
     else
      ofile.write((char*)&u1,sizeof(u1));
  }
     if(found==1)
    {
      delay(1000);
      clrscr();
      cout<<"\n\n\tTICKET CANCELLING INITIALISED\n\n";
      delay(1000);
      cout<<"\n\n\tTICKET CANCELLATION SUCCESSFUL\n\n";
    }
     else
    {
      cout<<"\n\n\t TICKET NUMBER NOT FOUND\n\n";
      delay(1000);
      cout<<"\n\n\tTICKET CANCELLATION FAILED\n\n";
    }
      remove("ticket");
      rename("temp","ticket");
      delay(1000);
      cout<<"\n\n\tREDIRECTING TO USER'S MENU.......\n\n";
      delay(1000);
      u1.userm();
 }               //END OF TICKET CANCELLING

     //GLOBAL FUNCTIONS

  void menu()
 {
   clrscr();
   int z;
   gotoxy(20,5);
   textcolor(CYAN);
   cout<<"\tCONTINUE AS\n "
       <<"\t1.ADMIN\n"
       <<"\t2.USER\n"
       <<"\t3.EXIT\n";
   cin>>z;
    switch(z)
   {
     case 1:
     a1.adminm();
     break;

     case 2:
     u1.userm();
     break;

     case 3:
     cout<<"Exiting...";
     delay(500);
     exit(0);

     default:
   cout<<"\n\tInvalid choice\n";
   menu();
   }
  }

 void main()
 {
  clrscr();

  int i,j,k,l;
  //setbkcolor(15);
  //setcolor(0);
  for(i=1;i<=79;i++)
  {
   gotoxy(i,2);
   cout<<char(178);
   delay(10);
  }
   for(j=2;j<=22;j++)
  {
   gotoxy(1,j);
   cout<<char(178);
   delay(10);
  }
  for(k=1;k<=79;k++)
  {
   gotoxy(k,23);
   cout<<char(178);
   delay(10);
  }
  for(l=18;l>=2;l--)
  {
   gotoxy(i,2);
   cout<<char(178);
   delay(10);
  }
  textcolor(CYAN);
  gotoxy(25,6);
  for(i=0;i<30;i++)
  {
   cout<<"*";
  }
  cout<<endl;
  cout<<endl;
  gotoxy(28,9);
  textcolor(CYAN);
  cout<<"WELCOME TO OUR CINEMAS";
  cout<<endl;
  cout<<endl;
  gotoxy(25,12);
  for(i=0;i<30;i++)
  {
   cout<<"*";
   delay(100);
  }
 /*int gd = DETECT, gm;
  initgraph(&gd,&gm,"C:\\TC\\BGI");
  setcolor(2);
  settextstyle(TRIPLEX_SCR_FONT,HORIZ_DIR,3);
  setcolor(8);

  outtextxy(300,300,"WELCOME TO ");
  setcolor(4);
  outtextxy(300,320,"PHOENIX CINEMAS");

  for(i=0;i<600;i++)
  {
   setcolor(9);
   line(50+i,405,100+i,405);
   line(75+i,375,125+i,375);
   line(50+i,405,75+i,375);
   line(100+i,405,125+i,375);
   line(150+i,405,100+i,345);
   line(75+i,375,75+i,370);
   line(70+i,370,80+i,370);
   line(80+i,345,100+i,345);
   circle(150+i,405,36);
   circle(50+i,405,30);
   line(0,436,getmaxx(),436);
   rectangle(getmaxx()-i,436,650-i,431);
   delay(5000);

   cleardevice();
  }
 delay(1000);
 closegraph();
 */

 menu();

  getch();
 }
