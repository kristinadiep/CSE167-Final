#include <stdlib.h>
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
// Use of degrees is deprecated. Use radians for GLM functions
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include "Screenshot.h"
#include "Scene.h"


static const int width = 800;
static const int height = 600;
static const char* title = "Scene viewer";
static const glm::vec4 background(0.1f, 0.2f, 0.3f, 1.0f);
static Scene scene;

#include "hw3AutoScreenshots.h"

void printHelp(){
    std::cout << R"(
    Available commands:
      press 'H' to print this message again.
      press Esc to quit.
      press 'O' to save a screenshot.
      press the arrow keys to rotate camera.
      press 'A'/'Z' to zoom.
      press 'R' to reset camera.
      press 'L' to turn on/off the lighting.
    
      press Spacebar to generate images for hw3 submission.
    
)";
}

void initialize(void){
    printHelp();
    glClearColor(background[0], background[1], background[2], background[3]); // background color
    glViewport(0,0,width,height);
    
    // Initialize scene
    scene.init();

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    scene.draw();
    
    glutSwapBuffers();
    glFlush();
    
}

void saveScreenShot(const char* filename = "test.png"){
    int currentwidth = glutGet(GLUT_WINDOW_WIDTH);
    int currentheight = glutGet(GLUT_WINDOW_HEIGHT);
    Screenshot imag = Screenshot(currentwidth,currentheight);
    imag.save(filename);
}

/* Adding a new function for Final code.*/
void animation(void) {
    // Update the status of your animated objects
    // This should update:
    //   - rotation matrix R
    //   - moment of inertia (in world) MOIw
    //   - 
    // ...

    // just gonna stick stuff in here, likely to move
    // INITIAL:
    // R(0), w, MOIm, [change in] t
    // 
    // DEPENDENCIES:
    // at start
    // R + MOIm -> MOIw(0)
    // MOIm + w -> L(static)
    //
    // per frame
    // MOIw + L -> w(new)
    // R + w + t -> R(new)
    // MOIm + R -> MOIw(new)

    // stays static:
    // MOIm, L, KE
    // model coordinate:
    //    - stays static -- MOIm, A, KE
    // world coordinate

    // ellipsoids
    // L -> A
    
    // rotation matrix (mat3)
    glm::mat3 R;
    // translation vector (vec3)
    glm::vec3 b /* = (position vec) + (velocity vec * t) + (0.5* accel vec * t^2)*/;
    // model matrix (mat4)
    glm::mat4 T /* = mat4 containing b * mat4 containing R */;

    // angular velocity (vec3), in world coordinate
    glm::vec3 w;  // (length is rotation spseed) (direction is rotation axis)
    /* new r = (mat3) (3D rotation matrix for axis a angle theta) * R */
    // angular velocity (vec3), in model coordinate
    glm::vec3 Omega /* = R inverse * w */;


    // moment of inertia (model) -- stays static
    // smthn smthn width of geometry in i-th coord direction, is proportional to sqrt mu_i
    glm::mat3 MOIm; // ? how do we initialize
    // moment of inertia (world)
    glm::mat3 MOIw /* = R * MOIm * R inverse */;
    // kinetic energy, in terms of [either] angular velocity w or Omega -- stays static
    float KE /* 1.5f * w transpose * MOIw * w */;

    // angular momentum (world) -- stays static
    glm::vec3 L /* = MOIw * w */;
    // angular momentum (model)
    glm::vec3 A /* = R inverse * L */; // or MOIm * Omega


    std::cout << "Let's go!";

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y){
    switch(key){
        case 27: // Escape to quit
            exit(0);
            break;
        case 'h': // print help
            printHelp();
            break;
        case 'o': // save screenshot
            saveScreenShot();
            break;
        case 'r':
            scene.camera -> aspect_default = float(glutGet(GLUT_WINDOW_WIDTH))/float(glutGet(GLUT_WINDOW_HEIGHT));
            scene.camera -> reset();
            glutPostRedisplay();
            break;
        case 'a':
            scene.camera -> zoom(0.9f);
            glutPostRedisplay();
            break;
        case 'z':
            scene.camera -> zoom(1.1f);
            glutPostRedisplay();
            break;
        case 'l':
            scene.shader -> enablelighting = !(scene.shader -> enablelighting);
            glutPostRedisplay();
            break;
        case ' ':
            hw3AutoScreenshots();
            glutPostRedisplay();
            break;
        default:
            glutPostRedisplay();
            break;
    }
}
void specialKey(int key, int x, int y){
    switch (key) {
        case GLUT_KEY_UP: // up
            scene.camera -> rotateUp(-10.0f);
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN: // down
            scene.camera -> rotateUp(10.0f);
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT: // right
            scene.camera -> rotateRight(-10.0f);
            glutPostRedisplay();
            break;
        case GLUT_KEY_LEFT: // left
            scene.camera -> rotateRight(10.0f);
            glutPostRedisplay();
            break;
    }
}

int main(int argc, char** argv)
{
    // BEGIN CREATE WINDOW
    glutInit(&argc, argv);
    
    glutInitContextVersion(3,1);
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
    glutInitWindowSize(width, height);
    glutCreateWindow(title);
    glewExperimental = GL_TRUE;
    GLenum err = glewInit() ;
    if (GLEW_OK != err) {
        std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
    }
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    // END CREATE WINDOW
    
    initialize();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKey);
    /* Adding new function (pre-defined) for Final.*/
    glutIdleFunc(animation);
    
    glutMainLoop();
	return 0;   /* ANSI C requires main to return int. */
}
