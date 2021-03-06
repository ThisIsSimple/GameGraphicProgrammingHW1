#include "scene.h"

#include "obj_teapot.h"
#include "tex_flower.h"
float test_yRotDegree = 50.0f;
Shader* Scene::vertexShader = nullptr;
Shader* Scene::fragmentShader = nullptr;
Program* Scene::program = nullptr;
Camera* Scene::camera = nullptr;
Light* Scene::light = nullptr;
Object* Scene::teapot = nullptr;
Material* Scene::flower = nullptr;
int frame = 0;
void Scene::setup(AAssetManager* aAssetManager) {

    // set asset manager
    Asset::setManager(aAssetManager);

    // create shaders
    vertexShader = new Shader(GL_VERTEX_SHADER, "vertex.glsl");
    fragmentShader = new Shader(GL_FRAGMENT_SHADER, "fragment.glsl");

    // create program
    program = new Program(vertexShader, fragmentShader);

    // create camera
    camera = new Camera(program);
    camera->eye = vec3(60.0f, 00.0f, 0.0f);

    // create light
    light = new Light(program);
    light->position = vec3(100.0f, 0.0f, 0.0f);

    // create floral texture
    flower = new Material(program, texFlowerData, texFlowerSize);

    // create teapot object
    teapot = new Object(program, flower, objTeapotVertices, objTeapotIndices,
                        objTeapotVerticesSize, objTeapotIndicesSize);
    //Set world matrix
    //careful! column-major order
    teapot->worldMatrix = mat4{
            0.5*(cos(0.872665)+1.0f), 0.5*(-cos(0.872665)+1.0f), -0.5*(sqrt(2))*sin(0.872665), 0.0f,
            (-cos(0.872665)+1.0f), (cos(0.872665)+1.0f), (sqrt(2))*sin(0.872665), 0.0f,
            0.25*(sqrt(2))*sin(0.872665), -0.25*(sqrt(2))*sin(0.872665), 0.5*cos(0.872665), 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
    };
}

void Scene::screen(int width, int height) {

    // set camera aspect ratio
    camera->aspect = (float) width / height;
}

void Scene::update(float deltaTime) {
    static float angle = 2.0f;
    // use program
    program->use();

    // rotate the camera relative to the object
//    camera->eye = vec3(-30.0f, 0.0f, -30.0f) * deltaTime;
    frame++;
    frame = frame % 180;
    camera->eye = vec3(-60.0f*cos(3.1415927f/90 * frame), -0.0f, -60.0f*sin(3.1415927f/90 * frame));
//    camera->eye = vec3(-60, 0, -60);

    // setup camera and light
    camera->setup();
    light->setup();

    // draw teapot
    teapot->draw();
}

