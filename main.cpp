#include <iostream>
#include <fstream>
#include <windows.h>
#include "glad/glad.h"      // this works glad's cmake set glad_dir
#include "GLFW/glfw3.h"
#include "users/mrp.h"
#include "users/interactive.h"
#include "users/ui.h"
#include "MDVConfig.h"

void processInput(GLFWwindow* window);
void mouse_Callback(GLFWwindow* window, double xpos, double ypos);
void mouse_Button_Callback(GLFWwindow* window, int button, int action, int mods);
void scroll_Callback(GLFWwindow* window, double xoffset, double yoffset);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods);
std::string get_CorrectPath(std::string path);

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

    int width = 800;
    int height = 600;
    bool is_SplitView = false;

    //hideConsole();
    std::cout << argv[0] << " VERSION: " << MDV_VERSION_MAJOR << "." << MDV_VERSION_MINOR << "\n" << std::endl;

    std::string model01_Path = "";
    std::string model02_Path = "NULL";
    std::string configure_Path = "";

    // read file from anywhere
    if (argc == 2)
    {
        model01_Path = argv[1];
    }
    else if (argc == 3)
    {
        model01_Path = argv[1];
        model02_Path = argv[2];

        is_SplitView = true;
        width = 1600;
    }
    else if (argc == 4)
    {
        model01_Path = argv[1];
        model02_Path = argv[2];

        configure_Path = argv[3];

        std::cout << "configure path: " << configure_Path << std::endl;
        std::ifstream config_File(configure_Path.c_str());
        if (config_File.good())
        {
            resource_Config configs;
            std::string line_Content;
            while (std::getline(config_File, line_Content))
            {
                int index = line_Content.find_first_of(' ');
                std::string key = line_Content.substr(0, index);
                std::string value = line_Content.substr(index + 1, line_Content.length() - 1);
                configs.configs_Pairs[key] = value;
            }

            if (configs.configs_Pairs.count("texture_Folder_Path"))
            {

                if (configs.configs_Pairs["texture_Folder_Path"].length() > 9 && std::filesystem::is_directory(configs.configs_Pairs["texture_Folder_Path"]))
                {
                    texture::textures_Directory = configs.configs_Pairs["texture_Folder_Path"];
                }

                //std::cout << "bb" << configs.configs_KV_Pairs["texture_Folder_Path"] << "cc" << std::endl;
            }
        }


        is_SplitView = true;
        width = 1600;

    }

    // init glfw 
    glfwInit();
    // init some settings for glfw window, note there are a lot of options...
    glfwWindowHint(GLFW_RESIZABLE, 0);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);		// here we set opengl version 4.6
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);		// core profile won't have backwords-compatible feature
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);		// needed when on Mac OS


    // create glfw window object with given parameters
    GLFWwindow* window = glfwCreateWindow(width, height, "慧渊's Model Reviewer By Miles (dev)", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // set vsync on
    glfwSwapInterval(1);

    // resize the viewport when the window size is changed, all the call-back functions must be registered before the render loop begins
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_Callback);
    glfwSetMouseButtonCallback(window, mouse_Button_Callback);
    glfwSetScrollCallback(window, scroll_Callback);
    glfwSetKeyCallback(window, key_Callback);

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

    // user shader files, check compile, check files
    //shaderV2 shader_red("shd_simple_v2.vert", "shd_simple_v3.frag", true, true);
    //shaderV2 shader_black("shd_simple_v2.vert", "shd_simple_v2.frag", true, true);
    shaderV2 shader_Chicken01(data::shader_Chicken01_Vert, data::shader_Chicken01_Frag, true, "chicken01");
    model model01(model01_Path, shader_Chicken01);
    model model02(model02_Path, shader_Chicken01);
    // compatiable orientation
    //model01.set_Rotate(-90.0f, 1.0f, 0.0f, 0.0f);

    //miles_RenderingPipeline.set_RenderingData(vao_0Pos3_1Col3_2Texcoord2, geo_Quad);
    //miles_RenderingPipeline.set_RenderingData(vao_0Pos3_2Texcoord2, geo_Cube);

    //material redMat(shader_red);
    //material greenMat(shader_black)
    //material mat_Suit_33(shader_Chicken01);
    //material mat_Gloves_33(shader_Chicken01);
    //material mat_Shoe_33(shader_Chicken01);

    //model01.set_Material_ForSubMesh(0, mat_Suit_33);
    //model01.set_Material_ForSubMesh(1, mat_Shoe_33);
    //model01.set_Material_ForSubMesh(2, mat_Gloves_33);

    // set texture data checkBoard01.png
    //texture tex_Suit_Diffuse("Suit_33_D.psd", true, true, true);
    //texture tex_Gloves_Diffuse("Gloves_33_D.psd", true, true, true);
    //texture tex_Shoe_Diffuse("Shoe_33.psd", true, true, true);
    //texture::set_BoundTextures_2D(3, tex01, tex02, tex03);

    //redMat.set_Textures(2, tex04, tex02);
    //mat_Suit_33.set_Texture("surf.diffuse", tex_Suit_Diffuse);
    //mat_Gloves_33.set_Texture("surf.diffuse", tex_Gloves_Diffuse);
    //mat_Shoe_33.set_Texture("surf.diffuse", tex_Shoe_Diffuse);

    // always active shader before setting uniform buffer
    //shader::use_Program();
    // set uniform buffer, this buffer won't be changed every frame
    //shader::set_Int("example1_Texture", 0);		// gl_texture0
    //shader::set_Int("example2_Texture", 1);		// gl_texture1
    //shader::set_Int("example3_Texture", 2);		// gl_texture2

    // init camera
    cam ca;

    // init render pipeline
    mrp miles_RenderingPipeline(ca);

    shaderV2 shader_Wireframe(data::shader_Wireframe_Vert, data::shader_Wireframe_Frag, true, "wireframe");
    material material_Wireframe(shader_Wireframe);
    miles_RenderingPipeline.wireframe_Material = &material_Wireframe;

    shaderV2 shader_NDC(data::shader_NDC_Vert, data::shader_NDC_Frag, true, "ndc");
    material material_NDC(shader_NDC);
    miles_RenderingPipeline.material_NDC = &material_NDC;

    // help quad
    mesh_Simple quad(8, 32, data::help_Quad_Attributes, 6, data::help_Quad_Indices);
    // help screen line
    mesh_NDC screenLine(6, 12, data::help_SplitLine_Attributes, 2, data::help_SplitLine_Indices);

    // this where the while loop ( render loop ) begins, iteration of the render loop is also called a frame
    while (!glfwWindowShouldClose(window))
    {
        // to orgnize our input control
        processInput(window);

        // interactive control
        double time = glfwGetTime();
        inter.set_DeltaTime(time);
        ca.set_Target(0.0f, inter.targetHeight, 0.0f);
        ca.set_SphericalSystem_With_Target(inter.zoom, inter.E, inter.T);
        inter.fade_T();

        // clear target
        miles_RenderingPipeline.clear_Buffer();
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        // draw mode
        //miles_RenderingPipeline.set_DrawMode(inter.draw_Mode);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        material_Wireframe.set_Vector4("color", 0.65, 0.6, 0.28, 1.0);

        switch (inter.draw_Mode)
        {
        case 1:
            if (is_SplitView)
            {
                miles_RenderingPipeline.draw_ScreenLine(&screenLine, false);
                int fill_Mode = (inter.draw_Mode_Press_Times + 3) % 3;
                glViewport(0, 0, width / 2, height);
                miles_RenderingPipeline.draw_Model(model01, true, fill_Mode);
                glViewport(width / 2, 0, width / 2, height);
                miles_RenderingPipeline.draw_Model(model02, true, fill_Mode);
            }
            else
            {
                int fill_Mode = (inter.draw_Mode_Press_Times + 3) % 3;
                miles_RenderingPipeline.draw_Model(model01, true, fill_Mode);
            }
            break;
        case 2:
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            if (is_SplitView)
            {
                miles_RenderingPipeline.draw_ScreenLine(&screenLine, false);
                int index = (inter.draw_Mode_Press_Times + model01.preview_Materials.size()) % model01.preview_Materials.size();
                glViewport(0, 0, width / 2, height);
                miles_RenderingPipeline.draw_Mesh(&quad, model01.preview_Materials[index], true, transform::mat_Identity);
                glViewport(width / 2, 0, width / 2, height);
                miles_RenderingPipeline.draw_Mesh(&quad, model02.preview_Materials[index], true, transform::mat_Identity);
            }
            else
            {
                int index = (inter.draw_Mode_Press_Times + model01.preview_Materials.size()) % model01.preview_Materials.size();
                miles_RenderingPipeline.draw_Mesh(&quad, model01.preview_Materials[index], true, transform::mat_Identity);
            }

            break;
        default:
            break;
        }


        // draw model

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

// key holding event
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetMouseButton(window, 0) == GLFW_PRESS)
    {
        // when holding mouse
        glfwGetCursorPos(window, &inter.cursorPos_X, &inter.cursorPos_Y);
        inter.set_ET(glfwGetTime());
    }
}

