#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

class Window
{
public:
	Window();
	Window(GLint widthWindow, GLint heightWindow);
	~Window();
	int Initialize();

	bool shouldClose() { return glfwWindowShouldClose(window); }
	void swapBuffers() { return glfwSwapBuffers(window); }

	GLfloat getBufferWidth() { return (GLfloat)bufferWidth; }
	GLfloat getBufferHeigth() { return (GLfloat)bufferHeigth; }

	bool * getKeys() { return keys; }
	GLfloat getXChange();
	GLfloat getYChange();


private:
	GLFWwindow* window;
	GLint width, height;
	int bufferWidth, bufferHeigth;

	//Callback de mouse e teclado
	void createCallbacks();

	//Configuração do teclado
	bool keys[1024];
	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);

	//Configuracao do Mouse
	bool mouseFirstMove;
	GLfloat lastX, lastY, xChange, yChange;
	static void handleMouse(GLFWwindow* window, double xPos, double yPos);

};

