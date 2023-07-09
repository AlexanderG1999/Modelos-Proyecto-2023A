#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>

#include <iostream>

#include "Header.h"
#include "Definitions.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void CargarCubo();
int getMajorAxis(double originAxis, double shockAxis);

// settings
const unsigned int SCR_WIDTH = 900;
const unsigned int SCR_HEIGHT = 700;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 8.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// lighting
glm::vec3 lightPos(-0.5f, -0.1f, -0.5f);

// Global variables
bool cuartoCargado;
room r;
source s;
point origin = point(-0.5f, -0.1f, -0.5f);

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader cubeShader("shaders/vertexShader.vs", "shaders/fragmentShader.fs");
    Shader rayShader("shaders/vertexShader.vs", "shaders/fragmentShader.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
    };

    // load room - ray-tracing
    CargarCubo();
    s.createRays(20);
    reflection* arrayreflecciones;
    
    arrayreflecciones = r.RayTracing(origin, s.Rays, 20);

    for (int i = 0; i < 50; i++) {
        printf("PuntoGolpe %d: x: %f, y: %f, z: %f\n", (i+1), arrayreflecciones[1].r[i].x, arrayreflecciones[1].r[i].y, arrayreflecciones[1].r[i].z);
    }

    printf("\nVelocidad [1]: %d\n", SPEED);

    point originPoint = point(arrayreflecciones[1].r[0].x, arrayreflecciones[1].r[0].y, arrayreflecciones[1].r[0].z);
    point shockPoint = point(arrayreflecciones[1].r[1].x, arrayreflecciones[1].r[1].y, arrayreflecciones[1].r[1].z);
    int auxCounter = 1;
    double auxTime = 0.0f;

    // ver coordenada mayor tanto para (x,y,z)
    double axisX = 0.0f;
    double axisY = 0.0f;
    double axisZ = 0.0f;
    axisX = getMajorAxis(originPoint.x, shockPoint.x);
    axisY = getMajorAxis(originPoint.y, shockPoint.y);
    axisZ = getMajorAxis(originPoint.z, shockPoint.z);

    float speed = SPEED;
    float greenColor = 0.05f;

    // first, configure the cube's VAO (and VBO)
    unsigned int VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int rayCubeVAO;
    glGenVertexArrays(1, &rayCubeVAO);
    glBindVertexArray(rayCubeVAO);

    // we only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need (it's already bound, but we do it again for educational purposes)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // be sure to activate shader when setting uniforms/drawing objects
        cubeShader.use();
        cubeShader.setVec3("objectColor", 1.0f, 0.0f, 0.0f);
        cubeShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        cubeShader.setMat4("projection", projection);
        cubeShader.setMat4("view", view);

        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        cubeShader.setMat4("model", model);

        // render the cube
        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);


        // also draw the lamp object
        rayShader.use();
        rayShader.setVec3("objectColor", 1.0f, greenColor, 0.0f);
        rayShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        rayShader.setMat4("projection", projection);
        rayShader.setMat4("view", view);
        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.05f)); // a smaller cube
        
        model = glm::translate(model, glm::vec3(originPoint.x, originPoint.y, originPoint.z));

        if ((originPoint.distancia(shockPoint) * (glfwGetTime() - auxTime) * SPEED) >= originPoint.distancia(shockPoint)) {
            auxTime = glfwGetTime();
            originPoint = shockPoint;

            if (auxCounter==50) {
                printf("\nTotal de impactos: %d\n", auxCounter);
                break;
            }
            else {
                auxCounter++;
                shockPoint.x = arrayreflecciones[1].r[auxCounter].x;
                shockPoint.y = arrayreflecciones[1].r[auxCounter].y;
                shockPoint.z = arrayreflecciones[1].r[auxCounter].z;
                speed = speed*0.8f;
                greenColor += 0.03f;
                //speed = SPEED; // descomentar si se desea que vaya mas fluido, para que no se pierda energia
                printf("Velocidad [%d]: %f\n", auxCounter, speed);
            }

        };

        //model = glm::scale(model, glm::vec3(0.8, 0.8, 0.8));
        model = glm::translate(model, glm::vec3(originPoint.x + ((shockPoint.x - originPoint.x)) * (glfwGetTime() - auxTime) * speed, originPoint.y + ((shockPoint.y - originPoint.y)) * (glfwGetTime() - auxTime) * speed, originPoint.z + ((shockPoint.z - originPoint.z) * (glfwGetTime() - auxTime)) * speed));

        rayShader.setMat4("model", model);

        glBindVertexArray(rayCubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &rayCubeVAO);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

