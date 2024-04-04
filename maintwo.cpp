// This thing is following learnopengl.com tutorials

#include <stdio.h>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);  
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {

	std::cout << "Welcome to hell :)";

	glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "dEngine", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}    

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};  

	//---------------AVertex Shader----------
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// Check error in shader
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "SHADER VERTEX COMPILATION FAILED \n" << infoLog << std::endl;
	}

	//---------Fragment Shader----------

	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success); // error checking, used the same variable because im lazy lmao
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "SHADER FRAGMENT COMPILATION FAILED \n" << infoLog << std::endl;
	}

	//--------Creating shader program----------
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Error checking
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR LINKING SHADER PROGRAM" << infoLog << std::endl;
	}

	// Deleting shaders cause not needed
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//-----------CREATE VAO (vertex array objects)-------
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//-------------- Create VBO (Vertex Buffer Objects) --------------
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	//------------Linking Vertex Attribute or whatever---------

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//unsigned int VBO, VAO;
 //   glGenVertexArrays(1, &VAO);
 //   glGenBuffers(1, &VBO);
 //   // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
 //   glBindVertexArray(VAO);

 //   glBindBuffer(GL_ARRAY_BUFFER, VBO);
 //   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

 //   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
 //   glEnableVertexAttribArray(0);

 //   // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
 //   glBindBuffer(GL_ARRAY_BUFFER, 0); 

 //   // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
 //   // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
 //   glBindVertexArray(0); 


	while(!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();    
	}

	glfwTerminate();

	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}  

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
