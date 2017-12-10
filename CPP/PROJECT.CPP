#include<conio.h>
#include<iostream.h>
#include<fstream.h>
#include<stdio.h>
#include<process.h>
#include<string.h>
#include<dos.h>
#include<time.h>

class Rum;
class Patient
{
	public:
		int p_id;
		char p_name[10];
		char gender[10];
		char city[10];
		char address[50];
		char name_relative[30];
		double p_contact;

};

class doctor
{ private:
	  int yfe;
	  char name[30];
	  char quali[20];
	  double contact;
public:
	int d_id;
	char uniqueinit[10];
	void getdata_d();
	void putdata_d();


};

class Rum:public Patient
{
protected:
	  char type[10];
	  char ward[10];
	  int d,m,y;
public:
	int rno;
	void getdata();
	void putdata();
	void date();
};

class Bill: public Rum
{  	int nfdays,service,extra,total;
public:
	void amount();
	void display();

};
void Rum::date()
{
	int d, m, y ;
	struct date d1;
	getdate(&d1);          //Inbuilt function to display current
	d = d1.da_day ;       //date of the system
	m = d1.da_mon ;
	y = d1.da_year ;
	cout <<"System Date : "<<d<<"/" <<m <<"/" <<y;
}

void doctor::getdata_d()
{       cout<<"\t **************DOCTORS DETAILS***********"<<endl;
	cout<<endl<<" Enter Doctors id no :";
	cin>>d_id;
	cout<<endl<<"Enter Doctors name :";
	gets(name);
	cout<<endl<<"Give doctor unique initialize name: ";
	gets(uniqueinit);
	cout<<endl<<"Enter Doctors qualification :";
	gets(quali);
	cout<<endl<<"Enter doctor's no of  expeience";
	cin>>yfe;
	cout<<endl<<"Enetr contact number";
	cin>>contact;
}
void doctor::putdata_d()
{   cout<<endl<<" Enter Doctors id no :";
	cout<<d_id;
	cout<<endl<<" Doctors name :";
	cout<<name;
	cout<<endl<<"Doctor identification name: ";
	cout<<uniqueinit;
	cout<<endl<<" Doctors qualification :";
	cout<<quali;
	cout<<endl<<"Doctor's expeience";
	cout<<yfe;
	cout<<endl<<"Doctor's contact number";
	cout<<contact;

}

 void Rum::getdata()
{       cout<<"\t ***********PATIENT DETAILS************" <<endl;
	cout<<endl<<"Enetr Patient ID:";
	cin>>p_id;
	cout<<endl<<"Enter Patient Name : ";
	gets(p_name);
	cout<<endl<<"Enetr Patient Gender:  ";
	gets(gender);
	cout<<endl<<"Enter Relative name : ";
	gets(name_relative);
	cout<<"Enetr contac number:";
	cin>>p_contact;
	cout<<"Enter city :" ;
	gets(city);
	cout<<"Enter date of admission in dd/mm/yyyy format: ";
	cin>>d;
	cin>>m;
	cin>>y;
	cout<<endl;
	cout<<"\t ***************ROOM DETAILS*******************"<<endl;
	cout<<"Enter Ward \nA.ICU \nB.CCU \nC.NORMAL: \n";
	gets(ward);
	cout<<endl<<"Enter type of room :\n A.Private Room \n B.Semi-private room \n C.General room:"<<endl;
	gets(type);
	cout<<endl<<"Enter room  no:  ";
	cin>>rno;
	cout<<endl<<"Room Alloted ";


}


void Rum::putdata()
{
	cout<<endl<<endl<<endl<<"   PATEINT  DETAILS   : ";
	cout<<endl<<"Room Number : ";
	cout<<rno;
	cout<<endl<<"Type of Ward:";
	cout<<endl<<ward;
	cout<<endl<<"Type of Room:";
	cout<<type;
	cout<<endl<<"Date Of Admission  : ";
	cout<<d<<"-"<<m<<"-"<<y;
	cout<<endl<<"Patient  Name : ";
	cout<<p_name;
	cout<<endl<<"City : ";
	cout<<city;

}

void write()
{
		clrscr();
		Rum r;
		ofstream os;
		os.open("room.dat",ios::binary|ios::app);
		r.getdata();
		os.write((char*)&r,sizeof(r));
		os.close();

}
void write_d()
{
		clrscr();
		doctor d;
		int found=0;
		ofstream os;
		ifstream is;
		is.open("doc.dat",ios::binary|ios::in);
		os.open("doc.dat",ios::binary|ios::app);
		int did;
		char init[5];
	       cout<<"Enter Doctors identification no : ";
	       //	gets(init);
		cout<<endl<<init<<endl;
		while(is.read((char*)&d,sizeof(d)))
		{
			if(did==d.d_id)
		       //	if(strcmp(init,d.uniqueinit)==0)
			{
				d.putdata_d();
				found=1;
			}
		}
		if(found==0)
		{
			d.getdata_d();
			os.write((char*)&d,sizeof(d));
		}
		os.close();
		is.close();
		cout<<endl;
}


