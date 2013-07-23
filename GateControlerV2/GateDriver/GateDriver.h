/*
 * GateDriver.h
 *
 * Created: 23.07.2013 14:06:18
 *  Author: mlyasnikov
 */ 


#ifndef GATEDRIVER_H_
#define GATEDRIVER_H_

//Gate Command
typedef enum 
{
	None,
	StarStop,
	Stop
	} *PtrGateCommand;

//gate states, info about sensor proceed within state action procedure
typedef enum
{
	Start,
	Opened,
	Closing,
	Closed,
	Opening,
	Stoped
	} *PtrGateStateEnum;

//Cross-state arguments
typedef struct
{
	PtrGateState prevState = NULL;
	PtrGateState nextState = NULL;
	void *userData;
} *PtrGateStateArgs;

//delegate ))) for state action
typedef void (*PtrStateAction)(PtrGateCommand, PtrGateStateArgs);

//state
typedef struct 
{
	PtrGateStateEnum type;
	PtrStateAction action;
	PtrGateState prevState;
} *PtrGateState;

void InitGateControler();
void ProccedGate(PtrGateCommand command);


#endif /* GATEDRIVER_H_ */