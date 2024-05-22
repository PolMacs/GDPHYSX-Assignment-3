#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>

//include for time
#include <chrono>
using namespace std::chrono_literals;

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include "p6/MyVector.h"
#include "p6/P6Particle.h"

//Modifier for the model's x Position
float x_mod = 0;
float z_mod = 0;
float y_mod = 0;

float scale = 0.5f;

void Key_Callback(GLFWwindow* window // Pointer to window
    , int key// keycode of press
    , int scancode // physical postion of the press
    , int action // either press / release
    , int mods) // which modifier keys are held down
{
    if (key == GLFW_KEY_D /*&& action == GLFW_PRESS*/) {
        //Move
        x_mod += 0.1f;
    }
    if (key == GLFW_KEY_A /*&& action == GLFW_PRESS*/) {
        //Move
        x_mod -= 0.1f;
    }
    if (key == GLFW_KEY_W /*&& action == GLFW_PRESS*/) {
        z_mod -= -0.1f;
    }
    if (key == GLFW_KEY_S /*&& action == GLFW_PRESS*/) {
        z_mod += -0.1f;
    }
}

int main(void)
{
    //load the vert shader file into a string stream
    std::fstream vertSrc("Shaders/Sample.vert");
    std::stringstream vertBuff;

    //Add the file stream to the string stream
    vertBuff << vertSrc.rdbuf();

    //Convert the stream to a character array
    std::string vertS = vertBuff.str();
    const char* v = vertS.c_str();

    //load the frag shader file into a string stream
    std::fstream fragSrc("Shaders/Sample.frag");
    std::stringstream fragBuff;

    //Add the file stream to the string stream
    fragBuff << fragSrc.rdbuf();

    //Convert the stream to a character array
    std::string fragS = fragBuff.str();
    const char* f = fragS.c_str();

    GLFWwindow* window;

    float window_width = 800;
    float window_height = 800;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(window_width, window_height, "Matthew Jayd Baldonado | Paul Davidion Macaraeg", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    gladLoadGL();

    //Create a Vertex Shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    //Assign the source to the vertex shader
    glShaderSource(vertexShader, 1, &v, NULL);

    //Compile the vertex shader
    glCompileShader(vertexShader);

    //Create a Fragment Shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    //Assign the source to the fragment shader
    glShaderSource(fragmentShader, 1, &f, NULL);

    //Compile the fragment shader
    glCompileShader(fragmentShader);


    //Create shader program
    GLuint shaderProg = glCreateProgram();


    //Attach the compiled Vertex shader
    glAttachShader(shaderProg, vertexShader);
    //Attach the compiled Vertex shader
    glAttachShader(shaderProg, fragmentShader);

    //Finalize the compilation process
    glLinkProgram(shaderProg);

    //Set the callback function to the window
    glfwSetKeyCallback(window, Key_Callback);

    std::string path = "3D/sphere.obj";
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> material;
    std::string warning, error;

    tinyobj::attrib_t attributes;

    bool success = tinyobj::LoadObj(&attributes, &shapes, &material, &warning, &error, path.c_str());

    std::vector<GLuint> mesh_indices;
    for (int i = 0; i < shapes[0].mesh.indices.size(); i++)
    {
        mesh_indices.push_back(shapes[0].mesh.indices[i].vertex_index);
    }

    GLfloat vertices[]
    {
        //x  //y   //z
        0.f, 0.5f, 0.f, //0
        -0.5f, -0.5f, 0.f, //1
        0.5f, -0.5f, 0.f //2

    };

    GLuint indices[]
    {
        0,1,2
    };

    //Create VAO,VBO,EBO Variables
    GLuint VAO, VBO, EBO;

    //Initialize VAO and VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    //Currently Editing VAO = null
    glBindVertexArray(VAO);
    //Currently Editing VAO = VAO
    // 
    //Currently Editing VBO = null
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //Currently Editing VBO = VBO
    //VAO <-VBO

    glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * attributes.vertices.size() /*Size of buffer in bytes*/,
        attributes.vertices.data() /*Array*/, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3 /*x y z*/, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    //Currently Editing VBO = VBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //Currently Editing VBO = EBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mesh_indices.size(), mesh_indices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glm::mat4 identity_martix = glm::mat4(1.0f);

    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    float scale_x = 500.0;
    float scale_y = 500.0;
    float scale_z = 500.0;

    float axis_x = 0.0;
    float axis_y = 1.0;
    float axis_z = 0.0;

    float theta = 0.0;


    //Create projection matrix
    glm::mat4 projectionMatrix = glm::ortho(-400.f, //L
        400.f,//R
        -400.f,//B
        400.f,//T
        -400.f,//Znear
        400.f);//Zfar


    /*P6::MyVector position(0, -350, 0);*/
    P6::MyVector scale(30, 30, 0);




    //time in between frames
    constexpr std::chrono::nanoseconds timestep(64ms);

    //initializing clock variables
    using clock = std::chrono::high_resolution_clock;
    auto curr_time = clock::now();
    auto prev_time = curr_time;
    std::chrono::nanoseconds curr_ns(0);

    //particle
    P6::P6Particle particle = P6::P6Particle();
    particle.Position = P6::MyVector(0, -100, 0);

    float partVx;
    float partVy;
    float partVz;

    ////this is 100m/s to the right
    //particle.Velocity = P6::MyVector(0, 0, 0);

    //this is 100m/s to the left
    particle.Acceleration = P6::MyVector(0, -50, 0);

    std::cout << "Input Velocity : " << std::endl;
    std::cout << "X: ";
    std::cin >> partVx;
    std::cout << "Y: ";
    std::cin >> partVy;
    std::cout << "Z:";
    std::cin >> partVz;

    particle.Velocity = P6::MyVector(partVx, partVy, partVz);

    bool timeStop = false;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        //time loop
        curr_time = clock::now();
        //duration between last iteration
        auto dur = std::chrono::duration_cast<std::chrono::nanoseconds> (curr_time - prev_time);
        //set prev with curr for next iterration
        prev_time = curr_time;
        //add duration since last iteration to time since last frame
        curr_ns += dur;
        if (curr_ns >= timestep) {
            //convert ns to ms
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(curr_ns);
            std::cout << "MS: " << (float)ms.count() << "\n";
            //reset
            curr_ns -= curr_ns;

            //updates
            // 
            //std::cout << "P6 Update\n";

            std::cout << "Position: " << particle.Position.x << ", " << particle.Position.y << ", " << particle.Position.z << std::endl;
            std::cout << "Velocity: " << particle.Velocity.x << ", " << particle.Velocity.y << ", " << particle.Velocity.z << std::endl;

            particle.update((float)ms.count() / 1000);

            if (timeStop == true)
            {
                
            }

            if (particle.Position.y <= -100 && timeStop == false)
            {
                timeStop == true;
                std::cout << "It took " << " seconds" << " for it to land" << std::endl;
            }

        }

        //std::cout << "Normal Update\n";

        z = z_mod;

        //Start with the translation matrix
        glm::mat4 transformation_matrix = glm::translate(identity_martix, (glm::vec3)particle.Position);

        //Multiply the resulting matrix with the scale matrix
        transformation_matrix = glm::scale(transformation_matrix, (glm::vec3)scale);

        //Finally, multiply it with the rotation matrix
        transformation_matrix = glm::rotate(transformation_matrix, glm::radians(theta), glm::normalize(glm::vec3(axis_x, axis_y, axis_z)));

        //Get location of projection matrix
        unsigned int projectionLoc = glGetUniformLocation(shaderProg, "projection");
        //Assign the matrix
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

        //Get location of transformation matrix
        unsigned int transformLoc = glGetUniformLocation(shaderProg, "transform");
        //Assign the matrix
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformation_matrix));

        //Tell openGL to use this shader
        //for VAO/s below
        glUseProgram(shaderProg);
        glBindVertexArray(VAO);

        //Bind The VAO to prep it for drawing
        glBindVertexArray(VAO);
        //Draw the triangle
        //glDrawArrays(GL_TRIANGLES, 0 , 3);
        glDrawElements(GL_TRIANGLES, mesh_indices.size(), GL_UNSIGNED_INT, 0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    //Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}