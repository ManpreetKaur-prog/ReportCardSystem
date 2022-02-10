#include<conio.h>
#include<string.h>
#include<fstream>
#include<iostream>
using namespace std;

class report_card  //base class containing data members
{
	public:

	int rno;
	float M,C,P;


};

class student :protected report_card//Class used in project
{
     char name[50];
public:
    	void create_card()
    {
        cout<<"\nEnter the roll no. of student: ";
        cin>>rno;
        cout<<"Enter the name of student: ";
        cin>>name;
        cout<<"Enter the marks of student in mathematics: ";
        cin>>M;
        cout<<"Enter the marks of student in chemistry: ";
        cin>>C;
        cout<<"Enter the marks of student in physics: ";
        cin>>P;
        cout<<"\n\n\t\tDETAILS REGISTERED!!";
    }
    int retrno()//return roll no
    {
        return rno;
    }
    char * retname()//return student name
    {
    	return name;
	}
    void show_card();

};

void student::  show_card()//non-inline function
    {
        cout<<"-------------------------------------------\n";
        cout<<"Rno\tName\n";
        cout<<rno<<"\t"<<name;
        cout<<"\n\nMaths\t\tChemistry\t\tPhysics";
        cout<<"\n"<<M<<"\t\t"<<C<<"\t\t\t"<<P;
        cout<<"\n\n\t\t\tTotal: "<<(M+C+P);
        cout<<"\n\t\t\tPercentage: "<<(M+C+P)/3;
        char grade;
        if((M+P+C)/3>90)
            grade='S';
        else if ((M+P+C)/3>80)
            grade='A';
        else if ((M+P+C)/3>70)
            grade='B';
        else if ((M+P+C)/3>60)
            grade='C';
        else if ((M+P+C)/3>50)
            grade='D';
        else if ((M+P+C)/3>40)
            grade='E';
        else
            grade='F';
        cout<<"\n\t\t\tGrade: "<<grade;
        cout<<"\n-------------------------------------------";
    }
//Global stream for object
fstream fp;
student pr;
void write_card()
{
    fp.open("Card.dat",ios::out|ios::app);
    pr.create_card();
    fp.write((char *)&pr,sizeof(student));
    fp.close();
}
void display_card()
{
    int no,found=0;
    cout<<"\n\nPlease enter the roll no of student whose report card you want to see: ";
    cin>>no;
    fp.open("Card.dat",ios::in|ios::out);
    while(fp.read((char *)& pr,sizeof(student))&&found==0)
    {
        if(pr.retrno()==no)
        {
            pr.show_card();
            found=1;
        }
    }
    if(found==0)
        cout<<"\n\nRecord not found!";
        fp.close();
        getch();
}
void modify_card()
{
    int no,found=0;
    cout<<"Enter the roll of student whose report card you want to modify: ";
    cin>>no;
    fp.open("Card.dat",ios::in|ios::out);
    while(fp.read((char *)&pr,sizeof(student))&&found==0)
    {
        if((pr.retrno())==no)
        {
            pr.show_card();
            cout<<"\nPlease enter the new details of Report card"<<endl;
            pr.create_card();
            int pos=-1*(int)sizeof(pr);
            fp.seekp(pos,ios::cur);
            fp.write((char *)&pr,sizeof(student));
            cout<<"\n\nRECORD UPDATED!!";
            found=1;
        }
    }
    fp.close();
    if(found==0)
        cout<<"Record not found!!";
    getch();
}
void delete_card()
{
    int no;
    cout<<"Enter the rollno of student whose record you want to delete: ";
    cin>>no;
    fp.open("Card.dat",ios::in|ios::out);
    fstream fp2;
    fp2.open("Temp.dat",ios::out);
    fp2.seekg(0,ios::beg);
    while(fp.read((char *)&pr,sizeof(student)))
    {
        if(pr.retrno()!=no)
        {
            fp2.write((char *)&pr,sizeof(student));
        }
    }
    fp2.close();
    fp.close();
    remove("Card.dat");
    rename("Temp.dat","Card.dat");
    cout<<"\n\n\tRecord deleted! .... ";
    getch();
}
void admin_menu()
{
    system("cls");
    char ch2,ch3;
    char pass[50];
    char logpass[]="363338";
    cout<<"Enter password for access:\n\t";
    int p=0;
    do
    {
        pass[p]=getch();
        if(pass[p]!='\r')
            cout<<"*";
        p++;
    }while(pass[p-1]!='\r');
    pass[p-1]='\0';
    if(strcmp(logpass,pass)==0)
        {cout<<"\n\nAccess Granted!";
        getch();}
    else
    {
        cout<<"Wrong password!\nAccess Denied!!";
        getch();
        return;
    }
    system("cls");
    do
    {
    cout<<"\n\n\t\t.....Welcome Administrator.....";
    cout<<"\n\n\t\tREPORT CARD";
    cout<<"\n1.New entry";
    cout<<"\n2.Display";
    cout<<"\n3.Modify";
    cout<<"\n4.Delete";
    cout<<"\n5.Back to main menu";
    cout<<"\n\tPlease enter your choice: ";
    ch2=getche();
    getch();
    switch(ch2)
    {
    case '1':
        system("cls");
        write_card();
        getch();
        break;
    case '2':
        system("cls");
        display_card();
        break;
    case '3':
        system("cls");
        modify_card();
        break;
    case '4':
        system("cls");
        delete_card();
        break;
    case '5':
        break;
    default:
         cout<<"invalid choice!!";
        break;
    }
    cout<<"\nDo you wish to continue?(y/n);";
    ch3=getche();
    system("cls");
    }while(ch3!='n');
    getch();
}
void intro() // INTRODUCTION FUNCTION
{
     system("cls");

    cout << "\n\n\n\n\n\n\n\n\t\t\t\t\tREPORT CARD SYSTEM";
    cout<<"\n\t\t\t\t\t===================";
    cout << "\n\n\t\t\t\t\tMADE BY :36,33,38(IT)";
    cout<<"\n\t\t\t\t\t=====================";
    getch();

}
int main()
{
    char ch;
    intro();
    do
    {
        system("cls");
        cout<<"\n\n\n\tMAIN MENU";
        cout<<"\n\n\t01 Administrator";
        cout<<"\n\n\t02 Exit";
        cout<<"\n\n\tPlease enter your choice:";
        ch=getche();
        switch (ch)
        {
        case '1':
            cout<<"\n\n\n\tWelcome Administrator!";
            getch();
            admin_menu();
            break;
        case '2':
            exit(0);
            break;
        default:
            cout<<"\n\n\n\tInvalid choice!";
            getch();

        }
    }while(ch!='2');
}
