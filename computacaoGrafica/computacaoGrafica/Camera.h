#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera
{
public:
	Camera();
	~Camera();
	Camera(glm::vec3 startPosition, glm::vec3 startWorldUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);

	void KeyControl(bool* keys);
	void MouseControl(GLfloat xChange, GLfloat yChage);
	glm::mat4 calculateViewMatrix();

private:
	void update();

	glm::vec3 position; //posição da camera
	glm::vec3 front; //Eixo Z
	glm::vec3 up; //Eixo Y
	glm::vec3 right; //Eixo X
	glm::vec3 worldUp; //Ponto de fulga ou limite de ceu e terreno

	GLfloat yaw; //Esquerda e da Direita
	GLfloat pitch; //Cima e baixo

	GLfloat moveSpeed, turnSpeed;
};

