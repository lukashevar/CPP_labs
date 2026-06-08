#pragma once
#include "states/State.h"
#include <stack>
#include <memory>

class StateManager {
public:
	void push(std::unique_ptr<State> state);
	void pop();
	void change(std::unique_ptr<State> state);
	State* current();
	bool isEmpty() const;
private:
	std::stack<std::unique_ptr<State>> states;
};
