#include <iostream>
#include <windows.h>
#include "glad/glad.h"      // this works glad's cmake set glad_dir
#include "GLFW/glfw3.h"
#include "users/mrp.h"
#include "users/interactive.h"
#include "MDVConfig.h"

void processInput(GLFWwindow* window);
void mouse_Callback(GLFWwindow* window, double xpos, double ypos);
void mouse_Button_Callback(GLFWwindow* window, int button, int action, int mods);
void scroll_Callback(GLFWwindow* window, double xoffset, double yoffset);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// this function hide the console window
void hideConsole()
{
    HWND Stealth;
    AllocConsole();
    Stealth = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(Stealth, 0);
}

interactive inter;

int main(int argc, char* argv[])
{
    //hideConsole();
    std::cout << argv[0] << " VERSION: " << MDV_VERSION_MAJOR << "." << MDV_VERSION_MINOR << "\n" << std::endl;
    // init glfw 
    glfwInit();
    // init some settings for glfw window, note there are a lot of options...
    glfwWindowHint(GLFW_RESIZABLE, 0);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);		// here we set opengl version 4.6
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
    glfwSetCursorPosCallback(window, mouse_Callback);
    glfwSetMouseButtonCallback(window, mouse_Button_Callback);
    glfwSetScrollCallback(window, scroll_Callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    // here we need to init the glad, this lib will manage all function pointers we need to use for opengl
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // init geometry quad
    //geometry geo_Quad(8, 32, data::quad_Example_Attributes, 6, data::quad_Example_Indices);
    // init geometry cube
    //geometry geo_Cube(5, 180, data::cube_Example_Attributes);

    model model01("sausage_Model.fbx");
    // compatiable orientation
    model01.set_Rotate(-90.0f, 1.0f, 0.0f, 0.0f);

    // init render pipeline
    mrp miles_RenderingPipeline;
    //miles_RenderingPipeline.set_RenderingData(vao_0Pos3_1Col3_2Texcoord2, geo_Quad);
    //miles_RenderingPipeline.set_RenderingData(vao_0Pos3_2Texcoord2, geo_Cube);

    // user shader files, check compile, check files
    shader miles_shaderProgram("shd_simple_v2.vert", "shd_simple_v2.frag", true, true);

    // set texture data
    //texture tex01("super_Mario_A.png", GL_RGBA, true, true);
    //texture tex02("batman.jpg", GL_RGB, true, true);
    //texture tex03("miaoYu.jpg", GL_RGB, true, true);
    //texture::set_BoundTextures_2D(3, tex01, tex02, tex03);

    // always active shader before setting uniform buffer
    shader::use_Program();
    // set uniform buffer, this buffer won't be changed every frame
    shader::set_Int("example1_Texture", 0);		// gl_texture0
    shader::set_Int("example2_Texture", 1);		// gl_texture1
    shader::set_Int("example3_Texture", 2);		// gl_texture2

    cam ca;

    GLfloat deltaTime = 0.0f;
    GLfloat lastFrame = 0.0f;

    // this where the while loop ( render loop ) begins, iteration of the render loop is also called a frame
    while (!glfwWindowShouldClose(window))
    {
        // to orgnize our input control
        processInput(window);

        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        std::cout << "delta time: " << deltaTime << std::endl;

        ca.set_Target(0.0f, inter.targetHeight, 0.0f);
        ca.set_SphericalSystem_With_Target(inter.zoom, inter.get_ElevationAngle(), inter.get_TurningAngle());

        // clear target
        miles_RenderingPipeline.clear_Buffer();

        // active current shader
        shader::use_Program();

        // draw loaded model
        glm::mat4 mvp = ca.get_Matrix_PerspectiveProjection() * ca.get_Matrix_Eye_Improved() * model01.get_Matrix_LocalToWorld();
        shader::set_Matrix("mvp", mvp);
        miles_RenderingPipeline.draw_Model(model01, true);

        //draw cube 10 time at certain positions
        /*
        for (int i = 0; i < 10; i++)
        {
            geo_Cube.set_Translate(data::some_Positions[i].x, data::some_Positions[i].y, data::some_Positions[i].z);
            geo_Cube.set_Rotate((i - 10) * 10.0f * glfwGetTime(), 0.7f, 0.7f, 0.0f);
            geo_Cube.set_Scale(1.0f, 0.7f, 1.0f);
            // test rotation
            ca.set_Translate(sin(glfwGetTime()) * 10.0f, 3.0f, cos(glfwGetTime()) * 10.0f);
            glm::mat4 mvp = ca.get_Matrix_PerspectiveProjection() * ca.get_Matrix_Eye_Improved() * geo_Cube.get_Matrix_LocalToWorld();
            shader::set_Matrix("mvp", mvp);
            miles_RenderingPipeline.draw_Geometry(geo_Cube, true);
        }
        */

        // simple draw
        /*
        geo_Cube.set_Translate(0.0f, 0.0f, 0.0f);
        glm::mat4 mvp1 = ca.get_Matrix_PerspectiveProjection() * ca.get_Matrix_Eye_Improved() * geo_Cube.get_Matrix_LocalToWorld();
        shader::set_Matrix("mvp", mvp1);
        miles_RenderingPipeline.draw_Geometry(geo_Cube, true);
        */

        // draw cube tower
        /*
        for (int i = 0; i < 20; i++)
        {
            geo_Cube.set_Translate(0.0f, i + i * 0.05f, 0.0f);
            geo_Cube.set_Rotate(i * 10.0f + glfwGetTime() * 2.0f, 0.0f, 1.0f, 0.0f);
            glm::mat4 mvp1 = ca.get_Matrix_PerspectiveProjection() * ca.get_Matrix_Eye_Improved() * geo_Cube.get_Matrix_LocalToWorld();
            shader::set_Matrix("mvp", mvp1);
            miles_RenderingPipeline.draw_Geometry(geo_Cube, true);

        }
        */

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
    {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        inter.targetHeight += 0.05f * (inter.zoom * 0.5f);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        inter.targetHeight -= 0.05f * (inter.zoom * 0.5f);
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        inter.reset();
    }

}

void scroll_Callback(GLFWwindow* window, double xoffset, double yoffset)
{
    inter.zoom += yoffset * 10.0f;
    if (inter.zoom < 0)
    {
        inter.zoom = 0.001f;
    }
}

void mouse_Callback(GLFWwindow* window, double xpos, double ypos)
{
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        inter.set_BothAngles(xpos, ypos, glfwGetTime());
    }
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
    }
}

void mouse_Button_Callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        inter.set_AutoTurningEnergy();
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
}
