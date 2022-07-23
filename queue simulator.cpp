#include<iostream>
#include<conio.h>
#include<bits/stdc++.h>
using namespace std;
int capacity,hour=10,total=0,minute=0;
char type;
string period="am";
struct customer
 {
 int serial;
 int serv_time;
 int arr_time;
 int wait_time;
 string start_time;
 struct customer*next;
 };
 struct Head
 {
 int count;
 struct customer*front;
 struct customer*rear;
 }*head;
 struct history
 {
 string data;
 struct history* next;
 }*top;
 void push(string s)
 {
 struct history*newnode=new history;
 newnode->data=s;
if(top==NULL)
 {
 newnode->next=NULL;
 top=newnode;
 }
else
 {
 newnode->next=top;
 top=newnode;
 }
 }
 string int_to_string(int n)
 {
 ostringstream s;
 s<<n;
 return s.str();
 }
 void enqueue(int value)
 {
 struct customer* newnode=new customer;
newnode->serial=value;
newnode->next=NULL;
if(head->front==NULL&&head->rear==NULL)
head->front=head->rear=newnode;
else
 {
 head->rear->next=newnode;
 head->rear=newnode;
 }
 (head->count)++;
  }
  int dequeue(customer data[])
 {
if(head->front==NULL)
return 0;
int number=0;
struct customer* temp=head->front;
number=head->front->serial;
if(head->front==head->rear)
head->front=head->rear=NULL;
else
head->front=head->front->next;
delete temp;
(head->count)--;
if(minute<10)
data[number-1].start_time=int_to_string(hour)+":0"+int_to_string(minute)+period;
else
data[number-1].start_time=int_to_string(hour)+":"+int_to_string(minute)+period;
return number;
 }
void time(int m)
 {
int h=0;
while(m>=60)
 {
 h++;
 m=m-60;
 }
if(h<10)
cout<<"0"<<h;
else
cout<<h;
if(m<10)
cout<<":0"<<m;
else
cout<<":"<<m;
 }
int current_queue(customer data[])
 {
system("cls");
if(head->count==0)
 {
 cout<<"| No customers in the Queue! |\n";
 return 0;
 }
string period=" AM";
int j=head->front->serial;
int total=head->count;
cout<<" Number of customer in the Queue: "<<total<<endl;
cout<<"| Serial\t\tArrival time |\n";
while(1)
 {
if(total==0)
break;
if(data[j-1].arr_time>=720)
period=" PM";
cout<<"| Customer "<<j<<"\t\t ";
time(data[j-1].arr_time);
cout<<period<<" |\n";
j++;
total--;
 }

 }
void arrival(customer data[])
 {
int m,h=hour;
enqueue(total+1);
m=minute+(5+rand()%10);
if(m>=60)
 {
 h++;
 m=0;
 }
data[total].arr_time=h*60+m;
cout<<"\nCustomer "<<total+1<<endl;
cout<<"Arrival time ";
time(data[total].arr_time);
cout<<period<<"\n\n";
total++;
 }
int wait_time(customer data[],int i)
 {
int wait=abs(data[i].arr_time-((hour*60)+minute));
cout<<"Waited time ";
time(wait);
cout<<" min\n\n";
data[i].wait_time=wait;
return wait;
 }
