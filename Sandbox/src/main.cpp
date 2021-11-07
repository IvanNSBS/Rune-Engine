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
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f  // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

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

    delete buf;
    delete idx;
    delete layout;

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}