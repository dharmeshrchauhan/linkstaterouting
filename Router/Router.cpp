#include <stdio.h>
#include "stdafx.h"
#include "Router.h"
#include "routing.h"
#include <conio.h>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//using namespace std;


void receive_input(void *dummy);
void negotiate_packets(void *dummy);
void del_notresponding_nodes(void *dummy);

void send_output(void *dummy);
void collectLST(void);
void update_table(void);



queue Qin, Qout,Qls, Qlsout;

const unsigned long PAUSE = 10000L;
const int n1 = 3;//12;
const int n2 = 6;//30;

bool  active_node_flag[MAX_NODES + 1];
bool  active_neighbour_flag[10] = {false, false, false, false, false,
                        false, false, false, false, false};
bool  lock = false;  // lock for routing table and LSTpacket
bool  neigh_lock = false;



packet *LSTpacket[500] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
                         ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
						 ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
						 ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
						 ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
						 ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
						 ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
						 ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
						 ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
						 ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
                         ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
                         ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
						 ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
						 ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
						 ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
						 ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
						 ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
						 ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
						 ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
						 ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
						 ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
                         ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
						 ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
						 ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
						 ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
						 ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
						 ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
						 ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
						 ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
						 ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
						 ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
                         ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
						 ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
						 ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
						 ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
						 ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
						 ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
						 ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
						 ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
						 ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
						 ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
                         ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
						 ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
						 ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
						 ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
						 ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
						 ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
						 ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
						 ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
						 ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL };


class forNController
{
	bool active_node_flag[13];
	bool active_line_flag[10];
	int  neighbour[13][10];
	int  line[13];
	int	 cost[13];
public:
	void load();
} ;


void forNController::load(void)
{
	int i, j;
	for(i=0; i<13; i++)
	{
		active_node_flag[i] = ::active_node_flag[i];
		if(!active_node_flag[i] && LSTpacket[i] != NULL)
			continue;
		for(j=0;j<10;j++)
		{
		
			if(LSTpacket[i] != NULL)
				neighbour[i][j] = LSTpacket[i]->neighbour[j];
		}

		line[i] = table[i].line;
		cost[i] = table[i].cost;
	}



}


/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

//using namespace std;

int _tmain(int argc, TCHAR* argv[])
{
	
	unsigned i, j;

    if( argc<5 || argc%2==0 )
	{
		cout<<"Error in command line argument number : ";
		cout<<argc;
	//	cout<<endl<<argv[0];
	//		<<endl<<argv[1];
	//	_getch(); _getch();
		exit(0);
	}
	
	SELF = atoi(argv[1]);        //address of this node
	
	
//GENERATE PORT NAMES	
	central_port = atoi(argv[2]);

	total_neigh = ((argc-3)/2);          //total immediate neighbours
	
		     
	for(i=3;i<(int)argc;i++)
	{
		if(i%2)
			inport[(i-1)/2 -1] = atoi(argv[i]);
		else
			outport[(i/2) - 2] = atoi(argv[i]);

	}

//************************************8	
//OPEN PORTS
	
//	centralline.Open(central_port, CFile::modeReadWrite);
	centralline = central_port;
	for(i=0;i<total_neigh;i++)
	{
		inputline[i] = inport[i];
		outputline[i] = outport[i];
		active_line_flag[i] = true;
	}
//*************************************

	for(i=0; i<=MAX_NODES; i++)
		
		active_node_flag[i] = false;

	


	_beginthread(del_notresponding_nodes, 0, NULL);
	
	if(_beginthread(receive_input, 0, NULL)==-1)
	{
		cout<<"Error! "<<endl;
		_getch(); _getch();
		exit(0);
	}
	_beginthread(negotiate_packets, 0, NULL);
	_beginthread(send_output, 0, NULL);

    packet p;

	forNController fnc;
	while(1)
	{
		p.sendHELLO();
        
		Sleep(PAUSE);

		p.sendLST();
         
				
		collectLST();

//		system("cls");
//		COORD coordScreen = { 0, 0 };    
//		SetConsoleCursorPosition( GetStdHandle(STD_INPUT_HANDLE), coordScreen );

		cout<<"SELF address : "<<SELF;
		
		cout<<endl<<endl<<"Link state packets received : "<<endl<<flush;
    	while(lock);
		lock = true;
		cout<<"Address  ";
		cout<<"Neighbours ";
		cout<<endl<<"----------------------------------------"<<endl<<flush;
		for(i=1; i<=MAX_NODES; i++)
		{
			if(LSTpacket[i] != NULL)
			{
    			cout<<i<<"        "<<flush;
				for(j=0; j<10; j++)
				{
					if( (*LSTpacket[i]).neighbour[j] != 0)
						cout<<" "<<(*LSTpacket[i]).neighbour[j]<<flush;
				}
				cout<<endl<<flush;
			}
		}
        cout<<endl<<"----------------------------------------"<<endl<<flush;	

		
		lock = false;

        
		update_table();
		
		while(lock);
		lock = true;
		
		cout<<endl<<"Routing table :";
		cout<<endl<<"Node line  cost";
		for(i=1; i<=MAX_NODES; i++)
		{
			if(table[i].line < 0)
				continue;
			cout<<endl<<i<<"      "<<neighbour[table[i].line]<<"      "<<table[i].cost;
			cout<<flush;
		}

//		cout<<flush;

		fnc.load();
		lock = false;
//		_write(centralline,((char*)&fnc, sizeof(forNController));
		cout<<endl<<endl;

	}   
 
	
   return 0;


}




