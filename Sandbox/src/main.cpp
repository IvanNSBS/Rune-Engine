#include <rune.h>

using namespace Rune;

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float orthoSize = 1.0f;
CameraCoordinates coords;
Projection proj;

class CloseCommand : public InputCommand 
{
public:
    CloseCommand(int key) : InputCommand(key){ }
    void Execute() override {
        Application::Close();
    }
};

class IncreaseOrthoSize : public InputCommand
{
public:
    IncreaseOrthoSize(int key) : InputCommand(key){ }
    void Execute() override {
        orthoSize += 0.01f;
        Camera::CreateOrtho(coords, orthoSize, 0.0001f, 1000.0f, proj);      
    }
};

class MoveW : public InputCommand
{
    public:
    MoveW(int key) : InputCommand(key){ }
    void Execute() override {
        Camera::MoveCamera({0, 0.01f, 0}, coords, proj);
    }
};

class MoveS : public InputCommand
{
    public:
    MoveS(int key) : InputCommand(key){ }
    void Execute() override {
        Camera::MoveCamera({0, -0.01f, 0}, coords, proj);
    }
};

class MoveA : public InputCommand
{
    public:
    MoveA(int key) : InputCommand(key){ }
    void Execute() override {
        Camera::MoveCamera({-0.01f, 0, 0}, coords, proj);
    }
};

class MoveD : public InputCommand
{
    public:
    MoveD(int key) : InputCommand(key){ }
    void Execute() override {
        Camera::MoveCamera({0.01f, 0, 0}, coords, proj);
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
    IncreaseOrthoSize cam(Key::F1);
    MoveW w(Key::W);
    MoveA a(Key::A);
    MoveS s(Key::S);
    MoveD d(Key::D);
    Application::StartApp(SCR_WIDTH, SCR_HEIGHT, "Rune Renderer");
    InputManager::RegisterCommand(&close);
    InputManager::RegisterCommand(&cam);
    InputManager::RegisterCommand(&w);
    InputManager::RegisterCommand(&a);
    InputManager::RegisterCommand(&s);
    InputManager::RegisterCommand(&d);

    ShaderProgram* program = ShaderProgram::Create("df_shaders\\df_sh1.glsl");

    bool success = program->Compile();
    program->Use();

    Camera::CreateOrtho(coords, orthoSize, 0.0001f, 10000.0f, proj);

    Renderer2D renderer;
    Shape* rect = Rect::CreateRect(1.f, 1.f); 

    renderer.Submit(rect, program);

    // render loop
    // -----------
    while (!Application::ShouldClose())
    {
        // std::cout << "Time since last frame: " << Application::GetTime()->DeltaTimeMillis() << std::endl;
        // std::cout << "FPS: " << Application::GetTime()->CurrentFPS() << std::endl;
        // std::cout << "Time Elapsed: " << Application::GetTime()->Elapsed() << std::endl;
        std::cout << "Pos: (" << coords.position.x << ", " << coords.position.y << ", " << coords.position.z << ")\n";
        // input
        // -----
        InputManager::HandleInputs();

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        renderer.Render(coords.position, proj);

        Application::Update();
    }

    // TODO: This terminate should be abstracted by the API
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}