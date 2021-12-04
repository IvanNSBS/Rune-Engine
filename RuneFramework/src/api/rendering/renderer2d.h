#pragma once

#include "./shapes/shape.h"
#include "./cameras/camera.h"
#include "./shaders/shaderprogram.h"
#include <vector>
#include <glad.h>

namespace Rune 
{
    class Renderer2D
    {
    private:
        std::vector<Shape*> _shapes;
        std::vector<ShaderProgram*> _shaders;
    public:
        void Batch();
        void Submit(Shape* shape, ShaderProgram* shader) 
        { 
            _shapes.push_back(shape); 
            _shaders.push_back(shader);
        }

        void Render(const glm::vec3& camPos, const Projection& camProj) const
        {
            for(int i = 0; i < _shapes.size(); i++)
            {
                auto shape = _shapes[i];
                auto shader = _shaders[i];

                shape->vertices->Bind();
                shader->Use();
                // shader->SetMat4("u_Model", mesh.GetModelMatrix());
                shader->SetMat4("u_mvp.view", camProj.view);
                shader->SetMat4("u_mvp.projection", camProj.projection);
                // shader->SetVec3("u_mvp.viewPos", camPos);

                // TODO: Draw Call should be abstracted
                glDrawElements(GL_TRIANGLES, shape->indices->Length(), GL_UNSIGNED_INT, 0);
            }
        }
    };
}