int search_name(char pname[])
{
	Rum r;
	int found=0;		         // room num to be checked out
	ifstream is;
	is.open("room.dat",ios::in|ios::binary);
	cout<<endl;
		while(is.read((char*)&r,sizeof(r)))
		{
			if( strcmp(pname,r.p_name)==0 )
			{       found=1;
				r.putdata();
			}
		}
	is.close();
	return found;
}
int search_room(int rmno)
{
	ifstream is;
	Rum r;
	int found=0;
	is.open("room.dat",ios::binary|ios::in);
	while(is.read((char*)&r,sizeof(r)))
		{
			if(rmno==r.rno)
			{
				found=1;
				r.putdata();
			}
		}
	is.close();
	return found;
}
void search()
{
	clrscr();
	int c,found1=0;              //found=for showing search result found or not.
	cout<<endl<<"   Search Patient Details   "<<endl<<endl<<endl;
	cout<<endl<<"1. Search By Name"<<endl<<endl;
	cout<<endl<<"2. Search By Room Num"<<endl<<endl<<endl;
	cout<<endl<<endl<<"Enter Your Choice : ";
	cin>>c;
	cout<<endl<<endl;
	switch(c)
	{

		case 1:
			char pname[10];
			cout<<endl<<endl<<"Enter Name To Be Searched : ";
			gets(pname);
			cout<<endl;
			found1=search_name(pname);
		break;
		case 2:
			int rmno;		         // room num to be checked out
			cout<<endl<<endl<<"Enter Room Number To Be Searched : ";
			cin>>rmno;
			cout<<endl;
			found1=search_room(rmno);
		break;
	 }
	 if(found1==0)
	 cout<<endl<<"Patient Not Found: ";
}


void modify()
{
	Rum r;
	int roomnum;
	ifstream is;
	is.open("room.dat",ios::binary);
	ofstream os;
	os.open("temp.dat",ios::binary|ios::in);
	cout<<endl<<"Enter The ROOM NUM To Be Modified : ";
	cin>>roomnum;
		while(is.read((char*)&r,sizeof(r)))
		{
			if(roomnum==r.rno)
			{
				r.getdata();
			}
		os.write((char*)&r,sizeof(r));
		}
	cout<<endl<<"Entries Modified"<<endl;
	is.close();
	os.close();
	remove("room.dat");
	rename("temp.dat","room.dat");
}


void read() // show all records to console
{
	cout<<"\n PAITIENT ROOM DETAILS"<<endl;
	Rum r;
	ifstream is;
	is.open("room.dat",ios::binary|ios::in);
	while(is.read((char*)&r,sizeof(r)))
	{
	   r.putdata();
	   cout<<endl<<endl<<endl;

	}
	is.close();

}
void read_d() // show all records to console
{
	cout<<" DOCTORS DETAILS"<<endl;
	doctor d;
	ifstream is;
	is.open("doc.dat",ios::binary|ios::in);
		while(is.read((char*)&d,sizeof(d)))
		{
		d.putdata_d();
		cout<<endl<<endl<<endl;
		}
	is.close();
}

//	delete function
void delet()
{
/*
to delete one record from middle is not poosible is c / c++
thus we apply a logic here
we call each record from file one by one
then check if that record is to deleted
if no then that record is copied/written to temporary file
if yes then that record is ignored and next record is called
once all records are copied den we
remove/ delete the old file
and rename the temporary file as the old file name.
*/
	Rum r;
	Patient p;
	int roomno;
	ifstream is;
	is.open("room.dat",ios::binary);
	ofstream os;
	os.open("temp.dat",ios::binary|ios::out);
	cout<<endl<<"Enter The ROOM NUM To Be deleted : ";
	cin>>roomno;
		while(is.read((char*)&r,sizeof(r)))
		{
			if(roomno!=r.rno)
			{
				os.write((char*)&r,sizeof(r));
			}
		 }
	cout<<endl<<"Entries deleted"<<endl;
	is.close();
	os.close();
	remove("room.dat");
	rename("temp.dat","room.dat");
}


void Bill::amount()
{
	cout<<endl<<"Enter No Of Days patient Admitted In The Hospital. : ";
	cin>>nfdays;
	cout<<"Enter The Service Charges: ";
	cin>>service;
	cout<<"Enter The Extra Charges if any: ";
	cin>>extra;
	cout<<endl<<"Patient Recipt";
	read();
	cout<<endl<<"Amount To Be Paid: ";
	total=(nfdays*service)+extra;
	cout<<total<<endl;

}

void main()
{
Rum r;
doctor d;
Bill b;
clrscr();
int ch;
char c='y';

while(c=='Y'||c=='y')
{
clrscr();
cout<<endl<<"*****************WELL COME****************  \n" ;
cout<<endl<<"*****************YASH HOSPITAL****************  \n";
cout<<endl<<"\n 1.Eneter Patient Details: " ;
cout<<endl<<"\n 2.Enter Doctor Dteails: " ;
cout<<endl<<"\n 3.Search Patient Record: ";
cout<<endl<<"\n 4.Modify Patient Record: ";
cout<<endl<<"\n 5.Delete Patient Record: ";
cout<<endl<<"\n 6.Print Bill: ";
cout<<endl<<"\n 7.Exit: ";
cout<<endl<<"\n Enter your choice: ";
cin>>ch;
switch(ch)
 {
		case 1:
			write();
			read();
			break;
		case 2:
			write_d();
			read_d();
			break;
		case 3:
			search();
			break;
		case 4:
			modify();
			break;
		case 5:
			delet();
			break;
		case 6:
			b.amount();
			break;
		case 7:
			exit(0);
			break;
 }

cout<<endl<<"\n Do You Want To Continue(y/n):\t";
 cin>>c;
}

getch();
}