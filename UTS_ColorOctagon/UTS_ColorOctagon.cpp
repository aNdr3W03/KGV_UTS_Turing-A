// UTS_ColorOctagon.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#define _USE_MATH_DEFINES
#include <iostream>
#include "Util.h"

using namespace std;

float vertices[6*8+1] = {};
float currentSize = 0.1;
GLint scaleLoc;

float deg_rad(float x) {
    return x * M_PI / 180;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
    {
        currentSize += 0.01;
        cout << "Current Size " << currentSize << "\n";
    }

    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
    {
        currentSize -= 0.01;
        cout << "Current Size " << currentSize << "\n";
    }

    /*
    if (key == GLFW_KEY_C && action == GLFW_PRESS)
    {
        cout << "\nC Pressed Color Changed\n";

        srand(time(NULL));
        for (int i = 3; i < 6 * 8 + 1; i += 6)
        {
            // vertices[i] = vertices[i+1] = vertices[i+2] = rand() % 256 / 256.0;
            vertices[i] = rand() * 1.0f / RAND_MAX;
            vertices[i + 1] = rand() * 1.0f / RAND_MAX;
            vertices[i + 2] = rand() * 1.0f / RAND_MAX;

            cout << "vertices[" << i << " " << i + 1 << " " << i + 2 << "] " << vertices[i] << "\n";
        }

        cout << "\n";

        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9 * 6, vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }
    */

    glUniform1f(scaleLoc, currentSize);
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 640, "UTS Color Octagon", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // Keyboard Pressed Key Callback
    glfwSetKeyCallback(window, keyCallback);

    GLenum err = glewInit();

    float deg = 360 / 8;
    float rad = deg_rad(deg);
    float r   = 0.5;

    vertices[6 * 8 + 1] = {};
    vertices[0] = 0;
    vertices[1] = 0;
    vertices[2] = 0;

    vertices[6] = -1 * sin(deg_rad(deg)) * r;
    vertices[7] = -1 * cos(deg_rad(deg)) * r;
    vertices[8] = 0.0;

    for (int i=12; i<(6*8+1); i+=6)
    {
        vertices[i]     = vertices[6] * cos(rad) - vertices[7] * sin(rad);
        vertices[i + 1] = vertices[6] * sin(rad) + vertices[7] * cos(rad);
        vertices[i + 2] = 0.0;
        vertices[i + 3] = 1.0;
        vertices[i + 4] = 0.0;
        vertices[i + 5] = 0.0;
        rad += deg_rad(deg);
    }
    
    for (int i=3; i<(6*8+1); i+=6)
    {
        // vertices[i] = vertices[i+1] = vertices[i+2] = rand() % 256 / 256.0;
        vertices[i]     = rand() * 1.0f / RAND_MAX;
        vertices[i + 1] = rand() * 1.0f / RAND_MAX;
        vertices[i + 2] = rand() * 1.0f / RAND_MAX;
    }

    unsigned int indexArr[] = {
        0, 1, 2,
        0, 2, 3,
        0, 3, 4,
        0, 4, 5,
        0, 5, 6,
        0, 6, 7,
        0, 7, 8,
        0, 8, 1
    };

    unsigned int vertexBuffer = 0;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9 * 6, vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int indexBuffer = 0;
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 8 * 3, indexArr, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);



    string vertexString = readFile("vertex.vert");
    string fragmentString = readFile("fragment.frag");

    const char* vertexChar = vertexString.c_str();
    const char* fragmentChar = fragmentString.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShader, 1, &vertexChar, NULL);
    glShaderSource(fragmentShader, 1, &fragmentChar, NULL);

    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);



    unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);



    /*
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    */



    scaleLoc = glGetUniformLocation(program, "size");



    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);

        /* Timed Color Change */
        srand(glfwGetTime());
        for (int i=3; i<6*8+1; i+=6)
        {
            // vertices[i] = vertices[i+1] = vertices[i+2] = rand() % 256 / 256.0;
            vertices[i]     = rand() * 1.0f / RAND_MAX;
            vertices[i + 1] = rand() * 1.0f / RAND_MAX;
            vertices[i + 2] = rand() * 1.0f / RAND_MAX;

            // cout << "vertices[" << i << " " << i+1 << " " << i+2 << "] " << vertices[i] << "\n";
        }
        
        /* Press C to Change The Color */
        int enter = glfwGetKey(window, GLFW_KEY_C);
        if (enter == GLFW_PRESS)
        {
            cout << "C Pressed Color Changed";

            srand(time(NULL));
            for (int i=3; i<6*8+1; i+=6)
            {
                // vertices[i] = vertices[i+1] = vertices[i+2] = rand() % 256 / 256.0;
                vertices[i]     = rand() * 1.0f / RAND_MAX;
                vertices[i + 1] = rand() * 1.0f / RAND_MAX;
                vertices[i + 2] = rand() * 1.0f / RAND_MAX;

                // cout << "vertices[" << i << " " << i+1 << " " << i+2 << "] " << vertices[i] << "\n";
            }

            cout << "\n";
        }

        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9 * 6, vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 8 * 3, indexArr, GL_STATIC_DRAW);

        glUniform1f(scaleLoc, currentSize);

        // Draw using IndexBuffer
        glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, nullptr);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
