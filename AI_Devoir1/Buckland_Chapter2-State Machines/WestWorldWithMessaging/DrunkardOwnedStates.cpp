#include "DrunkardOwnedStates.h"
#include "MinerOwnedStates.h"
#include "Drunkard.h"
#include "Locations.h"
#include "Time/CrudeTimer.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "EntityNames.h"

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
	//1 in 10 chance of starting a fight (provided he is not already fighting)
	if ((RandFloat() < 0.1) &&
		!drunkie->GetFSM()->isInState(*StartingFights::Instance()))
	{
		drunkie->GetFSM()->ChangeState(StartingFights::Instance());
	}
}

bool DrunkardGlobalState::OnMessage(Drunkard* drunkie, const Telegram& msg)
{
	SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	switch (msg.Msg)
	{
	case Msg_Annoyance:
	{
		cout << "\nMessage handled by " << GetNameOfEntity(drunkie->ID()) << " at time: "
			<< Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(drunkie->ID()) <<
			": Listen here you flyin' didgeridoo. Come down to da saloon if ye dare!";

		drunkie->GetFSM()->ChangeState(Drink::Instance());
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
	cout << "\n" << GetNameOfEntity(drunkie->ID()) << ": Imma sippin' my good ol' whiskey!";
}


void Drink::Execute(Drunkard* drunkie)
{
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
	cout << "\n" << GetNameOfEntity(drunkie->ID()) << ": Seein' some fellah I nevah seen befo'!";
}


void Heckle::Execute(Drunkard* drunkie)
{
	cout << "\n" << GetNameOfEntity(drunkie->ID()) << ": THIS IS OUR TOWN SCRUB! BEAT IT!";

	drunkie->GetFSM()->RevertToPreviousState();
}

void Heckle::Exit(Drunkard* drunkie)
{
	cout << "\n" << GetNameOfEntity(drunkie->ID()) << ": Damn outsiders! They're takin' our 'yobs!!";
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
		cout << "\n" << GetNameOfEntity(drunkie->ID()) << ": Crackling mah fists";
		drunkie->SetDrinking(false);
	}
}


void StartingFights::Execute(Drunkard* drunkie)
{
	cout << "\n" << GetNameOfEntity(drunkie->ID()) << ": Breakin' tables and faces";
}

void StartingFights::Exit(Drunkard* drunkie)
{
	SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	cout << "\n" << GetNameOfEntity(drunkie->ID()) << ": Spittin' blood through mah broken teeth";
}


bool StartingFights::OnMessage(Drunkard* drunkie, const Telegram& msg)
{
	SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	switch (msg.Msg)
	{
	case Msg_Boast:
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