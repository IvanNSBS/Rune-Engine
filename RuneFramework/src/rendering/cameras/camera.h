#pragma once

#include <glm/vec3.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Rune
{
    struct CameraCoordinates
    {
        glm::vec3 position = {0,   0,   10};
        glm::vec3 forward  = {0,   0,   -1};
        glm::vec3 up       = {0,   1,   0};
    };

    struct Projection
    {
        glm::mat4 view;
        glm::mat4 projection;
    };

    class Camera
    {
    public:
        static void CreateOrtho(CameraCoordinates& coords, float orthoWidth, float near, float far, Projection& outProj)
        {
            glm::mat4 v = glm::lookAt(coords.position, coords.position + coords.forward, coords.up);
            glm::mat3 inv_v = glm::mat3(glm::inverse(v));

            float halfWidth = orthoWidth * 0.5f;
            float left, right, top, bottom;
            left = bottom = -halfWidth;
            right = top = halfWidth;

            outProj.view = v;
            // TODO: Might use this propertu later for moving a camera
            // outProj.inverseView = inv_v;
            outProj.projection = glm::ortho(left, right, bottom, top, near, far);
        }

        static void MoveCamera(glm::vec3 deltaPos, CameraCoordinates& coords, Projection& proj)
        {
            // glm::mat3 inverseView = glm::mat3(glm::inverse(proj.view));
            // glm::vec3 localDirection = inverseView * deltaPos;

            // coords.forward = localDirection;
            // coords.position += localDirection;

            coords.position += deltaPos;
            coords.forward = {0, 0, -1};
            coords.up = {0, 1, 0};

    		proj.view = glm::lookAt(coords.position, coords.position + coords.forward, coords.up);
        }

        static void RotateCamera(CameraCoordinates& coords, Projection& proj)
        {

        }
    };
}