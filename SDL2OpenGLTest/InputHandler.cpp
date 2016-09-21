#include "stdafx.h"
#include "InputHandler.h"

void InputHandler::handleInput()
{
	SDL_Event e;
	
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT)
		{
			buttonQuit_->execute();
			return;
		}
		switch (e.type) {
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym) {
					case SDLK_LEFT:
						printf("Boop");
						buttonA_->execute();
				}
		}
	}
}

