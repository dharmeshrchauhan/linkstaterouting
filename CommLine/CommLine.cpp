// CommLine.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "CommLine.h"
#include "CommLineDlg.h"
#include "Packet.h"
#include "Status.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCommLineApp

BEGIN_MESSAGE_MAP(CCommLineApp, CWinApp)
	//{{AFX_MSG_MAP(CCommLineApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCommLineApp construction

CCommLineApp::CCommLineApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CCommLineApp object and other global declarations

CCommLineApp theApp;
/*defined in Status.h
enum COMMAND{ UP, DN, REPORT, SHUTDOWNN} command;
enum ACK    { ACKUP, ACKDN, ACKREP, ACKSHUTDOWN} ack;
*/

COMMAND command;
ACK     ack;
//VARIABLES TO STORE COMMAND LINE ARGUMENTS

unsigned long nAddress;
unsigned long delay;

UINT   hReadNC,     hWriteNC,
       hReadR1,     hWriteR1,
	   hReadR2,     hWriteR2;

UINT   nDelay;

CPacket pkt1, pkt2;

CEvent evAckDown1, evAckDown2,
       //evUp must be received by both waiting threads
	   //so manual reset is TRUE
       evUp(INFINITE, TRUE),      /*vShutDown(INFINITE, TRUE),*/
	   evAckUp1,   evAckUp2,
	   evAckShutDown1, evAckShutDown2;

CSyncObject * pevAckDown[2] = { &evAckDown1, &evAckDown2},
		//	* pevUp[2]      = { &evUp,       &evShutDown},
			* pevAckUp[2]   = { &evAckUp1,    &evAckUp2},
			* pevAckShutDown[2]
			= {&evAckShutDown1, &evAckShutDown2};

CMultiLock  mlAckDown(pevAckDown, 2),
        //    mlUp(pevUp,2),
			mlAckUp(pevAckUp,2),
			mlAckShutDown(pevAckShutDown,2);

CStatus    Status;

/////////////////////////////////////////////////////////////////////////////
// CCommLineApp initialization

BOOL CCommLineApp::InitInstance()
{
	
	UINT From1To2(void * dummy);
	UINT From2To1(void * dummy);
    void ParseCommandLine();

    ASSERT(command != SHUTDOWN);

	CWinThread * pThread1, *pThread2;
	
	ParseCommandLine(); 
	//if initial command is down wait until next command before running threads
	if(command == DOWN)
	{
		while(!_read(hReadNC, &command, sizeof(command)));
		pThread1 = AfxBeginThread(From1To2, NULL);
	    pThread2 = AfxBeginThread(From2To1, NULL);
	}

	else
	{
		pThread1 = AfxBeginThread(From1To2, NULL);
	    pThread2 = AfxBeginThread(From2To1, NULL);
		_read(hReadNC, &command, sizeof(command));	
	}

	while(1)
	{
		switch(command)
		{
		case UP: 
			Status.Set(UP);      //Set status
			evUp.SetEvent();      
			mlAckUp.Lock();
			evUp.ResetEvent();
			ack = ACKUP;
			_write(hWriteNC, &ack, sizeof(ack));
			break;

		case DOWN:               
			Status.Set(DOWN);
			//No events set as loop each time checks value of Status
			mlAckDown.Lock();
			ack = ACKDOWN;
			_write(hWriteNC, &ack, sizeof(ack));
			break;

		case SHUTDOWN:
			Status.Set(SHUTDOWN);
			//code sets evUp to awake the threads if previous command 
			//was DOWN
			evUp.SetEvent(); 
			mlAckShutDown.Lock();
			evUp.ResetEvent();
			ack = ACKSHUTDOWN;
			_write(hWriteNC, &ack, sizeof(ack));
			break; 
		}

		if(command == SHUTDOWN) //
			break;
		_read(hReadNC, &command, sizeof(command));
	}

	return FALSE;
}



UINT From1To2(void* dummy)
{
	while(1)
	{
		if(Status.Get() == DOWN)
		{
			evAckDown1.SetEvent();
			evUp.Lock();    // both UP and SHUTDOWN will set evUp
		}

		if(Status.Get() == SHUTDOWN) // Status may be changed from 
			                         // DOWN to SHUTDOWN
									 //i.e both ifs could be evaluated 
									 // true in some cases
		{
			evAckShutDown1.SetEvent();
			break;
		}
		if (!_read(hReadR1, &pkt1, sizeof(pkt1)))
		{
			AfxMessageBox("Error in reading");
			exit(0);
		}
//	    ASSERT(pkt1.m_Source > 0 && pkt1.m_Source < 10);
//		if(!(pkt2.m_Source > 0 && pkt2.m_Source < 100))
//			continue;
		Sleep(nDelay);
		if(!_write(hWriteR2, &pkt1, sizeof(pkt1)))
		{
			AfxMessageBox("Error in writing");
				exit(0);
		}
	}
	return 0;
}

UINT From2To1(void* dummy)
{
	while(1)
	{
		if(Status.Get() == DOWN)
		{
			evAckDown2.SetEvent();
			evUp.Lock();
		}

		if(Status.Get() == SHUTDOWN)
		{
			evAckShutDown2.SetEvent();
			break;
		}
		if(!_read(hReadR2, &pkt2, sizeof(pkt2)))
			AfxMessageBox("Error in pipe reading 2");
//This statement is added as there is error in pipe communication
//If source address goes out of range the packet is discarded and 
//is not forwarded
//		if(!(pkt2.m_Source > 0 && pkt2.m_Source < 100))
//			continue;
		Sleep(nDelay);
		_write(hWriteR1, &pkt2, sizeof(pkt2));
	}

	return 0;
}


void ParseCommandLine()
{ 
	ASSERT(__argc == 10);
	
	nAddress = atoi(__argv[1]);
	nDelay   = atoi(__argv[2]);
	command  = (COMMAND) atoi(__argv[3]);

	hReadNC  = atoi(__argv[4]);
	hWriteNC = atoi(__argv[5]);

	hReadR1  = atoi(__argv[6]);
	hWriteR1 = atoi(__argv[7]);
	
	hReadR2  = atoi(__argv[8]);
	hWriteR2 = atoi(__argv[9]);
}
