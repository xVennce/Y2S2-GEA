#pragma once
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

namespace GE {
	class GameEngine {
	public:
		GameEngine();			//Constructor
		virtual ~GameEngine();	//Deconstructor

		bool init();			//Object initialisation
		bool keep_running();	//Indicates if user has closed window to end the game
		void update();			//This is where we update game logic
		void draw();			//This is called when the game is ending
		void shutdown();		//To release objects created during the game

		//extra methods
		void setwindowtitle(const char*);

	private:
		//private data
		//SDL window object to represent the frame
		SDL_Window* window;
		//SDL GL context to represent OpenGL in the program
		SDL_GLContext glContext;
	};
	void display_info_message(const char*);
}