#include<glad/glad.h> 
#include<GLFW/glfw3.h> 

const char* vertexShaderSource = "#version 330 core\n"
"Layout(location=0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"gl_position = vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
"}\0"
;

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n" 
"FragColor =vec(0.5f,0.7f,1.0f,1.0f);\n"
"}\0"


;
int main() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window= glfwCreateWindow(800, 800, "OPENGL", NULL, NULL);
	glfwMakeContextCurrent(window);
	gladLoadGL();

	glViewport(0, 0, 800, 800);

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);//on les assemble 
	glCompileShader(vertexShader);
    

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);	

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);	

	GLfloat vertices[] = {
		-1.0f, -0.5f, 0.0f, //X Y Z 1(1er point) 
		 0.5f, -0.5f, 0.0f, //ps pour faire un carre il faut deux triangles donc deux fois plu
		 0.0f,  0.5f, 0.0f
	};


	GLuint VAO, VBO; 

	glGenVertexArrays(1, &VAO);	
	glGenBuffers(1, &VBO);	 

	glBindVertexArray(VAO);  
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //VAO instructions

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);//last?
	glEnableVertexAttribArray(0);//buffer_index=0

	glBindBuffer(GL_ARRAY_BUFFER, 0); 
	glBindVertexArray(0);





	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.3f, 0.1f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram); 
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3); 

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);


	glfwDestroyWindow(window);
	glfwTerminate();
	 
	return 0; 
}
