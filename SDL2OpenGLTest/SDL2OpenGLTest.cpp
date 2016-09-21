// SDL2OpenGLTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL OpenGL, standard IO, and, strings

#include <SDL.h>
#include <SDL_opengl.h>
#include <gl\GLU.h>
#include <stdio.h>
#include <string>
#include "InputHandler.h"
#include "main.h"
#include "Options.h"
#include <iostream>
#include <fstream>
#include <glm\glm.hpp>
#include <vector>
#include "glm/ext.hpp"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

GLfloat vertices[][3] = { { -1.0, -1.0, -1.0 },{ 1.0, -1.0, -1.0 },{ 1.0, 1.0, -1.0 },{ -1.0, 1.0, -1.0 },{ -1.0, -1.0, 1.0 },{ 1.0, -1.0, 1.0 },{ 1.0, 1.0, 1.0 },{ -1.0, 1.0, 1.0 } };

GLfloat colors[][3] = { { 0.0, 0.0, 0.0 },{ 1.0, 0.0, 0.0 },{ 1.0, 1.0, 0.0 },{ 0.0, 1.0, 0.0 },{ 0.0, 0.0, 1.0 },{ 1.0, 0.0, 1.0 },{ 1.0, 1.0, 1.0 },{ 0.0, 1.0, 1.0 } };

bool stop = false;

std::vector<glm::vec3> vertex;
std::vector<glm::vec3> normal;
std::vector<glm::vec3> face;
std::vector<glm::vec3> face_normal;

GLuint index;

//InputHandler

//global quit application
//bool quit;

//Starts up SDL, creates window, and initializes OpenGL
bool init();

//Initializes matrices and clear color
bool initGL();

//Input handler
void handleKeys(unsigned char key, int x, int y);

//Per frame update
void update();

//Renders quad to the screen
void Render();

//Frees media and shuts down SDL
void close();

//Input processed here
void ProcessInput();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//OpenGL context
SDL_GLContext gContext;

//Render flag
bool gRenderQuad = true;

bool init()
{



	//Initialization flag
	bool success = true;

	//input handler

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Use OpenGL 2.1
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create context
			gContext = SDL_GL_CreateContext(gWindow);
			if (gContext == NULL)
			{
				printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Use Vsync
				if (SDL_GL_SetSwapInterval(1) < 0)
				{
					printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
				}

				//Initialize OpenGL
				if (!initGL())
				{
					printf("Unable to initialize OpenGL!\n");
					success = false;
				}
			}
		}
	}

	return success;
}

bool initGL()
{
	bool success = true;
	GLenum error = GL_NO_ERROR;

	//Initialize Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//Check for error
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		printf("Error initializing OpenGL! %s\n", gluErrorString(error));
		success = false;
	}

	//Initialize Modelview Matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Check for error
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		printf("Error initializing OpenGL! %s\n", gluErrorString(error));
		success = false;
	}

	//Initialize clear color
	glClearColor(0.f, 0.f, 0.f, 1.f);

	//Check for error
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		printf("Error initializing OpenGL! %s\n", gluErrorString(error));
		success = false;
	}

	return success;
}

void handleKeys(unsigned char key, int x, int y)
{
	//Toggle quad
	if (key == 'q')
	{
		gRenderQuad = !gRenderQuad;
	}
}

void update()
{
	//No per frame update needed
}

static GLfloat theta[] = { 0.0, 0.0, 0.0 };
static GLint axis = 2;

void polygon(int a, int b, int c, int d)
{
	glBegin(GL_POLYGON);
	glColor3fv(colors[a]);
	glVertex3fv(vertices[a]);
	glColor3fv(colors[b]);
	glVertex3fv(vertices[b]);
	glColor3fv(colors[c]);
	glVertex3fv(vertices[c]);
	glColor3fv(colors[d]);
	glVertex3fv(vertices[d]);
	glEnd();
}

void colorcube()
{
	printf("bunny coded up ya");
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < face.size(); i++) {
		
		//Vertices and Normals
		glVertex3f(vertex[face[i].x - 1].x, vertex[face[i].x - 1].y, vertex[face[i].x - 1].z);
		glNormal3f(normal[face_normal[i].x - 1].x, normal[face_normal[i].x - 1].y, normal[face_normal[i].x - 1].z);
		glVertex3f(vertex[face[i].y - 1].x, vertex[face[i].y - 1].y, vertex[face[i].y - 1].z);
		glNormal3f(normal[face_normal[i].y - 1].x, normal[face_normal[i].y - 1].y, normal[face_normal[i].y - 1].z);
		glVertex3f(vertex[face[i].z - 1].x, vertex[face[i].z - 1].y, vertex[face[i].z - 1].z);
		glNormal3f(normal[face_normal[i].z - 1].x, normal[face_normal[i].z - 1].y, normal[face_normal[i].z - 1].z);
	}
	glEnd();
	
}

void Render()
{
	//Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT);

	//Render quad
	if (gRenderQuad)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		glColor3f(0.75f, 0.0f, 1.0f);
		//glRotatef(45, 1.0, 0.0, 0.0);
		//glRotatef(45, 0.0, 1.0, 0.0);
		//glRotatef(theta[2], 1.0, 0.0, 1.0);
		//colorcube();
		glCallList(index);
		//printf("Drawing Grid\n");
		/*glBegin(GL_LINES);
		/*for (int i = 0; i < 17; i++) {
			//x line
			glVertex3f(-8, -2, i - 8);
			glVertex3f(8, -2, i - 8);
			//z line
			glVertex3f(i - 8, -2, -8);
			glVertex3f(i - 8, -2, 8);

			//printf("f %d %d %d\n", face[i].i, face[i].j, face[i].k);
		}
		glEnd();*/
		glFlush();
	}
}

