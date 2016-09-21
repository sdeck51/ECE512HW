#pragma once
#include <SDL.h>

class Command
{
public:
	virtual ~Command() {}
	virtual void execute() = 0;
};

class InputHandler
{
public:
	void handleInput();

private:
	Command* buttonX_;
	Command* buttonY_;
	Command* buttonA_;
	Command* buttonB_;
};