
#include<iostream>
#include<iomanip>
#include<conio.h>
#include<string>
#include<fstream>
#include<stddef.h>
#include<process.h>

#define MAX_AGE    5
#define QSIZE      100
#define MAX_NODES  13  


using namespace std;
enum packet_type{hello, d, reply, lst};
typedef unsigned address;

unsigned total_neigh;
unsigned seq_nr = 0;

int central_port;
int outport[10];
int inport[10];
address SELF ;


int inputline[10];
int outputline[10];
int centralline;
address neighbour[10]={0,0,0,0,0,0,0,0,0,0};
bool active_line_flag[10];



class queue;
extern queue Qin, Qout,Qls, Qlsout;



//ROUTING TABLE
class routing_table
{
public:
	int line;
	int cost;
};

routing_table table[MAX_NODES+1];


//PACKET
class packet
{
public:
	packet_type type;
	address     source;
	address     dest;
    char        data[2];
	
    // for type LINK_STATE
	address     neighbour[10];
	int         age;
	int         line;  //output line before sending
	                   //input line after receving
	int         seq;

	
	void sendHELLO(void);
	void sendREPLY(void);
    void sendDATA(address a, char c);
	void forward(void);
    void sendLST(void);
	void handleLST(void);

};


class queue
{
	enum {unlocked, locked} status ;
	packet p[QSIZE];
	int f,r;
	
public:
	queue() {f=-1; r=-1; status = unlocked;}
	int insert(packet &pack);
    int retrieve(packet &pack);
    void showqueue(void);	
};





//PACKET functions


void packet::sendLST(void)
{
	int i;
	
	type = lst ;
	source = SELF;
	for(i=0; i<10; i++)
		neighbour[i] = ::neighbour[i];
	seq = (::seq_nr)++ ;
	age = MAX_AGE;
	Qls.insert(*this);
	
	
//	cout<<endl<<"Qls queue after sendLST ";
//	Qls.showqueue();
//  cout<<endl<<"flag 0 :"<<active_line_flag[0];
//	cout<<endl<<"flag 1 :"<<active_line_flag[1];
	
	for(i=0;i<10;i++)
	{
		if(active_line_flag[i])
		{
			line = i;
			Qlsout.insert(*this);
//			cout<<endl<<"Qlsout after sendLST ";
//			Qls.showqueue();
		}
	}
}


void packet::handleLST(void)
{
	
	if(age <= 0) 
		return; //Packet discarded

	if(source<=0 || source >= MAX_NODES)
	{
		cout<<"Invalid Link state packet : ";
		exit(0);
	}


	Qls.insert(*this);

//	cout<<endl<<"Qls queue after handleLST ";
//	Qls.showqueue();

	
	age--;
	
	int inputline = line;
	for(int i=0;i<10;i++)
	{
		if(active_line_flag[i])
		{
			if(i == inputline) continue;

			line = i;
			Qlsout.insert(*this);

//			cout<<endl<<"Qlsout after handleLST ";
//			Qls.showqueue();
		
		}
	}
}
	

void packet::forward(void)
{
	line = table[dest].line;
	Qout.insert(*this);
}

void packet::sendDATA(address a, char c)
{
	type   = d;
	source = SELF;
	dest   = a;
	data[0] = c;
	data[1] = '\0';
	line   = table[dest].line;
	Qout.insert(*this);
}

void packet::sendHELLO(void)
{
	type = hello;
	for(int i=0;i<10;i++)
	{
		if(!active_line_flag[i])
			continue;
		line   = i;
		Qout.insert(*this);
	}
}

void packet::sendREPLY(void)
{
	type = reply;
	source = SELF;
	                //send back to input line
	Qout.insert(*this);
}






//QUEUE functions


int queue::insert(packet &pack)
{
   while(status == locked) ;	
   
   status = locked;
	
   if(f>=QSIZE || r>=QSIZE || f<-1 || r<-1)
   {
	   cout<<endl<<"Error in queue logic "<<endl;
	   status = unlocked;
	   return 0;
   }	

   
	if(( (r+1)%QSIZE)  == f)
	{   status = unlocked;
		return 0;
	}
	
	if(f==-1)
	   f=0;

	r = (r+1)%QSIZE ;
	
	p[r] = pack;

   if(f>=QSIZE || r>=QSIZE || f<-1 || r < -1)
   {
	   cout<<endl<<"Error in insert queue operation logic "<<endl;
	   exit(0);
   }	
   
   status = unlocked;
   return 1;

}


int queue::retrieve(packet &pack)
{
   while(status == locked)
   {
	while(status == locked);
	Sleep(100);
   }
    
   status = locked;

   if(f>=QSIZE || r>=QSIZE || f<-1 || r < -1)
   {
	   cout<<endl<<"Error in queue logic "<<endl;
	   status = unlocked;
	   return 0;
   }
	
	if(f==-1)
	{   status = unlocked;
		return 0;
	}

	pack = p[f];

	if(f==r) {f=-1;r=-1;}
	else
		f=(f+1)%QSIZE;


	if(f>=QSIZE || r>=QSIZE || f<-1 || r < -1)
   {
	   cout<<endl<<"Error in retrive queue operation logic "<<endl;
	   exit(0);
   }

    status = unlocked;
	return 1;
}


void queue::showqueue(void)
{
	while(status == locked);

	status = locked;
	
	cout<<endl<<"f = :"<<f;
	cout<<endl<<"r = :"<<r;
	if(f == -1) { status = unlocked ;return; }
	
	unsigned i = f;
	while(i != r)
	{
		cout<<endl<<setw(5)<<p[i].source
			      <<setw(5)<<p[i].type
				  <<setw(5)<<p[i].line
				  <<setw(5)<<f
				  <<setw(5)<<r;
		i = (i+1)%QSIZE ;
	     
	}

	cout<<endl<<setw(5)<<p[i].source
			      <<setw(5)<<p[i].type
				  <<setw(5)<<p[i].line
				  <<setw(5)<<f
				  <<setw(5)<<r;

      if(f>=QSIZE || r>=QSIZE || f<-1 || r < -1)
	  {
	   cout<<endl<<"Error in show operation logic "<<endl;
	   exit(0);
	  }

	  status = unlocked;
}