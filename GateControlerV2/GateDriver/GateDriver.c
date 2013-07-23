/*
 * GateDriver.c
 *
 * Created: 23.07.2013 14:06:30
 *  Author: mlyasnikov
 */ 
#include "GateDriver.h"

volatile PtrGateState _currentState;

volatile PtrGateState _stateStoped;
volatile PtrGateState _stateClosed;
volatile PtrGateState _stateOpening;
volatile PtrGateState _stateOpened;
volatile PtrGateState _stateClosing;

inline void InitGateControler()
{
	CleanMem();
	
	_currentState = (PtrGateState)malloc(sizeof(PtrGateState));
	_currentState->type = Start;
	_currentState->action = &ProccedStart;
	
	_stateStoped = (PtrGateState)malloc(sizeof(PtrGateState));
	_stateStoped->type = Stoped;
	_stateStoped->action = &ProccedStart;
	
	_stateClosed = (PtrGateState)malloc(sizeof(PtrGateState));
	_stateClosed->type = Closed;
	_stateClosed->action = &ProccedStart;
	
	_stateOpening = (PtrGateState)malloc(sizeof(PtrGateState));
	_stateOpening->type = Opening;
	_stateOpening->action = &ProccedStart;
	
	_stateOpened = (PtrGateState)malloc(sizeof(PtrGateState));
	_stateOpened->type = Opened;
	_stateOpened->action = &ProccedStart;
	
	_stateClosing = (PtrGateState)malloc(sizeof(PtrGateState));
	_stateClosing->type = Closing;
	_stateClosing->action = &ProccedStart;
	
}

inline void ProccedGate(PtrGateCommand command)
{
	PtrGateStateArgs _args = (PtrGateStateArgs)malloc(sizeof(PtrGateStateArgs));
	_args->prevState = _currentState;
	
	_currentState->action(command,_args);
	
	if (_args->nextState != NULL)
		_currentState = _args->nextState;
	
	free(_args);
}

void ProccedStart(PtrGateState _currentState, PtrGateCommand _command, PtrGateStateArgs _args)
{
	if (_args->userData != NULL)
		_args->nextState = _stateClosed;
	else
	{
		_args->nextState = _stateStoped;
		_args->prevState = _stateClosing;
	}		
		
}

inline void CleanMem()
{
	if (_currentState != NULL)
		free(_currentState);
	if (_stateClosed != NULL)
		free(_stateClosed);
	if (_stateStoped != NULL)
		free(_stateStoped);
	if (_stateOpened != NULL)
		free(_stateOpened);
	if (_stateClosing != NULL)
		free(_stateClosing);
	if (_stateOpening != NULL)
		free(_stateOpening);
}