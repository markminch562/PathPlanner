//
// Created by plotb on 8/21/22.
//

#ifndef PATHPLANNER_DISPLAY_H
#define PATHPLANNER_DISPLAY_H

#define GLFW_INCLUDE_NONE
#include "glad/glad.h"
#include "GLFW/glfw3.h"


struct Display
{
    //This is for loading in the glfw window information that is going to be used, you should only pass a nullptr int this function
    int SetUpGraphics();

    int LoadShaders();

    unsigned int shaderProgram;


    GLFWwindow* window = nullptr;


};





#endif //PATHPLANNER_DISPLAY_H
