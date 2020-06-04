//header files
#include "tigl.h"
#include "FpsCam.h"
#include "Environment.h"
#include "Cube.h"

//lib files
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>;

//misc.
using tigl::Vertex;

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

//prototypes
void init();
void update();
void draw();
void keyCallBack(GLFWwindow*, int, int, int, int);

//Attributes
GLFWwindow* window;
double lastFrameTime;
FpsCam* camera;

//Cubes
Cube cube1(0, -1, 0);
Cube cube2(0, -1, 2);
Cube cube3(0, -1, 4);
Cube cube4(0, -1, 6);
Cube cube5(0, -1, 8);

int main(void)
{
    if (!glfwInit())
        throw "Could not initialize glwf";
    window = glfwCreateWindow(1400, 800, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        throw "Could not initialize glwf";
    }
    glfwMakeContextCurrent(window);

    tigl::init();

    init();

	while (!glfwWindowShouldClose(window))
	{
		update();
		draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();


    return 0;
}

void init()
{
    glfwSetKeyCallback(window, keyCallBack);
    camera = new FpsCam(window);
}

void update()
{
    double currentTime = glfwGetTime();
    double deltaTime = currentTime - lastFrameTime;
    lastFrameTime = currentTime;
    
    camera->update(window); 
    
    cube1.update(deltaTime);
}

void draw()
{
    //settings
    glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    glm::mat4 projection = glm::perspective(glm::radians(75.0f), viewport[2] / (float)viewport[3], 0.01f, 100.0f);

    tigl::shader->setProjectionMatrix(projection);
    tigl::shader->setViewMatrix(camera->getMatrix());
    tigl::shader->setModelMatrix(glm::mat4(1.0f));

    tigl::shader->enableColor(false);
    tigl::shader->enableTexture(true);

    glEnable(GL_DEPTH_TEST);

    Environment environment;

    environment.draw();

    cube1.draw();
    cube2.draw();
    cube3.draw();
    cube4.draw();
    cube5.draw();
}

void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE)
    {
        glfwSetWindowShouldClose(window, true);
    }
    else if (key == GLFW_KEY_SPACE) 
    {
        std::cout << "SPACE DETECTED" << "\n";
    }
}

