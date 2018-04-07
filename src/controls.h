#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

void computeMatricesFromInputs(GLFWwindow *window);

glm::mat4 getProjectionMatrix();
glm::mat4 getViewMatrix();