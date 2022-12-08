/**************************************************
Camera is a class for a camera object.
*****************************************************/
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef __CAMERA_H__
#define __CAMERA_H__

/** Kat: Moved from Camera.cpp to here, Camera.h, so I can use it in main. 
    C'mon, it doesn't make that much of a differnce, does it? 
    yes it does. externs babey. uhh.. will deal with this later, otherwise unharmed from Camera.cpp*/
// Quaternion multiplication p * q
extern glm::vec4 qmultiply(const glm::vec4 p, const glm::vec4 q);

// Quaternion conjugation
extern glm::vec4 qconj(const glm::vec4 q);

extern glm::mat3 rotation(const float degrees, const glm::vec3 axis);


class Camera {
public:
    glm::vec3 eye;// position of the eye
    glm::vec3 target;  // look at target
    glm::vec3 up;      // up vector
    float fovy;  // field of view in degrees
    float aspect; // aspect ratio
    float zNear; // near clipping distance
    float zFar; // far clipping distance
    
    // default values for reset
    glm::vec3 eye_default = glm::vec3(5.0f, 0.0f, 0.0f);
    glm::vec3 target_default = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 up_default = glm::vec3(0.0f, 1.0f, 0.0f);
    float fovy_default = 30.0f;
    float aspect_default = 4.0f/3.0f;
    float zNear_default = 0.01f;
    float zFar_default = 100.0f;
    
    glm::mat4 view = glm::mat4(1.0f);   // view matrix
    glm::mat4 proj = glm::mat4(1.0f);   // projection matrix
    
    void rotateRight(const float degrees);
    void rotateUp(const float degrees);
    void zoom(const float factor);
    void computeMatrices(void);
    void reset(void);
};

#endif 
