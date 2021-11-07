#include <rune.h>

using namespace Rune;

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

struct PosCol
{
    float x, y, z;
    float r, g, b;
};

int main()
{
    std::cout << "Starting the app...\n";

    CloseCommand close(Key::ESCAPE);
    // TODO: Make a CreateApp and Init Application Function. Perhaps 
    //       calling all inits could be done for the sandbox?
    Application::StartApp(SCR_WIDTH, SCR_HEIGHT, "Rune Renderer");
    InputManager::RegisterCommand(&close);

    ShaderProgram program("df_shaders\\df_sh1.glsl");

    bool success = program.Compile();
    program.Use();

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    PosCol vertices[] = {
         0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // top right
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom left
        -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f  // top left 
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
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(PosCol), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(PosCol), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    // no3*sizeof(floatte that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    VertexLayout* layout = VertexLayout::Create();
    layout->PushFloat(3); // position
    layout->PushFloat(3); // color
    VertexBuffer* buf = VertexBuffer::Create();
    IndexBuffer* idx = IndexBuffer::Create();
    buf->Bind();
    buf->SetData(vertices, sizeof(vertices), layout);
    idx->SetData(indices, sizeof(indices));
    buf->SetIndices(idx);


    // render loop
    // -----------
    while (!Application::ShouldClose())
    {
        // std::cout << "Time since last frame: " << Application::GetTime()->DeltaTimeMillis() << std::endl;
        // std::cout << "FPS: " << Application::GetTime()->CurrentFPS() << std::endl;
        // std::cout << "Time Elapsed: " << Application::GetTime()->Elapsed() << std::endl;

        // input
        // -----
        InputManager::HandleInputs();

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        program.Use();
        buf->Bind();
        glDrawElements(GL_TRIANGLES, buf->GetIndices()->Length(), GL_UNSIGNED_INT, 0);

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