// key press event
void key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_1 && action == GLFW_PRESS)
    {

        if (inter.draw_Mode == 1)
        {
            inter.draw_Mode_Press_Times++;
        }
        else
        {
            inter.draw_Mode = 1;    // change to material view
            inter.draw_Mode_Press_Times = 0;
        }
    }
    if (key == GLFW_KEY_2 && action == GLFW_PRESS)
    {

        if (inter.draw_Mode == 2)
        {
            inter.draw_Mode_Press_Times++;
        }
        else
        {
            inter.draw_Mode = 2;    // change to material view
            inter.draw_Mode_Press_Times = 0;
        }
    }
}

// scroll mouse event
void scroll_Callback(GLFWwindow* window, double xoffset, double yoffset)
{
    inter.set_Zoom(yoffset);
}

// dragging event
void mouse_Callback(GLFWwindow* window, double xpos, double ypos)
{
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        glfwGetCursorPos(window, &inter.cursorPos_X, &inter.cursorPos_Y);
        inter.set_TargetHeightOffset(glfwGetTime());
    }
}

// click event
void mouse_Button_Callback(GLFWwindow* window, int button, int action, int mods)
{
    if ((button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) || (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS))
    {
        glfwGetCursorPos(window, &inter.updating_X, &inter.updating_Y);
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        inter.set_Acceleration();
    }
    if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
    {
        inter.reset_View();
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width / 2, height / 2);
}

std::string get_CorrectPath(std::string path)
{
    for (int i = 0; i < path.length(); i++)
    {
        if (path[i] == '/')
        {
            path[i] = '\\';
        }
    }
    return path + '\\';
}
