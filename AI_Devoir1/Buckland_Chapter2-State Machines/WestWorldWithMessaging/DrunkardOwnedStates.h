#ifndef DRUNKARD_OWNED_STATES_H
#define DRUNKARD_OWNED_STATES_H
//------------------------------------------------------------------------
//
//  Name:   DrunkardOwnedStates.h
//
//  Desc:   All the states that can be assigned to the Drunkard class
//
//  Author: Mike Heck 2019
//
//------------------------------------------------------------------------
#include "fsm/State.h"

class Drunkard;



//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class DrunkardGlobalState : public State<Drunkard>
{
private:

	DrunkardGlobalState() {}

	//copy ctor and assignment should be private
	DrunkardGlobalState(const DrunkardGlobalState&);
	DrunkardGlobalState& operator=(const DrunkardGlobalState&);

public:

	//this is a singleton
	static DrunkardGlobalState* Instance();

	virtual void Enter(Drunkard* drunkie) {}

	virtual void Execute(Drunkard* drunkie);

	virtual void Exit(Drunkard* drunkie) {}

	virtual bool OnMessage(Drunkard* drunkie, const Telegram& msg);
};


//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class Drink : public State<Drunkard>
{
private:

	Drink() {}

	//copy ctor and assignment should be private
	Drink(const Drink&);
	Drink& operator=(const Drink&);

public:

	//this is a singleton
	static Drink* Instance();

	virtual void Enter(Drunkard* drunkie);

	virtual void Execute(Drunkard* drunkie);

	virtual void Exit(Drunkard* drunkie);

	virtual bool OnMessage(Drunkard* drunkie, const Telegram& msg);

};



//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class Heckle : public State<Drunkard>
{
private:

	Heckle() {}

	//copy ctor and assignment should be private
	Heckle(const Heckle&);
	Heckle& operator=(const Heckle&);

public:

	//this is a singleton
	static Heckle* Instance();

	virtual void Enter(Drunkard* drunkie);

	virtual void Execute(Drunkard* drunkie);

	virtual void Exit(Drunkard* drunkie);

	virtual bool OnMessage(Drunkard* drunkie, const Telegram& msg);

};


//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class StartingFights : public State<Drunkard>
{
private:

	StartingFights() {}

	//copy ctor and assignment should be private
	StartingFights(const StartingFights&);
	StartingFights& operator=(const StartingFights&);

public:

	//this is a singleton
	static StartingFights* Instance();

	virtual void Enter(Drunkard* drunkie);

	virtual void Execute(Drunkard* drunkie);

	virtual void Exit(Drunkard* drunkie);

	virtual bool OnMessage(Drunkard* drunkie, const Telegram& msg);
};


#endif