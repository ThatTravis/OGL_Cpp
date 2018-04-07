#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>


glm::vec3 position = glm::vec3(0, 3, 5);
float horizontalAngle = 3.14f;
float verticalAngle = 5.9f;
float FoV = 45.0f;

float speed = 3.0f; // 3 units / second
float mouseSpeed = 0.1;

double  xpos, ypos, xoffset, yoffset;
int width, height;

double currentTime, lastTime;
float deltaTime;

glm::mat4 pMatrix, vMatrix;

glm::mat4 getProjectionMatrix() {
	return pMatrix;
}

glm::mat4 getViewMatrix() {
	return vMatrix;
}



void computeMatricesFromInputs(GLFWwindow *window) {

	glfwGetWindowSize(window, &width, &height);
	glfwGetCursorPos(window, &xpos, &ypos);
	glfwSetCursorPos(window, width / 2, height / 2);

	lastTime = currentTime;
	currentTime = glfwGetTime();
	deltaTime = float(currentTime - lastTime);

	// Compute new orientation
	horizontalAngle += mouseSpeed * (float)deltaTime * float(width / 2 - xpos);
	verticalAngle += mouseSpeed * (float)deltaTime * float(height / 2 - ypos);

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	// Right vector
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
	);

	// Up vector : perpendicular to both direction and right
	glm::vec3 up = glm::cross(right, direction);


	// Move forward
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		position += direction * (float)deltaTime * speed;
	}
	// Move backward
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		position -= direction * (float)deltaTime * speed;
	}
	// Strafe right
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		position += right * (float)deltaTime * speed;
	}
	// Strafe left
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		position -= right * (float)deltaTime * speed;
	}


	// Projection matrix : 45&deg; Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	pMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
	vMatrix = glm::lookAt(
		position,           // Camera is here
		position + direction, // and looks here : at the same position, plus "direction"
		up//glm::vec3{ 0, 1, 0 }                  // Head is up (set to 0,-1,0 to look upside-down)
	);


}






