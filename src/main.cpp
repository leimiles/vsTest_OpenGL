#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "users/mrp.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 640;
const unsigned int SCR_HEIGHT = 480;

int main()
{
	// init glfw 
	glfwInit();
	// init some settings for glfw window, note there are a lot of options...
	glfwWindowHint(GLFW_RESIZABLE, 0);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);		// here we set opengl version 3.3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);		// core profile won't have backwords-compatible feature
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);		// needed when on Mac OS

	// create glfw window object with given parameters
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "慧渊's Model Reviewer By Miles", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// resize the viewport when the window size is changed, all the call-back functions must be registered before the render loop begins
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// here we need to init the glad, this lib will manage all function pointers we need to use for opengl
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// init render pipeline
	mrp miles_RenderingPipeline;
	// set rendering data
	miles_RenderingPipeline.set_RenderingData();
	// set texture data
	texture tex01("super_Mario.png", false, true);
	// user shader files, check compile, check files
	shader miles_shaderProgram("shd_simple_v1.vert", "shd_simple_v1.frag", false, false);

	// this where the while loop ( render loop ) begins, iteration of the render loop is also called a frame
	while (!glfwWindowShouldClose(window))
	{
		// to orgnize our input control
		processInput(window);
		//... here our drawing commands are
		miles_RenderingPipeline.clear_ColorBuffer();

		shader::use_Program();
		miles_RenderingPipeline.draw_Geometry_Elements();

		// double buffer avoiding the tearing
		glfwSwapBuffers(window);
		// this method is used to check if there's any event function (call back) should run, like keyboard, mouse window states ,etc.
		glfwPollEvents();
	}

	miles_RenderingPipeline.release_Resource();
	// if the while loop stopped, glfw will stop too, the whole app is over
	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
