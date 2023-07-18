#include "engine.hxx"
#include <glad/glad.h>

#include <fstream>
#include <sstream>

namespace core {

const std::string LoadShaderSource(const std::string &path) {
  std::string shaderCode;
  std::ifstream shaderStream(path, std::ios::in);
  if (shaderStream.is_open()) {
    std::stringstream sstr;
    sstr << shaderStream.rdbuf();
    shaderCode = sstr.str();
    shaderStream.close();
  } else
    throw std::runtime_error("Can't find shader file!");

  return shaderCode;
}

unsigned int CompileShader(unsigned int type, const char *src) {
  unsigned int id = glCreateShader(type);
  glShaderSource(id, 1, &src, nullptr);
  glCompileShader(id);

  GLint success;
  glGetShaderiv(id, GL_COMPILE_STATUS, &success);

  if (!success) {
    GLchar InfoLog[1024];
    glGetShaderInfoLog(id, sizeof(InfoLog), NULL, InfoLog);
    fprintf(stderr, "Error compiling shader type [%s]: '%s'\n",
            type == GL_VERTEX_SHADER ? "vertex" : "fragment", InfoLog);
  }

  return id;
}

unsigned int CreateVertexShader(const char *src) {
  unsigned int shaderId = CompileShader(GL_VERTEX_SHADER, src);
  return shaderId;
}

unsigned int CreateFragmentShader(const char *src) {
  unsigned int shaderId = CompileShader(GL_FRAGMENT_SHADER, src);
  return shaderId;
}

unsigned int CreateShaderProgram(unsigned int vsId, unsigned int fsId) {
  unsigned int programId = glCreateProgram();
  glAttachShader(programId, vsId);
  glAttachShader(programId, fsId);
  glLinkProgram(programId);

  GLint success;
  glGetProgramiv(programId, GL_LINK_STATUS, &success);
  if (!success) {
    GLchar ErrorLog[1024];
    glGetProgramInfoLog(programId, sizeof(ErrorLog), NULL, ErrorLog);
    fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
  }

  glValidateProgram(programId);
  glDeleteShader(vsId);
  glDeleteShader(fsId);

  return programId;
}

} // namespace core