class buf
{
public:
	packet p[10];
	bool frame_arrival[10];
	buf()
	{frame_arrival[0] = false; frame_arrival[1] = false;
	 frame_arrival[2] = false; frame_arrival[3] = false;
	 frame_arrival[4] = false; frame_arrival[5] = false;
	 frame_arrival[6] = false; frame_arrival[7] = false;
	 frame_arrival[8] = false; frame_arrival[9] = false;
	}
}buffer;



void receive_input(void *dummy)
{
	int i=0;
	//packet p;


	void wait_for_input(void *integer);

	for(i=0;i<10;i++)
		if(active_line_flag[i])
			_beginthread(wait_for_input, 0,(void *)i);
	while(1)
	{
		if(active_line_flag[i])
		{
            if(buffer.frame_arrival[i] == true)
			{
				buffer.p[i].line = i;
				if(!Qin.insert(buffer.p[i]))
					   cout<<"Buffer overflow";
				buffer.frame_arrival[i] = false;
			}
		}
		
		i = (i+1)%10;
	}
}



void wait_for_input(void *integer)
{
	int i = (int)integer;
	while(1)
	{
		while(buffer.frame_arrival[i]);
	
		if(_read(inputline[i], (char*)&buffer.p[i],sizeof(packet)))
		{
			::buffer.frame_arrival[i] = true;
			//cout<<endl<<"Packet received ";
		}

	}
}



void negotiate_packets(void *dummy)
{
	packet p;

	while(1)
	{
		if(Qin.retrieve(p))
		{
//			if( p.type== d && p.dest == SELF )
//				cout<<endl<<p.data ;
			
//			else if(p.type == d && p.dest != SELF)
//				p.forward();

 			if(p.type == hello)
				p.sendREPLY();
			
			else if(p.type == reply)
			{   
				while(::neigh_lock);
				neigh_lock = true;
				active_neighbour_flag[p.line] = true;
				if(p.source>0 && p.source <= MAX_NODES)
					neighbour[p.line] = p.source ;
				neigh_lock = false;
			}
			
			else if(p.type == lst) 
			{
				active_node_flag[p.source] = true;
				p.handleLST();							
			}
		}

	}

}


void send_output(void *dummy)
{
	packet p;
	
	while(1)
	{
		if(Qlsout.retrieve(p))
			_write (outputline[p.line],(char*)&p, sizeof(packet));
		bool l = 1;
  		l = Qout.retrieve(p);
		if(l)
			_write (outputline[p.line],(char*)&p, sizeof(packet));
	}
	

}



void collectLST(void)
{
	packet p;
	
	while(Qls.retrieve(p))
	{
		while(lock);

		lock = true;
		
		if(LSTpacket[p.source] == NULL)
		{
		    if( (LSTpacket[p.source]  = new packet) != NULL)
			   *(LSTpacket[p.source]) = p;
			else
				cout<<endl<<"Memory overflow ";
		}

		else if(LSTpacket[p.source]->seq < p.seq)
		{
			*(LSTpacket[p.source]) = p;
		}

		lock = false;

		//else discard packet
	}
}


