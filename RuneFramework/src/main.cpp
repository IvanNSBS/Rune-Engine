#include <glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "filesystem/fileloader.h"
#include "application/application.h"
#include "rendering/shaders/shaderprogram.h"
#include "application/input/inputmanager.h"
#include "application/input/inputcommand.h"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

class CloseCommand : public InputCommand 
{
public:
    CloseCommand(int key) : InputCommand(key){ }
    void Execute() override {
        Application::Close();
    }
};

int main()
{
    std::cout << "Starting the app...\n";

    CloseCommand close(Key::ESCAPE);
    // TODO: Make a CreateApp and Init Application Function. Perhaps 
    //       calling all inits could be done for the sandbox?
    Application::StartApp(SCR_WIDTH, SCR_HEIGHT, "Rune Renderer");
    InputManager::RegisterCommand(&close);
    InputManager::SetCommandKey(&close, Key::F12);

    ShaderProgram program("df_shaders\\df_sh1.glsl");

    bool success = program.Compile();
    program.Use();

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    // render loop
    // -----------
    while (!Application::ShouldClose())
    {
        // input
        // -----
        InputManager::HandleInputs();

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        program.Use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        Application::Update();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------'------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}