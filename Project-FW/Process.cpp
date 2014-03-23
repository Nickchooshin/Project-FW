#include "StdAfx.h"
#include "Process.h"
#include "ProcessType.h"

#include "Game.h"

extern Process* m_Process ;

void ChangeProcess(ProcessType cProcess)
{
	static int nProcess ;

	if(nProcess!=cProcess)
	{
		if(m_Process)
		{
			m_Process->Terminate() ;
			delete g_Process ;
			m_Process = NULL ;
		}

		switch(cProcess)
		{
		case pTeamLogo :
			//m_Process = new TeamLogo ;
			break ;
		case pTitle :
			//m_Process = new Title ;
			break ;
		case pGame :
			m_Process = new Game ;
			break ;
		}
		nProcess = cProcess ;

		if(m_Process)
			m_Process->Initialize();
	}
}