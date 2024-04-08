#include <iostream>
#include <string>
#include <glad/glad.h>
#include "shader.h"
#include <GLFW/glfw3.h>
#include <numbers>
#include <vector>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow *window);

void error_callback(int error, const char *msg);

GLuint ex5();

void drawEx5(Shader *shader);

GLuint ex6(int numberOfTriangles, bool pacman, bool star);

void drawEx6(Shader *shader, int numberOfTriangles);

GLuint ex7(float initialRadius, float radiusDecrement);

void drawEx7(Shader *shader, float initialRadius, float radiusDecrement);

GLuint ex8();

void drawEx8();

GLuint ex9();

void drawEx9(Shader *shader);

const unsigned int SCREEN_WIDTH = 600;
const unsigned int SCREEN_HEIGHT = 600;

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwSetErrorCallback(error_callback);

    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile shader program
    // É necessário utilizar "../" porque o programa será executado dentro da pasta de build do cmake
    // Shaders para exercicios 5, 6, 7 e 9
    Shader shader("../shaders/HelloTriangle.vert", "../shaders/HelloTriangle.frag");
    // Shaders para exercicio 8
//    Shader shader("../shaders/HelloTriangle.vert", "../shaders/ColoredTriangle.frag");


//     Exercicios
    // Dois triangulos com borda e vertices diferenciados
    GLuint VAO = ex5();

//    // Circulo
//    int sides = 32;
//    GLuint VAO = ex6(sides, false, false);
//    // Octagono
//    int sides = 8;
//    GLuint VAO = ex6(sides, false, false);
//    // Pentagono
//    int sides = 5;
//    GLuint VAO = ex6(sides, false, false);
//    // Pacman
//    int sides = 32;
//    GLuint VAO = ex6(sides, true, false);
//    // Estrela
//    int sides = 10;
//    GLuint VAO = ex6(sides, false, true);

//    // Espiral
//    float initialRadius = 0.5f;
//    float radiusDecrement = 0.005f;
//    GLuint VAO = ex7(initialRadius, radiusDecrement);

//    // Triangulo colorido
//    GLuint VAO = ex8();

//    GLuint VAO = ex9();


    shader.use();
    // render loop
    while(!glfwWindowShouldClose(window)) {
        // input
        processInput(window);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);

        drawEx5(&shader);
//        drawEx6(&shader, sides);
//        drawEx7(&shader, initialRadius, radiusDecrement);
//        drawEx8();
//        drawEx9(&shader);

        glBindVertexArray(0);

        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void error_callback(int error, const char *msg) {
    std::string s;
    s = " [" + std::to_string(error) + "] " + msg + '\n';
    std::cerr << s << std::endl;
}

GLuint ex5() {
    GLfloat vertices[] = {
            // Triangle 1
             0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
             0.0f,  0.0f, 0.0f,
            // Triangle 2
             0.5f, 0.5f, 0.0f,
            -0.5f, 0.5f, 0.0f,
             0.0f, 0.0f, 0.0f
    };

    GLuint VBO, VAO;
    //Geração do identificador do VBO
    glGenBuffers(1, &VBO);
    //Faz a conexão (vincula) do buffer como um buffer de array
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //Envia os dados do array de floats para o buffer da OpenGl
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Geração do identificador do VAO (Vertex Array Object)
    glGenVertexArrays(1, &VAO);
    // Vincula (bind) o VAO primeiro, e em seguida  conecta e seta o(s) buffer(s) de vértices
    // e os ponteiros para os atributos
    glBindVertexArray(VAO);
    // Para cada atributo do vertice, criamos um "AttribPointer" (ponteiro para o atributo), indicando:
    // Localização no shader * (a localização dos atributos devem ser correspondentes no layout especificado no vertex shader)
    // Numero de valores que o atributo tem (por ex, 3 coordenadas xyz)
    // Tipo do dado
    // Se está normalizado (entre zero e um)
    // Tamanho em bytes
    // Deslocamento a partir do byte zero
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)nullptr);
    glEnableVertexAttribArray(0);

    // Observe que isso é permitido, a chamada para glVertexAttribPointer registrou o VBO como o objeto de buffer de vértice
    // atualmente vinculado - para que depois possamos desvincular com segurança
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Desvincula o VAO (é uma boa prática desvincular qualquer buffer ou array para evitar bugs medonhos)
    glBindVertexArray(0);

    return VAO;
}

void drawEx5(Shader *shader) {
    glLineWidth(10);
    glPointSize(20);

    shader->setVec4("inputColor", 0.0f, 0.0f, 1.0f, 1.0f);

    // Triangulos preenchidos
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawArrays(GL_TRIANGLES, 3, 3);

    shader->setVec4("inputColor", 0.0f, 1.0f, 0.0f, 1.0f);

    // Contornos
    glDrawArrays(GL_LINE_LOOP, 0, 3);
    glDrawArrays(GL_LINE_LOOP, 3, 3);

    // Pontos
    glDrawArrays(GL_POINTS, 0, 6);
}

