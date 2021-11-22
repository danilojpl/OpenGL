#include "Window.h"

Window::Window() {
    width = 800;
    height = 600;

    for (int i = 0; i < 1024; i++) {
        keys[i] = false;
    }
    mouseFirstMove = true;
}

Window::Window(GLint widthWindow, GLint heightWindow) {
    width = widthWindow;
    height = heightWindow;

    for (int i = 0; i < 1024; i++) {
        keys[i] = false;
    }
    mouseFirstMove = true;
}

int Window::Initialize() {
    //Iniciar o GLFW
    if (!glfwInit()) {
        printf("GLFW não foi iniciado \n");
        return 1;
    }

    //Garantir que estamos usando a versão 3.0
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Cria a janela
    window = glfwCreateWindow(width, height, "Ola Mundo!", NULL, NULL);
    if (!window) {
        printf("GLWF nao consegiu criar a janela");
        glfwTerminate();
        return 1;
    }

    //Define a janela como principal
    glfwMakeContextCurrent(window);

    //Armazena as informaÁıes de tamanho de janela do buffer

    glfwGetFramebufferSize(window, &bufferWidth, &bufferHeigth);

    //GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        printf("Não foi iniciado o GLEW");
        glfwDestroyWindow(window);
        glfwTerminate();
        return 1;
    }

    glEnable(GL_DEPTH_TEST); //Habilitar o Depth Test

    glViewport(0, 0, bufferWidth, bufferHeigth);
    glfwSetWindowUserPointer(window, this);
    createCallbacks();

    return 0;
}


Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::createCallbacks()
{
    glfwSetKeyCallback(window, handleKeys);
    glfwSetCursorPosCallback(window, handleMouse);
}

void Window::handleKeys(GLFWwindow* window, int key, int code, int action, int mode) {
    Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    //Limitar a 1024
    if (key > 0 && key <= 1024) {
        if (action == GLFW_PRESS) {
            theWindow->keys[key] = true;
           // printf("Pressed: %d \n", key);
        }
        else if (action == GLFW_RELEASE) {
            theWindow->keys[key] = false;
            //printf("Released: %d \n", key);
        }
    }
}

void Window::handleMouse(GLFWwindow* window, double xPos, double yPos) {
    Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

    //É o pimeiro movimento?
    if (theWindow->mouseFirstMove) {
        theWindow->lastX = xPos;
        theWindow->lastY = yPos;
        theWindow->mouseFirstMove = false;
    }

    theWindow->xChange = xPos - theWindow->lastX;
    theWindow->yChange = theWindow->lastY - yPos;

    theWindow->lastX = xPos;
    theWindow->lastY = yPos;

   // printf("x: %.2f | y: %.2f\n", theWindow->xChange, theWindow->yChange);
}

GLfloat Window::getXChange() {
    GLfloat change = xChange;
    xChange = 0.0f;
    return change;
}

GLfloat Window::getYChange() {
    GLfloat change = yChange;
    yChange = 0.0f;
    return change;
}
