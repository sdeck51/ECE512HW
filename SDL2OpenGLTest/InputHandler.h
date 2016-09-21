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
	InputHandler(Command* command, Command* command2) {
		buttonA_ = command;
		buttonQuit_ = command2;
	}

private:
	Command* buttonX_;
	Command* buttonY_;
	Command* buttonA_;
	Command* buttonB_;
	Command* buttonQuit_;
};

class JumpCommand : public Command
{
public:
	virtual void execute() { printf("JumpCommand"); }
};
class QuitCommand : public Command
{
	bool* quit;
public:
	QuitCommand(bool &_quit)
	{
		quit = &_quit;
	}
	virtual void execute() 
	{ 
		*quit = true; 
	}
};