GLuint ex6(int numberOfTriangles, bool pacman, bool star) {

    // parâmetros do círculo
    float radius = 0.5;
    float x, y, z;
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;

    float pi = std::numbers::pi;
    float slice = 2 * pi / ((float) numberOfTriangles);

    // número de vértices é igual ao número de triângulos + 2, porque
    // é preciso 3 vértices para compor o primeiro triângulo
    // depois mais um vértice para completar cada um dos próximos
    std::vector<GLfloat> vertices((numberOfTriangles + 2) * 3);

    vertices[0] = x;
    vertices[1] = y;
    vertices[2] = z;

    float angle;
    if (pacman) {
        angle = pi / 4.0f;
        numberOfTriangles -= numberOfTriangles/4;
    } else {
        angle = pi / 2.0f;
    }

    for (int i = 1; i < numberOfTriangles + 2; ++i) {
        if (star && i % 2 == 0) {
            float noEndRadius = radius / 2.5f;
            vertices[i * 3] = noEndRadius * cos(angle) + x;
            vertices[(i * 3) + 1] = noEndRadius * sin(angle) + y;
            vertices[(i * 3) + 2] = z;
        } else {
            vertices[i * 3] = radius * cos(angle) + x;
            vertices[(i * 3) + 1] = radius * sin(angle) + y;
            vertices[(i * 3) + 2] = z;
        }

        angle += slice;
    }

    GLuint VBO, VAO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    auto size = (GLsizeiptr) (sizeof(GLfloat) * (numberOfTriangles + 2) * 3);
    glBufferData(GL_ARRAY_BUFFER, size, vertices.data(), GL_STATIC_DRAW);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)nullptr);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return VAO;
}

void drawEx6(Shader *shader, int numberOfTriangles) {
    shader->setVec4("inputColor", 1.0f, 1.0f, 0.0f, 1.0f);
    glDrawArrays(GL_TRIANGLE_FAN, 0, numberOfTriangles + 2);
}

GLuint ex7(float initialRadius, float radiusDecrement) {
    // Parametros da espiral
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    int sides = 32;

    float pi = std::numbers::pi;
    float slice = 2 * pi / ((float) sides);
    std::vector<GLfloat> vertices;
    float angle = 0;
    float radius = initialRadius;

    while (radius > 0) {
        vertices.push_back(radius * cos(angle) + x);
        vertices.push_back(radius * sin(angle) + y);
        vertices.push_back(z);

        angle -= slice;
        radius -= radiusDecrement;
    }

    vertices.insert(vertices.end(), {x, y, z});

    GLuint VBO, VAO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    auto size = (GLsizeiptr) (sizeof(GLfloat) * vertices.size());
    glBufferData(GL_ARRAY_BUFFER, size, vertices.data(), GL_STATIC_DRAW);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)nullptr);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return VAO;
}

void drawEx7(Shader *shader, float initialRadius, float radiusDecrement) {
    glLineWidth(2);
    shader->setVec4("inputColor", 1.0f, 1.0f, 0.0f, 1.0f);
    glDrawArrays(GL_LINE_STRIP, 0, (int) ceil(initialRadius / radiusDecrement) + 1);
}

GLuint ex8() {
    GLfloat vertices[] = {
            // positions        // colors
            0.6f, -0.3f, 0.0f,  0.0f, 0.0f, 1.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
            0.0f,  0.6f, 0.0f,  1.0f, 0.0f, 0.0f   // top
    };

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)nullptr);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    return VAO;
}

void drawEx8() {
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

GLuint ex9() {
    GLfloat vertices[] = {
            // Roof
            0.8f, 0.25f, 0.0f,
            0.0f, 1.0f, 0.0f,
            -0.8f, 0.25f, 0.0f,
            // House body
            -0.8f, -1.0f, 0.0f,
            0.8f, -1.0f, 0.0f,
            -0.8f, 0.25f, 0.0f,
            0.8f, 0.25f, 0.0f,
            // Door
            0.2f, -0.5f, 0.0f,
            -0.2f, -0.5f, 0.0f,
            0.2f, -1.0f, 0.0f,
            -0.2f, -1.0f, 0.0f,
            // Window body
            -0.1f, 0.0f, 0.0f,
            -0.5f, 0.0f, 0.0f,
            -0.1f, -0.4f, 0.0f,
            -0.5f, -0.4f, 0.0f,
            // Window frame border
            -0.1f, 0.0f, 0.0f,
            -0.5f, 0.0f, 0.0f,
            -0.5f, -0.4f, 0.0f,
            -0.1f, -0.4f, 0.0f,
            // Window frame cross
            -0.1f, -0.2f, 0.0f,
            -0.5f, -0.2f, 0.0f,
            -0.3f, -0.0f, 0.0f,
            -0.3f, -0.4f, 0.0f,
            // Bottom
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f
    };

    GLuint VBO, VAO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)nullptr);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return VAO;
}

void drawEx9(Shader *shader) {
    // Roof
    shader->setVec4("inputColor", 1.0f, 0.0f, 0.0f, 1.0f);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // House body
    shader->setVec4("inputColor", 1.0f, 1.0f, 1.0f, 1.0f);
    glDrawArrays(GL_TRIANGLE_STRIP, 3, 4);

    // Door
    shader->setVec4("inputColor", 0.6f, 0.3f, 0.0f, 1.0f);
    glDrawArrays(GL_TRIANGLE_STRIP, 7, 4);

    // Window Body
    shader->setVec4("inputColor", 1.0f, 1.0f, 0.0f, 1.0f);
    glDrawArrays(GL_TRIANGLE_STRIP, 11, 4);

    // Window Frame
    glLineWidth(10);
    shader->setVec4("inputColor", 0.6f, 0.3f, 0.0f, 1.0f);
    glDrawArrays(GL_LINE_LOOP, 15, 4);
    glDrawArrays(GL_LINES, 19, 4);

    // Bottom
    shader->setVec4("inputColor", 1.0f, 0.6f, 0.0f, 1.0f);
    glDrawArrays(GL_LINES, 23, 2);
}