void close()
{
	//Destroy window	
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

void loadModel(std::string path, std::vector<glm::vec3> &vertex_out, std::vector<glm::vec3> &vertex_normal_out, std::vector<glm::vec3> &face_out, std::vector<glm::vec3> &face_normal_out) {

	bool has_normal = false;

	FILE* file = fopen(path.c_str(), "r");

	if (file == NULL) {
		//printf("%s File not found", path);
		return;
	}
	char line_header[128];
	unsigned int i = 0;
	while (fscanf(file, "%s", line_header) != EOF)
	{
		
		//printf("%s", line_header);
		//printf("fileRead");
		if (strcmp (line_header, "v") == 0) {
			//printf("vert");
			glm::vec3 vertex;
			fscanf(file, " %f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			vertex_out.push_back(vertex);

			//printf("v %d %d %d\n", vertex_out[i].x, vertex_out[i].y, vertex_out[i].z);
			//i++;
		}
		else if (strcmp(line_header, "vn") == 0) {
			//printf("norm");
			has_normal = true;
			glm::vec3 normal;
			fscanf(file,  " %f %f %f\n", &normal.x, &normal.y, &normal.z);
			
			vertex_normal_out.push_back(glm::normalize(normal));
		}
		else if (strcmp(line_header, "f") == 0) {
			//printf("face");
			glm::vec3 face;
			if (has_normal)
			{
				glm::vec3 face_normal;
				fscanf(file, " %f//%f %f//%f %f//%f\n", &face.x, &face_normal.x, &face.y, &face_normal.y, &face.z, &face_normal.z);
				face_normal_out.push_back(face_normal);

				//printf("face: %d %d %d\n", face[j].i, face[j].j, face[j].k);

			}
			else {
				fscanf(file, "%f %f %f\n", &face.x, &face.y, &face.z);
				//std::cout << glm::to_string(face) << std::endl;
				
			}
			face_out.push_back(face);
		}
		
	}

	fclose(file);

	if (!has_normal) {
		//flat normals
		for (int i = 0; i < face_out.size(); i++) {
			//printf("DONT POST");
			//calculate normal per face and add to faces
			glm::vec3 a, b, c;
			a = vertex_out[face_out[i].x - 1];
			b = vertex_out[face_out[i].y - 1];
			c = vertex_out[face_out[i].z - 1];
			glm::vec3 cross = glm::normalize(glm::cross(a - c, b - c));
			//std::cout << glm::to_string(cross) << std::endl;
			vertex_normal_out.push_back(cross);
			glm::vec3 out;
			out.x = (float)i+1;
			out.y = (float)i+1;
			out.z = (float)i+1;
			face_normal_out.push_back(out);
			//std::cout << glm::to_string(out) << std::endl;
			//std::cout << glm::to_string(a-c) << std::endl;
			//std::cout << glm::to_string(b-c) << std::endl;
			//std::cout << glm::to_string(glm::normalize(cross_product)) << std::endl;
		}
	}
	index = glGenLists(1);
	glNewList(index, GL_COMPILE);
	colorcube();
	glEndList();
}


/*void ProcessInput() {
//Event handler
SDL_Event sdlEvent;

//Handle events on queue
while (SDL_PollEvent(&sdlEvent) != 0)
{
//User requests quit
if (sdlEvent.type == SDL_QUIT)
{
quit = true;
}
//Handle keypress with current mouse position
else if (sdlEvent.type == SDL_TEXTINPUT)
{
int x = 0, y = 0;
SDL_GetMouseState(&x, &y);
handleKeys(sdlEvent.text.text[0], x, y);
}
}

}*/


int main(int argc, char* args[])
{
	Options options;
	JumpCommand jump;
	QuitCommand quitH(options.quit);
	InputHandler input_handler(&jump, &quitH);

	//
	

	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else

	{
		GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat mat_shininess[] = { 50.0 };
		GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glShadeModel(GL_FLAT);

		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_DEPTH_TEST);
		glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		//glOrtho(-2.0, 2.0, -2.0, 2.0, -10.0, 10.0);
		gluPerspective(70, SCREEN_WIDTH / SCREEN_HEIGHT, 1, 100);
		glm::vec3 eye;
		eye.z = 2;
		glm::vec3 center;
		center.z = -1;
		glm::vec3 up;
		up.y = 1;
		gluLookAt(eye.x, eye.y, eye.z, center.x, center.y, center.z, up.x, up.t, up.z);
		/*if (w <= h)
		glOrtho(-2.0, 2.0, -2.0 * (GLfloat) h / (GLfloat) w,
		2.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
		else
		glOrtho(-2.0 * (GLfloat) w / (GLfloat) h,
		2.0 * (GLfloat) w / (GLfloat) h, -2.0, 2.0, -10.0, 10.0);*/

		glMatrixMode(GL_MODELVIEW);
		//Enable text input
		//SDL_StartTextInput();

		//load model
		loadModel("bunny.obj", vertex, normal, face, face_normal);
		printf("LEFT LOAD MODEL");

		std::cout << glm::to_string(vertex[0]) << std::endl;

		printf("we're a go\n");

		//While application is running
		while (!options.quit)
		{
			//Input
			//ProcessInput();
			input_handler.handleInput();
			//Logic
			//Logic();
			theta[axis] += 2.0;
			if (theta[axis] > 360, 0) theta[axis] -= 360;
			//Render quad
			Render();
			//Update screen
			SDL_GL_SwapWindow(gWindow);
		}

		//Disable text input
		//SDL_StopTextInput();
	}

	//Free resources and close SDL
	close();

	return 0;
}