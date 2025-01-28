#include "GameEngine.h"
#include <iostream>

namespace GE {
	GameEngine::GameEngine() {

	}
	GameEngine::~GameEngine() {

	}
	bool GameEngine::init() {
		//Initialise SDL video subsystem
		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			std::cerr << "Unable to initilise SDL! SDL error: " << SDL_GetError() << std::endl;
			return false;
		}

		//Set the OpenGL version for the program
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		//Set the type of profile which is core meaning modern OpenGL
		//Means no legacy features for backwards compatibility
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		//Create the window and frame features
		//In this case window has a fixed size and prepares windows for OpenGL to render into
		window = SDL_CreateWindow("SDL OpenGL", 50, 50, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		
		//Create window was creted
		if (window == nullptr) {
			//Display an error if window wasn't created
			//Could log the errors to a file or create more robust error handling
			//e.g give specific errors a number
			std::cerr << "Unable to create window! SDL error: " << SDL_GetError() << std::endl;

			//Return failure so caller can work out what to do
			return false;
		}
		//Creates the OpenGl context and links it tot the window object
		//Context represents OpenGL for program such as objects and drawing
		glContext = SDL_GL_CreateContext(window);

		//Check context object was created
		if (glContext == nullptr) {
			//Display error and return failure
			std::cerr << "SDL could not create GL context! SDL error: " << SDL_GetError() << std::endl;
			return false;
		}

		//Initialise GLEW. GLEW solves a problem with OpenGL on windows
		//as a default API supported by windows is 1.1 (from 1997)
		//GLEW binds latest extensions that can be used
		GLenum status = glewInit();

		//Check if GLEW initialised
		if (status != GLEW_OK) {
			std::cerr << "Error initialising GLEW! Error: " << glewGetErrorString(status) << std::endl;

			return false;
		}

		//Try to turn on VSync. Maybe this could be a parameter to the init method
		//rather than hard coded
		if (SDL_GL_SetSwapInterval(1) != 0) {
			std::cerr << "Warning: unable to set VSync! Error: " << SDL_GetError() << std::endl;

			return false;
		}

		//Got this far then must have been successful setting up SDL and OpenGL
		return true;
	}

	//A game would call this function to check if the user closed the window
	//resulting in a SDL_QUIT message
	bool GameEngine::keep_running() {
		//Need to do this to keep the event queue up to date
		SDL_PumpEvents();

		SDL_Event evt;

		//Check for quit event
		if (SDL_PeepEvents(&evt, 1, SDL_GETEVENT, SDL_QUIT, SDL_QUIT)) {
			//If the user quit program, then return false meaning
			//Don't keep running
			return false;
		}

		//Got this far means no quit event so keep running
		return true;
	}

	//Update method which updates game logic
	void GameEngine::update() {

	}

	//Draw method
	void GameEngine::draw() {
		glClearColor(0.329f, 0.584f, 0.929f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		SDL_GL_SwapWindow(window);
	}

	//Shutdown method closes OpenGL and SDL down
	//Will need to modify when we create additional objects
	void GameEngine::shutdown() {
		SDL_DestroyWindow(window);

		window = nullptr;

		SDL_Quit();
	}

	//Simple helper to set the text in the window title bar
	void GameEngine::setwindowtitle(const char* new_title) {
		SDL_SetWindowTitle(window, new_title);
	}

	//Simple helper function to display program information
	//Note it is seperate from the GameEngine class as it doesn't depend on it
	void display_info_message(const char* msg) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Basic Game Engine", msg, nullptr);
	}
}