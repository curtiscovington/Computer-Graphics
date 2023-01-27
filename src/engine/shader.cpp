#include <engine/shader.h>
#include <string>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>

// reads the contents of a file into a string
static std::string readFile(const char* path) {
    if (path == nullptr) {
        return "";
    }
    std::ifstream file(path);
    std::string contents;
    std::string line;
    while (std::getline(file, line)) {
        contents.append(line);
        contents.append("\n");
    }

    return contents;
}

static void checkProgramError(const std::string name, GLuint program) {
    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        printf("Name %s\n", name.c_str());
        printf("Error linking program: %s\n", infoLog);
        exit(1);
    }
}

static void checkShaderError(GLuint shader, std::string type) {
    // check for errors
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        printf("Error compiling %s shader: %s\n", type.c_str(), infoLog);
        exit(1);
    }
}

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath, const char* geometryShaderPath) {
    // get the contents of the files
    std::string vertSource = readFile(vertexShaderPath);
    std::string fragSource = readFile(fragmentShaderPath);
    std::string geomSource = readFile(geometryShaderPath);
    // printf("vertSource: %s\n", vertSource.c_str());
    // printf("fragSource: %s\n", fragSource.c_str());
    // create the shaders
    auto vertShader = glCreateShader(GL_VERTEX_SHADER);
    auto fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    auto geomShader = glCreateShader(GL_GEOMETRY_SHADER);
    // compile the shaders
    const char* vertSourceCStr = vertSource.c_str();
    const char* fragSourceCStr = fragSource.c_str();
    const char* geomSourceCStr = geomSource.c_str();
    glShaderSource(vertShader, 1, &vertSourceCStr, NULL);
    glCompileShader(vertShader);
    glShaderSource(fragShader, 1, &fragSourceCStr, NULL);
    glCompileShader(fragShader);


    if (geometryShaderPath != nullptr) {
        glShaderSource(geomShader, 1, &geomSourceCStr, NULL);
        glCompileShader(geomShader);
    }
   
    // create the program
    m_program = glCreateProgram();
    glAttachShader(m_program, vertShader);
    if (geometryShaderPath != nullptr) {
        glAttachShader(m_program, geomShader);
    }
    glAttachShader(m_program, fragShader);
    glLinkProgram(m_program);

    checkProgramError(vertexShaderPath, m_program);
    checkShaderError(vertShader, "vertex");
    checkShaderError(fragShader, "fragment");
    if (geometryShaderPath != nullptr) {
        checkShaderError(geomShader, "geometry");
    }
    
    // delete the shaders as the program now owns them
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
    glDeleteShader(geomShader);
}

Shader::Shader(const char* vertexShaderPath, const char* tessellationControlShaderPath, const char* tessellationEvaluationShaderPath, const char* geometryShaderPath, const char* fragmentShaderPath)
{
    // get the contents of the files
    std::string vertSource = readFile(vertexShaderPath);
    std::string tessCSource = readFile(tessellationControlShaderPath);
    std::string tessESource = readFile(tessellationEvaluationShaderPath);
    std::string geomSource = readFile(geometryShaderPath);
    std::string fragSource = readFile(fragmentShaderPath);

    // printf("vertSource: %s\n", vertSource.c_str());
    // printf("fragSource: %s\n", fragSource.c_str());
    // create the shaders
    auto vertShader = glCreateShader(GL_VERTEX_SHADER);
    // auto tessCShader = glCreateShader(GL_TESS_CONTROL_SHADER);
    auto tessEShader = glCreateShader(GL_TESS_EVALUATION_SHADER);
    auto geomShader = glCreateShader(GL_GEOMETRY_SHADER);
    auto fragShader = glCreateShader(GL_FRAGMENT_SHADER);

    // compile the shaders
    const char* vertSourceCStr = vertSource.c_str();
    // const char* tessCSourceCStr = tessCSource.c_str();
    const char* tessESourceCStr = tessESource.c_str();
    const char* geomSourceCStr = geomSource.c_str();
    const char* fragSourceCStr = fragSource.c_str();
    glShaderSource(vertShader, 1, &vertSourceCStr, NULL);
    glCompileShader(vertShader);
    // glShaderSource(tessCShader, 1, &tessCSourceCStr, NULL);
    // glCompileShader(tessCCShader);
    glShaderSource(tessEShader, 1, &tessESourceCStr, NULL);
    glCompileShader(tessEShader);
    glShaderSource(geomShader, 1, &geomSourceCStr, NULL);
    glCompileShader(geomShader);
    glShaderSource(fragShader, 1, &fragSourceCStr, NULL);
    glCompileShader(fragShader);
    
    // create the program
    m_program = glCreateProgram();
    glAttachShader(m_program, vertShader);
    // glAttachShader(m_program, tessCShader);
    glAttachShader(m_program, tessEShader);
    glAttachShader(m_program, geomShader);
    glAttachShader(m_program, fragShader);
    glLinkProgram(m_program);

    checkProgramError(vertexShaderPath, m_program);
    checkShaderError(vertShader, "vertex");
    // checkShaderError(tessCShader, "tessellation control");
    checkShaderError(tessEShader, "tessellation evaluation");
    checkShaderError(geomShader, "geometry");
    checkShaderError(fragShader, "fragment");
    
    // delete the shaders as the program now owns them
    glDeleteShader(vertShader);
    // glDeleteShader(tessShader);
    glDeleteShader(geomShader);
    glDeleteShader(fragShader);
}



Shader::~Shader() {
    glDeleteProgram(m_program);
}

void Shader::Bind() {
    glUseProgram(m_program);
}

void Shader::Unbind() {
    glUseProgram(0);
}

void Shader::SetUniform(const char* name, float value) {
    glUniform1f(glGetUniformLocation(m_program, name), value);
}

void Shader::SetUniform(const char* name, int value) {
    glUniform1i(glGetUniformLocation(m_program, name), value);
}

void Shader::SetUniform(const char* name, const glm::vec2& value) {
    glUniform2f(glGetUniformLocation(m_program, name), value.x, value.y);
}

void Shader::SetUniform(const char* name, const glm::vec3& value) {
    glUniform3f(glGetUniformLocation(m_program, name), value.x, value.y, value.z);
}

void Shader::SetUniform(const char* name, const glm::mat4& value) {
    glUniformMatrix4fv(glGetUniformLocation(m_program, name), 1, GL_FALSE, glm::value_ptr(value));
}
