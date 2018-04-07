#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
//#include <IL/il.h>
//#include <IL/ilut.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "imageLoader.h"
#include "shader.h"
#include "controls.h"






int main(void)
{
	GLFWwindow* window;

	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	
	/* Create a windowed mode window and its OpenGL context */
	int windowWidth = 1024;
	int windowHeight = 768;
	window = glfwCreateWindow(windowWidth, windowHeight, "I'm a Window", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwSetWindowSizeLimits(window, 200, 200, 1600, 1200);
	glfwSetWindowAspectRatio(window, 4, 3);
	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		std::cout << "GLEW ERROR!" << std::endl;}
	/*Check for GLEW Initialization*/
	std::cout << glGetString(GL_VERSION) << std::endl;

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetCursorPos(window, windowWidth / 2, windowHeight / 2);

	/*Genereate Coords for Vertecies*/
	// Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
	// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
	static const GLfloat vertices[] = {
//		positions			 texCoords
//Oben	  X		 Y		Z	  U		V
		-1.0f,  1.0f,  1.0f, 0.5f, 1.0f, //LOH 0  
		-1.0f,  1.0f, -1.0f, 0.5f, 0.0f, //LOV 1
		 1.0f,  1.0f, -1.0f, 1.0f, 0.0f, //ROV 3
		 1.0f,  1.0f, -1.0f, 1.0f, 0.0f, //ROV 3
		 1.0f,  1.0f,  1.0f, 1.0f, 1.0f, //ROH 2
		-1.0f,  1.0f,  1.0f, 0.5f, 1.0f, //LOH 0
//Vorne	  X		 Y		Z	  U		V
		-1.0f,  1.0f, -1.0f, 0.0f, 1.0f, //LOV 1  
		-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, //LUV 5
		 1.0f, -1.0f, -1.0f, 0.5f, 0.0f, //RUV 7
		 1.0f, -1.0f, -1.0f, 0.5f, 0.0f, //RUV 7
		 1.0f,  1.0f, -1.0f, 0.5f, 1.0f, //ROV 3
		-1.0f,  1.0f, -1.0f, 0.0f, 1.0f, //LOV 1
//Hinten  X		 Y		Z	  U		V
		 1.0f,  1.0f,  1.0f, 0.0f, 1.0f, //ROH 2  
	 	 1.0f, -1.0f,  1.0f, 0.0f, 0.0f, //RUH 6
		-1.0f, -1.0f,  1.0f, 0.5f, 0.0f, //LUH 4
		-1.0f, -1.0f,  1.0f, 0.5f, 0.0f, //LUH 4
		-1.0f,  1.0f,  1.0f, 0.5f, 1.0f, //LOH 0 
		 1.0f,  1.0f,  1.0f, 0.0f, 1.0f, //ROH 2
//Links	  X		 Y		Z	  U		V
		-1.0f,  1.0f,  1.0f, 0.0f, 1.0f, //LOH 0  
		-1.0f, -1.0f,  1.0f, 0.0f, 0.0f, //LUH 4
		-1.0f, -1.0f, -1.0f, 0.5f, 0.0f, //LUV 5
		-1.0f, -1.0f, -1.0f, 0.5f, 0.0f, //LUV 5
		-1.0f,  1.0f, -1.0f, 0.5f, 1.0f, //LOV 1 
		-1.0f,  1.0f,  1.0f, 0.0f, 1.0f, //LOH 0
//Rechts  X		 Y		Z	  U		V
		 1.0f,  1.0f, -1.0f, 0.0f, 1.0f, //ROV 3 
		 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, //RUV 7
		 1.0f, -1.0f,  1.0f, 0.5f, 0.0f, //RUH 6
		 1.0f, -1.0f,  1.0f, 0.5f, 0.0f, //RUH 6
		 1.0f,  1.0f,  1.0f, 0.5f, 1.0f, //ROH 2
		 1.0f,  1.0f, -1.0f, 0.0f, 1.0f, //ROV 3
//Links	  X		 Y		Z	  U		V
		 1.0f, -1.0f,  1.0f, 0.0f, 1.0f, //RUH 6 
		 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, //RUV 7
		-1.0f, -1.0f, -1.0f, 0.5f, 0.0f, //LUV 5
		-1.0f, -1.0f, -1.0f, 0.5f, 0.0f, //LUV 5
		-1.0f, -1.0f,  1.0f, 0.5f, 1.0f, //LUH 4
		 1.0f, -1.0f,  1.0f, 0.0f, 1.0f, //RUH 6
	};
	

	imageLoader("res/textures/textureMap.bmp");
	unsigned int shader = CreateShader();
	glUseProgram(shader);
	
	/*Variables for FPS Counter*/
	double lastTime = glfwGetTime();
	int nbFrames = 0;

	/*Generate and bind Vertex Buffer*/
	GLuint vertexBuffer;	
	glGenBuffers(1, &vertexBuffer);	
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, 6*6*5*sizeof(float), vertices, GL_STATIC_DRAW);
	
	
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	//position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), 0);
	//texCoords
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)12);

	
	glm::mat4 ModelMatrix = glm::mat4(1.0f);
	
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
	// Cull triangles which normal is not towards the camera
	//glEnable(GL_CULL_FACE);


	/* Loop until the user closes the window */
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0)
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Send our transformation to the currently bound shader, in the "MVP" uniform
		
		computeMatricesFromInputs(window);
		glm::mat4 ProjectionMatrix = getProjectionMatrix();
		glm::mat4 ViewMatrix = getViewMatrix();
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		GLuint MatrixID = glGetUniformLocation(shader, "MVP");
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		

		//Draw that bound array
		glDrawArrays(GL_TRIANGLES,0 ,sizeof(float)*3*6*6);

		// Measure speed
		double currentTime = glfwGetTime();
		nbFrames++;
		if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1 sec ago
											 // printf and reset timer
			printf("%f fps\n", double(nbFrames));
			nbFrames = 0;
			lastTime += 1.0;
		}
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		glfwGetWindowSize(window, &windowWidth, &windowHeight);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glDeleteProgram(shader); 

	glfwTerminate();
	return 0;
}