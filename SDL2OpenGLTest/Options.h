#pragma once

class Options 
{
	
public:
	bool quit;
	int win_height;
	int win_width;
	Options() 
	{
		quit = false;
		win_height = 480;
		win_width = 640;
	}
	void SetQuit(bool _quit);


};