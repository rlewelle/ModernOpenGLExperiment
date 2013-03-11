#ifndef PROGRAM_H
#define PROGRAM_H

#include "Rendering.h"
#include "Shader.h"

/**
 * Program - Contains linked shaders representing the programmable part of the pipeline.
 * We'll typically attach this to a Model for use in rendering a Mesh.
 *
 * If this implementation looks familiar - it's modeled after Gameplay's Effect class, though
 * this class is meant to be a flattened version of the material hierarchy in that engine (to
 * keep things simple).
 */
class Program {
private:
    GLuint programHandle;
    GLint  linkResult;

    std::map<std::string, Uniform_t> uniforms;
    std::map<std::string, VertexAttribute_t> attributes;

    Program() : programHandle(glCreateProgram()), linkResult(GL_FALSE) {}

    void Link();
    void AcquireUniforms();
    void AcquireAttributes();

    // The only thing that really matters about this is that the location will be 0
    // (Which the default constructor will do for us)
    static const Uniform_t DEFAULT_UNIFORM;

public:
    static Program* CreateFromShaders(Shader<VertexShader>* vertexShader, Shader<FragmentShader>* fragmentShader);

    ~Program();

    std::string GetLinkLog() const;

    bool IsValid() const { return programHandle != 0 && linkResult == GL_TRUE; }
    void Bind() const { glUseProgram(programHandle); }

    Uniform_t const * GetUniform(const std::string& name) const;
    GLuint GetUniformID(const std::string& name) const;

    VertexAttribute_t const * GetAttribute(const std::string& attrName) const;
    GLuint GetAttributeID(const std::string& attrName) const;

    static void SetUniform(Uniform_t const * uniform, GLfloat value) {
        glUniform1f(uniform->location, value);
    }

    static void SetUniform(Uniform_t const * uniform, GLint value) {
        glUniform1i(uniform->location, value);
    }

    static void SetUniform(Uniform_t const * uniform, GLuint value) {
        glUniform1ui(uniform->location, value);
    }

    static void SetUniform(Uniform_t const * uniform, const glm::mat4& value) {
        glUniformMatrix4fv(uniform->location, 1, GL_FALSE, glm::value_ptr(value));
    }
};

#endif