void instruction()
{
cout<<"\t          *****Super Shop*****\n\n";
cout<<"Instructions: \n";
cout<<"\t # Simulation Keys.             \n";
cout<<"\t # A/a: Is for new Arrival.     \n";
cout<<"\t # S/s: Is for Service.         \n";
cout<<"\t # Q/q: Is for Check the Queue. \n";
cout<<"\t # Any: Stop Simulation Process. \n";
}
void call_history()
 {
if(top==NULL)
 {
cout<<"\n\nNo History Found!\n\n";
return;
 }
struct history* temp=top;
cout<<"\n\tCall history:\n";
while(temp!=NULL)
{
cout<<"\t| "<<temp->data<<" |\n";
temp=temp->next;
 }

 cout<<"\n\n";
 }
 void statistics(customer data[],int avg_service_time, int
avg_wait_time)
 {
int i=0,served_customer;
int served=dequeue(data);
if(served==1)
 {
 cout<<"\nNo Customer Served Today!\n\n";
 return;
 }
 if(served==0)
 served_customer=total;
 else
 served_customer=served-1;
 cout<<"| Customer\tArrival Time\tWaiting Time\tStartTime\tService Time |\n";
while(1)
 {
if(i==served_customer)
break;
cout<<"| Customer "<<i+1<<"\t ";
if(data[i].arr_time>=720)
period=" PM";
else
period=" AM";
 time(data[i].arr_time);
cout<<period<<"\t ";
 time(data[i].wait_time);
cout<<" min\t ";
cout<<data[i].start_time<<"\t ";
 time(data[i].serv_time);
cout<<" min |\n";
 i++;
 }
cout<<"Average Service Time: ";
time(avg_service_time/served_customer);cout<<" min\n";
cout<<"Average Waited Time: ";
time(avg_wait_time/served_customer); cout<<" min\n\n";
 }
 int main()
{
 head=new Head;
 head->count=0;
 head->front=NULL;
 head->rear=NULL;
 top=NULL;
 string sep=":";
 instruction();
 cout<<" \nEnter the maximum no. of customers(Capacity of Queue): ";
 cin>>capacity;
 int avg_wait_time=0,avg_serv_time=0;
 customer data[100];
 system("cls");
while(1)
 {
if(minute<10)
 sep=":0";
 else
 sep=":";
cout<<"\t\t\t| Current Time"<<hour<<sep<<minute<<period<<" |\n";
process:
cout<<"Press A for 'Arrival' \n ";
cout<<"Press S for 'Service' \n ";
cout<<"Press Q for 'Current Queue' \n ";
cout<<"Press any other key for 'More' \n\n ";
type=getch();
 if(type=='a' || type=='A')
 {
 if(head->count>=capacity)
 {
 system("cls");
 cout<<"| Queue is full! |\n";
 goto process;
 }
 arrival(data);
 minute+=10+rand()%15;
 }
 else if(type=='s' || type=='S')
 {
 if(head->count==0)
 {
 cout<<"\nNo customer left in the Queue!\n\n";
 goto process;
 }
 int number=dequeue(data);
 int service_time=5+rand()%20;
 cout<<"\nCustomer "<<number<<" served\n\n";
 data[number-1].serv_time=service_time;
 cout<<"Service time ";
 time(data[number-1].serv_time);
 cout<<" min\n";
 avg_wait_time+=wait_time(data,number-1);
 cout<<"Average wait time ";
 time(avg_wait_time/number);
 cout<<" min\n";
 avg_serv_time+=service_time;
 cout<<"Average service time ";
 time(avg_serv_time/number);
 cout<<" min\n";
 if(minute<10)
 sep=":0";
 else
 sep=":";
 if(number<10)
 push("Customer "+int_to_string(number)
 +" Call time: "+int_to_string(hour)
 +sep+int_to_string(minute)+period);
 else
 push("Customer "+int_to_string(number)
 +" Call time: "+int_to_string(hour)
 +sep+int_to_string(minute)+period);
 minute+=service_time;
 }
 else if(type=='q' || type=='Q')
 current_queue(data);
 else
 break;
 if(minute>=60)
 {
 hour++;
 minute=0;
 }
 if(hour>=12)
 {
 hour=1;
 period=" PM";
 }
 }
 while(1)
 {
 cout<<"\n 1. Call history\t2. Statistics\t 0.Exit\n";
 type=getch();
 if(type=='1')
 call_history();
 else if(type=='2')
 statistics(data,avg_serv_time,avg_wait_time);
 else
 break;
 }
 };
