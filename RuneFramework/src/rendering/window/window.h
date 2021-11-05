#pragma once

struct WindowProps
{
public:
    unsigned int width = 1280;
    unsigned int height = 720;
    bool vsync = true;
    char* title = "Rune Engine";
    
    WindowProps() { }
    WindowProps(unsigned int w, unsigned int h, char* t, bool v = true)
    {
        width = w;
        height =h;
        title = t;
        vsync = v;
    }
};

class Window 
{
protected:
    WindowProps _props;
    
public:
    virtual ~Window() { };
    virtual void OnUpdate() = 0;
    virtual void Close() = 0;
    virtual bool ShouldClose() = 0;
    virtual const bool GetVsync() const = 0;
    virtual void SetVsync(bool activate) = 0;
    virtual inline const unsigned int GetWidth() const { return _props.width; }
    virtual inline const unsigned int GetHeight() const { return _props.height; }

    static Window* Create(WindowProps props);

    // TODO: 
    // This will likely become part of the event system 
    // and will need a refactor later for other types of windows 
    // besides GLFW
    // virtual void SetResizeCallback(void(*callback_ptr)(int, int));
};