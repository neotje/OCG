#include <LinkedList.h>
#include "State.h"

#ifndef _STATEMACHINE_H
#define _STATEMACHINE_H

class StateMachine
{
  public:
    // Methods
    
    StateMachine();
    ~StateMachine();
    void init();
    void run();

    // When a stated is added we pass the function that represents 
    // that state logic
    void addState(State* state);
	State* transitionTo(State* s);
	int transitionTo(int i);
	
    // Attributes
    LinkedList<State*> *stateList;
    int currentState = -1;	//Indicates the current state number
};

StateMachine::StateMachine(){
  stateList = new LinkedList<State*>();
};

StateMachine::~StateMachine(){};

/*
 * Main execution of the machine occurs here in run
 * The current state is executed and it's transitions are evaluated
 * to determine the next state. 
 * 
 * By design, only one state is executed in one loop() cycle.
 */
void StateMachine::run(){
  //Serial.println("StateMachine::run()");
  // Early exit, no states are defined
  if(stateList->size() == 0) return;

  // Initial condition
  if(this->currentState == -1){
    transitionTo(0);
  }
  
  // Execute state logic and return transitioned
  // to state number. 

  Serial.println(currentState);
  int next = stateList->get(this->currentState)->execute();

  if (this->currentState != next) {
    transitionTo(next);
  }
}

/*
 * Adds a state to the machine
 * It adds the state in sequential order.
 */
void StateMachine::addState(State* state) {
  stateList->add(state);
  state->index = stateList->size()-1;
}

/*
 * Jump to a state
 * given by a pointer to that state.
 */
State* StateMachine::transitionTo(State* state){
  if (this->currentState != -1) {
    stateList->get(this->currentState)->exit();
  }

  Serial.print("From: ");
  Serial.print(this->currentState);
  Serial.print(" To: ");
  Serial.println(state->index);

  this->currentState = state->index;
  state->enter();
  return state;
}

/*
 * Jump to a state
 * given by a state index number.
 */
int StateMachine::transitionTo(int i){
  if(i < stateList->size()){
	transitionTo(stateList->get(i));
  }
  return this->currentState;
}

#endif