void CargarCubo()
{
    int nt; //Contador de triángulos para el ID único

    int nd = 2; //Numero de divisiones de las caras cuadradas

    cuartoCargado = true;
    //Inicializaciones cubo
    r.Clear();
    r.NewPlanes(6);
    //-------------square 1 back
    r.p[0].NewPoints(4);
    r.p[0].p[0].x = -5.0f;
    r.p[0].p[0].y = 5.0f;
    r.p[0].p[0].z = 5.0f;
    r.p[0].p[1].x = -5.0f;
    r.p[0].p[1].y = -5.0f;
    r.p[0].p[1].z = 5.0f;
    r.p[0].p[2].x = -5.0f;
    r.p[0].p[2].y = -5.0f;
    r.p[0].p[2].z = -5.0f;
    r.p[0].p[3].x = -5.0f;
    r.p[0].p[3].y = 5.0f;
    r.p[0].p[3].z = -5.0f;
    r.p[0].PointGenTriangle();//MoreTriangle(nd);//

    //-------------square 2 front
    r.p[1].NewPoints(4);
    r.p[1].p[0].x = 5.0f;
    r.p[1].p[0].y = 5.0f;
    r.p[1].p[0].z = 5.0f;
    r.p[1].p[1].x = 5.0f;
    r.p[1].p[1].y = 5.0f;
    r.p[1].p[1].z = -5.0f;
    r.p[1].p[2].x = 5.0f;
    r.p[1].p[2].y = -5.0f;
    r.p[1].p[2].z = -5.0f;
    r.p[1].p[3].x = 5.0f;
    r.p[1].p[3].y = -5.0f;
    r.p[1].p[3].z = 5.0f;
    r.p[1].PointGenTriangle();//MoreTriangle(nd);//

    //-------------square 3 left
    r.p[2].NewPoints(4);
    r.p[2].p[0].x = -5.0f;
    r.p[2].p[0].y = -5.0f;
    r.p[2].p[0].z = 5.0f;
    r.p[2].p[1].x = 5.0f;
    r.p[2].p[1].y = -5.0f;
    r.p[2].p[1].z = 5.0f;
    r.p[2].p[2].x = 5.0f;
    r.p[2].p[2].y = -5.0f;
    r.p[2].p[2].z = -5.0f;
    r.p[2].p[3].x = -5.0f;
    r.p[2].p[3].y = -5.0f;
    r.p[2].p[3].z = -5.0f;
    r.p[2].PointGenTriangle();//MoreTriangle(nd);//

    //-------------square 4 right
    r.p[3].NewPoints(4);
    r.p[3].p[0].x = 5.0f;
    r.p[3].p[0].y = 5.0f;
    r.p[3].p[0].z = 5.0f;
    r.p[3].p[1].x = -5.0f;
    r.p[3].p[1].y = 5.0f;
    r.p[3].p[1].z = 5.0f;
    r.p[3].p[2].x = -5.0f;
    r.p[3].p[2].y = 5.0f;
    r.p[3].p[2].z = -5.0f;
    r.p[3].p[3].x = 5.0f;
    r.p[3].p[3].y = 5.0f;
    r.p[3].p[3].z = -5.0f;
    r.p[3].PointGenTriangle();//MoreTriangle(nd);//

    //-------------square 5 top
    r.p[4].NewPoints(4);
    r.p[4].p[0].x = -5.0f;
    r.p[4].p[0].y = -5.0f;
    r.p[4].p[0].z = 5.0f;
    r.p[4].p[1].x = -5.0f;
    r.p[4].p[1].y = 5.0f;
    r.p[4].p[1].z = 5.0f;
    r.p[4].p[2].x = 5.0f;
    r.p[4].p[2].y = 5.0f;
    r.p[4].p[2].z = 5.0f;
    r.p[4].p[3].x = 5.0f;
    r.p[4].p[3].y = -5.0f;
    r.p[4].p[3].z = 5.0f;
    r.p[4].PointGenTriangle();//MoreTriangle(nd);//

    //-------------square 1 bottom
    r.p[5].NewPoints(4);
    r.p[5].p[0].x = -5.0f;
    r.p[5].p[0].y = 5.0f;
    r.p[5].p[0].z = -5.0f;
    r.p[5].p[1].x = -5.0f;
    r.p[5].p[1].y = -5.0f;
    r.p[5].p[1].z = -5.0f;
    r.p[5].p[2].x = 5.0f;
    r.p[5].p[2].y = -5.0f;
    r.p[5].p[2].z = -5.0f;
    r.p[5].p[3].x = 5.0f;
    r.p[5].p[3].y = 5.0f;
    r.p[5].p[3].z = -5.0f;
    r.p[5].PointGenTriangle();//MoreTriangle(nd);//

    //Calcular los normales del plano
    int cont_t = 0;
    for (int i = 0; i < r.NP; i++) {
        r.p[i].n = NormalPlano(r.p[i]);
        for (int j = 0; j < r.p[i].NT; j++) {
            r.p[i].t[j].CalculateProjection();
            r.p[i].t[j].Centroid();
            r.p[i].t[j].ID = cont_t;
            cont_t++;
        }
    }
};

int getMajorAxis(double originAxis, double shockAxis) {
    int result = 0;
    if (originAxis < shockAxis) {
        result = 1;
    }
    else {
        result = -1;
    }
    return result;
};