enum status_type{temp, perm};     //temperory permanent

struct label_info
{
	status_type status;
	int cost;
	int line;
} ;


void update_table(void)
{
	label_info *LABEL[MAX_NODES + 1] ;

	address min_cost_node(label_info *LABEL[]);  //returns address of temperory
	                                             //node with minimum cost   

    unsigned  j;
	
	while(lock);
	lock = true;
	
	
	for(j=0; j<=MAX_NODES; j++)
	{
		if(LSTpacket[j] == NULL)
		{
			LABEL[j] = NULL;
			continue;
		}

		if( (LABEL[j] = new label_info) == NULL)
		{
			cout<<endl<<"Insufficiant memory";
			_getch(); _getch();
			exit(0);
		}

		LABEL[j]->status = temp;            //temperory
    	LABEL[j]->cost   = -1;
	}


   
     
	address cur = SELF ;
	address nbr;                //neighbour of cur;
	packet cur_node;

	
	LABEL[SELF]->cost = 0;
	LABEL[SELF]->line = -1;
		
		
	while(cur!=0)
	{

		cur_node = *LSTpacket[cur];           
        LABEL[cur]->status = perm ;         //permanent


		for(j=0; j<10; j++)
		{
			nbr = cur_node.neighbour[j];
			if( (nbr == 0) || (LABEL[nbr] == NULL) )
				continue;

			if(  
				 ( LABEL[nbr]  != NULL)    &&
			     (( LABEL[nbr]->cost  <  0) ||
				  ( LABEL[nbr]->cost  >  LABEL[cur]->cost + 1 ) )
			 
			   )
			
			{
				LABEL[nbr]->cost     =  LABEL[cur]->cost + 1;
				LABEL[nbr]->line     = (LABEL[cur]->line == -1)? 
                                        j: LABEL[cur]->line ;
			}
		}


		cur = min_cost_node(LABEL);
			
	}


	for(j=0; j<=MAX_NODES; j++)
	{
		if(LABEL[j] == NULL)
			table[j].line = -1;

		else
		{
			table[j].line = LABEL[j]->line;
			table[j].cost = LABEL[j]->cost;
		}
	}


	lock = false;

}



address min_cost_node(label_info *LABEL[])
{
	int minimum = 25;

	address node_addr = 0 ;

	for(int i=1; i<= MAX_NODES; i++)
	{
		if(LABEL[i] == NULL)
			continue;
		if(LABEL[i]->status == temp && LABEL[i]->cost >= 0
			&& minimum > LABEL[i]->cost)
		{
			minimum = LABEL[i]->cost;
			node_addr = i;
		}
	}

	return node_addr;
}


void del_notresponding_nodes(void* dummy)
{
	int i;
	void del_node_thread(void * addr);
	void del_neighbour_thread(void * line);

	for(i=1; i<=MAX_NODES +1; i++)
		if(i!=SELF)
			_beginthread(del_node_thread, 0, (void*)i);

	for(i=0; i<10; i++)
	  if(active_line_flag)
		_beginthread(del_neighbour_thread, 0, (void*)i);
}


void del_node_thread(void * node_addr)
{
	address a = (address) node_addr ;

	while(1)
	{
		Sleep( n2 * PAUSE );

		if(active_node_flag[a] == false  &&
		   LSTpacket[a]        != NULL)
		{
			while(lock);
			lock = true;
            
			while(::neigh_lock);
			
			neigh_lock = true;            // if node to be removed is neighbour
			                              //then neighbour entry is updated
			for(int i=0; i<10; i++)
				if(neighbour[i] == a)
					neighbour[i] = 0;
			neigh_lock = false ;
           
			
			delete LSTpacket[a];
			LSTpacket[a]  = NULL ;
			lock = false;
		}

		active_node_flag[a] = false;
	}
}

void del_neighbour_thread(void * line)
{
	int l = (int) line;

	while(true)
	{
		Sleep( n1 * PAUSE );

		if(active_neighbour_flag[l] == false)
		{
			while(neigh_lock);
			neigh_lock = true;
			::neighbour[l] = 0 ;

			neigh_lock = false;
		}

		active_neighbour_flag[l] = false;
	}
}
