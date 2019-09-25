#include "DrunkardOwnedStates.h"
#include "MinerOwnedStates.h"
#include "Drunkard.h"
#include "Locations.h"
#include "Time/CrudeTimer.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "EntityNames.h"
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include <iostream>
using std::cout;

#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif

//-----------------------------------------------------------------------Global state

DrunkardGlobalState* DrunkardGlobalState::Instance()
{
	static DrunkardGlobalState instance;

	return &instance;
}


void DrunkardGlobalState::Execute(Drunkard* drunkie)
{
	//2 in 10 chance of heckling
	if ((RandFloat() < 0.2) && !drunkie->GetFSM()->isInState(*Heckle::Instance()))
		drunkie->GetFSM()->ChangeState(Heckle::Instance());
}

bool DrunkardGlobalState::OnMessage(Drunkard* drunkie, const Telegram& msg)
{
	SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	switch (msg.Msg)
	{
	case Msg_Enter:
	{
		cout << "\nMessage handled by " << GetNameOfEntity(drunkie->ID()) << " at time: "
			<< Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(drunkie->ID()) <<
			": Listen here you flyin' didgeridoo. Miner Bob is comin' here from the canyon!";
		if ((RandFloat() < 0.3))
			drunkie->GetFSM()->ChangeState(Heckle::Instance());
		else 
			drunkie->GetFSM()->ChangeState(StartingFights::Instance());
	}
	return true;

	}//end switch

	return false;
}

//-------------------------------------------------------------------------Drink

Drink* Drink::Instance()
{
	static Drink instance;

	return &instance;
}


void Drink::Enter(Drunkard* drunkie)
{
	if (!drunkie->Drinking())
	{
		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		cout << "\n" << GetNameOfEntity(drunkie->ID()) << ": Imma sippin' my good ol' whiskey now!";
		drunkie->SetDrinking(true);
	}
}


void Drink::Execute(Drunkard* drunkie)
{
	SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	switch (RandInt(0, 2))
	{
	case 0:

		cout << "\n" << GetNameOfEntity(drunkie->ID()) << ": Drinkin' on ice!";

		break;

	case 1:

		cout << "\n" << GetNameOfEntity(drunkie->ID()) << ": Drinkin' and pissin' me pantaloons...";

		break;

	case 2:

		cout << "\n" << GetNameOfEntity(drunkie->ID()) << ": Drinkin' and tellin' me favorite joke!";

		break;
	}
}

void Drink::Exit(Drunkard* drunkie)
{
}

bool Drink::OnMessage(Drunkard* drunkie, const Telegram& msg)
{
	return false;
}

//------------------------------------------------------------------------Heckle

Heckle* Heckle::Instance()
{
	static Heckle instance;

	return &instance;
}


void Heckle::Enter(Drunkard* drunkie)
{
	SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << "\n" << GetNameOfEntity(drunkie->ID()) << ": Time for some good ol' heckle!";
}


void Heckle::Execute(Drunkard* drunkie)
{
	SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	switch (RandInt(0, 2))
	{
	case 0:
		cout << "\n" << GetNameOfEntity(drunkie->ID()) << ": IMMA HECKLIN' THIS FELLA!";
		break;

	case 1:
		cout << "\n" << GetNameOfEntity(drunkie->ID()) << ": IMMA KICK THIS MAN'S BUTT";
		break;

	case 2:
		cout << "\n" << GetNameOfEntity(drunkie->ID()) << ": IMMA HIT ON THIS COOCOO'S WIFE";
		break;
	}
	SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
		drunkie->ID(),        //ID of sender
		ent_Miner_Bob,        //ID of recipient
		Msg_Annoyance,   //the message
		NO_ADDITIONAL_INFO);

	drunkie->GetFSM()->RevertToPreviousState();
}

void Heckle::Exit(Drunkard* drunkie)
{
	SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << "\n" << GetNameOfEntity(drunkie->ID()) << ": Damn outsiders! They're takin' our jobs!!";
	drunkie->SetDrinking(false);
}


bool Heckle::OnMessage(Drunkard* drunkie, const Telegram& msg)
{
	return false;
}


//------------------------------------------------------------------------StartingFights

StartingFights* StartingFights::Instance()
{
	static StartingFights instance;

	return &instance;
}


void StartingFights::Enter(Drunkard* drunkie)
{
	//If drinking, the drunkard will want to fight
	if (drunkie->Drinking())
	{
		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		cout << "\n" << GetNameOfEntity(drunkie->ID()) << ": Puttin' mah drink down an' cracking mah fists";
		drunkie->SetDrinking(false);
	}
}


void StartingFights::Execute(Drunkard* drunkie)
{
	SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << "\n" << GetNameOfEntity(drunkie->ID()) << ": Breakin' tables and faces";
	
	SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
		drunkie->ID(),        //ID of sender
		ent_Miner_Bob,        //ID of recipient
		Msg_Boast,   //the message
		NO_ADDITIONAL_INFO);
	drunkie->GetFSM()->RevertToPreviousState();
}

void StartingFights::Exit(Drunkard* drunkie)
{
	SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	cout << "\n" << GetNameOfEntity(drunkie->ID()) << ": Spittin' blood through mah broken teeth";
}


bool StartingFights::OnMessage(Drunkard* drunkie, const Telegram& msg)
{
	SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	switch (msg.Msg)
	{
	case Msg_StewReady:
	{
		cout << "\nMessage received by " << GetNameOfEntity(drunkie->ID()) <<
			" at time: " << Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		cout << "\n" << GetNameOfEntity(drunkie->ID()) << ": Victory for mah good self!";

		drunkie->GetFSM()->ChangeState(Drink::Instance());
	}

	return true;

	}//end switch

	return false;
}