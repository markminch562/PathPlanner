#include <iostream>
#include <vector>
#include <string>
#include "libs/MatrixMath/MatrixMath.h"
#define GLFW_INCLUDE_NONE
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#define STB_IMAGE_IMPLEMENTATION
#include "libs/stb/stb_image.h"
#include "src/graphics/ShaderData.h"
#include "src/graphics/Display.h"
#include "src/maps/include/Map.h"
struct color
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

void printData(std::vector<float> data)
{
    for(int i = 0; i < data.size(); ++i )
    {
        std::cout<<data[i]<<" ";
    }
    std::cout<<std::endl;
}




struct Mat
{
    int rows;
    int cols;
    std::vector<float> Data;
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}




int main() {

    std::vector<float> MatData = { 0.0f, 0.0f, 0.0f, 1.0f, 3.0f, 0.0f, 0.0f, 0.0f,
                                   0.0f, 2.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.0f , 0.0f,
                                   0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                                   2.0f, 3.44f, 7.0f, 1.0f, 0.0f, 0.0f, 0.0f,0.0f};
    SparseMatrix myMat(4, 8, MatData);

    std::vector<float> DataSet = myMat.getRow(2);
    printData(myMat.getRow(0));
    printData(myMat.getRow(3));


    /*
     * Some basic matrix math
     *
     * When working with matrix math on a computer cpu make sure to not use the default way of doing matrix math taught in schools
     * It too cache inefficient on large matrix items such a photos, using this index method we can remove several
     */

    Mat m1 = {2, 3, {1.0, 3.0, 4.0, 2.0, 1.0, 1.5}};
    Mat m2 = {2, 3, {3.0, 1.0, 2.5,
                                      2.5, 23.3, 7.5  }};

    Mat resultData = {m2.cols, m1.rows, std::vector<float>(m2.cols*m1.rows)};

    int rowOffsetM1 = 0;
    for(int RightRow = 0; RightRow < m1.rows; ++RightRow) {
        int resultOffset = RightRow *m2.cols;
        for (int RightCol = 0; RightCol < m1.cols; ++RightCol, ++rowOffsetM1) {
            int rowOffsetM2 = RightCol*m2.cols;
            for (int LeftCol = 0; LeftCol < m2.cols; ++LeftCol) {
                float mat1 = m1.Data[rowOffsetM1];
                float mat2 = m2.Data[rowOffsetM2 + LeftCol];
                resultData.Data[resultOffset + LeftCol] += mat1*mat2;
            }
        }
    }

    Display PlanningImage;
    if(PlanningImage.SetUpGraphics() != 1)
    {
        return 0;
    }
    GLFWwindow* window = PlanningImage.window;
    glfwSwapInterval(0);
    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    if(PlanningImage.LoadShaders() != 1)
    {
        return 0;
    }

    unsigned int shaderProgram = PlanningImage.shaderProgram;



    int width, height, nrChannels;
    unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);




    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
            // positions          // colors           // texture coords
            1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
            1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
            -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
            -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
    };

    unsigned int indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    // glBindVertexArray(0);

    // as we only have a single shader, we could also just activate our shader once beforehand if we want to
    glUseProgram(shaderProgram);


    int Iwidth;
    int Iheight;
    int channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* mapData = stbi_load("../Maps/Path1.png",&Iwidth, &Iheight, &channels, 0);

    int FileDataSize = Iwidth *Iheight;
    Mapper::Point* mapItter = (Mapper::Point*)mapData;
    int startLocation = 0;
    std::vector<Mapper::Point> Storage;
    for(int i = 0 ; i < FileDataSize; i++)
    {
        Storage.push_back(mapItter[i]);

    }
    Mapper::Grid<Mapper::Point> Grid({Iwidth, Iheight}, Storage);
    Mapper::DykstraBreadthPlanner MapPlanner(&Grid, {0, 0, 255}, {255, 0, 0});
    MapPlanner.DrawCostMap();
    while(!MapPlanner.PathFound())
    {
        MapPlanner.Update();
        MapPlanner.DrawCostMap();

    }




    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if(mapData)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,Iwidth, Iheight, 0, GL_RGB, GL_UNSIGNED_BYTE, mapData);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout<<" Failed to load texture"<<std::endl;
    }
    double currentTime = glfwGetTime();
    while (glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // render the triangle

        /*
        glBindTexture(GL_TEXTURE_2D, texture);

        if(startLocation <  FileDataSize)
        {
            mapItter[startLocation].R = 0;
            mapItter[startLocation].G = 0;
            mapItter[startLocation].B = 0;
            startLocation++;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,Iwidth, Iheight, 0, GL_RGB, GL_UNSIGNED_BYTE, mapData);
        */

        //glUseProgram(shaderProgram);
        //glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
        std::cout<<1.0f/(glfwGetTime() -currentTime)<<std::endl;
        currentTime = glfwGetTime();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}


