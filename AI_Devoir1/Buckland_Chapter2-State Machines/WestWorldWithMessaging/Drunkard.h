#ifndef DRUNKARD_H
#define DRUNKARD_H
//------------------------------------------------------------------------
//
//  Name: Drunkard.h
//
//  Desc: class to implement the tavern's drunk slob.
//
//  Author: Mike Heck 2019
//
//------------------------------------------------------------------------

#include <string>

#include "fsm/State.h"
#include "BaseGameEntity.h"
#include "Locations.h"
#include "DrunkardOwnedStates.h"
#include "misc/ConsoleUtils.h"
#include "Miner.h"
#include "fsm/StateMachine.h"
#include "misc/Utils.h"



class Drunkard : public BaseGameEntity
{
private:

	//an instance of the state machine class
	StateMachine<Drunkard>* m_pStateMachine;

	location_type   m_Location;

	//is he presently drunk?
	bool            m_drinking;


public:

	Drunkard(int id) :m_Location(saloon),
		m_drinking(true),
		BaseGameEntity(id)

	{
		//set up the state machine
		m_pStateMachine = new StateMachine<Drunkard>(this);

		m_pStateMachine->SetCurrentState(Drink::Instance());

		m_pStateMachine->SetGlobalState(DrunkardGlobalState::Instance());
	}

	~Drunkard() { delete m_pStateMachine; }


	//this must be implemented
	void          Update();

	//so must this
	virtual bool  HandleMessage(const Telegram& msg);

	StateMachine<Drunkard>* GetFSM()const { return m_pStateMachine; }

	//----------------------------------------------------accessors
	location_type Location()const { return m_Location; }
	void          ChangeLocation(location_type loc) { m_Location = loc; }

	bool          Drinking()const { return m_drinking; }
	void          SetDrinking(bool val) { m_drinking = val; }

};

#endif
