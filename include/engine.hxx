#include <string>

namespace core {

const std::string LoadShaderSource(const std::string &path);
unsigned int CompileShader(unsigned int type, const char *src);
unsigned int CreateVertexShader(const char *src);
unsigned int CreateFragmentShader(const char *src);
unsigned int CreateShaderProgram(unsigned int vsId, unsigned int fsId);
} // namespace core